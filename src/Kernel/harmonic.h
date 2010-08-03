#ifndef HARMONIC_H
#define HARMONIC_H
/// \file harmonic.h
/// \brief  harmonic kernel

/// Harmonic kernel class
#include "Kernel/kernel.h"

class Harmonic : public Kernel
{

public:

  ///constructor to initialize the data members (auxiliary factors for kernel calculation)
  Harmonic(const double supportlength, const double harmonic_n);
  
  ///\brief Calculates the kernel value for the given distance of two particles
  virtual double w(const double distance) const;
  
  ///\brief Calculates the kernel derivation  for the given distance of two particles 
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

#endif //HARMONIC_H
