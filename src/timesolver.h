class Initiation;
class Hydrodynamics;
class ParticleManager;
class Boundary;
class QuinticSpline;
class Diagnose;
class MLS;
class TimeSolver{
	double cell_size;
	double box_size[2];
	double smoothinglength;
	int ite;
	double dt;
public:
	explicit TimeSolver(Initiation *ini);
	void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, double D_time, Diagnose &diagnose, Initiation &ini, QuinticSpline &weight_function, MLS &mls);
};
