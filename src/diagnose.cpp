#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
class Initiation;
class Hydrodynamics;
class ParticleManager;
class MLS;
class QuinticSpline;
class Material;
class Interaction;
class Force;
class Boundary;
#include "glbfunc.h"
#include "particle.h"
#include "dllist.h"
#include "list.h"
#include "vv.h"
#include "initiation.h"
#include "hydrodynamics.h"
#include "mls.h"
#include "particlemanager.h"
#include "material.h"
#include "diagnose.h"
using namespace std;
#define LIST ListNode
Diagnose::Diagnose(Initiation *ini, Hydrodynamics *hydro)
{
    int k, l, m;
    x_cells = ini->x_cells; y_cells = ini->y_cells;
    hdelta = ini->hdelta;
    delta = ini->delta;
    strcpy(Project_name, ini->Project_name);
    number_of_materials = ini->number_of_materials;
    gridx = x_cells*hdelta + 1; gridy = y_cells*hdelta + 1;
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
        for (LIST *p = hydro->particle_list.first();
             !hydro->particle_list.isEnd(p);
             p = hydro->particle_list.next(p)) {
            Particle *prtl = hydro->particle_list.retrieve(p);
            for(k = 0;  k < number_of_materials; k++)
                if(strcmp(prtl->mtl->material_name, hydro->materials[k].material_name) == 0)
                    mtl_m[k] += prtl->m;
            ttl_m += prtl->m;
        }
        char file_name[FILENAME_MAX];
        strcpy(file_name,"./outdata/kinetic_info.dat");
        ofstream out(file_name);
        out<<"title='kinetic_infomation' \n";
        out<<"variables=time, ttl_m, glb_Ek,";
        for(k = 0; k < number_of_materials; k++) {
            out<<hydro->materials[k].material_name<<"-R[0],  "<<hydro->materials[k].material_name<<"-R[1],  ";
            out<<hydro->materials[k].material_name<<"-v[0],  "<<hydro->materials[k].material_name<<"-v[1],  ";
        }
        out<<"\n";
        out.close();
    }
}
void Diagnose::SaveStates(Hydrodynamics *hydro)
{
    int k;
    LIST *p = hydro->particle_list.first();
    for(k = 0; k < 1; k++) p = hydro->particle_list.next(p);
    Particle *prtl = hydro->particle_list.retrieve(p);
    double *p1 = new double;
    *p1 = prtl->U[0];
    double *p2 = new double;
    *p2 = prtl->U[1];
    double *p3 = new double;
    *p3 = prtl->rho;
    vx_list.insert(vx_list.first(), p1);
    vy_list.insert(vy_list.first(), p2);
    rho_list.insert(rho_list.first(), p3);
}
void Diagnose::OutputProfile(double Time)
{
    int k, m;
    double Itime;
    char file_name[FILENAME_MAX], file_list[110];
    Itime = Time*1.0e8;
    strcpy(file_name,"./outdata/dstr");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    ofstream out(file_name);
    out<<"title='distributions' \n";
    out<<"variables=aUx, Ux, aUy, Uy, arho, rho \n";
    for(k = 0; k < 2; k++)
        for(m = 0; m < 101; m++) vx_dstrb[k][m] = 0.0;
    BuildDistribution(&vx_list, vx_dstrb);
    for(k = 0; k < 2; k++)
        for(m = 0; m < 101; m++) vy_dstrb[k][m] = 0.0;
    BuildDistribution(&vy_list, vy_dstrb);
    for(m = 0; m < 101; m++) rho_dstrb[0][m] = 1.0;
    for(m = 0; m < 101; m++) rho_dstrb[1][m] = 0.0;
    BuildDistribution(&rho_list, rho_dstrb);
    k =  vx_list.length();
    for(m = 0; m < 101; m++) {
        out<<vx_dstrb[0][m]<<"  "<<vx_dstrb[1][m]/double(k)<<"  "
           <<vy_dstrb[0][m]<<"  "<<vy_dstrb[1][m]/double(k)<<"  "
           <<rho_dstrb[0][m]<<"  "<<rho_dstrb[1][m]/double(k)<<"  \n";
    }
}
void Diagnose::BuildDistribution(Llist<double> *list, double dstrb[2][101])
{
    int m;
    for (LlistNode<double> *p = list->first();
         !list->isEnd(p); p = list->next(p)) {
        dstrb[0][0] = AMIN1(dstrb[0][0], *list->retrieve(p));
        dstrb[0][100] = AMAX1(dstrb[0][100], *list->retrieve(p));
    }
    double delta;
    delta = (dstrb[0][100] - dstrb[0][0])*0.01;
    for(m = 0; m < 101; m++) dstrb[0][m] = dstrb[0][0] + delta*(double)m;
    for (LlistNode<double> *p1 = list->first();
         !list->isEnd(p1); p1 = list->next(p1)) {
        m = int ((*list->retrieve(p1) - dstrb[0][0]) / delta);
        dstrb[1][m] += 1.0;
    }
}
void Diagnose::Average(ParticleManager *particles, MLS *mls, QuinticSpline *weight_function)
{
    int i, j, n;
    double pstn[2];
    double rho, pressure, Temperature, x_velocity, y_velocity;
    double m_n_average, r_n_average;
    n_average ++;
    for(j = 0; j < gridy; j++) {
        for(i = 0; i < gridx; i++) {
            pstn[0] = i*delta; pstn[1] = j*delta;
            particles->BuildNNP(pstn);
            if(!particles->NNP_list.empty())
                mls->MLSMapping(pstn, particles->NNP_list, *weight_function, 1);
            n = 0;
            rho = 0.0; pressure = 0.0; Temperature = 0.0;
            x_velocity = 0.0; y_velocity = 0.0;
            for (LIST *p = particles->NNP_list.first();
                 !particles->NNP_list.isEnd(p);
                 p = particles->NNP_list.next(p)) {
                Particle *prtl = particles->NNP_list.retrieve(p);
                rho += prtl->rho*mls->phi[n];
                pressure += prtl->p*mls->phi[n];
                Temperature += prtl->T*mls->phi[n];
                x_velocity += prtl->U[0]*mls->phi[n];
                y_velocity += prtl->U[1]*mls->phi[n];
                n ++;
            }
            particles->NNP_list.clear();
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
    Itime = Time*1.0e8;
    strcpy(file_name,"./outdata/statistics");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");
    ofstream out(file_name);
    out<<"title=averaged states with '"<<n_average<<"' samples' \n";
    out<<"variables=x, y, p, rho, Ux, Uy, T \n";
    out<<"zone t='filed', i="<<gridx<<", j="<<gridy<<"\n";
    for(j = 0; j < gridy; j++) {
        for(i = 0; i < gridx; i++) {
            pstn[0] = i*delta; pstn[1] = j*delta;
            out<<pstn[0]<<"  "<<pstn[1]
               <<"  "<<U[1][i][j]<<"  "<<U[0][i][j]
               <<"  "<<U[3][i][j]<<"  "<<U[4][i][j]
               <<"  "<<U[2][i][j]<<"\n";
        }
    }
    out.close();
}
void Diagnose::KineticInformation(double Time, Hydrodynamics *hydro)
{
    enum {X, Y};
    int k;
    char file_name[FILENAME_MAX];
    strcpy(file_name,"./outdata/kinetic_info.dat");
    ofstream out(file_name, ios::out | ios::ate);
    for(k = 0; k < number_of_materials; k++) {
        wght_cntr[2*k + X] = wght_cntr[2*k + Y] = 0.0;
        wght_v[2*k + X] = wght_v[2*k + Y] = 0.0;
    }
    glb_ave_Ek = 0.0;
    for (LIST *p = hydro->particle_list.first();
         !hydro->particle_list.isEnd(p);
         p = hydro->particle_list.next(p)) {
        Particle *prtl = hydro->particle_list.retrieve(p);
        for(k = 0;  k < number_of_materials; k++)
            if(strcmp(prtl->mtl->material_name, hydro->materials[k].material_name) == 0) {
                wght_cntr[2*k + X] += prtl->R[X]*prtl->m;
                wght_cntr[2*k + Y] += prtl->R[Y]*prtl->m;		
                wght_v[2*k + X] += prtl->U[X]*prtl->m;
                wght_v[2*k + Y] += prtl->U[Y]*prtl->m;		
            }
        glb_ave_Ek += 0.5*sqrt(vv_abs(prtl->U))*prtl->m;
    }
    out<<Time<<"  "<<ttl_m<<"  "<<glb_ave_Ek<<"  ";
    for(k = 0; k < number_of_materials; k++) {
        out<<wght_cntr[2*k + X]/mtl_m[k]<<"  "<<wght_cntr[2*k + Y]/mtl_m[k]<<"  ";
        out<<wght_v[2*k + X]/mtl_m[k]<<"  "<<wght_v[2*k + Y]/mtl_m[k]<<"  ";
    }
    out<<"\n";
    out.close();
}
