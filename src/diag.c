#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glbfunc.h"
#include "particle.h"
#include "list.h"
#include "vv.h"
#include "ini.h"
#include "mls.h"
#include "manager.h"
#include "material.h"
#include "vv.h"
#include "macro.h"
#include "err.h"
#include "diag.h"

struct Diag {
    double delta;
    double glb_ave_Ek;
    double *mtl_m;
    double rho_dstrb[2][101];
    double ttl_m;
    double **U[5];
    double vx_dstrb[2][101];
    double vy_dstrb[2][101];
    double *wght_cntr;
    double *wght_v;
    int gridx;
    int gridy;
    int n_average;
    int number_of_materials;
    int x_cells, y_cells;
    struct List *rho_list;
    struct List *vx_list;
    struct List *vy_list;
};

struct Diag *
diag_ini(struct Ini *ini, struct List *particle_list,
	 struct Material *materials)
{
    char file_name[FILENAME_MAX], *name;
    int k, l, m;
    struct ListNode *p;
    struct Particle *prtl;
    FILE *f;
    int number_of_materials;
    struct Diag *q;

    q = malloc(sizeof(struct Diag));
    if (q == NULL)
	ABORT(("can't alloc"));


    number_of_materials = q->number_of_materials =
	ini->number_of_materials;
    q->vx_list = list_ini();
    q->vy_list = list_ini();
    q->rho_list = list_ini();
    q->x_cells = ini->x_cells;
    q->y_cells = ini->y_cells;
    q->delta = ini->delta;
    q->gridx = q->x_cells * ini->cell_ratio + 1;
    q->gridy = q->y_cells * ini->cell_ratio + 1;
    for (k = 0; k < 5; k++) {
	q->U[k] = malloc(q->gridx * sizeof(double *));
	if (q->U[k] == NULL)
	    ABORT(("can't alloc"));
	for (l = 0; l < q->gridx; l++) {
	    q->U[k][l] = malloc(q->gridy * sizeof(double));
	    if (q->U[k] == NULL)
		ABORT(("can't alloc"));
	}
    }
    for (k = 0; k < 5; k++)
	for (m = 0; m < q->gridx; m++)
	    for (l = 0; l < q->gridy; l++)
		q->U[k][m][l] = 0.0;
    q->n_average = 0;
    if (ini->diag == 2) {
	q->mtl_m =
	    malloc(number_of_materials * sizeof(*q->mtl_m));
	q->wght_cntr =
	    (double *) malloc(2 * number_of_materials *
			      sizeof(*q->wght_cntr));
	q->wght_v =
	    malloc(2 * number_of_materials *
			      sizeof(*q->wght_v));

	q->ttl_m = 1.0e-40;
	for (k = 0; k < number_of_materials; k++)
	    q->mtl_m[k] = 1.0e-40;
	LOOP_P(prtl, particle_list) {
	    for (k = 0; k < number_of_materials; k++)
		if (strcmp
		    (prtl->mtl->material_name,
		     materials[k].material_name) == 0)
		    q->mtl_m[k] += prtl->m;
	    q->ttl_m += prtl->m;
	}
	strcpy(file_name, "./outdata/kinetic_info.dat");
	f = fopen(file_name, "w");
	if (!f)
	    ABORT(("can't open '%s'", file_name));
	fprintf(f, "%s", "title='kinetic_infomation' \n");
	fprintf(f, "%s", "variables=time, ttl_m, glb_Ek,");
	for (k = 0; k < number_of_materials; k++) {
	    name = materials[k].material_name;
	    fprintf(f, "%s-R[0],  %s-R[1],  ", name, name);
	    fprintf(f, "%s-v[0],  %s-v[1],  ", name, name);
	}
	fprintf(f, "\n");
	fclose(f);
    }
    return q;
}

int
SaveStates(struct Diag *q, struct List *particle_list)
{
    int k;
    struct ListNode *p;
    double *p1, *p2, *p3;
    struct Particle *prtl;

    p1 = malloc(sizeof(*p1));
    p2 = malloc(sizeof(*p2));
    p3 = malloc(sizeof(*p3));

    p = list_first(particle_list);
    for (k = 0; k < 1; k++)
	p = list_next(particle_list, p);
    prtl = (struct Particle *) list_retrieve(particle_list, p);
    *p1 = prtl->U[0];

    *p2 = prtl->U[1];
    *p3 = prtl->rho;
    INSERT_P(p1, q->vx_list);
    INSERT_P(p2, q->vy_list);
    INSERT_P(p3, q->rho_list);
    return 0;
}

int
OutputProfile(struct Diag *q, double Time)
{
    int k, m;
    double Itime;
    char file_name[FILENAME_MAX], file_list[110];
    FILE *f;

    Itime = Time * 1.0e8;
    strcpy(file_name, "./outdata/dstr");
    sprintf(file_list, "%d", (int) Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    f = fopen(file_name, "a");
    if (!f)
	ABORT(("can't open '%s'", file_name));
    fprintf(f, "%s", "title='distributions' \n");
    fprintf(f, "variables=aUx, Ux, aUy, Uy, arho, rho \n");
    for (k = 0; k < 2; k++)
	for (m = 0; m < 101; m++)
	    q->vx_dstrb[k][m] = 0.0;
    BuildDistribution(q->vx_list, q->vx_dstrb);
    for (k = 0; k < 2; k++)
	for (m = 0; m < 101; m++)
	    q->vy_dstrb[k][m] = 0.0;
    BuildDistribution(q->vy_list, q->vy_dstrb);
    for (m = 0; m < 101; m++)
	q->rho_dstrb[0][m] = 1.0;
    for (m = 0; m < 101; m++)
	q->rho_dstrb[1][m] = 0.0;
    BuildDistribution(q->rho_list, q->rho_dstrb);
    k = list_length(q->vx_list);
    for (m = 0; m < 101; m++) {
	fprintf(f, "%.6g %.6g %.6g %.6g %.6g %.6g\n",
		q->vx_dstrb[0][m], q->vx_dstrb[1][m] / (double) k,
		q->vy_dstrb[0][m], q->vy_dstrb[1][m] / (double) k,
		q->rho_dstrb[0][m], q->rho_dstrb[1][m] / (double) k);
    }
    return 0;
}

int
BuildDistribution(struct List *list, double dstrb[2][101])
{
    int m;
    struct ListNode *p;
    double delta;
    double *x;

    DLOOP_P(x, list) {
	dstrb[0][0] = AMIN1(dstrb[0][0], *x);
	dstrb[0][100] = AMAX1(dstrb[0][100], *x);
    }
    delta = (dstrb[0][100] - dstrb[0][0]) * 0.01;
    for (m = 0; m < 101; m++)
	dstrb[0][m] = dstrb[0][0] + delta * (double) m;

    DLOOP_P(x, list) {
	m = (int) ((*x - dstrb[0][0]) / delta);

	dstrb[1][m] += 1.0;
    }
    return 0;
}

int
Average(struct Diag *q, struct Manager *manager, struct MLS *mls,
	struct Kernel *kernel)
{
    int i, j, n;
    double pstn[2];
    double rho, pressure, Temperature, x_velocity, y_velocity;
    double m_n_average, r_n_average;
    double ***U;
    double *phi;
    struct ListNode *p;
    struct Particle *prtl;

    U = q->U;
    q->n_average++;
    for (j = 0; j < q->gridy; j++) {
	for (i = 0; i < q->gridx; i++) {
	    pstn[0] = i * q->delta;
	    pstn[1] = j * q->delta;
	    manager_build_nnp(manager, pstn);
	    if (list_empty(manager->NNP_list))
		mls_map(mls, pstn, manager->NNP_list, kernel,
			1);
	    n = 0;
	    rho = 0.0;
	    pressure = 0.0;
	    Temperature = 0.0;
	    x_velocity = 0.0;
	    y_velocity = 0.0;
	    mls_phi(mls, &phi);
	    LOOP_P(prtl, manager->NNP_list) {
		rho += prtl->rho * phi[n];
		pressure += prtl->p * phi[n];
		Temperature += prtl->T * phi[n];
		x_velocity += prtl->U[0] * phi[n];
		y_velocity += prtl->U[1] * phi[n];
		n++;
	    }
	    list_clear(manager->NNP_list);
	    m_n_average = (double) (q->n_average) - 1.0;
	    r_n_average = 1.0 / (double) (q->n_average);

	    U[0][i][j] = (U[0][i][j] * m_n_average + rho) * r_n_average;
	    U[1][i][j] =
		(U[1][i][j] * m_n_average + pressure) * r_n_average;
	    U[2][i][j] =
		(U[2][i][j] * m_n_average + Temperature) * r_n_average;
	    U[3][i][j] =
		(U[3][i][j] * m_n_average + x_velocity) * r_n_average;
	    U[4][i][j] =
		(U[4][i][j] * m_n_average + y_velocity) * r_n_average;
	}
    }
    return 0;
}

int
OutputAverage(struct Diag *q, double Time)
{
    int i, j;
    double pstn[2];
    double Itime;
    char file_name[FILENAME_MAX], file_list[110];
    FILE *f;
    double ***U;

    U = q->U;
    Itime = Time * 1.0e8;
    strcpy(file_name, "./outdata/statistics");
    sprintf(file_list, "%d", (int) Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    f = fopen(file_name, "a");
    if (!f)
	ABORT(("can't open '%s'", file_name));
    fprintf(f, "title=averaged states with '%d' samples' \n",
	    q->n_average);
    fprintf(f, "variables=x, y, p, rho, Ux, Uy, T \n");
    fprintf(f, "zone t='filed', i=%d, j=%d\n", q->gridx, q->gridy);
    for (j = 0; j < q->gridy; j++) {
	for (i = 0; i < q->gridx; i++) {
	    pstn[0] = i * q->delta;
	    pstn[1] = j * q->delta;
	    fprintf(f, "%.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
		    pstn[0], pstn[1],
		    U[1][i][j], U[0][i][j], U[3][i][j], U[4][i][j],
		    U[2][i][j]);
	}
    }
    fclose(f);
    return 0;
}

int
KineticInformation(struct Diag *q, double Time,
		   struct List *particle_list, struct Material *materials)
{
    enum { X, Y };
    int k;
    char file_name[FILENAME_MAX];
    struct ListNode *p;
    struct Particle *prtl;
    int number_of_materials;
    FILE *f;

    number_of_materials = q->number_of_materials;
    strcpy(file_name, "./outdata/kinetic_info.dat");
    f = fopen(file_name, "a");
    if (!f)
	ABORT(("can't open '%s'", file_name));
    for (k = 0; k < number_of_materials; k++) {
	q->wght_cntr[2 * k + X] = q->wght_cntr[2 * k + Y] = 0.0;
	q->wght_v[2 * k + X] = q->wght_v[2 * k + Y] = 0.0;
    }
    q->glb_ave_Ek = 0.0;
    LOOP_P(prtl, particle_list) {
	for (k = 0; k < number_of_materials; k++)
	    if (strcmp
		(prtl->mtl->material_name,
		 materials[k].material_name) == 0) {
		q->wght_cntr[2 * k + X] += prtl->R[X] * prtl->m;
		q->wght_cntr[2 * k + Y] += prtl->R[Y] * prtl->m;
		q->wght_v[2 * k + X] += prtl->U[X] * prtl->m;
		q->wght_v[2 * k + Y] += prtl->U[Y] * prtl->m;
	    }
	q->glb_ave_Ek += 0.5 * sqrt(vv_abs(prtl->U)) * prtl->m;
    }
    fprintf(f, "%.6g %.6g %.6g", Time, q->ttl_m, q->glb_ave_Ek);
    for (k = 0; k < number_of_materials; k++) {
	fprintf(f, "%.6g %.6g %.6g %.6g ",
		q->wght_cntr[2 * k + X] / q->mtl_m[k],
		q->wght_cntr[2 * k + Y] / q->mtl_m[k],
		q->wght_v[2 * k + X] / q->mtl_m[k],
		q->wght_v[2 * k + Y] / q->mtl_m[k]);
    }
    fprintf(f, "\n");
    fclose(f);
    return 0;
}

int
diag_fin(struct Diag *q)
{
    int k, l;
    int gridx;
    double ***U;
    struct ListNode *p;
    double *d;

    gridx = q->gridx;
    U = q->U;
    for (k = 0; k < 5; k++) {
	for (l = 0; l < gridx; l++)
	    free(U[k][l]);
	free(U[k]);
    }

    /*
       free(q->mtl_m);
       free(q->wght_cntr);
       free(q->wght_v);
       free(q); */

    DLOOP_P(d, q->vx_list)
	free(d);
    DLOOP_P(d, q->vy_list)
	free(d);
    DLOOP_P(d, q->rho_list)
	free(d);
    list_fin(q->vx_list);
    list_fin(q->vy_list);
    list_fin(q->rho_list);
    free(q);
    return 0;
}
