#ifndef KERNEL_H
#define KERNEL_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
//#include "dllist.h"


//-----------------------------------------------------------------------
//					Kernel abstract base
//-----------------------------------------------------------------------

/// Kernel abstract base class
class Kernel
{
public:
    ///Conctructor
  Kernel(double smoothingLength);
    
  ///Virtual destructor 
  virtual ~Kernel();
  
  
  /// Calculates the kernel value for the given distance of two particles
  virtual double w(double distance) const = 0;
  
  /// Calculates the kernel derivation for the given distance of two particles */
  virtual Vec2d gradW(double distance, const Vec2d& distanceVector) const = 0;
  
protected:

  ///A local copy of the smoothing length
  const double smoothingLength;
};
#endif
