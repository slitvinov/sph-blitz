#ifndef SRC_PARTICLEMANAGER_H_
#define SRC_PARTICLEMANAGER_H_
/// Copyright 2010 TUM
/// \file particlemanager.h
/// \brief particle manager
#include <list>
#include "vec2d.h"
#include "particle.h"

class Hydrodynamics;
class Initiation;
class Boundary;
class Interaction;
class Kernel;


namespace blast = boost::numeric::ublas;

/// Particle manager class
class ParticleManager {
  double supportlength;  ///<smoothinglenth
  double supportlengthsquare; ///<smoothinglenth square
  Vec2d box_size; ///<computational domain size
  int initial_condition; ///<initial condition marker
  double cll_sz; ///<cell size
  double delta; ///<the inital particle distance
  int hdelta; ///<the ration between smoothing length and inital particle distance
public:
  //linked cell matrix size
  int x_clls;  ///<linked cell matrix size x-direction
  int y_clls;  ///<linked cell matrix size y-direction
  /// cell linked list in 2-d array
  blast::matrix<std::list<spParticle > > cell_lists;
  /// default constructor
  explicit ParticleManager(const Initiation &ini);

  /// constructor to create ParticleManager without help of Initiation object.
  /// This constructor is used only for testing
  ParticleManager(const double supportlength, const Vec2d& box_size,
		  const double cell_size,
		  const int x_clls, const int y_cells,
		  const int initial_condition, const int hdelta,
		  const double delta);



  ///buid the initial particles and the linked lists for liquids (incompressible)
  void BuildRealParticle(vecMaterial materials,
			 std::list<spParticle >& particle_list,
			 Initiation &ini);
  ///build the initial particles and the linked lists for gas dynamcis
  void BuildRealParticleGasDyn(vecMaterial materials, 
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
			spKernel weight_function,
			const Initiation& ini);
};

#endif  // SRC_PARTICLEMANAGER_H_
