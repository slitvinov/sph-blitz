#include "sph/material.h"
#include <math.h>
#include <stdio.h>

double get_p(struct Material *q, double rho) {
  return q->b0 * pow(rho / q->rho0, q->gamma);
}

double get_Cs(struct Material *q, double p, double rho) {
  return sqrt(q->gamma * p / rho);
}
