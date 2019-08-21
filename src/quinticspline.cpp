#include <tgmath.h>
#include "quinticspline.h"

static const double pi = 3.141592653589793;
QuinticSpline::QuinticSpline(double _smoothingLength)
{
    double norm = 63.0 / 478.0 / pi;
    smoothingLength = _smoothingLength;
    reciprocH = 1.0 / smoothingLength;
    factorW     = norm * pow(reciprocH, 2);
    factorGradW = 15.0*norm * pow(reciprocH, 3);
    factorLapW = 15.0*12.0*norm * pow(reciprocH, 4);
}

double w(QuinticSpline *q, double distance)
{
    double normedDist = 3.0*distance * q->reciprocH;
    double ss3, ss2, ss1;

    ss3 = (3.0 - normedDist);
    ss2 = (2.0 - normedDist);
    ss1 = (1.0 - normedDist);
    if (normedDist < 1.0)
	{
	    return q->factorW * (ss3*ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1*ss1*ss1);
	}
    else if (normedDist < 2.0)
	{
	    return q->factorW * (ss3*ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2*ss2);
	}
    else if (normedDist < 3.0)
	{
	    return q->factorW * ss3*ss3*ss3*ss3*ss3;
	}
    else
	{
	    return 0.0;
	}
}
//----------------------------------------------------------------------------------------
//		Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double F(QuinticSpline *q, double distance)
{
    double normedDist = 3.0*distance * q->reciprocH;
    double ss3 = (3.0 - normedDist);
    double ss2 = (2.0 - normedDist);
    double ss1 = (1.0 - normedDist);
    if (normedDist < 1.0)
	{
	    return q->factorGradW * (ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1*ss1);
	}
    else if (normedDist < 2.0)
	{
	    return q->factorGradW * (ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2);
	}
    else if (normedDist < 3.0)
	{
	    return q->factorGradW * ss3*ss3*ss3*ss3;
	}
    else
	{
	    return 0.0;
	}
}

double LapW(QuinticSpline *q, double distance)
{
    double normedDist = 3.0*distance * reciprocH;
    double ss3, ss2, ss1;

    ss3 = (3.0 - normedDist);
    ss2 = (2.0 - normedDist);
    ss1 = (1.0 - normedDist);

    if (normedDist < 1.0)
	{
	    return factorLapW * (ss3*ss3*ss3 - 6.0*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1);
	}
    else if (normedDist < 2.0)
	{
	    return factorLapW * (ss3*ss3*ss3 - 6.0*ss2*ss2*ss2);
	}
    else if (normedDist < 3.0)
	{
	    return factorLapW * ss3*ss3*ss3;
	}
    else
	{
	    return 0.0;
	}
}
