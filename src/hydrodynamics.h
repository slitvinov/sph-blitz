#ifndef HYDRODYNAMICS_H
#define HYDRODYNAMICS_H
/// \file hydrodynamics.h
/// \brief  Definition of  materials and their hydrodynamical interactions


/// Definition of  materials and their hydrodynamical interactions
class Hydrodynamics
{	
	int number_of_materials;
	Vec2d gravity;
	double supportlength;
	int simu_mode;
	double delta, delta2, delta3;
	double dt_g_vis, dt_surf;

	///the interaction (particle pair) list
	Llist<Interaction> interaction_list;

	//for time step 
	double viscosity_max;///<for first time step

public:

	///the materials used
	Material *materials;
	///the interaction force used
	Force **forces;
	Llist<Particle> particle_list; ///<particle list for all particles

	///constructor
	Hydrodynamics(ParticleManager &particles, Initiation &ini);

	///get the time step
	double GetTimestep();

	///build new pairs
	void BuildPair(ParticleManager &particles, Kernel &weight_function);
	///update new parameters in pairs
	void UpdatePair(Kernel &weight_function);

	//manupilate the particle physics
	///initiate particle change rate
	void ZeroChangeRate();
	///add the gravity effects
	void AddGravity();
	///calculate interaction with updating interaction list
	void UpdateChangeRate(ParticleManager &particles, Kernel &weight_function);
	///calculate interaction without updating interaction list
	void UpdateChangeRate();
	///initiate particle density to zero
	void Zero_density();
	void Zero_ShearRate();
	///summation for particles density (with updating interaction list)
	void UpdateDensity(ParticleManager &particles, Kernel &weight_function, Initiation &ini);
        ///summation for shear rates (with updating interaction list)
	void UpdateShearRate(ParticleManager &particles, Kernel &weight_function);
	///currently no shear rate calculated  without updating interaction list
	void UpdateDensity(Initiation &ini);///???
	void UpdateShearRate();

	///calculate states from conservatives
	void UpdateState(Initiation &ini);
	///calculate partilce volume
	void UpdateVolume(ParticleManager &particles, Kernel &weight_function);

	/// predictor method, density evaluated directly
	void Predictor(double dt);
	/// corrector method, density evaluated directly:<b> corrector advances p, rho, U</b>
	void Corrector(double dt);

	///for predictor method, density evaluated with summation (that means: no density update within this method)
	void Predictor_summation(double dt);
        ///for corrector method, density evaluated with summation (that means: no density update within this method)
	void Corrector_summation(double dt);

	//test for debug
	void MovingTest();///test for debug
	double ConservationTest();//test for debug

	///special uitilities
	void Zero_Velocity();

};

#endif //HYDRODYNAMICS_H
