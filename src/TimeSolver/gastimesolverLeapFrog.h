#ifndef GAS_TIMESOLVERLEAPFROG_H
#define GAS_TIMESOLVERLEAPFROG_H
/// \file gastimesolverLeapFrog.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------

#include "TimeSolver/timesolver.h"

/// Time solver class 
class GasTimeSolverLeapFrog : public TimeSolver {
	int ite; ///<number of iteration
public:
  /// constructor
  GasTimeSolverLeapFrog();
  /// advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, const double D_time, 
                              const Initiation &ini, spKernel weight_function);
  void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, const double D_time, 
                              const Initiation &ini, spKernel weight_function);

  void show_information() const;
};
#endif //GAS_TIMESOLVERLEAPFROG_H
