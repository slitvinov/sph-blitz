/// \file output.h 
/// \brief Output the computational results

/// Output class 
class Output {
	
	///the project name
	char Project_name[25];

	int number_of_materials;
	///the inital particle distance
	double delta;
	///cells matrix for real particles
	int x_cells, y_cells;
	///the ratio between smoothing length and inital particle distance
	int hdelta; 
	int simu_mode;

public:

	///constructor
	Output(Initiation &ini);

	///output particle positions respected different materials
	void OutputParticles(Hydrodynamics &hydro, Boundary &boundary, 
						double Time, Initiation &ini);
	///output material states on uniform grid
	void OutputStates(ParticleManager &particles, MLS &mls, Kernel &weight_function, 
					  double Time, Initiation &ini);
	///Output real particle data for restart the computation
	void OutRestart(Hydrodynamics &hydro, double Time);
	///create a head file for a movie of particle motion
	void CreatParticleMovie();
	///write the data for a movie of particle motion (output real and wall particles)	
	void WriteParticleMovie(Hydrodynamics &hydro, double Time, Initiation &ini);
	///avergaed values for Poiseuille and Couette flows (average is taken in horizontal direction)
	void OutAverage(ParticleManager &particles, MLS &mls, Kernel &weight_function, 
					double Time, Initiation &ini);
};
