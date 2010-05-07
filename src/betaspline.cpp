// bskernel.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

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
#include "betaspline.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
BetaSpline::BetaSpline(double smoothingLength)
    : Kernel(smoothingLength)
{
    // initialize the auxiliary factors
    reciprocH = 1.0 / smoothingLength;
    
    //normalize to 1.0
	norm = 40.0 / 7.0 / pi;
      
    factorW     = norm * pow(reciprocH, 2);
    factorGradW = - 6.0 * norm * pow(reciprocH, 3);
    
    // a comment on the gradW sign:
    // In Speith (3.21) gradW has a minus in front!
    // This is the one before the 6.0 * ...
}
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
// We take this from Monaghan & Lattenzio (1985)
// but used a doubled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
double BetaSpline::w(double distance) const
{
    // dist/smoothingLength is often needed
    double normedDist = distance * reciprocH;

    // the beta-spline is composed of three functions, so we must determine, were we are
    if (normedDist < 0.5) 
    // we are in the inner region of the kernel
    {
        return factorW * (6.0 * normedDist * normedDist * normedDist - 
                            6.0 * normedDist * normedDist + 1.0);
    }
    else if (normedDist < 1.0)
    // we are in the outer region of the kernel (not outside!)
    {
        double aux = 1.0 - normedDist;
        return factorW * ( 2.0 * aux * aux * aux );
    }
    else
    // dist is bigger then the kernel.
    {
        return 0.0;
    }
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Monaghan & Lattenzio (1985)
// but used a doubled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d BetaSpline::gradW(double distance, const Vec2d& distanceVector) const
{
    // dist/smoothingLength is often needed
    double normedDist = distance * reciprocH;
    // the beta-spline is composed of three functions (so the derivate is also), 
    // we must determine, were we are
    if (normedDist < 0.5) 
    // we are in the inner region of the kernel
    {
        return distanceVector * (factorGradW * (3.0 * normedDist * reciprocH - 2.0 * reciprocH));
    }
    else if (normedDist < 1.0)
    // we are in the outer region of the kernel (not outside!)
    {
        return distanceVector * (- factorGradW * (1.0 / distance - 2.0 * reciprocH + normedDist * reciprocH));
    }
    else
    // dist is bigger then the kernel.
    {
		return Vec2d();
    }
}
//----------------------------------------------------------------------------------------
//				Calculates the kernel derivation to distance
//----------------------------------------------------------------------------------------
double BetaSpline::F(double distance) const
{
    // dist/smoothingLength is often needed
    double normedDist = distance * reciprocH;
    // the beta-spline is composed of three functions (so the derivate is also), 
    // we must determine, were we are
    if (normedDist < 0.5) 
    // we are in the inner region of the kernel
    {
        return (factorGradW * (3.0 * normedDist * reciprocH - 2.0 * reciprocH));
    }
    else if (normedDist < 1.0)
    // we are in the outer region of the kernel (not outside!)
    {
        return (- factorGradW * (1.0 / distance - 2.0 * reciprocH + normedDist * reciprocH));
    }
    else
    // dist is bigger then the kernel.
    {
		return 0.0;
    }
}



