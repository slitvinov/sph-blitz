/// \file bspline.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      A concrete kernel class
//		see Monaghan & Lattanzio (1985).
//		Most often used kernel.
//		bskernel.cpp
//----------------------------------------------------------------------------------------
#include "src/Kernel/bspline.h"
#include <glog/logging.h>
#include <boost/math/constants/constants.hpp>

const double pi = boost::math::constants::pi<double>();
BSpline::BSpline(double supportlength)
    : Kernel(supportlength) {
    ///-  initialize the auxiliary factors
    reciprocH = 1.0 / supportlength;
    ///- normalize to 1.0
    norm = 40.0 / 7.0 / pi;
    factorW     = norm * pow(reciprocH, 2);
    factorGradW = -3.0*norm * pow(reciprocH, 3);
    LOG(INFO) << "constructor of BSpline called";
}
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
// We take this from Monaghan & Lattenzio (1985)
// but used a doubled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
double BSpline::w(double distance) const
{
    // dist/supportlength is often needed
    const double normedDist = distance * reciprocH;
    // the beta-spline is composed of three functions, so we must determine, were we are
    if (normedDist < 0.5) {
    // we are in the inner region of the kernel
        return factorW * (6.0 * normedDist * normedDist * normedDist - 
                            6.0 * normedDist * normedDist + 1.0);
    } else if (normedDist < 1.0) {
    // we are in the outer region of the kernel (not outside!)
        double aux = 1.0 - normedDist;
        return factorW * ( 2.0 * aux * aux * aux );
    } else {
        return 0.0;
    }
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Monaghan & Lattenzio (1985)
// but used a doubled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d BSpline::gradW(double distance, const Vec2d& distanceVector) const {
    return F(distance)*distanceVector;
}
//----------------------------------------------------------------------------------------
//				Calculates the kernel derivation to distance
//----------------------------------------------------------------------------------------
double BSpline::F(double distance) const {
    // dist/supportlength is often needed
    const double normedDist = 2.0*distance * reciprocH;
    // the beta-spline is composed of three functions (so the derivate is also), 
    // we must determine, were we are
    if (normedDist < 1.0) 
    // we are in the inner region of the kernel
    {
      return factorGradW * (3.0/2.0 * normedDist*normedDist - 2.0*normedDist);
    }
    else if (normedDist < 2.0)
    // we are in the outer region of the kernel (not outside!)
    {
      const double aux = 2.0 - normedDist;
      return -0.5*factorGradW * aux*aux;
    }
    else
    // dist is bigger then the kernel.
    {
      return 0.0;
    }
}


void BSpline::show_information() const {
  std::cerr << "(kernel) BSpline\n";
}
