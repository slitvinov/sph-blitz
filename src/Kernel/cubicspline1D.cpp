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
const double pi = 3.141592653589793238462643383279502884197;

/// Cubic spline kernel (see Liu eq. (3.6)
Cubicspline1D::Cubicspline1D(const double supportlength)
  : Kernel(supportlength),
    norm( 10.0 / (7.0*pi)  / (supportlength*supportlength) ) ,
    factorGradW( 2.0*norm /supportlength )
{
  // initialize the auxiliary factors

 }
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
//----------------------------------------------------------------------------------------
double Cubicspline1D::w(const double distance) const
{
  const double R= 2.0 * distance/ supportlength;
  if(R>2.0)
    {
      //support of 4h, everything beyond is zero
      return 0.0;
    }
  else if(R>1.0) {
    const double s2 = 2.0 - R;
    return norm * s2 * s2 * s2 ;
  }
  else
    {
      const double s2 = 2.0 - R;
      const double s1 = 1.0 - R;
      return norm * ( s2*s2*s2 - 4.0*s1*s1*s1 );
    };
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Morris, Fox and Zhu (1997)
// but used a tripled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d Cubicspline1D::gradW(const double distance, const Vec2d& distanceVector) const
{  Vec2d GradW;

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
  double R= 2.0*distance/ supportlength; // 
  if (R>2.0) {
    //support of 4h, everything beyond is zero    
    return 0.0;
  }
  else if(R>1.0 ) {
    const double s2 = 2.0 - R;
    return  factorGradW * ( 3.0 * s2*s2);
  } else  {
    const double s1 = 1.0 - R;
    const double s2 = 2.0 - R;
    return  -factorGradW * ( 12.0 * s1*s1 - 3.0 * s2 * s2 );
  }
}

//----------------------------------------------------------------------------------------
//					Calculates the kernel Laplacian. 
//----------------------------------------------------------------------------------------
double Cubicspline1D::LapW(const double distance) const
{
  std::cerr << "LapW of Cubicspline1D shell not be called" << '\n';
  exit(-1);
}

