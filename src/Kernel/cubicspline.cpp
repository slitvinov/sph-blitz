///\file cubicspline.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      A concrete kernel class
//		see Monaghan & Lattanzio (1985).
//		Most often used kernel.
//		bskernel.cpp
//----------------------------------------------------------------------------------------

//local includes
#include "src/Kernel/cubicspline.h"
#include <boost/math/constants/constants.hpp>


using namespace std;
const double pi = boost::math::constants::pi<double>();

/// Cubic spline kernel (see Liu eq. (3.6)
CubicSpline::CubicSpline(const double supportlength)
  : Kernel(supportlength),
    norm( 10.0 / (7.0*pi)/*1.0/3.0*/  / (supportlength/**/*supportlength/**/) ) ,
    factorGradW( 2.0*norm /supportlength )
{
  // initialize the auxiliary factors

 }
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
//----------------------------------------------------------------------------------------
double CubicSpline::w(const double distance) const
{
  const double R= 2.0 * distance/ supportlength;
  if(R>2.0)
    {
      //support of 4h (supportlength =2h, h=0.015), everything beyond is zero
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
Vec2d CubicSpline::gradW(const double distance, const Vec2d& distanceVector) const
{  
  return CubicSpline::F(distance)*distanceVector;
}
//----------------------------------------------------------------------------------------
//		Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double CubicSpline::F(const double distance) const
{
  double R= 2.0*distance/ supportlength; 
  if (R>2.0) {
    //support of 4h, everything beyond is zero    
    return 0.0;
  }
  else if(R>1.0 ) {
    const double s2 = 2.0 - R;
    return/*minus inserted!!! */ - factorGradW * ( 3.0 * s2*s2);
  } else  {
    const double s1 = 1.0 - R;
    const double s2 = 2.0 - R;
    return /* -*/factorGradW * ( 12.0 * s1*s1 - 3.0 * s2 * s2 );
  }
}

void CubicSpline::show_information() const {
  std::cerr << "(kernel) CubicSpline\n";
}
