#include "vv.h"
#include <tgmath.h>

enum { X, Y };

double
vv_abs(double v[2])
{
    return sqrt(v[X] * v[X] + v[Y] * v[Y]);
}

/// Return the distance of two points given as vectors
double
vv_distance(double a[2], double b[2])
{
    double x, y;

    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return sqrt(x * x + y * y);
}

/// Return the distance of two points given as vectors
double
vv_sq_distance(double a[2], double b[2])
{
    double x, y;

    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return x * x + y * y;
}

/// Return the square difference of the vector values
double
vv_sqdiff(double v[2])
{
    return v[X] * v[X] - v[Y] * v[Y];
}

/// Return the square sum of the vector values
double
vv_sq(double v[2])
{
    return v[X] * v[X] + v[Y] * v[Y];
}
