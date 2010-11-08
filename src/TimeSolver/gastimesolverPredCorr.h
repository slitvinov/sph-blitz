#ifndef GAS_TIMESOLVERPREDCORR_H
#define GAS_TIMESOLVERPREDCORR_H
/// \file gastimesolverPredCorr.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------

#include "TimeSolver/timesolver.h"

/// Time solver class 
class GasTimeSolverPredCorr : public TimeSolver {
	int ite; ///<number of iteration
public:
  /// constructor
  GasTimeSolverPredCorr();
  /// advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, double D_time, 
                              const Initiation &ini, spKernel weight_function,
			      spSolidObstacles obstacles);
  void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, 
		    Boundary &boundary, double &Time, double D_time, 
		    const Initiation &ini, spKernel weight_function,
		    spSolidObstacles obstacles);

  void show_information() const;
};
#endif //GAS_TIMESOLVERPREDCORR_H
