///\file quinticspline.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      A concrete kernel class
//		see Monaghan & Lattanzio (1985).
//		Most often used kernel.
//		bskernel.cpp
//----------------------------------------------------------------------------------------

// ***** system includes *****
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

//local includes
#include "glbcls.h"
#include "glbfunc.h"

using namespace std;

//----------------------------------------------------------------------------------------
//										constructor
//----------------------------------------------------------------------------------------
QuinticSpline::QuinticSpline(const double smoothingLength)
  : Kernel(smoothingLength), 
    norm(63.0 / 478.0 / pi)
{
  // initialize the auxiliary factors
    reciprocH = 1.0 / smoothingLength;
      
    factorW     = norm * pow(reciprocH, 2);
    factorGradW = 15.0*norm * pow(reciprocH, 3);
    factorLapW = 15.0*12.0*norm * pow(reciprocH, 4);

    // a comment on the gradW sign:
    // The gradW has a minus in front!
}
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
// We take this from Morris, Fox and Zhu (1997)
// but used a tripled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
double QuinticSpline::w(const double distance) const
{
    // dist/smoothingLength is often needed
    double normedDist = 3.0*distance * reciprocH;
	double ss3, ss2, ss1;

	ss3 = (3.0 - normedDist);
	ss2 = (2.0 - normedDist);
	ss1 = (1.0 - normedDist);

    // the quintic-spline is composed of four functions, so we must determine, were we are
    if (normedDist < 1.0) 
    // we are in the inner region of the kernel
    {
        return factorW * (ss3*ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1*ss1*ss1);
    }
    else if (normedDist < 2.0)
    // we are in the middle region of the kernel (not outside!)
    {
        return factorW * (ss3*ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2*ss2);
    }
    else if (normedDist < 3.0)
    // we are in the outer region of the kernel (not outside!)
    {
        return factorW * ss3*ss3*ss3*ss3*ss3;
    }
    else
    // distance is bigger than the kernel.
    {
        return 0.0;
    }
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Morris, Fox and Zhu (1997)
// but used a tripled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d QuinticSpline::gradW(const double distance, const Vec2d& distanceVector) const
{
    // dist/smoothingLength is often needed
    double normedDist = 3.0*distance * reciprocH;
	double ss3, ss2, ss1;

	ss3 = (3.0 - normedDist);
	ss2 = (2.0 - normedDist);
	ss1 = (1.0 - normedDist);

    // the quintic-spline is composed of four functions, so we must determine, were we are
    if (normedDist < 1.0) 
    // we are in the inner region of the kernel
    {
        return distanceVector * factorGradW * (ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1*ss1);
    }
    else if (normedDist < 2.0)
    // we are in the middle region of the kernel (not outside!)
    {
        return distanceVector * factorGradW * (ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2);
    }
    else if (normedDist < 3.0)
    // we are in the outer region of the kernel (not outside!)
    {
        return distanceVector * factorGradW * ss3*ss3*ss3*ss3;
    }
    else
    // dist is bigger then the kernel.
    {
        return Vec2d();
    }
}
//----------------------------------------------------------------------------------------
//		Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double QuinticSpline::F(const double distance) const
{
    // dist/smoothingLength is often needed
    const double normedDist = 3.0*distance * reciprocH;
    
    const double ss3 = (3.0 - normedDist);
    const double ss2 = (2.0 - normedDist);
    const double ss1 = (1.0 - normedDist);

    // the quintic-spline is composed of four functions, so we must determine, were we are
    if (normedDist < 1.0) 
    // we are in the inner region of the kernel
    {
        return factorGradW * (ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1*ss1);
    }
    else if (normedDist < 2.0)
    // we are in the middle region of the kernel (not outside!)
    {
        return factorGradW * (ss3*ss3*ss3*ss3 - 6.0*ss2*ss2*ss2*ss2);
    }
    else if (normedDist < 3.0)
    // we are in the outer region of the kernel (not outside!)
    {
        return factorGradW * ss3*ss3*ss3*ss3;
    }
    else
    //the distiance is bigger than the kernel.
    {
        return 0.0;
    }
}
//----------------------------------------------------------------------------------------
//					Calculates the kernel Laplacian. 
//----------------------------------------------------------------------------------------
double QuinticSpline::LapW(const double distance) const
{
    // dist/smoothingLength is often needed
    double normedDist = 3.0*distance * reciprocH;
	double ss3, ss2, ss1;

	ss3 = (3.0 - normedDist);
	ss2 = (2.0 - normedDist);
	ss1 = (1.0 - normedDist);

    // the quintic-spline is composed of four functions, so we must determine, were we are
    if (normedDist < 1.0) 
    // we are in the inner region of the kernel
    {
        return factorLapW * (ss3*ss3*ss3 - 6.0*ss2*ss2*ss2 + 15.0*ss1*ss1*ss1);
    }
    else if (normedDist < 2.0)
    // we are in the middle region of the kernel (not outside!)
    {
        return factorLapW * (ss3*ss3*ss3 - 6.0*ss2*ss2*ss2);
    }
    else if (normedDist < 3.0)
    // we are in the outer region of the kernel (not outside!)
    {
        return factorLapW * ss3*ss3*ss3;
    }
    else
    //the distiance is bigger than the kernel.
    {
        return 0.0;
    }

}




