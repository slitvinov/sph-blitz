#ifndef QUINTICSPLINE_H
#define QUINTICSPLINE_H
/// \file quinticspline.h 
/// \brief Quintic spline kernel

#include "Kernel/kernel.h"


/// Quintic spline class 
class QuinticSpline : public Kernel
{

public:

  ///constructor to initialize the data members (auxiliary factors for kernel calculation)
  QuinticSpline(const double supportlength);
  
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

  /// show the kernel type
  void show_information() const;


private:
    ///Normalization factor
    const double norm;

    ///Auxiliary factors for intermediate results: The inverse smoothing length
    const double reciprocH;

   
    ///Auxiliary factors for intermediate results: A pre-factor for w 
    const double factorW;

    ///Auxiliary factors for intermediate results: A pre-factor for grad w
    const double factorGradW;

};

#endif //QUINTICSPLINE_H
