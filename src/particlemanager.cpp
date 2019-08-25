#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tgmath.h>
#include "glbfunc.h"
#include "vv.h"
#include "initiation.h"
#include "particle.h"
#include "dllist.h"
#include "list.h"
#include "ilist.h"
#include "interaction.h"
#include "material.h"
#include "boundary.h"
#include "particlemanager.h"
#include "macro.h"
#include "err.h"

#define MAX_SIZE 4096
enum {X, Y};

#define NEW(pos, vel, den, pre, tem, mtl) particle_real(pos, vel, den, pre, tem, mtl)
#define LIST ListNode
#define ILIST IListNode

struct ParticleManager*
manager_ini(struct Initiation *ini)
{
    struct ParticleManager *q;
    int i, j;

    q = (struct ParticleManager*)malloc(sizeof(ParticleManager));
    if (q == NULL)
	return NULL;
    
    q->smoothinglength = ini->smoothinglength;
    q->cell_size = ini->cell_size;
    q->x_clls = ini->x_cells + 2;
    q->y_clls = ini->y_cells + 2;
    q->cell_ratio = ini->cell_ratio;

    q->cell_lists = (List***)malloc(q->x_clls*sizeof(List**));
    for(i = 0; i < q->x_clls; i++) {
	q->cell_lists[i] = (List**)malloc(q->y_clls*sizeof(List*));
	for (j = 0; j < q->y_clls; j++)
	    q->cell_lists[i][j] = list_ini();
    }
    q->NNP_list = list_ini();
    return q;
}

int manager_update_list(struct ParticleManager *q)
{

    int i, j;
    int k, m;
    LIST *p;
    Particle *prtl;
    
    int x_clls;
    int y_clls;
    double cell_size;
    List ***cell_lists;
    x_clls = q->x_clls;
    y_clls = q->y_clls;
    cell_size = q->cell_size;
    cell_lists = q->cell_lists;
    
    for(i = 0; i < x_clls; i++) {
	for(j = 0; j < y_clls; j++) {
	    p = list_first(cell_lists[i][j]);
	    while(!list_endp(cell_lists[i][j], p)) {
		prtl = list_retrieve(cell_lists[i][j], p);
		if(prtl->bd == 0) {
		    k = int ((prtl->R[0] + cell_size)/ cell_size);
		    m = int ((prtl->R[1] + cell_size)/ cell_size);
		    if(k != i || m !=j) {
			list_remove(cell_lists[i][j], p);
			INSERT(prtl, *cell_lists[k][m]);
		    } else p = list_next(cell_lists[i][j], p);
		} else p = list_next(cell_lists[i][j], p);
	    }

	}
    }
    return 0;
}

int manager_build_nnp(ParticleManager *q, double point[2])
{
    int i, j;
    int k, m;
    double dstc;
    LIST *p;
    Particle *prtl;

    List *NNP_list;
    int x_clls;
    int y_clls;
    double cell_size;
    double smoothinglength;
    List ***cell_lists;
    x_clls = q->x_clls;
    y_clls = q->y_clls;
    cell_size = q->cell_size;
    cell_lists = q->cell_lists;
    smoothinglength = q->smoothinglength;
    NNP_list = q->NNP_list;

    list_clear(NNP_list);
    k = int ((point[0] + cell_size)/ cell_size);
    m = int ((point[1] + cell_size)/ cell_size);
    for(i = k - 1; i <= k + 1; i++)
	for(j = m - 1; j <= m + 1; j++)
	    if(i < x_clls && j < y_clls && i >= 0 && j >= 0)
		LOOP_P(prtl, cell_lists[i][j]) {
		    dstc = vv_distance(point, prtl->R);
		    if(dstc < smoothinglength)
			INSERT(prtl, *NNP_list);
		}
    return 0;
}

int manager_build_interaction(struct ParticleManager *q, struct IList *interactions, List *particle_list,
				       Force **forces, QuinticSpline *weight_function)
{
    LIST *p, *p1;
    int i, j, k, m;
    double dstc;
    double sm2;
    Particle *prtl_org, *prtl_dest;
    Interaction *pair;

    double smoothinglength;
    double cell_size;
    List ***cell_lists;
    cell_size = q->cell_size;
    cell_lists = q->cell_lists;
    smoothinglength = q->smoothinglength;
    
    sm2 = smoothinglength * smoothinglength;
    ilist_clear_data(interactions);
    LOOP_P(prtl_org, particle_list) {
	if(prtl_org->bd == 0) {
	    i = int ((prtl_org->R[0] + cell_size)/ cell_size);
	    j = int ((prtl_org->R[1] + cell_size)/ cell_size);
	    for(k = i - 1; k <= i + 1; k++)
		for(m = j - 1; m <= j + 1; m++) {
		    LOOP1(prtl_dest, *cell_lists[k][m]) {
			dstc = vv_sq_distance(prtl_org->R, prtl_dest->R);
			if(dstc <= sm2 && prtl_org->ID >= prtl_dest->ID) {
			    pair = new Interaction(prtl_org, prtl_dest, forces, weight_function, sqrt(dstc));
			    IINSERT_P(pair, interactions);
			}
		    }
		}
	}
    }
    return 0;
}

void manager_build_particles(struct ParticleManager *q, Material *materials, List *particle_list, Initiation *ini)
{

    int i, j, k, m;
    double position[2];
    double velocity[2];
    double delta;
    double density, pressure, Temperature;
    int material_no;
    Particle *prtl;
    int n, N, cnt;
    char inputfile[FILENAME_MAX], line[MAX_SIZE];
    char material_name[MAX_SIZE];
    FILE *f;

    int x_clls;
    int y_clls;
    int cell_ratio;
    double cell_size;
    List ***cell_lists;
    x_clls = q->x_clls;
    y_clls = q->y_clls;
    cell_size = q->cell_size;
    cell_lists = q->cell_lists;
    cell_ratio = q->cell_ratio;
    
    delta = cell_size/cell_ratio;
    if(ini->initial_condition==0) {
	for(i = 1; i < x_clls - 1; i++) {
	    for(j = 1; j < y_clls - 1; j++) {
		for(k = 0; k < cell_ratio; k++) {
		    for(m = 0; m < cell_ratio; m++) {
			position[0] = (i - 1)*cell_size + (k + 0.5)*delta;
			position[1] = (j - 1)*cell_size + (m + 0.5)*delta;
			material_no = 1;
			velocity[X] = ini->U0[X];
			velocity[Y] = ini->U0[Y];
			Temperature = ini->T0;
			density = materials[material_no].rho0;
			pressure = get_p(&materials[material_no], density);
			prtl = NEW(position, velocity, density, pressure, Temperature, &materials[material_no]);
			prtl->cell_i = i; prtl->cell_j = j;
			INSERT(prtl, *particle_list);
			INSERT(prtl, *cell_lists[i][j]);

		    }
		}
	    }
	}
    }

    if(ini->initial_condition==1) {
	strcpy(inputfile, ini->Project_name);
	strcat(inputfile, ".rst");
	f = fopen(inputfile, "r");
	if (!f)
	    ABORT(("can't open file '%s'", inputfile));
	else WARN(("Read real particles from '%s'", inputfile));
	if (fgets(line, MAX_SIZE, f) == NULL)
		ABORT(("can't read a line from '%s'", inputfile));
	sscanf(line, "%lf", &ini->Start_time);
	ini->End_time += ini->Start_time;
	if (fgets(line, MAX_SIZE, f) == NULL)
		ABORT(("can't read a line from '%s'", inputfile));
	cnt = sscanf(line, "%d", &N);
	if (cnt != 1)
	    ABORT(("can't read number of particles from '%s'", N));
	else
	    WARN(("N = %d", N));
	for(n = 0; n < N; n++) {
	    if (fgets(line, MAX_SIZE, f) == NULL)
		ABORT(("can't read a line from '%s'", inputfile));
	    cnt = sscanf(line, "%s %lf %lf %lf %lf %lf, %lf %lf", 
			 material_name, &position[0], &position[1], &velocity[0], &velocity[1], &density, &pressure, &Temperature);
	    if (cnt != 8) {
		/* todo
		WARN(("line: '%s'", line));
		WARN(("material_name: %s", material_name));
		WARN(("can't read a particle from '%s' (cnt = %d, n = %d)", inputfile, cnt, n)); */
	    }
	    material_no = -1;
	    for(k = 0;  k < ini->number_of_materials; k++)
		if(strcmp(material_name, materials[k].material_name) == 0) material_no = k;
	    if(material_no != -1) {
		pressure = get_p(&materials[material_no], density);
		prtl = NEW(position, velocity, density, pressure, Temperature, &materials[material_no]);
		INSERT(prtl, *particle_list);
		i = int (prtl->R[0] / cell_size) + 1;
		j = int (prtl->R[1] / cell_size) + 1;
		prtl->cell_i = i; prtl->cell_j = j;
		INSERT(prtl, *cell_lists[i][j]);
	    } else {
		ABORT(("The material in the restart file is not used by the program!"));
	    }
	}
	fclose(f);
    }
}

int manager_fin(struct ParticleManager *q)
{
    list_fin(q->NNP_list);
    free(q);
    return 0;
}
