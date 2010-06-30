#ifndef KERNEL_H
#define KERNEL_H

/// \file kernel.h 
/// \brief Kernel abstract base

/// Kernel abstract base
#include "vec2d.h"
#include <blitz/array.h>

class Kernel
{

public:

    ///Constructor to initialize data members
  Kernel(double supportlength);
    
  ///Base classes with virtual member functions should have a virtual destructor
  virtual ~Kernel();



    /// Calculates the kernel value for the given distance of two particles
  virtual double w(double distance) const = 0;

  /// Calculates the kernel vector derivation for the given distance of two particles 
  virtual Vec2d gradW(double distance, const Vec2d& distanceVector) const = 0;

  /// Calculates the kernel scalar derivation for the given distance of two particles 
  virtual double F(const double distance) const = 0;

  virtual void show_information() const = 0;

  /// we need it only for testing
  BZ_DECLARE_MEMBER_FUNCTION(Kernel, w);
  BZ_DECLARE_MEMBER_FUNCTION(Kernel, F);


protected:
    ///A local copy of the smoothing length
    const double supportlength;
};

#endif //KERNEL_H
