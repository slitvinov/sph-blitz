#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
/// \file particlemanager.h 
/// \brief particle manager

#include "vec2d.h"
#include "particle.h"
#include <list>

class Hydrodynamics;
class Initiation;
class Boundary;
class Interaction;
class Kernel;


namespace blast = boost::numeric::ublas;

/// spParticle manager class 
class ParticleManager
{
  //parameters copied from initiation
  double supportlength; ///<smoothinglenth
  double supportlengthsquare; ///<smoothinglenth
  double cll_sz; ///<cell size
  Vec2d box_size; ///<computational domain size
  int initial_condition; ///<initial condition marker
  double delta; ///<the inital particle distance
  int hdelta; ///<the ration between smoothing length and inital particle distance
  Vec2d U0; ///<inital flow speed
  double rho0, p0, T0; ///<initial particle mass and density, pressure and temperature


  ///private init class to create Lists
  void Init();

public:

  //linked cell matrix size
  int x_clls;///<linked cell matrix size x-direction
  int y_clls;///<linked cell matrix size y-direction

  //lists
  blast::matrix<std::list<spParticle > > cell_lists; ///<cell linked list in 2-d array
  /// default constructor
  ParticleManager(const Initiation &ini);

  /// constructor to create ParticleManager without help of Initiation object.
  /// This constructor is used only for testing 
  ParticleManager(
		  const double supportlength, const Vec2d& box_size, 
		  const double cell_size, 
		  const int x_clls, const int y_cells,
		  const int initial_condition, const int hdelta,
		  const double delta, 
		  const Vec2d& U0_in, const double rho0_in, const double p0_in, 
		  const double T0_in);


  ///buid the initial particles and the linked lists
  void BuildRealParticle(vecMaterial materials, 
			 std::list<spParticle >& particle_list, 
			 Initiation &ini);

  ///buid the initial wall particles and the linked lists
  void BuildWallParticle(Hydrodynamics &hydro, Boundary &boundary);

  /// build real particles 
  void BuildRealParticle(Hydrodynamics &hydro);

  ///update the cell linked lists for real particles
  void UpdateCellLinkedLists();

  ///do NNP search around a point and build the NNP list
  std::list<spParticle> BuildNNP(Vec2d &point);

  ///build the interaction (particle pair) list
  void BuildInteraction(std::list<spInteraction> &interactions, 
			std::list<spParticle > &particle_list, 
			const Kernel &weight_function,
			const Initiation& ini);
};

#endif //PARTICLEMANAGER_H
