#include <tgmath.h>
#include "kernel.h"

static const double pi = 3.141592653589793;
int
kernel_ini(double smoothingLength, struct Kernel *q)
{
    double norm = 63.0 / 478.0 / pi;

    q->smoothingLength = smoothingLength;
    q->reciprocH = 1.0 / smoothingLength;
    q->factorW = norm * pow(q->reciprocH, 2);
    q->factorGradW = 15.0 * norm * pow(q->reciprocH, 3);
    return 0;
}

double
w(struct Kernel *q, double distance)
{
    double normedDist = 3.0 * distance * q->reciprocH;
    double ss3, ss2, ss1;

    ss3 = (3.0 - normedDist);
    ss2 = (2.0 - normedDist);
    ss1 = (1.0 - normedDist);
    if (normedDist < 1.0) {
	return q->factorW * (ss3 * ss3 * ss3 * ss3 * ss3 -
			     6.0 * ss2 * ss2 * ss2 * ss2 * ss2 +
			     15.0 * ss1 * ss1 * ss1 * ss1 * ss1);
    } else if (normedDist < 2.0) {
	return q->factorW * (ss3 * ss3 * ss3 * ss3 * ss3 -
			     6.0 * ss2 * ss2 * ss2 * ss2 * ss2);
    } else if (normedDist < 3.0) {
	return q->factorW * ss3 * ss3 * ss3 * ss3 * ss3;
    } else {
	return 0.0;
    }
}

//----------------------------------------------------------------------------------------
//              Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double
F(struct Kernel *q, double distance)
{
    double normedDist = 3.0 * distance * q->reciprocH;
    double ss3 = (3.0 - normedDist);
    double ss2 = (2.0 - normedDist);
    double ss1 = (1.0 - normedDist);

    if (normedDist < 1.0) {
	return q->factorGradW * (ss3 * ss3 * ss3 * ss3 -
				 6.0 * ss2 * ss2 * ss2 * ss2 +
				 15.0 * ss1 * ss1 * ss1 * ss1);
    } else if (normedDist < 2.0) {
	return q->factorGradW * (ss3 * ss3 * ss3 * ss3 -
				 6.0 * ss2 * ss2 * ss2 * ss2);
    } else if (normedDist < 3.0) {
	return q->factorGradW * ss3 * ss3 * ss3 * ss3;
    } else {
	return 0.0;
    }
}
