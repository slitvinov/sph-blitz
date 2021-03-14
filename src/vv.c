#include "sph/vv.h"
#include <math.h>

enum { X, Y };

double
vv_abs(double v[2])
{
    return sqrt(v[X] * v[X] + v[Y] * v[Y]);
}

double
vv_distance(double a[2], double b[2])
{
    double x, y;

    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return sqrt(x * x + y * y);
}

double
vv_sq_distance(double a[2], double b[2])
{
    double x, y;

    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return x * x + y * y;
}

double
vv_sqdiff(double v[2])
{
    return v[X] * v[X] - v[Y] * v[Y];
}
