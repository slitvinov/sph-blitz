/// \file initiation.h 
/// \brief Initiates the simulation

class Hydrodynamics;
class ParticleManager;
class QuinticSpline;

///\brief Initiates the simulation
class Initiation {
public:
	///the project name
	char Project_name[FILENAME_MAX];

	///\brief number of materials
	///
	///- the no. zero material is always the wall
	///- therefore at least 2 materials should be included
	int number_of_materials;
	///the global inputfile name: a *.cfg file
	char inputfile[FILENAME_MAX];

	/// \brief initial condition marker:
	///
	///- 0 initialize from the .cfg file; 
	///- 1 read from the .rst file particle by particle with non-dimensional data
	int initial_condition;
	///diagnose information maker: 1 output diagnose information
	int diagnose;
	///artificial viscosity
	double art_vis;

	///smoothinglength
	double smoothinglength;
	///the compuational domain size
	double box_size[2];
	///cell size
	double cell_size;
	///the inital particle distance
	double delta;
	///the ration between smoothing length and inital particle distance
	int hdelta;
	///cells matrix for real particles
	int x_cells, y_cells;
	///g force on particles
	double g_force[2];

	//timing control
	double Start_time;///<Simulation start time
	double End_time;///<Simulation end time
        double D_time;///<time interval for output (every D_time: output)

	double U0[2];///<inital flow speed (if initial condition is defined here)w
	double rho0;///<initial particle density(if initial condition is defined here)
	double p0;///<initial pressure(if initial condition is defined here)
	double T0;///<initial temperature(if initial condition is defined here)

	///Moving Least Squarr
	int MLS_MAX;

	///constructor
	///\param *project_name: a pointer to the project name array (the project name is defined as a main-function argument and therefore given as an additional command line element when running the progam) 
	explicit Initiation(const char *project_name);
	void show_information();
	///predict the particle volume and mass
};

void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function);
