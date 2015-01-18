///\file harmonic.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
///\author changes by: Sergey Litvinov <slitvinov@gmail.com>

//----------------------------------------------------------------------------------------
//      A concrete kernel class
//		see Monaghan & Lattanzio (1985).
//		Most often used kernel.
//		bskernel.cpp
//----------------------------------------------------------------------------------------

//local includes
#include "src/Kernel/harmonic.h"
#include <boost/math/constants/constants.hpp>
const double pi = boost::math::constants::pi<double>();

/// Harmonic kernel 
/// (see J. Comput. Phys., Academic Press Inc Elsevier Science, 2008, 227, 8523-8540)
Harmonic::Harmonic(const double supportlength, const double harmonic_n)
  : Kernel(supportlength),
    n(harmonic_n) {
  
  /// check the range of the parameter
  assert(n<6.1);
  assert(n>1.9);
  assert(supportlength>0.0);
  
  /// get normalization parameters for 2D using polynomoms
  /// J. Comput. Phys., 2008, 227, 8523-8540
  const double a0 = 7.332473e-2;
  const double a1 = 1.196425e-1;
  const double a2 = 3.319287e-3;
  const double a3 = -5.511885e-4;
  const double a4 = 4.828286e-5;
  const double a5 = -1.733766e-6;

  const double Kn = a5*pow(n, 5.0) + a4*pow(n, 4.0) +
    a3*pow(n, 3.0) + a2*pow(n, 2.0) + a1*n + a0;
  std::cerr << "Kn = " << Kn << '\n';
  norm = 2.0*Kn/supportlength;
  factorGradW = norm / supportlength;
}

//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
//----------------------------------------------------------------------------------------
double Harmonic::w(const double distance) const {
  const double R= 2.0 * distance/ supportlength;
  if (R>2.0) {
    return 0.0;
  }
  else if (R==0.0) {
    return norm;
  } else {
    const double aux  = pi*R/2.0;
    return norm* pow(sin(aux)/aux, n);
  }
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Morris, Fox and Zhu (1997)
// but used a tripled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d Harmonic::gradW(const double distance, const Vec2d& distanceVector) const {
  return Harmonic::F(distance)*distanceVector;
}
//----------------------------------------------------------------------------------------
//		Calculates the kernel derivation (a double not vector) to distance
//----------------------------------------------------------------------------------------
double Harmonic::F(const double distance) const {
  double R= 2.0*distance/ supportlength;
  if (R>2.0) {
    return 0.0;
  }
  else if (R==0.0 ) {
    return 0.0;
  } else {
    const double x  = pi*R/2.0;
    return - factorGradW * ( n*x*pow(sin(x)/x, n) * (cos(x)/x - sin(x)/(x*x)) ) / sin(x);
  }
}

void Harmonic::show_information() const {
  std::cerr << "(kernel) Harmonic\n";
}
