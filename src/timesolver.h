/// \file timesolver.h 
/// \brief Time solver class
///
///provides methods that iterate over one output time interval (D_time) either with the summation density approach or with the continuity density approach
//-----------------------------------------------------------------------

/// Time solver class 
class TimeSolver{

	//parameters copied from initiation
	double cell_size;///<will be copied from initiation
	Vec2d box_size;///<will be copied from initiation
	double smoothinglength;///<will be copied from initiation

	int ite; ///<number of iteration
	double dt; ///<time step

public:
	
	///constructor
	TimeSolver(Initiation &ini);
	
	///advance time interval D_time (=output time interval)
	void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
				   double &Time, double D_time, Diagnose &diagnose,
				   Initiation &ini, Kernel &weight_function, MLS &mls);

	///advance time interval D_time with summation for density
	void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, double D_time, Diagnose &diagnose,
				   Initiation &ini, Kernel &weight_function, MLS &mls);

};
