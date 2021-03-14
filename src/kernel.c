#include <math.h>
#include <stdlib.h>
#include "sph/err.h"
#include "sph/kernel.h"

struct Kernel {
    double reciprocH;
    double factorW;
    double factorGradW;
    double smoothingLength;
};

static double pi = 3.141592653589793;
struct Kernel *
kernel_ini(double smoothingLength)
{
    double norm;
    struct Kernel *q;

    q = malloc(sizeof(*q));
    if (q == NULL) {
        ABORT(("fail to alloc"));
        return q;
    }

    norm = 63.0 / 478.0 / pi;
    q->smoothingLength = smoothingLength;
    q->reciprocH = 1.0 / smoothingLength;
    q->factorW = norm * pow(q->reciprocH, 2);
    q->factorGradW = 15.0 * norm * pow(q->reciprocH, 3);
    return q;
}

int
kernel_fin(struct Kernel *q)
{
    free(q);
    return 0;
}

double
w(struct Kernel *q, double r)
{
    double d = 3.0 * r * q->reciprocH;
    double a, b, c;

    a = (3.0 - d);
    b = (2.0 - d);
    c = (1.0 - d);
    if (d < 1.0) {
        return q->factorW * (a * a * a * a * a -
                             6.0 * b * b * b * b * b +
                             15.0 * c * c * c * c * c);
    } else if (d < 2.0) {
        return q->factorW * (a * a * a * a * a - 6.0 * b * b * b * b * b);
    } else if (d < 3.0) {
        return q->factorW * a * a * a * a * a;
    } else {
        return 0.0;
    }
}

double
F(struct Kernel *q, double r)
{
    double a, b, c, d;

    d = 3.0 * r * q->reciprocH;
    a = (3.0 - d);
    b = (2.0 - d);
    c = (1.0 - d);

    if (d < 1.0) {
        return q->factorGradW * (a * a * a * a - 6.0 * b * b * b * b +
                                 15.0 * c * c * c * c);
    } else if (d < 2.0) {
        return q->factorGradW * (a * a * a * a - 6.0 * b * b * b * b);
    } else if (d < 3.0) {
        return q->factorGradW * a * a * a * a;
    } else {
        return 0.0;
    }
}
