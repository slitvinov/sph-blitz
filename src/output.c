#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "glbfunc.h"
#include "list.h"
#include "mls.h"
#include "ini.h"
#include "material.h"
#include "boundary.h"
#include "manager.h"
#include "macro.h"
#include "err.h"
#include "output.h"

struct Output *
output_ini(struct Ini *ini)
{
    struct Output *q;

    q = malloc(sizeof(struct Output));
    if (q == NULL)
	return NULL;
    strcpy(q->Project_name, ini->Project_name);
    q->x_cells = ini->x_cells;
    q->y_cells = ini->y_cells;
    q->cell_ratio = ini->cell_ratio;
    q->delta = ini->delta;
    q->number_of_materials = ini->number_of_materials;
    return q;
}

int
output_particles(struct Output *q, struct List *particle_list,
		 struct Material *materials, struct Boundary *boundary,
		 double Time)
{
    char file_name[FILENAME_MAX], file_list[FILENAME_MAX];
    double Itime;
    FILE *f;
    int i, j;
    int number_of_materials;
    struct List *blist;
    struct ListNode *p;
    struct Particle *prtl;

    blist = boundary_list(boundary);
    number_of_materials = q->number_of_materials;

    Itime = Time * 1.0e6;
    strcpy(file_name, "./outdata/p.");
    sprintf(file_list, "%.10lld", (long long) Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");

    f = fopen(file_name, "w");
    if (!f)
	ABORT(("can't write '%s'", file_name));
    fprintf(f, "%s", "title='particle position' \n");
    fprintf(f, "%s", "variables=x, y, Ux, Uy \n");
    for (i = 0; i < number_of_materials; i++) {
	j = 0;
	LOOP_P(prtl, particle_list) {
	    if (strcmp
		(materials[i].material_name,
		 prtl->mtl->material_name) == 0) {
		j++;
		if (j == 1)
		    fprintf(f, "zone t='%s' \n",
			    materials[i].material_name);
		fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1],
			prtl->U[0], prtl->U[1]);
	    }
	}
	LOOP_P(prtl, blist) {
	    if (strcmp
		(materials[i].material_name,
		 prtl->mtl->material_name) == 0) {
		j++;
		if (j == 1)
		    fprintf(f, "zone t='%s' \n",
			    materials[i].material_name);
		fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1],
			prtl->U[0], prtl->U[1]);
	    }
	}
    }
    fclose(f);
    return 0;
}

int
output_states(struct Output *q, struct Manager *manager, struct MLS *mls,
	      struct Kernel *kernel, double Time)
{
    FILE *f;
    int i, j, n;
    int gridx, gridy;
    double pstn[2];
    double rho, phi0, pressure, Temperature, x_velocity, y_velocity;
    double Itime;
    char file_name[FILENAME_MAX], file_list[10];
    struct Particle *prtl;
    struct ListNode *p;
    double *phi;

    double delta;
    int x_cells;
    int y_cells;
    int cell_ratio;

    delta = q->delta;
    x_cells = q->x_cells;
    y_cells = q->y_cells;
    cell_ratio = q->cell_ratio;

    gridx = x_cells * cell_ratio;
    gridy = y_cells * cell_ratio;
    Itime = Time * 1.0e6;
    strcpy(file_name, "./outdata/states");
    sprintf(file_list, "%d", (int) Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    f = fopen(file_name, "w");
    if (!f)
	ABORT(("can't write '%s'", file_name));
    fprintf(f, "%s", "title='mapped states' \n");
    fprintf(f, "%s", "variables=x, y, p, rho, phi, Ux, Uy, T \n");
    fprintf(f, "zone t='filed', i=%d, j=%d\n", gridx + 1, gridy + 1);
    for (j = 0; j <= gridy; j++) {
	for (i = 0; i <= gridx; i++) {
	    pstn[0] = i * delta;
	    pstn[1] = j * delta;
	    manager_build_nnp(manager, pstn);
	    if (!list_empty(manager->NNP_list))
		mls_map(mls, pstn, manager->NNP_list, kernel,
			1);
	    n = 0;
	    rho = 0.0;
	    phi0 = 0.0;
	    pressure = 0.0;
	    Temperature = 0.0;
	    x_velocity = 0.0;
	    y_velocity = 0.0;
	    mls_phi(mls, &phi);
	    LOOP_P(prtl, manager->NNP_list) {
		rho += prtl->rho * phi[n];
		phi0 += prtl->phi[2][2] * phi[n];
		pressure += prtl->p * phi[n];
		Temperature += prtl->T * phi[n];
		x_velocity += prtl->U[0] * phi[n];
		y_velocity += prtl->U[1] * phi[n];
		n++;
	    }
	    list_clear(manager->NNP_list);
	    fprintf(f, "%.6g %.6g, %.6g %.6g, %.6g %.6g, %.6g %.6g\n",
		    pstn[0], pstn[1], pressure, rho, phi0, x_velocity,
		    y_velocity, Temperature);
	}
    }
    fclose(f);
    return 0;
}

int
output_restart(struct Output *q, struct List *particle_list, double Time)
{
    int n;
    char file_name[FILENAME_MAX];
    struct Particle *prtl;
    struct ListNode *p;
    FILE *f;

    strcpy(file_name, q->Project_name);
    strcat(file_name, ".rst");
    f = fopen(file_name, "w");
    if (!f)
	ABORT(("can't write '%s'", file_name));
    n = 0;
    LOOP_P(prtl, particle_list) {
	if (prtl->bd == 0)
	    n++;
    }
    fprintf(f, "%.6g\n", Time);
    fprintf(f, "%d\n", n);
    LOOP_P(prtl, particle_list) {
	if (prtl->bd == 0)
	    fprintf(f, "%s %.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
		    prtl->mtl->material_name, prtl->R[0], prtl->R[1],
		    prtl->U[0], prtl->U[1], prtl->rho, prtl->p, prtl->T);
    }
    fclose(f);
    return 0;
}

int
output_fin(struct Output *q)
{
    free(q);
    return 0;
}
