/// \file particlemanager.h 
/// \brief particle manager

class Particle;
class Boundary;
class Hydrodynamics;
class Initiation;
class Interaction;
class Force;

/// Particle manager class 
class ParticleManager
{
	//parameters copied from initiation
	char Project_name[FILENAME_MAX]; ///<the project name
	int number_of_materials;
	double smoothinglength; ///<smoothinglenth
	double smoothinglengthsquare; ///<smoothinglenth
	double cll_sz; ///<cell size
	double box_size[2]; ///<computational domain size
	int initial_condition; ///<initial condition marker
	double delta; ///<the inital particle distance
	int hdelta; ///<the ration between smoothing length and inital particle distance
	double U0[2]; ///<inital flow speed
	double rho0, p0, T0; ///<initial particle mass and density, pressure and temperature

	///buid the initial wall particles and the linked lists
	void BuildWallParticles(Hydrodynamics &hydro, Boundary &boundary);

public:

	//linked cell matrix size
	int x_clls;///<linked cell matrix size x-direction
        int y_clls;///<linked cell matrix size y-direction

	//lists
	Llist<Particle> **cell_lists;	///<cell linked list in 2-d array
	
	Llist<Particle> NNP_list; ///<list for the nearest neighbor particles

	/// constructor
	explicit ParticleManager(Initiation &ini);

	///buid the initial particles and the linked lists
	void BuildRealParticles(Hydrodynamics &hydro, Initiation &ini);

	///update the cell linked lists for real particles
	void UpdateCellLinkedLists();

	///do NNP search around a point and build the NNP list
	void BuildNNP(Vec2d &point);

	///do NNP search around a point and build the NNP list for MLS approximation
	void BuildNNP_MLSMapping(Vec2d &point);

	///build the interaction (particle pair) list
	void BuildInteraction(Llist<Interaction> &interactions, Llist<Particle> &particle_list, 
						Force **forces, QuinticSpline &weight_function);
	
};

