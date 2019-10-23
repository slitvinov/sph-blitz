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

int
SymmetricInverse3x3(double *M)
{
    enum { XX, XY, XZ, YX, YY, YZ, ZX, ZY, ZZ };
    double z1, z2, z3, z4, z5, z6, z7, z8, z9, z10, z11, z12;
    double z13, z14, z15, z16;
    double m00, m01, m02, m11, m12, m22;

    m00 = M[XX];
    m01 = M[XY];
    m02 = M[XZ];
    m11 = M[YY];
    m12 = M[YZ];
    m22 = M[ZZ];

    z1 = m01 * m01;
    z2 = m01 * m02;
    z3 = m02 * m02;
    z4 = m00 * m11;
    z5 = -m02 * m11;
    z6 = -m00 * m12;
    z7 = m01 * m12;
    z8 = m02 * m12;
    z9 = m12 * m12;
    z10 = m00 * m22;
    z11 = -m01 * m22;
    z12 = m11 * m22;
    z13 = 2. * m12 * z2;
    z14 = m22 * z4;
    z1 = -z1;
    z15 = m22 * z1;
    z3 = -z3;
    z16 = m11 * z3;
    z2 = z2 + z6;
    z5 = z5 + z7;
    z6 = z11 + z8;
    z7 = -z9;
    z8 = m00 * z7;
    z3 = z10 + z3;
    z7 = z12 + z7;
    z8 = z13 + z14 + z15 + z16 + z8;
    if (fabs(z8) < 1.0e-2)
        return 0;
    z1 = z1 + z4;
    z4 = 1. / z8;
    z2 = z2 * z4;
    z5 = z4 * z5;
    z6 = z4 * z6;
    z3 = z3 * z4;
    z7 = z4 * z7;
    z1 = z1 * z4;

    M[XX] = z7;
    M[YY] = z3;
    M[ZZ] = z1;
    M[YZ] = M[ZY] = z2;
    M[XZ] = M[ZX] = z5;
    M[XY] = M[YX] = z6;
    return 1;
}
