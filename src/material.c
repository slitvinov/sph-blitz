#include <stdio.h>
#include <math.h>
#include "sph/material.h"

static double
AMAX1(double a, double b)
{
    return a > b ? a : b;
}

void
Set_nu(struct Material *q)
{
    q->nu = AMAX1(q->eta, q->zeta) / q->rho0;
}

void
Set_b0(struct Material *q, double sound)
{
    q->b0 = q->a0 * sound / q->gamma;
}

double
get_p(struct Material *q, double rho)
{
    return q->b0 * pow(rho / q->rho0, q->gamma);
}

double
get_rho(struct Material *q, double p)
{
    return q->rho0 * pow(p / q->b0, 1.0 / q->gamma);
}

double
get_Cs(struct Material *q, double p, double rho)
{
    return sqrt(q->gamma * p / rho);
}
