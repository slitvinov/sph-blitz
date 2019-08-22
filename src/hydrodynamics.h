class Material;
class Interaction;
class Force;
class Particle;
class ParticleManager;
class Initiation;
class Boundary;
class Material;
struct Hydrodynamics
{
	int number_of_materials;
	double gravity[2];
	double smoothinglength;
	double delta, delta2, delta3;
	double dt_g_vis, dt_surf;
	Llist<Interaction> interaction_list;
	double viscosity_max;
	double  surface_max;
	Material *materials;
	Force **forces;
	Llist<Particle> particle_list; 
	Hydrodynamics(ParticleManager *particles, Initiation *ini);
	double GetTimestep();
	void BuildPair(ParticleManager *particles, QuinticSpline *weight_function);
	void UpdatePair(QuinticSpline *weight_function);
	void ZeroChangeRate();
	void AddGravity();
	void UpdateChangeRate(ParticleManager *particles, QuinticSpline *weight_function);
	void UpdateChangeRate();
	void Zero_density();
	void UpdateDensity();
	void UpdatePhaseGradient(Boundary *boundary);
	void Zero_PhaseGradient(Boundary *boundary);
	void UpdateSurfaceStress(Boundary *boundary);
	void UpdatePahseMatrix(Boundary *boundary);
	void UpdateState();
	void UpdateVolume(ParticleManager *particles, QuinticSpline *weight_function);
	void Predictor(double dt);
	void Corrector(double dt);
	void Predictor_summation(double dt);
	void Corrector_summation(double dt);
	void Zero_Random();
	void UpdateRandom(double sqrtdt);
	void RandomEffects();
};
