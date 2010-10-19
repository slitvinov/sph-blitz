#ifndef CUBICSPLINE1D_H
#define CUBICSPLINE1D_H
/// \file CubicSpline1D.h 
/// \brief  cubic spline kernel 1D

/// CubicSpline class

#include "src/Kernel/kernel.h"

class CubicSpline1D : public Kernel
{

public:

  ///constructor to initialize the data members (auxiliary factors for kernel calculation)
  CubicSpline1D(const double supportlength);
  
  ///\brief Calculates the kernel value for the given distance of two particles
  ///
  /// We take this from Morris, Fox and Zhu (1997)
  /// but used a tripled smoothing length for the definition of the interaction radius. 
  virtual double w(const double distance) const;
  
  ///\brief Calculates the kernel derivation  for the given distance of two particles 
  ///
  /// We take this from Morris, Fox and Zhu (1997)
  /// but used a tripled smoothing length for the definition of the interaction radius.
  virtual Vec2d gradW(const double distance, const Vec2d& distanceVector) const;
  
  ///Calculates the kernel derivation (a double, not a vector) to distance
  double F(const double distance) const;

  ///Calculates the kernel Laplacian
  double LapW(const double distance) const;

  /// show the kernel type
  void show_information() const;

private:
    ///smoothing length
    double h;

    ///Normalization factor
    const double norm;

    ///Auxiliary factors for intermediate results: The inverse smoothing length
    double reciprocH;

    ///Auxiliary factors for intermediate results: A pre-factor for w 
    double factorW;

    ///Auxiliary factors for intermediate results: A pre-factor for grad w
    double factorGradW;

    ///Auxiliary factors for Laplacian
    double factorLapW;

};

#endif //CUBICSPLINE1D_H
