/// \file hydrodynamics.h
/// \brief  Definition of  materials and their hydrodynamical interactions

class Material;
class Interaction;
class Force;
class Particle;
class ParticleManager;
class Initiation;
class Boundary;
class Material;

/// Definition of  materials and their hydrodynamical interactions
struct Hydrodynamics
{
	int number_of_materials;
	double gravity[2];
	double smoothinglength;
	double delta, delta2, delta3;
	double dt_g_vis, dt_surf;

	///the interaction (particle pair) list
	Llist<Interaction> interaction_list;

	//for time step 
	double viscosity_max;///<for first time step
	double  surface_max;///<for first time step

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
	void BuildPair(ParticleManager &particles, QuinticSpline &weight_function);
	///update new parameters in pairs
	void UpdatePair(QuinticSpline &weight_function);

	//manupilate the particle physics
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
	///summation for particles density (with updating interaction list)
	void UpdateDensity(ParticleManager &particles, QuinticSpline &weight_function);
	///currently no shear rate calculated  without updating interaction list
	void UpdateDensity();///???
	
	//update phase field
	void UpdatePhaseGradient(Boundary &boundary);///< not independant with UpdateDensity
	void Zero_PhaseGradient(Boundary &boundary);
	void UpdateSurfaceStress(Boundary &boundary);
	///calculate surface tension coefficient
	double SurfaceTensionCoefficient();
	///this method currently does <b>NOTHING</b>
	void UpdatePahseMatrix(Boundary &boundary);

	///calculate states from conservatives
	void UpdateState();
	///calculate partilce volume
	void UpdateVolume(ParticleManager &particles, QuinticSpline &weight_function);

	/// predictor method, density evaluated directly
	void Predictor(double dt);
	/// corrector method, density evaluated directly:<b> corrector advances p, rho, U</b>
	void Corrector(double dt);

	///for predictor method, density evaluated with summation (that means: no density update within this method)
	void Predictor_summation(double dt);
        ///for corrector method, density evaluated with summation (that means: no density update within this method)
	void Corrector_summation(double dt);

	//DPD simultion
	///initiate random force (DPD simulation)
	void Zero_Random();
	///calculate random interaction without updating interaction list (DPD simulation)
	void UpdateRandom(double sqrtdt);
	///including random effects (DPD simulation)
	void RandomEffects();

};

