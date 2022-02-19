#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sph/err.h"
#include "sph/force.h"
#include "sph/ini.h"
#include "sph/pair.h"
#include "sph/list.h"
#include "sph/macro.h"
#include "sph/material.h"
#include "sph/particle.h"
#include "sph/kernel.h"
#include "sph/vv.h"

enum { X, Y };
static double
AMAX1(double a, double b)
{
    return a > b ? a : b;
}

static double
AMIN1(double a, double b)
{
    return a < b ? a : b;
}

void
UpdatePair(struct Ini *q, struct Kernel *kernel)
{
    struct ListNode *p;
    struct Pair *pair;

    ILOOP_P(pair, q->pair_list) {
        RenewPair(pair, kernel);
    }
}

void
UpdatePhaseGradient(struct Ini *q, struct Ini *boundary)
{
    struct ListNode *p;
    struct Pair *pair;

    Zero_PhaseGradient(q, boundary);
    ILOOP_P(pair, q->pair_list) {
        SummationPhaseGradient(pair);
    }
}

void
UpdateDensity(struct Ini *q)
{
    struct ListNode *p;
    struct Pair *pair;

    Zero_density(q);
    ILOOP_P(pair, q->pair_list) {
        SummationDensity(pair);
    }
    UpdateState(q);
}

void
UpdateChangeRate(struct Ini *q)
{
    struct ListNode *p;
    struct Pair *pair;

    ZeroChangeRate(q);
    ILOOP_P(pair, q->pair_list) {
        UpdateForces(pair);
    }
    AddGravity(q);
}

void
UpdateRandom(struct Ini *q, double sqrtdt)
{
    struct ListNode *p;
    struct Pair *pair;

    Zero_Random(q);
    ILOOP_P(pair, q->pair_list) {
        RandomForces(pair, sqrtdt);
    }
}

void
ZeroChangeRate(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->dedt = 0.0;
        prtl->drhodt = 0.0;
        prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
        prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void
Zero_density(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->rho = 0.0;
    }
}

void
Zero_PhaseGradient(struct Ini *q, struct Ini *boundary)
{
    struct ListNode *p;
    struct Particle *prtl;
    struct List *blist;

    blist = boundary_list(boundary);

    LOOP_P(prtl, q->particle_list) {
        prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    LOOP_P(prtl, blist) {
        prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
}

void
Zero_Random(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void
AddGravity(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->dUdt[X] += q->gravity[X];
        prtl->dUdt[Y] += q->gravity[Y];
    }
}

void
UpdateState(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->p = get_p(prtl->mtl, prtl->rho);
    }
}

void
UpdatePahseMatrix(struct Ini *q, struct Ini *boundary)
{
    struct ListNode *p;
    struct Particle *prtl;
    int
     i, j, number_of_materials;
    struct List *blist;

    blist = boundary_list(boundary);
    number_of_materials = q->number_of_materials;
    LOOP_P(prtl, q->particle_list) {
        for (i = 0; i < number_of_materials; i++)
            for (j = 0; j < number_of_materials; j++) {
                if (i != j)
                    prtl->phi[i][j] = prtl->phi[i][j];
            }
    }
    LOOP_P(prtl, blist) {
        for (i = 0; i < number_of_materials; i++)
            for (j = 0; j < number_of_materials; j++) {
                if (i != j)
                    prtl->phi[i][j] = prtl->phi[i][j];
            }
    }
}

void
UpdateSurfaceStress(struct Ini *q, struct Ini *boundary)
{
    double
     epsilon = 1.0e-30;
    double
     interm0, interm1, interm2;
    struct Particle *prtl;
    struct ListNode *p;
    struct List *blist;

    blist = boundary_list(boundary);

    LOOP_P(prtl, q->particle_list) {
        interm0 = 1.0 / (vv_abs(prtl->del_phi) + epsilon);
        interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
        interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
        prtl->del_phi[0] = interm1 * interm0;
        prtl->del_phi[1] = interm2 * interm0;
    }
    LOOP_P(prtl, blist) {
        interm0 = vv_abs(prtl->del_phi) + epsilon;
        interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
        interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
        prtl->del_phi[0] = interm1 / interm0;
        prtl->del_phi[1] = interm2 / interm0;
    }
}

double
GetTimestep(struct Ini *q)
{
    struct Particle *prtl;
    struct ListNode *p;
    double
     Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
    double
     dt;

    LOOP_P(prtl, q->particle_list) {
        Cs_max = AMAX1(Cs_max, prtl->Cs);
        V_max = AMAX1(V_max, vv_abs(prtl->U));
        rho_min = AMIN1(rho_min, prtl->rho);
        rho_max = AMAX1(rho_max, prtl->rho);
    }
    dt = AMIN1(sqrt(0.5 * (rho_min + rho_max)) * q->dt_surf, q->dt_g_vis);
    return 0.25 * AMIN1(dt, q->delta / (Cs_max + V_max));
}

void
Predictor_summation(struct Ini *q, double dt)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->R_I[X] = prtl->R[X];
        prtl->R_I[Y] = prtl->R[Y];
        prtl->U[X] += prtl->_dU[X];
        prtl->U[Y] += prtl->_dU[Y];
        prtl->U_I[X] = prtl->U[X];
        prtl->U_I[Y] = prtl->U[Y];
        prtl->R[X] = prtl->R[X] + prtl->U[X] * dt;
        prtl->R[Y] = prtl->R[Y] + prtl->U[Y] * dt;
        prtl->U[X] = prtl->U[X] + prtl->dUdt[X] * dt;
        prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y] * dt;
        prtl->R[X] = (prtl->R[X] + prtl->R_I[X]) * 0.5;
        prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y]) * 0.5;
        prtl->U[X] = (prtl->U[X] + prtl->U_I[X]) * 0.5;
        prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y]) * 0.5;
    }
}

void
Corrector_summation(struct Ini *q, double dt)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->U[X] += prtl->_dU[X];
        prtl->U[Y] += prtl->_dU[Y];
        prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
        prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
        prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
        prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
    }
}

void
RandomEffects(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->U[X] = prtl->U[X] + prtl->_dU[X];
        prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
    }
}

void
hydro_fin(struct Ini *q)
{
    int i;
    struct ListNode *p;
    struct Pair *pair;
    struct Particle *prtl;

    for (i = 0; i < q->number_of_materials; i++)
        free(q->forces[i]);
    free(q->forces);
    free(q->materials);

    ILOOP_P(pair, q->pair_list) {
        pair_fin(pair);
    }
    list_fin(q->pair_list);

    LOOP_P(prtl, q->particle_list) {
        particle_fin(prtl);
    }
    list_fin(q->particle_list);
}
