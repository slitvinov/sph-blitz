#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
/// \file particlemanager.h 
/// \brief particle manager

/// Particle manager class 
class ParticleManager
{
	//parameters copied from initiation
	char Project_name[FILENAME_MAX]; ///<the project name
	int number_of_materials;
	double smoothinglength; ///<smoothinglenth
	double smoothinglengthsquare; ///<smoothinglenth
	double cll_sz; ///<cell size
	Vec2d box_size; ///<computational domain size
	int initial_condition; ///<initial condition marker
	double delta; ///<the inital particle distance
	int hdelta; ///<the ration between smoothing length and inital particle distance
	Vec2d U0; ///<inital flow speed
	double rho0, p0, T0; ///<initial particle mass and density, pressure and temperature

	///buid the initial wall particles and the linked lists
	void BiuldWallParticles(Hydrodynamics &hydro, Initiation &ini, Boundary &boundary);

public:

	//linked cell matrix size
	int x_clls;///<linked cell matrix size x-direction
        int y_clls;///<linked cell matrix size y-direction

	//lists
	Llist<Particle> **cell_lists;	///<cell linked list in 2-d array
	
	Llist<Particle> NNP_list; ///<list for the nearest neighbor particles

	//constructors
	///"empty" constructor
	ParticleManager();
	/// constructor
	ParticleManager(Initiation &ini);
	///
	ParticleManager(double cell_size, int x_cells, int y_cells);

	///buid the initial particles and the linked lists
	void BiuldRealParticles(Hydrodynamics &hydro, Initiation &ini);
	void BiuldRealParticles(Hydrodynamics &hydro);

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

#endif //PARTICLEMANAGER_H
