///\file harmonic.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      A concrete kernel class
//		see Monaghan & Lattanzio (1985).
//		Most often used kernel.
//		bskernel.cpp
//----------------------------------------------------------------------------------------

//local includes
#include "Kernel/harmonic.h"
const double pi = 3.141592653589793238462643383279502884197;

/// Cubic spline kernel (see Liu eq. (3.6)
Harmonic::Harmonic(const double supportlength, const double harmonic_n)
  : Kernel(supportlength),
    norm( 10.0 / (7.0*pi)/*1.0/3.0*/  / (supportlength/**/*supportlength/**/) ) ,
    factorGradW( 2.0*norm /supportlength )
{
  // initialize the auxiliary factors

 }
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
//----------------------------------------------------------------------------------------
double Harmonic::w(const double distance) const
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
Vec2d Harmonic::gradW(const double distance, const Vec2d& distanceVector) const
{  
  return Harmonic::F(distance)*distanceVector;
}
//----------------------------------------------------------------------------------------
//		Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double Harmonic::F(const double distance) const
{
  double R= 2.0*distance/ supportlength; // 
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

void Harmonic::show_information() const {
  std::cerr << "(kernel) Harmonic\n";
}
