#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glbfunc.h"
#include "particle.h"
#include "list.h"
#include "vv.h"
#include "initiation.h"
#include "hydrodynamics.h"
#include "mls.h"
#include "manager.h"
#include "material.h"
#include "diagnose.h"
#include "macro.h"
#include "err.h"

Diagnose::Diagnose(struct Initiation *ini, struct List *particle_list, struct Material *materials)
{
    char file_name[FILENAME_MAX], *name;
    int k, l, m;
    struct ListNode *p;
    struct Particle *prtl;
    FILE *f;

    vx_list = list_ini();
    vy_list = list_ini();
    rho_list = list_ini();
    x_cells = ini->x_cells; y_cells = ini->y_cells;
    delta = ini->delta;
    number_of_materials = ini->number_of_materials;
    gridx = x_cells*ini->cell_ratio + 1;
    gridy = y_cells*ini->cell_ratio + 1;
    U = new double **[5];
    for(k = 0; k < 5; k++) {
	U[k] = new double *[gridx];
	for(l = 0; l < gridx; l++) U[k][l] = new double [gridy];
    }
    for(k = 0; k < 5; k++)
	for(m = 0; m < gridx; m++)
	    for(l = 0; l < gridy; l++) U[k][m][l] = 0.0;
    n_average = 0;
    if(ini->diagnose == 2) {
	mtl_m = new double [number_of_materials];
	wght_cntr = new double [2*number_of_materials];
	wght_v = new double [2*number_of_materials];
	ttl_m = 1.0e-40;
	for(k = 0; k < number_of_materials; k++) mtl_m[k] = 1.0e-40;
	LOOP_P(prtl, particle_list) {
	    for(k = 0;  k < number_of_materials; k++)
		if(strcmp(prtl->mtl->material_name, materials[k].material_name) == 0)
		    mtl_m[k] += prtl->m;
	    ttl_m += prtl->m;
	}
	strcpy(file_name,"./outdata/kinetic_info.dat");
	f = fopen(file_name, "w");
	if (!f)
	    ABORT(("can't open '%s'", file_name));
	fprintf(f, "%s", "title='kinetic_infomation' \n");
	fprintf(f, "%s", "variables=time, ttl_m, glb_Ek,");
	for(k = 0; k < number_of_materials; k++) {
	    name = materials[k].material_name;
	    fprintf(f, "%s-R[0],  %s-R[1],  ", name, name);
	    fprintf(f, "%s-v[0],  %s-v[1],  ", name, name);
	}
	fprintf(f, "\n");
	fclose(f);
    }
}
void Diagnose::SaveStates(Hydrodynamics *hydro)
{
    int k;
    struct ListNode *p;
    double *p1, *p2, *p3;
    Particle *prtl;
    p1 = new double;
    p2 = new double;
    p3 = new double;

    p = list_first(hydro->particle_list);
    for(k = 0; k < 1; k++)
	p = list_next(hydro->particle_list, p);
    prtl = (struct Particle*)list_retrieve(hydro->particle_list, p);
    *p1 = prtl->U[0];

    *p2 = prtl->U[1];
    *p3 = prtl->rho;
    INSERT_P(p1, vx_list);
    INSERT_P(p2, vy_list);
    INSERT_P(p3, rho_list);
}
void Diagnose::OutputProfile(double Time)
{
    int k, m;
    double Itime;
    char file_name[FILENAME_MAX], file_list[110];
    FILE *f;
    Itime = Time*1.0e8;
    strcpy(file_name,"./outdata/dstr");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    f = fopen(file_name, "a");
    if (!f)
	ABORT(("can't open '%s'", file_name));
    fprintf(f, "%s", "title='distributions' \n");
    fprintf(f, "variables=aUx, Ux, aUy, Uy, arho, rho \n");
    for(k = 0; k < 2; k++)
	for(m = 0; m < 101; m++) vx_dstrb[k][m] = 0.0;
    BuildDistribution(vx_list, vx_dstrb);
    for(k = 0; k < 2; k++)
	for(m = 0; m < 101; m++) vy_dstrb[k][m] = 0.0;
    BuildDistribution(vy_list, vy_dstrb);
    for(m = 0; m < 101; m++) rho_dstrb[0][m] = 1.0;
    for(m = 0; m < 101; m++) rho_dstrb[1][m] = 0.0;
    BuildDistribution(rho_list, rho_dstrb);
    k =  list_length(vx_list);
    for(m = 0; m < 101; m++) {
	fprintf(f, "%.6g %.6g %.6g %.6g %.6g %.6g\n",
		vx_dstrb[0][m], vx_dstrb[1][m]/double(k),
		vy_dstrb[0][m], vy_dstrb[1][m]/double(k),
		rho_dstrb[0][m], rho_dstrb[1][m]/double(k));
    }
}
void Diagnose::BuildDistribution(List *list, double dstrb[2][101])
{
    int m;
    ListNode *p;
    double delta;
    double *x;

    DLOOP_P(x, list) {
	dstrb[0][0] = AMIN1(dstrb[0][0], *x);
	dstrb[0][100] = AMAX1(dstrb[0][100], *x);
    }
    delta = (dstrb[0][100] - dstrb[0][0])*0.01;
    for(m = 0; m < 101; m++)
	dstrb[0][m] = dstrb[0][0] + delta*(double)m;

    DLOOP_P(x, list) {
	m = int ((*x - dstrb[0][0]) / delta);
	dstrb[1][m] += 1.0;
    }
}
void Diagnose::Average(Manager *particles, MLS *mls, QuinticSpline *weight_function)
{
    int i, j, n;
    double pstn[2];
    double rho, pressure, Temperature, x_velocity, y_velocity;
    double m_n_average, r_n_average;
    struct ListNode *p;
    Particle *prtl;
    n_average ++;
    for(j = 0; j < gridy; j++) {
	for(i = 0; i < gridx; i++) {
	    pstn[0] = i*delta; pstn[1] = j*delta;
	    manager_build_nnp(particles, pstn);
	    if(list_empty(particles->NNP_list))
		mls_map(mls, pstn, particles->NNP_list, weight_function, 1);
	    n = 0;
	    rho = 0.0; pressure = 0.0; Temperature = 0.0;
	    x_velocity = 0.0; y_velocity = 0.0;
	    LOOP_P(prtl, particles->NNP_list) {
		rho += prtl->rho*mls->phi[n];
		pressure += prtl->p*mls->phi[n];
		Temperature += prtl->T*mls->phi[n];
		x_velocity += prtl->U[0]*mls->phi[n];
		y_velocity += prtl->U[1]*mls->phi[n];
		n ++;
	    }
	    list_clear(particles->NNP_list);
	    m_n_average = double(n_average) - 1.0;
	    r_n_average = 1.0/double(n_average);
	    U[0][i][j] = (U[0][i][j]*m_n_average + rho)*r_n_average;
	    U[1][i][j] = (U[1][i][j]*m_n_average + pressure)*r_n_average;
	    U[2][i][j] = (U[2][i][j]*m_n_average + Temperature)*r_n_average;
	    U[3][i][j] = (U[3][i][j]*m_n_average + x_velocity)*r_n_average;
	    U[4][i][j] = (U[4][i][j]*m_n_average + y_velocity)*r_n_average;
	}
    }
}
void Diagnose::OutputAverage(double Time)
{
    int i, j;
    double pstn[2];
    double Itime;
    char file_name[FILENAME_MAX], file_list[110];
    FILE *f;

    Itime = Time*1.0e8;
    strcpy(file_name,"./outdata/statistics");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    f = fopen(file_name, "a");
    if (!f)
	ABORT(("can't open '%s'", file_name));
    fprintf(f, "title=averaged states with '%d' samples' \n", n_average);
    fprintf(f, "variables=x, y, p, rho, Ux, Uy, T \n");
    fprintf(f, "zone t='filed', i=%d, j=%d\n", gridx, gridy);
    for(j = 0; j < gridy; j++) {
	for(i = 0; i < gridx; i++) {
	    pstn[0] = i*delta; pstn[1] = j*delta;
	    fprintf(f, "%.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
		    pstn[0], pstn[1],
		    U[1][i][j], U[0][i][j], U[3][i][j], U[4][i][j], U[2][i][j]);
	}
    }
    fclose(f);
}
void Diagnose::KineticInformation(double Time, Hydrodynamics *hydro)
{
    enum {X, Y};
    int k;
    char file_name[FILENAME_MAX];
    struct ListNode *p;
    struct Particle *prtl;
    FILE *f;

    strcpy(file_name,"./outdata/kinetic_info.dat");
    f = fopen(file_name, "a");
    if (!f)
	ABORT(("can't open '%s'", file_name));
    for(k = 0; k < number_of_materials; k++) {
	wght_cntr[2*k + X] = wght_cntr[2*k + Y] = 0.0;
	wght_v[2*k + X] = wght_v[2*k + Y] = 0.0;
    }
    glb_ave_Ek = 0.0;
    LOOP_P(prtl, hydro->particle_list) {
	for(k = 0;  k < number_of_materials; k++)
	    if(strcmp(prtl->mtl->material_name, hydro->materials[k].material_name) == 0) {
		wght_cntr[2*k + X] += prtl->R[X]*prtl->m;
		wght_cntr[2*k + Y] += prtl->R[Y]*prtl->m;
		wght_v[2*k + X] += prtl->U[X]*prtl->m;
		wght_v[2*k + Y] += prtl->U[Y]*prtl->m;
	    }
	glb_ave_Ek += 0.5*sqrt(vv_abs(prtl->U))*prtl->m;
    }
    fprintf(f, "%.6g %.6g %.6g", Time, ttl_m, glb_ave_Ek);
    for(k = 0; k < number_of_materials; k++) {
	fprintf(f, "%.6g %.6g %.6g %.6g ",
		wght_cntr[2*k+X]/mtl_m[k], wght_cntr[2*k+Y]/mtl_m[k], wght_v[2*k+X]/mtl_m[k], wght_v[2*k+Y]/mtl_m[k]);
    }
    fprintf(f, "\n");
    fclose(f);
}
