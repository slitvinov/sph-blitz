#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "particle.h"
#include "glbfunc.h"
#include "list.h"
#include "mls.h"
#include "initiation.h"
#include "hydrodynamics.h"
#include "material.h"
#include "boundary.h"
#include "manager.h"
#include "macro.h"
#include "err.h"
#include "output.h"
using namespace std;
#define LIST ListNode

Output::Output(Initiation *ini)
{
    strcpy(Project_name, ini->Project_name);
    number_of_materials = ini->number_of_materials;
    x_cells = ini->x_cells; y_cells = ini->y_cells;
    cell_ratio = ini->cell_ratio;
    delta = ini->delta;
}
void Output::OutputParticles(Hydrodynamics *hydro, Boundary *boundary,  double Time)
{
    FILE *f;
    int i, j;
    double Itime;
    char file_name[FILENAME_MAX], file_list[FILENAME_MAX];
    Particle *prtl;
    LIST *p;
    Itime = Time*1.0e6;
    strcpy(file_name,"./outdata/p.");
    sprintf(file_list, "%.10lld", (long long)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");

    f = fopen(file_name, "w");
    if (!f)
	ABORT(("can't write '%s'", file_name));
    fprintf(f, "%s", "title='particle position' \n");
    fprintf(f, "%s", "variables=x, y, Ux, Uy \n");
    for(i = 0; i < number_of_materials; i++) {
	j = 0;
	LOOP_P(prtl, hydro->particle_list) {
	    if(strcmp(hydro->materials[i].material_name, prtl->mtl->material_name) == 0) {
		j++;
		if(j == 1)
		    fprintf(f, "zone t='%s' \n", hydro->materials[i].material_name);
		fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0], prtl->U[1]);
	    }
	}
	LOOP_P(prtl, boundary->b) {
	    if(strcmp(hydro->materials[i].material_name, prtl->mtl->material_name) == 0) {
		j++;
		if(j == 1)
		    fprintf(f, "zone t='%s' \n", hydro->materials[i].material_name);
		fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0], prtl->U[1]);
	    }
	}
    }
    fclose(f);
}
void Output::OutputStates(Manager *particles, MLS *mls, QuinticSpline *weight_function, double Time)
{
    int i, j, n;
    int gridx, gridy;
    double pstn[2];
    double rho, phi, pressure, Temperature, x_velocity, y_velocity;
    double Itime;
    char file_name[FILENAME_MAX], file_list[10];
    Particle *prtl;
    LIST *p;
    gridx = x_cells*cell_ratio; gridy = y_cells*cell_ratio;
    Itime = Time*1.0e6;
    strcpy(file_name,"./outdata/states");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    ofstream out(file_name);
    out<<"title='mapped states' \n";
    out<<"variables=x, y, p, rho, phi, Ux, Uy, T \n";
    out<<"zone t='filed', i="<<gridx + 1<<", j="<<gridy + 1<<"\n";
    for(j = 0; j <= gridy; j++) {
	for(i = 0; i <= gridx; i++) {
	    pstn[0] = i*delta; pstn[1] = j*delta;
	    manager_build_nnp(particles, pstn);
	    if(!list_empty(particles->NNP_list))
		mls_map(mls, pstn, particles->NNP_list, weight_function, 1);
	    n = 0;
	    rho = 0.0; phi = 0.0; pressure = 0.0; Temperature = 0.0;
	    x_velocity = 0.0; y_velocity = 0.0;
	    LOOP_P(prtl, particles->NNP_list) {
		rho += prtl->rho*mls->phi[n];
		phi += prtl->phi[2][2]*mls->phi[n];
		pressure += prtl->p*mls->phi[n];
		Temperature += prtl->T*mls->phi[n];
		x_velocity += prtl->U[0]*mls->phi[n];
		y_velocity += prtl->U[1]*mls->phi[n];
		n ++;
	    }
	    list_clear(particles->NNP_list);
	    out<<pstn[0]<<"  "<<pstn[1] <<"  "<<pressure<<"  "<<rho <<"  "<<phi <<"  "<<x_velocity<<"  "<<y_velocity <<"  "<<Temperature<<"\n";
	}
    }
    out.close();
}
void Output::OutRestart(Hydrodynamics *hydro, double Time)
{
    int n;
    char outputfile[FILENAME_MAX];
    Particle *prtl;
    LIST *p;
    strcpy(outputfile, Project_name);
    strcat(outputfile,".rst");
    ofstream out(outputfile);
    n = 0;
    LOOP_P(prtl, hydro->particle_list) {
	if(prtl->bd == 0) n++;
    }
    out<<Time<<"\n";
    out<<n<<"\n";
    LOOP_P(prtl, hydro->particle_list) {
	if(prtl->bd == 0)
	    out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1] <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<< '\n';
    }
    out.close();
}
