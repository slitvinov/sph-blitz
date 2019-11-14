#include <math.h>
#include "glbfunc.h"
double
AMAX1(double a, double b)
{
    if (a > b)
        return a;
    return b;
}

double
AMIN1(double a, double b)
{
    if (a < b)
        return a;
    return b;
}
