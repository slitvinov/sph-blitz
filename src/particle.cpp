#include <stdlib.h>
#include <stdio.h>
#include "glbfunc.h"
#include "material.h"
#include "particle.h"

enum {X, Y};

long particle_ID_max;
int particle_number_of_materials;

#define A(v) v = q->v
#define B(a, b) a = b;

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
    particle_ID_max++;

    B(bd, 0);
    B(bd_type, 0);
    B(ID, particle_ID_max);
    B(mtl, material);
    B(eta, mtl->eta);
    B(zeta, mtl->zeta);
    B(R[X], position[X]);
    B(R[Y], position[Y]);
    B(rho, density);
    B(p, pressure);
    B(T, temperature);
    B(Cs, get_Cs(mtl, p, rho));
    B(U[X], velocity[X]);
    B(U[Y], velocity[Y]);
    B(U_I[X], U[X]);
    B(U_I[Y], U[Y]);
    B(m, 0.0);
    B(V, 0.0);
    B(R_I[X], R[X]);
    B(R_I[Y], R[Y]);
    B(P_I[X], P[X]);
    B(P_I[Y], P[Y]);
    B(rho_I, rho);
    B(P_n[X], P[X]);
    B(P_n[Y], P[Y]);
    B(U_n[X], U[X]);
    B(U_n[Y], U[Y]);
    B(rho_n, rho);
    B(phi, phi_ini());
}

Particle::Particle(double x, double y, Material *material)
{
    B(bd, 1);
    B(bd_type, 0);
    B(ID, 0);
    B(mtl, material);
    B(R[0], x);
    B(R[1], y);
    B(U[0], 0);
    B(U[1], 0);
    B(rho, 0.0);
    B(p, 0.0);
    B(T, 0.0);
}

Particle::Particle(Particle *q)
{
    B(bd, 1);
    B(bd_type, 1);
    B(ID, 0);
    B(rl_prtl, q);
    A(mtl);
    B(eta, mtl->eta);
    B(zeta, mtl->zeta);
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
    B(phi, phi_ini());
}

Particle::Particle(Particle *q, Material *material)
{
    B(bd, 1);
    B(bd_type, 0);
    B(ID, 0);
    B(rl_prtl, q);
    B(mtl, material);
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
    B(rho_I, rho);
    A(P_n[X]);
    A(P_n[Y]);
    A(U_n[X]);
    A(U_n[Y]);
    A(rho_n);
    B(phi, phi_ini());
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
