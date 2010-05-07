//-----------------------------------------------------------------------
//					Output the computational results
//-----------------------------------------------------------------------
class Output {
	
	//the project name
	char Project_name[25];

	int number_of_materials;
	//the inital particle distance
	double delta;
	//cells matrix for real particles
	int x_cells, y_cells;
	//the ration between smoothing length and inital particle distance
	int hdelta; 

public:

	//constructor
	Output(Initiation &ini);

	//output particle positions respected different materials
	void OutputParticles(Hydrodynamics &hydro, Boundary &boundary, 
						double Time, Initiation &ini);
	//output material states on uniform grid
	void OutputStates(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
					  double Time, Initiation &ini);
	//Output data for restart
	void OutRestart(Hydrodynamics &hydro, double Time, Initiation &ini);
	//a movie for particle motion
	void CreatParticleMovie();
	void WriteParticleMovie(Hydrodynamics &hydro, double Time, Initiation &ini);
	//avergaed values for Poiseuille and Couette flows
	void OutAverage(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
					double Time, Initiation &ini);
};
