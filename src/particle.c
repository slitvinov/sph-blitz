#include <stdlib.h>
#include <stdio.h>
#include "sph/material.h"
#include "sph/particle.h"

enum { X, Y };

long particle_ID_max;
int particle_number_of_materials;

#define A(v) q->v = s->v
#define B(a, b) q->a = b
#define C(a, b) q->a = q->b

#define XX					\
    struct Particle *q;				\
    q = malloc(sizeof(*q));			\
    if (q == NULL)				\
	abort()

#define YY return q;

static double **
phi_ini(void)
{
    int n, i, j;
    double **q;

    n = particle_number_of_materials;
    q = malloc(n * sizeof(*q));
    for (i = 0; i < n; i++)
        q[i] = malloc(n * sizeof(*q));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            q[i][j] = 0.0;
    return q;
}

int
particle_fin(struct Particle *q)
{
    int i;

    for (i = 0; i < particle_number_of_materials; i++) {
        free(q->phi[i]);
    }
    free(q->phi);
    free(q);
    return 0;
}

struct Particle *
particle_real(double position[2], double velocity[2], double density,
              double pressure, double temperature,
              struct Material *material)
{
    XX;

    particle_ID_max++;

    B(bd, 0);
    B(bd_type, 0);
    B(ID, particle_ID_max);
    B(mtl, material);
    C(eta, mtl->eta);
    C(zeta, mtl->zeta);
    B(R[X], position[X]);
    B(R[Y], position[Y]);
    B(rho, density);
    B(p, pressure);
    B(T, temperature);
    B(Cs, get_Cs(q->mtl, q->p, q->rho));
    B(U[X], velocity[X]);
    B(U[Y], velocity[Y]);
    C(U_I[X], U[X]);
    C(U_I[Y], U[Y]);
    B(m, 0.0);
    B(V, 0.0);
    C(R_I[X], R[X]);
    C(R_I[Y], R[Y]);
    C(P_I[X], P[X]);
    C(P_I[Y], P[Y]);
    C(rho_I, rho);
    C(P_n[X], P[X]);
    C(P_n[Y], P[Y]);
    C(U_n[X], U[X]);
    C(U_n[Y], U[Y]);
    C(rho_n, rho);
    B(phi, phi_ini());

    YY;
}

struct Particle *
particle_image(struct Particle *s)
{
    XX;

    B(bd, 1);
    B(bd_type, 1);
    B(ID, 0);
    B(rl_prtl, s);
    A(mtl);
    C(eta, mtl->eta);
    C(zeta, mtl->zeta);
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
    C(rho_I, rho);
    A(P_n[X]);
    A(P_n[Y]);
    A(U_n[X]);
    A(U_n[Y]);
    A(rho_n);
    B(phi, phi_ini());

    YY;
}

struct Particle *
particle_mirror(struct Particle *s, struct Material *material)
{
    XX;

    B(bd, 1);
    B(bd_type, 0);
    B(ID, 0);
    B(rl_prtl, s);
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
    C(rho_I, rho);
    A(P_n[X]);
    A(P_n[Y]);
    A(U_n[X]);
    A(U_n[Y]);
    A(rho_n);
    B(phi, phi_ini());

    YY;
}

int
particle_copy(struct Particle *q, struct Particle *s, int type)
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
    if (type == 1) {
        A(del_phi[X]);
        A(del_phi[Y]);
        for (i = 0; i < particle_number_of_materials; i++) {
            for (j = 0; j < particle_number_of_materials; j++) {
                A(phi[i][j]);
            }
        }
    }
    if (type == 0) {
        q->phi[0][0] = 0;
        for (i = 1; i < particle_number_of_materials; i++)
            q->phi[0][0] += s->phi[i][i];
    }
    return 0;
}
