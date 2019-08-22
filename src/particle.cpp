#include <stdlib.h>
#include <stdio.h>
#include "glbfunc.h"
#include "material.h"
#include "particle.h"

enum {X, Y};

long particle_ID_max;
int particle_number_of_materials;

#define A(v) v = q->v

static double**
phi_ini(void)
{
    int n, i, j;
    double **q;
    n = particle_number_of_materials;
    q = (double**)malloc(n*sizeof(*q));
    for(i = 0; i < n; i++)
	q[i] = (double*)malloc(n*sizeof(*q));
    for(i = 0; i < n; i++)
	for(j = 0; j < n; j++)
	    q[i][j] = 0.0;
    return q;
}

Particle::~Particle()
{
    int i;
    for(i = 0; i < particle_number_of_materials; i++) {
	free(phi[i]);
    }
    free(phi);
}

Particle::Particle(double position[2], double velocity[2], double density, double pressure, double temperature, Material *material)
{
    int i, j;
    particle_ID_max++;

    bd = 0;
    bd_type = 0;
    ID = particle_ID_max;
    mtl = material;
    eta = mtl->eta;
    zeta = mtl->zeta;
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
    phi = phi_ini();
}

Particle::Particle(double x, double y, Material *material)
{
    bd = 1;
    bd_type = 0;
    ID = 0;
    mtl = material;
    R[0] = x;
    R[1] = y;
    U[0] = 0;
    U[1] = 0;
    rho = 0.0;
    p = 0.0;
    T = 0.0;
}

Particle::Particle(Particle *q)
{
    bd = 1;
    bd_type = 1;
    ID = 0;
    rl_prtl = q;
    A(mtl);
    eta = mtl->eta;
    zeta = mtl->zeta;
    A(R[X]);
    A(R[Y]);
    A(rho);
    A(p);
    A(T);
    A(Cs);
    A(U[X]);
    A(U[Y]);
    A(U_I[X]);
    A(U_I[Y]);
    A(ShearRate_x[X]);
    A(ShearRate_x[Y]);
    A(ShearRate_y[X]);
    A(ShearRate_y[Y]);
    A(m);
    A(V);
    A(e);
    A(R_I[X]);
    A(R_I[Y]);
    A(P[X]);
    A(P[Y]);
    A(P_I[X]);
    A(P_I[Y]);
    rho_I = rho;
    A(P_n[X]);
    A(P_n[Y]);
    A(U_n[X]);
    A(U_n[Y]);
    A(rho_n);
    phi = phi_ini();
}

Particle::Particle(Particle *q, Material *material)
{
    bd = 1;
    bd_type = 0;
    ID = 0;
    rl_prtl = q;
    mtl = material;
    A(eta);
    A(zeta);
    A(R[X]);
    A(R[Y]);
    A(rho);
    A(p);
    A(T);
    A(Cs);
    A(U[X]);
    A(U[Y]);
    A(U_I[X]);
    A(U_I[Y]);
    A(ShearRate_x[X]);
    A(ShearRate_x[Y]);
    A(ShearRate_y[X]);
    A(ShearRate_y[Y]);
    A(m);
    A(V);
    A(e);
    A(R_I[X]);
    A(R_I[Y]);
    A(P[X]);
    A(P[Y]);
    A(P_I[X]);
    A(P_I[Y]);
    rho_I = rho;
    A(P_n[X]);
    A(P_n[Y]);
    A(U_n[X]);
    A(U_n[Y]);
    A(rho_n);
    phi = phi_ini();
}

void Particle::StatesCopier(Particle *q, int type)
{
    int i, j;
    A(R[X]);
    A(R[Y]);
    A(m);
    A(rho);
    A(V);
    A(p);
    A(T);
    A(rho_I);
    A(Cs);
    A(U[X]);
    A(U[Y]);
    A(U_I[X]);
    A(U_I[Y]);
    A(ShearRate_x[X]);
    A(ShearRate_x[Y]);
    A(ShearRate_y[X]);
    A(ShearRate_y[Y]);
    if (type == 1 ) {
	A(del_phi[X]);
	A(del_phi[Y]);
	for(i = 0; i < particle_number_of_materials; i++) {
	    for(j = 0; j < particle_number_of_materials; j++) {
		A(phi[i][j]);
	    }
	}
    }
    if (type == 0) {
	phi[0][0] = 0;
	for(i = 1; i < particle_number_of_materials; i++)
	    phi[0][0] += q->phi[i][i];
    }
}
