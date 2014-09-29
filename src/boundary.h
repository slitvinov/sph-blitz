#ifndef BOUNDARY_H
#define BOUNDARY_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
#include <vector>
//#include "wiener.h"
#include "dllist.h"
#include "boundarystruct.h"

//#include "node.h"


class Initiation;
//#include "initiation.h" // needs a declaration of initiation class
//#include "particle.h"
//#include "particlemanager.h"

class Hydrodynamics;
class ParticleManager;
class Node;
//class BoundaryStruct;

//class Boundary;
//class Force;
//-----------------------------------------------------------------------
//				boundary condition
//				wall particle used for wall boundary condition
//-----------------------------------------------------------------------

/// boundary condition class
class Boundary
{
  ///if read wall particle from file .wll
  int wall_file;
  ///computational domain size
  Vec2d box_size;
  ///cell matrix size
  int x_clls, y_clls;
  int number_of_materials;
  
  ///vector containing the BoundaryStructures
  vector<const BoundaryStruct*> bsVector_;
  
  ///non-dimensionalize
  void non_dimensionalize(const Initiation* const ini);
  ///show information on screen
  void show_information(const Initiation* const ini) const; 
  
  ///implement a side boundary by modify particle states
  void Boundary_W(Node *prtl);
  void Boundary_E(Node *prtl);
  void Boundary_S(Node *prtl);
  void Boundary_N(Node *prtl);
  void Boundary_SW(Node *prtl);
  void Boundary_SE(Node *prtl);
  void Boundary_NW(Node *prtl);
  void Boundary_NE(Node *prtl);
public:
  //boundary condition indicator
  //left, right, upper and bottom
  //0: wall boundary condition
  //1: periodic boundary condition
  //2: free slip wall boundary condition
  //3: symmetry boundary condition 
  int  xBl, xBr, yBd, yBu;
  Vec2d UxBl, UxBr, UyBd, UyBu; //boundary velocity
  
  ///boundary particle lists
  Llist<Node> boundary_particle_list; //boundary particle list for all boundary particles
  
  ///constructor
  Boundary(Initiation* ini, 
	   Hydrodynamics &hydro, ParticleManager &particles);
  
  ///build boundary particles
  void BuildBoundaryParticles(ParticleManager &particles, 
			      Hydrodynamics &hydro);
  ///boundary conditions
  void BoundaryCondition(ParticleManager &particles);
  ///check particle if particle run out of the computational domain
  void RunAwayCheck(Hydrodynamics &hydro);
  ///get distance between two radios victors (periodic boundary conditions are
  ///taken into account)
  Vec2d getBDistance(const Vec2d&, const Vec2d&) const;
  
};
#endif
