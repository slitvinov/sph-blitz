#include <cmath>
#include <cstdio>
#include "vv.h"
#include "glbfunc.h"
#include "material.h"
#include "particle.h"

enum {X, Y};

long particle_ID_max;
int particle_number_of_materials;

static int
phi_ini(double ***pq)
{
    int n, i, j;
    double **q;
    n = particle_number_of_materials;
    q = new double*[n];
    for(i = 0; i < n; i++)
	q[i] = new double[n];
    for(i = 0; i < n; i++)
	for(j = 0; j < n; j++)
	    q[i][j] = 0.0;
    *pq = q;
    return 0;
}

Particle::~Particle()
{
    int i;
    for(i = 0; i < particle_number_of_materials; i++) {
	delete[] phi[i];
    }
    delete[] phi;
}

Particle::Particle(double position[2], double velocity[2], double density, double pressure, double temperature, Material *material)
{
    int i, j;
    bd = 0;
    particle_ID_max++;

    ID = particle_ID_max;
    mtl = material;
    eta = mtl->eta; zeta = mtl->zeta;
    R[X] = position[X];
    R[Y] = position[Y];
    rho = density;
    p = pressure;
    T = temperature;
    Cs = get_Cs(mtl, p, rho);
    U[X] = velocity[X];
    U[Y] = velocity[Y];
    U_I[X] = U[X];
    U_I[Y] = U[Y];
    m = 0.0;
    V = 0.0;
    R_I[X] = R[X];
    R_I[Y] = R[Y];
    P_I[X] = P[X];
    P_I[Y] = P[Y];
    rho_I = rho;
    P_n[X] = P[X];
    P_n[Y] = P[Y];
    U_n[X] = U[X];
    U_n[Y] = U[Y];
    rho_n = rho;
    phi_ini(&phi);
}

Particle::Particle(double x, double y, double u, double v, Material *material)
{
    bd = 1;
    bd_type = 0;
    ID = 0;
    mtl = material;
    R[0] = x;
    R[1] = y;
    U[0] = u;
    U[1] = v;
    rho = 0.0;
    p = 0.0;
    T = 0.0;
}

Particle::Particle(Particle &q)
{
    int i, j;
    bd = 1;
    bd_type = 1;
    ID = 0;
    rl_prtl = &q;
    mtl = q.mtl;
    eta = mtl->eta; zeta = mtl->zeta;
    R[X] = q.R[X];
    R[Y] = q.R[Y];
    rho = q.rho;
    p = q.p;
    T = q.T;
    Cs =q.Cs;
    U[X] = q.U[X];
    U[Y] = q.U[Y];
    U_I[X] = q.U_I[X];
    U_I[Y] = q.U_I[Y];
    ShearRate_x[X] = q.ShearRate_x[X];
    ShearRate_x[Y] = q.ShearRate_x[Y];
    ShearRate_y[X] = q.ShearRate_y[X];
    ShearRate_y[Y] = q.ShearRate_y[Y];
    m = q.m;
    V = q.V;
    e = q.e;
    R_I[X] = q.R_I[X];
    R_I[Y] = q.R_I[Y];
    P[X] = q.P[X];
    P[Y] = q.P[Y];
    P_I[X] = q.P_I[X];
    P_I[Y] = q.P_I[Y];
    rho_I = rho;
    P_n[X] = q.P_n[X];
    P_n[Y] = q.P_n[Y];
    U_n[X] = q.U_n[X];
    U_n[Y] = q.U_n[Y];
    rho_n = q.rho_n;
    phi_ini(&phi);
}

Particle::Particle(Particle *q, Material *material)
{
    int i, j;
    bd = 1;
    bd_type = 0;
    ID = 0;
    rl_prtl = q;
    mtl = material;
    eta = q->eta;
    zeta = q->zeta;
    R[X] = q->R[X];
    R[Y] = q->R[Y];
    rho = q->rho;
    p = q->p;
    T = q->T;
    Cs = q->Cs;
    U[X] = q->U[X];
    U[Y] = q->U[Y];
    U_I[X] = q->U_I[X];
    U_I[Y] = q->U_I[Y];
    ShearRate_x[X] = q->ShearRate_x[X];
    ShearRate_x[Y] = q->ShearRate_x[Y];
    ShearRate_y[X] = q->ShearRate_y[X];
    ShearRate_y[Y] = q->ShearRate_y[Y];
    m = q->m;
    V = q->V;
    e = q->e;
    R_I[X] = q->R_I[X];
    R_I[Y] = q->R_I[Y];
    P[X] = q->P[X];
    P[Y] = q->P[Y];
    P_I[X] = q->P_I[X];
    P_I[Y] = q->P_I[Y];
    rho_I = rho;
    P_n[X] = q->P_n[X];
    P_n[Y] = q->P_n[Y];
    U_n[X] = q->U_n[X];
    U_n[Y] = q->U_n[Y];
    rho_n = q->rho_n;
    phi_ini(&phi);
}

void Particle::StatesCopier(Particle *q, int type)
{
    int i, j;

    R[X] = q->R[X];
    R[Y] = q->R[Y];
    m = q->m;
    rho = q->rho;
    V = q->V;
    p = q->p;
    T = q->T;
    rho_I = q->rho_I;
    Cs =q->Cs;
    U[X] = q->U[X];
    U[Y] = q->U[Y];
    U_I[X] = q->U_I[X];
    U_I[Y] = q->U_I[Y];
    ShearRate_x[X] = q->ShearRate_x[X];
    ShearRate_x[Y] = q->ShearRate_x[Y];
    ShearRate_y[X] = q->ShearRate_y[X];
    ShearRate_y[Y] = q->ShearRate_y[Y];
    if (type == 1 ) {
	del_phi[X] = q->del_phi[X];
	del_phi[Y] = q->del_phi[Y];
	for(i = 0; i < particle_number_of_materials; i++) {
	    for(j = 0; j < particle_number_of_materials; j++) {
		phi[i][j] = q->phi[i][j];
	    }
	}
    }
    if (type == 0) {
	phi[0][0] = 0;
	for(i = 1; i < particle_number_of_materials; i++)
	    phi[0][0] += q->phi[i][i];
    }
}
