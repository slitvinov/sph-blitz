/// \file quinticspline.h 
/// \brief                                      Quintic spline kernel.

#ifndef QUINTICSPLINE_H
#define QUINTICSPLINE_H

#include "kernel.h"

/// Quintic spline class 
class QuinticSpline : public Kernel
{

public:

    ///constructor to initialize the data members and
    QuinticSpline(const double smoothingLength);
  
    ///Calculates the kernel value for the given distance of two particles. 
    virtual double w(const double distance) const;
  
    ///Calculates the kernel derivation for the given distance of two particles. 
    virtual Vec2d gradW(const double distance, const Vec2d& distanceVector) const;
  
    ///Calculates the kernel derivation to distance. 
    double F(const double distance) const;

    ///Calculates the kernel Laplacian. 
    double LapW(const double distance) const;

private:
    ///Normalization factor
    const double norm;

    ///Auxiliary factors for intermediate results: The inverse smoothing length */
    double reciprocH;

    ///Auxiliary factors for intermediate results: A pre-factor for w */
    double factorW;

    ///Auxiliary factors for intermediate results: A pre-factor for grad w */
    double factorGradW;

    ///Auxiliary factors for Laplacian/
    double factorLapW;

};

#endif
