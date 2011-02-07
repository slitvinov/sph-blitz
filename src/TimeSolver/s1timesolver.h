#ifndef SRC_TIMESOLVER_S1_TIMESOLVER_H
#define SRC_TIMESOLVER_S1_TIMESOLVER_H
/// \file hydrotimesolver.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------

#include "TimeSolver/timesolver.h"

/// Time solver class 
void s1SubStep(Hydrodynamics &hydro, ParticleManager &particles, 
	       spKernel weight_function, const double pdt,
	       const int nit, const Initiation& ini);

void s1PairUpdate(spInteraction pair,  spKernel weight_function, const double pdt, const Initiation& ini);

class S1TimeSolver : public TimeSolver {
  int ite; ///<number of iteration
public:
  /// constructor
  S1TimeSolver();
  /// advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, 
                              const double D_time, 
                              const Initiation &ini, spKernel weight_function);
/// advance time interval D_time with integration for density (has still to be implemented)
  void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, 
                    Boundary &boundary, double &Time, 
                    const double D_time, 
                    const Initiation &ini, spKernel weight_function);
  
  /// show some information about the solver
  void show_information() const;
  
  /// S1TimeSolver destructor
  ~S1TimeSolver();
};
#endif //SRC_TIMESOLVER_S1_TIMESOLVER_H
