#ifndef TIMESOLVER_H
#define TIMESOLVER_H
/// \file timesolver.h 
/// \brief Time solver class
///
/// provides methods that iterate over one output time interval (D_time) 
/// either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------
#include <boost/utility.hpp>
/// Time solver abstract base class 
class TimeSolver : boost::noncopyable {
 public:
  /// advance time interval D_time with summation for density
  virtual void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, 
                                      const double D_time, const Initiation &ini, spKernel weight_function) = 0;
  /// advance time interval D_time with integration for density
  virtual void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, 
                            const double D_time, const Initiation &ini, spKernel weight_function) = 0;
  /// print kernel type
  virtual void show_information() const = 0;

 protected:
  /// constructor
  TimeSolver();
  virtual ~TimeSolver();
};
#endif //TIMESOLVER_H
