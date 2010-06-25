#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
/// \file particlemanager.h 
/// \brief particle manager

#include "vec2d.h"
#include "dllist.h"
#include "particle.h"
#include <boost/numeric/ublas/matrix.hpp>

class Hydrodynamics;
class Initiation;
class Boundary;
class Interaction;
class Force;
class Kernel;

/// Particle manager class 
using namespace boost::numeric::ublas;

class ParticleManager
{
	//parameters copied from initiation
	char Project_name[25]; ///<the project name
	int number_of_materials;
	double supportlength; ///<smoothinglenth
	double supportlengthsquare; ///<smoothinglenth
	double cll_sz; ///<cell size
	Vec2d box_size; ///<computational domain size
	int initial_condition; ///<initial condition marker
	int simu_mode;///<simulation mode
	double delta; ///<the inital particle distance
	int hdelta; ///<the ration between smoothing length and inital particle distance
	Vec2d U0; ///<inital flow speed
	double rho0, p0, T0; ///<initial particle mass and density, pressure and temperature

	///buid the initial wall particles and the linked lists
	void BuildWallParticles(Hydrodynamics &hydro, Boundary &boundary);

  ///private init class to create Lists
  void Init();

public:

	//linked cell matrix size
	int x_clls;///<linked cell matrix size x-direction
        int y_clls;///<linked cell matrix size y-direction

	//lists
  matrix<Llist<Particle> > cell_lists;	///<cell linked list in 2-d array
	
	Llist<Particle> NNP_list; ///<list for the nearest neighbor particles

  /// default constructor
  ParticleManager(Initiation &ini);

  /// constructor to create ParticleManager without help of Initiation object.
  /// This constructor is used only for testing 
  ParticleManager(const char Project_name[25], const int number_of_materials, 
		  const double supportlength, const Vec2d box_size, 
		  const double cell_size, 
		  const int x_clls, const int y_cells,
		  const int initial_condition, const int hdelta,
		  const double delta, const int simu_mode, 
		  const Vec2d U0_in, const double rho0_in, const double p0_in, 
		  const double T0_in);



	///buid the initial particles and the linked lists
  void BuildRealParticles(Material* materials, 
			  Llist<Particle>& particle_list, 
			  Initiation &ini);
	void BuildRealParticles(Hydrodynamics &hydro);

	///update the cell linked lists for real particles
	void UpdateCellLinkedLists();

	///do NNP search around a point and build the NNP list
	void BuildNNP(Vec2d &point);

	///do NNP search around a point and build the NNP list for MLS approximation
	void BuildNNP_MLSMapping(Vec2d &point);

	///build the interaction (particle pair) list
	void BuildInteraction(Llist<Interaction> &interactions, Llist<Particle> &particle_list, 
						Force **forces, Kernel &weight_function);
};

#endif //PARTICLEMANAGER_H
