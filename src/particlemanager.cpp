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
#include "hydrodynamics.h"
#include "material.h"
#include "boundary.h"
#include "particlemanager.h"
#include "macro.h"
#include "err.h"

#define MAX_SIZE 4096

using namespace std;
enum {X, Y};

#define NEW(pos, vel, den, pre, tem, mtl) particle_real(pos, vel, den, pre, tem, mtl)
#define LIST ListNode
#define ILIST IListNode
ParticleManager::ParticleManager(Initiation *ini)
{

    int i, j;
    strcpy(Project_name, ini->Project_name);
    number_of_materials = ini->number_of_materials;
    smoothinglength = ini->smoothinglength;
    smoothinglengthsquare = smoothinglength*smoothinglength;
    box_size[X] = ini->box_size[X];
    box_size[Y] = ini->box_size[Y];
    cll_sz = ini->cell_size;
    x_clls = ini->x_cells + 2; y_clls = ini->y_cells + 2;
    initial_condition = ini->initial_condition;
    hdelta = ini->hdelta; delta = ini->delta;

    if(initial_condition == 0) {
	U0[X] = ini->U0[X];
	U0[Y] = ini->U0[Y];
	rho0 = ini->rho0;
	p0 = ini->p0;
	T0 = ini->T0;
    }
    cell_lists = (List***)malloc(x_clls*sizeof(List**));
    for(i = 0; i < x_clls; i++) {
	cell_lists[i] = (List**)malloc(y_clls*sizeof(List*));
	for (j = 0; j < y_clls; j++)
	    cell_lists[i][j] = list_ini();
    }
    NNP_list = list_ini();
}
void ParticleManager::UpdateCellLinkedLists()
{

    int i, j;
    int k, m;
    LIST *p;
    Particle *prtl;
    for(i = 0; i < x_clls; i++) {
	for(j = 0; j < y_clls; j++) {
	    p = list_first(cell_lists[i][j]);
	    while(!list_isEnd(cell_lists[i][j], p)) {
		prtl = list_retrieve(cell_lists[i][j], p);
		if(prtl->bd == 0) {
		    k = int ((prtl->R[0] + cll_sz)/ cll_sz);
		    m = int ((prtl->R[1] + cll_sz)/ cll_sz);
		    if(k != i || m !=j) {
			list_remove(cell_lists[i][j], p);
			INSERT(prtl, *cell_lists[k][m]);
		    } else p = list_next(cell_lists[i][j], p);
		} else p = list_next(cell_lists[i][j], p);
	    }

	}
    }
}

void ParticleManager::BuildNNP(double point[2])
{
    int i, j;
    int k, m;
    double dstc;
    LIST *p;
    Particle *prtl;

    list_clear(NNP_list);
    k = int ((point[0] + cll_sz)/ cll_sz);
    m = int ((point[1] + cll_sz)/ cll_sz);
    for(i = k - 1; i <= k + 1; i++) {
	for(j = m - 1; j <= m + 1; j++) {
	    if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
		LOOP(prtl, *cell_lists[i][j]) {
		    dstc = vv_distance(point, prtl->R);
		    if(dstc < smoothinglength) {
			INSERT(prtl, *NNP_list);
		    }
		}
	    }
	}
    }
}

void ParticleManager::BuildNNP_MLSMapping(double point[2])
{
    int i, j;
    int k, m;
    double dstc;
    LIST *p;
    Particle *prtl;

    k = int ((point[0] + cll_sz)/ cll_sz);
    m = int ((point[1] + cll_sz)/ cll_sz);
    for(i = k - 1; i <= k + 1; i++) {
	for(j = m - 1; j <= m + 1; j++) {
	    if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
		LOOP(prtl, *cell_lists[i][j]) {
		    dstc = vv_distance(point, prtl->R);
		    if(dstc < smoothinglength && prtl->bd == 0) {
			INSERT(prtl, *NNP_list);
		    }
		}
	    }
	}
    }
}

void ParticleManager::BuildInteraction(IList *interactions, List *particle_list,
				       Force **forces, QuinticSpline *weight_function)
{
    ILIST *first_unused, *current;
    bool used_up_old;
    int old_length;
    LIST *p, *p1;
    int i, j, k, m;
    double dstc;
    int current_used = 0;
    Particle *prtl_org, *prtl_dest;
    Interaction *pair;

    current = interactions->first();
    used_up_old = interactions->isEnd(current);
    current_used = 0;
    old_length = interactions->length();
    LOOP(prtl_org, *particle_list) {
	if(prtl_org->bd == 0) {
	    i = int ((prtl_org->R[0] + cll_sz)/ cll_sz);
	    j = int ((prtl_org->R[1] + cll_sz)/ cll_sz);
	    for(k = i - 1; k <= i + 1; k++)
		for(m = j - 1; m <= j + 1; m++) {
		    LOOP1(prtl_dest, *cell_lists[k][m]) {
			dstc = vv_sq_distance(prtl_org->R, prtl_dest->R);
			if(dstc <= smoothinglengthsquare && prtl_org->ID >= prtl_dest->ID) {
			    if(current_used == old_length) {
				pair = new Interaction(prtl_org, prtl_dest, forces, weight_function, sqrt(dstc));
				IINSERT(pair, *interactions);
			    }
			    else {
				interactions->retrieve(current)->NewInteraction(prtl_org, prtl_dest, forces, weight_function, sqrt(dstc));
				current = interactions->next(current);
				current_used++;
			    }
			}
		    }
		}
	}
    }
    if (current_used == old_length)
	used_up_old = true;
    else
	first_unused = current;
    if (!used_up_old) {
	while (!interactions->isEnd(first_unused)) { delete interactions->retrieve(first_unused); interactions->remove(first_unused); }
    }
}

void ParticleManager::BuildRealParticles(Hydrodynamics *hydro, Initiation *ini)
{

    int i, j, k, m;
    double position[2];
    double velocity[2];
    double density, pressure, Temperature;
    int material_no;
    Particle *prtl;
    int n, N, cnt;
    char inputfile[FILENAME_MAX], line[MAX_SIZE];
    char material_name[MAX_SIZE];
    FILE *f;

    if(initial_condition==0) {
	for(i = 1; i < x_clls - 1; i++) {
	    for(j = 1; j < y_clls - 1; j++) {
		for(k = 0; k < hdelta; k++) {
		    for(m = 0; m < hdelta; m++) {
			position[0] = (i - 1)*cll_sz + (k + 0.5)*delta;
			position[1] = (j - 1)*cll_sz + (m + 0.5)*delta;
			material_no = 1;
			velocity[X] = U0[X];
			velocity[Y] = U0[Y];
			Temperature = T0;
			density = hydro->materials[material_no].rho0;
			pressure = get_p(&hydro->materials[material_no], density);
			prtl = NEW(position, velocity, density, pressure, Temperature, &hydro->materials[material_no]);
			prtl->cell_i = i; prtl->cell_j = j;
			INSERT(prtl, *hydro->particle_list);
			INSERT(prtl, *cell_lists[i][j]);

		    }
		}
	    }
	}
    }

    if(initial_condition==1) {
	strcpy(inputfile, Project_name);
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
	    for(k = 0;  k < number_of_materials; k++)
		if(strcmp(material_name, hydro->materials[k].material_name) == 0) material_no = k;
	    if(material_no != -1) {
		pressure = get_p(&hydro->materials[material_no], density);
		prtl = NEW(position, velocity, density, pressure, Temperature, &hydro->materials[material_no]);
		INSERT(prtl, *hydro->particle_list);
		i = int (prtl->R[0] / cll_sz) + 1;
		j = int (prtl->R[1] / cll_sz) + 1;
		prtl->cell_i = i; prtl->cell_j = j;
		INSERT(prtl, *cell_lists[i][j]);
	    } else {
		ABORT(("The material in the restart file is not used by the program!"));
	    }
	}
	fclose(f);
    }
}

ParticleManager::~ParticleManager() {
    list_fin(NNP_list);
}
