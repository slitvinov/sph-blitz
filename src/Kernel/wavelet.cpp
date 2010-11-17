/// \file bspline.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>

//----------------------------------------------------------------------------------------
//      A concrete kernel class
//		wavelet.cpp
//----------------------------------------------------------------------------------------
#include "src/Kernel/wavelet.h"
#include <glog/logging.h>
#include <boost/math/constants/constants.hpp>

const double pi = boost::math::constants::pi<double>();
Wavelet::Wavelet(double supportlength)
    : Kernel(supportlength) {
    ///-  initialize the auxiliary factors
    reciprocH = 1.0 / supportlength;
    ///- normalize to 1.0
    norm = 120.0 / 7.0 / pi;
    factorW     = norm * pow(reciprocH, 2);
    factorGradW = -2.0*norm * pow(reciprocH, 3);
    LOG(INFO) << "constructor of Wavelet called";
}
//----------------------------------------------------------------------------------------
// Calculates the kernel value for the given distance of two particles
// We take this from Monaghan & Lattenzio (1985)
// but used a doubled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
double Wavelet::w(double distance) const
{
    // dist/supportlength is often needed
    const double s = 2.0*distance * reciprocH;
    // the beta-spline is composed of three functions, so we must determine, were we are
    if (s < 1.0) {
      // we are in the inner region of the kernel
      return factorW * ( 1.0 - 5.0*s*s/2.0 + 3.0*s*s*s/2.0 );
    } else if (s < 2.0) {
      // we are in the outer region of the kernel (not outside!)
      return factorW * ( (1.0-s)*(2.0-s)*(2.0-s) / 2.0 );
    } else {
        return 0.0;
    }
}
//----------------------------------------------------------------------------------------
// Calculates the kernel derivation for the given distance of two particles
// We take this from Monaghan & Lattenzio (1985)
// but used a doubled smoothing length for the definition of the interaction radius.
//----------------------------------------------------------------------------------------
Vec2d Wavelet::gradW(double distance, const Vec2d& distanceVector) const {
    return F(distance)*distanceVector;
}
//----------------------------------------------------------------------------------------
//				Calculates the kernel derivation to distance
//----------------------------------------------------------------------------------------
double Wavelet::F(double distance) const {
    // dist/supportlength is often needed
    const double s = 2.0*distance * reciprocH;
    // the beta-spline is composed of three functions (so the derivate is also), 
    // we must determine, were we are
    if (s < 1.0) 
    // we are in the inner region of the kernel
    {
      return factorGradW * (9.0*s*s/2.0 - 5*s);
    }
    else if (s < 2.0)
    // we are in the outer region of the kernel (not outside!)
    {
      return factorGradW * ( -(1.0-s)*(2.0-s) - (2.0-s)*(2.0-s)/2.0) ;
    }
    else
    // dist is bigger then the kernel.
    {
      return 0.0;
    }
}


void Wavelet::show_information() const {
  std::cerr << "(kernel) Wavelet\n";
}
