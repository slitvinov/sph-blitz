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

#include <math.h>

//local includes
#include "glbcls.h"
#include "glbfunc.h"
#include "Kernel/cubicspline1D.h"

using namespace std;

//----------------------------------------------------------------------------------------
//										constructor
//----------------------------------------------------------------------------------------

/*

QuinticSpline::QuinticSpline(const double smoothingLength)
  : Kernel(smoothingLength), 
    norm(/*63.0 / 478.0 / pi  360)
{
  // initialize the auxiliary factors
    reciprocH = 1.0 / smoothingLength;
      
      factorW     = norm * pow(reciprocH,1/* 2 );
	factorGradW = 15.0*norm * pow(reciprocH,2/* 3 /);
	  factorLapW = 15.0*12.0*norm * pow(reciprocH,3/* 4 /);

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





*/
Cubicspline1D::Cubicspline1D(const double smoothingLength)
  : Kernel(smoothingLength), 
    norm(1)
{
  // initialize the auxiliary factors


  h =smoothingLength/2;//factor two as the use ofsmoothinglength within this program is not consistent with its actula definition
	double alphaD=1/h; //coefficient for cubic spline kernel in 1D (see Liu eq(3.6), page 64)

 }
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
//----------------------------------------------------------------------------------------
double Cubicspline1D::w(const double distance) const
{
	double alphaD=1/h; //coefficient for cubic spline kernel in 1D (see Liu eq(3.6), page 64)
	double R= distance/h;
	double W;
if(R>2)//support of 4h, everything beyond is zero
	{
		W=0;
	}
	else if(R<1)
	{
		W=(double)2/3-pow(R,2)+0.5*pow(R,3); //attention: the "^"symbol does NOT mean "exponent"!!!
	}
	else
	{
		W=(double)1/6*pow((2-R),3);
	};
	W=W*alphaD;
	return W;
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Morris, Fox and Zhu (1997)
// but used a tripled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d Cubicspline1D::gradW(const double distance, const Vec2d& distanceVector) const
{
  Vec2d GradW;

double dW;
	double alphaD=1/h; //coefficient for cubic spline kernel in 1D (see Liu eq(3.6), page 64)
	double R= distance/h; //nondimensional distance
	if(R>2)//support of 4h, everything beyond is zero
	{
		dW=0;
	}
	else if(R<1)
	{
		dW=-2*R+1.5*pow(R,2);
	}
	else
	{
		dW=-((double)1)/2*pow((2-R),2);
	};
	if (R!=0)

	dW=dW*alphaD*distanceVector[0]/distance/h; //deltaX/r for the sign (-->*(+/-1) )!!!, h because of d/dr=d/dR*dR/dr (dR/dr=1/h)-->substituted by distance vector

	else
        {
	  dW=0;
	}
	GradW[0]=dW;
	GradW[1]=0;
	return GradW;
}
//----------------------------------------------------------------------------------------
//		Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double Cubicspline1D::F(const double distance) const
{
  /*  // dist/smoothingLength is often needed
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
	}*/
}
//----------------------------------------------------------------------------------------
//					Calculates the kernel Laplacian. 
//----------------------------------------------------------------------------------------
double Cubicspline1D::LapW(const double distance) const
{/*
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
    */
}

