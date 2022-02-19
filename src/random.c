#include <math.h>
#include <stdlib.h>
#include "sph/random.h"

void
random_gaussian(double *y1, double *y2)
{
    double x1, x2, w;

    do {
        x1 = (double) rand() / RAND_MAX;
        x2 = (double) rand() / RAND_MAX;
        x1 = 2.0 * x1 - 1.0;
        x2 = 2.0 * x2 - 1.0;
        w = x1 * x1 + x2 * x2;
    } while (w >= 1.0 || w == 0.0);
    w = sqrt((-2.0 * log(w)) / w);
    *y1 = x1 * w;
    *y2 = x2 * w;
}
