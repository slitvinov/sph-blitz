#ifndef TIMESOLVER_H
#define TIMESOLVER_H
/// \file timesolver.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------


/// Time solver class 
class TimeSolver{

	//parameters copied from initiation
  //	double cell_size;///<will be copied from initiation
  //	Vec2d box_size;///<will be copied from initiation
  //	double supportlength;///<will be copied from initiation

	int ite; ///<number of iteration

public:
  /// constructor
  TimeSolver();
  /// advance time interval D_time with summation for density
  void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                              Boundary &boundary, double &Time, double D_time, 
                              const Initiation &ini, const Kernel &weight_function);
};
#endif //TIMESOLVER_H
