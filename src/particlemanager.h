/// \file particlemanager.h
#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
#include "dllist.h"
#include <blitz/array.h>

class Force;
class Hydrodynamics;
class InteractionState;
class QuinticSpline;
class Node;
class PolymerParticle;
class Initiation;
//class Particle;
//-----------------------------------------------------------------------
//					Pre-claimer
//-----------------------------------------------------------------------
class Diagose;
class Boundary;

/// Particle manager
class ParticleManager
{
/// \name parameters copied from initiation
//@{    
  ///the project name
  char Project_name[25]; 
  ///the number of materials
  int number_of_materials;
  ///the smoothing length
  double smoothinglength; 
  ///the squear of the smoothing length
  double smoothinglengthsquare; 
  ///the cell size
  double cll_sz; 
  ///computational domain size
  Vec2d box_size; 
  ///initial condition marker
  int initial_condition; 
  ///the inital particle distance
  double delta; 
  ///the ration between smoothing length and inital particle distance
  int hdelta; 
  ///inital flow speed
  Vec2d U0;
  ///inital particle density 
  double rho0;
  ///inital particle pressure
  double p0;
  ///inital particle temperature
  double T0; 

public:

  ///  linked cell matrix size
  int x_clls, y_clls;

  ///cell linked list in 2-d array
  //  Array<Nod
  //Llist<Node> **cell_lists;	
  blitz::Array <Llist<Node>, 2> cell_lists;	

  //a list for the nearest neighbor particles
  Llist<Node> NNP_list; 
  
  ///Particle constructors
  //@{ 
  ParticleManager();
  ParticleManager(const Initiation* const  ini);
  ParticleManager(double cell_size, int x_cells, int y_cells);  
  //@}
  
  ///destructio
  virtual ~ParticleManager();
  /// buid the initial particles and the linked lists
  //@{  
  void BuildRealParticles(Hydrodynamics &hydro, 
			  Initiation* ini);
  void BuildRealParticles(Hydrodynamics &hydro);
  //@}

  ///update the cell linked lists
  void UpdateCellLinkedLists();

  ///do NNP search around a point and build the NNP list
  void BuildNNP(Vec2d &point);  
  ///do NNP search around a point and build the NNP list for MLS approximation
  void BuildNNP_MLSMapping(Vec2d &point);
  ///build the interaction (particle pair) list
  void BuildInteraction(Llist<InteractionState> &interactions, 
			const Llist<Node> &particle_list, 
			Force **forces, 
			QuinticSpline &weight_function);
  ///buid the initial wall particles and the linked lists
  void BuildWallParticles(Hydrodynamics &hydro, Initiation &ini, Boundary &boundary);  

  ///returns the pointer to the clossest particle to the given vector
  virtual Node* getClosestParticle(const Vec2d& vec) const throw();
};
#endif
