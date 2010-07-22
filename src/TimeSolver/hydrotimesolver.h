#ifndef HYDRO_TIMESOLVER_H
#define HYDRO_TIMESOLVER_H
/// \file timesolver.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------

#include "TimeSolver/timesolver.h"

/// Time solver class 
class HydroTimeSolver : public TimeSolver {
	int ite; ///<number of iteration
public:
  /// constructor
  HydroTimeSolver();
  /// advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, double D_time, 
                              const Initiation &ini, spKernel weight_function);
/// advance time interval D_time with integration for density (has still to be implemented)
void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, double D_time, 
                              const Initiation &ini, spKernel weight_function);

  /// show some information about the solver
  void show_information() const;

  /// HydroTimeSolver destructor
  ~HydroTimeSolver();
};
#endif //HYDRO_TIMESOLVER_H
