#ifndef TIMESOLVER_H
#define TIMESOLVER_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
#include "subject.h"
//#include "wiener.h"
//#include "dllist.h"
//#include "initiation.h"
//#include "boundary.h"
//#include "mls.h"
//#include "diagnose.h"


//-----------------------------------------------------------------------
//					Time solver class
//-----------------------------------------------------------------------

/// time solver class
class Initiation;
class ParticleManager;
class Boundary;
class Diagnose;
class Hydrodynamics;
class QuinticSpline;
class MLS;
///ODE solver
class TimeSolver: public Subject{
  ///parameters copied from initiation
  double cell_size;
  Vec2d box_size;
  double smoothinglength;
  
  ///number of itenary
  int ite;
  
  ///time step
  double dt; 
  
public:	
  ///constructor
  TimeSolver(const Initiation* const ini);
  ~TimeSolver();
  ///advance time interval D_time
  void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
		    double &Time, double D_time, Diagnose &diagnose,
		    const Initiation* const ini, QuinticSpline &weight_function, MLS &mls);
  ///advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
			      double &Time, double D_time, Diagnose &diagnose,
			      const Initiation* const ini, QuinticSpline &weight_function, MLS &mls);
private:
  double solvertime_;
};
#endif
