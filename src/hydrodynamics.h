/// \file hydrodynamics.h
/// \brief Definition of hydrodynamics

/// Definition of hydrodynamics
class Hydrodynamics
{	
	int number_of_materials;
	Vec2d gravity;
	double smoothinglength;
	double delta, delta2, delta3;
	double dt_g_vis, dt_surf;

	///the interaction (particle pair) list
	Llist<Interaction> interaction_list;

	///for time step 
	double viscosity_max, surface_max;


public:

	///the materials used
	Material *materials;
	///the interaction force used
	Force **forces;
	Llist<Particle> particle_list; ///particle list for all particles

	///Wiener process
	Wiener wiener;

	///constructor
	Hydrodynamics(ParticleManager &particles, Initiation &ini);

	///get the time step
	double GetTimestep();

	///update new parameters in pairs
	void BuildPair(ParticleManager &particles, QuinticSpline &weight_function);
	void UpdatePair(QuinticSpline &weight_function);

	///manupilate the particle physics
	///initiate particle change rate
	void ZeroChangeRate();
	///add the gravity effects
	void AddGravity();
	///calculate interaction with updating interaction list
	void UpdateChangeRate(ParticleManager &particles, QuinticSpline &weight_function);
	///calculate interaction without updating interaction list
	void UpdateChangeRate();
	///initiate particle density to zero
	void Zero_density();
	void Zero_ShearRate();
	///summation for particles density and shear rates
	void UpdateDensity(ParticleManager &particles, QuinticSpline &weight_function);
	void UpdateShearRate(ParticleManager &particles, QuinticSpline &weight_function);
	///currently no shear rate calculated  without updating interaction list
	void UpdateDensity();
	void UpdateShearRate();
	
	///update pahse field
	void UpdatePhaseGradient(Boundary &boundary);
	void Zero_PhaseGradient(Boundary &boundary);
	void UpdatePhaseField(Boundary &boundary);
	void Zero_PhaseField(Boundary &boundary);
	void UpdateSurfaceStress(Boundary &boundary);
	void UpdatePhaseLaplacian(Boundary &boundary);
	void Zero_PhaseLaplacian(Boundary &boundary);
	double SurfaceTensionCoefficient();
	void UpdatePahseMatrix(Boundary &boundary);

	///calculate states from conservatives
	void UpdateState();
	///calculate partilce volume
	void UpdateVolume(ParticleManager &particles, QuinticSpline &weight_function);

	///for predictor and corrector method, density evaluated directly
	void Predictor(double dt);
	void Corrector(double dt);

	///for predictor and corrector method, density evaluated with summation
	void Predictor_summation(double dt);
	void Corrector_summation(double dt);

	///DPD simultion
	///initiate random force
	void Zero_Random();
	///calculate random interaction without updating interaction list
	void UpdateRandom(double sqrtdt);
	///including random effects
	void RandomEffects();

	///tests for debug
	void MovingTest(Initiation &ini);
	double ConservationTest();

	///special uitilities
	void Zero_Velocity();

};
