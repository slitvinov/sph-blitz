#ifndef GAS_TIMESOLVER_H
#define GAS_TIMESOLVER_H
/// \file timesolver.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------

#include "TimeSolver/timesolver.h"

/// Time solver class 
class GasTimeSolver : public TimeSolver {
	int ite; ///<number of iteration
public:
  /// constructor
  GasTimeSolver();
  /// advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, double D_time, 
                              const Initiation &ini, spKernel weight_function);
  void show_information() const;
};
#endif //GAS_TIMESOLVER_H
