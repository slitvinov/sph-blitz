#ifndef POROSITIES_H
#define POROSITIES_H
/// \file porosities.h
/// \brief  solidObstacles class for porosities

/// Porosities class

#include "SolidObstacles/solidObstacles.h"

class Porosities : public SolidObstacles
{

public:

  ///constructor to initialize the data members (auxiliary factors for solidObstacles calculation)
  Porosities(const Initiation& ini);

  
  /// \brief checks if the particle (given by its coordinates) lies within the solid obstacle
  ///
  /// returns the following values:
  /// 0: if particle is located outslde the wall (i.e real particle)
  /// 1: if particle located inside the solid wall wih a distance of <=
  /// one supportlength to the wall surface(i.e particle is ghost particle)
  /// 2: if particle is located further inside the solid obstacle:
  /// in this case particle does not need to be taken into account for the simulation
  int prtl_in_solid(const Vec2d& coordinates) const;

  void cut_ivs_file_header(std::ifstream& inputfile) const;

  void set_solObs_tangentAndDistance(spParticle& prtl) const;
 
  /// show the solidObstacles type
  void show_information() const;
  
 private:
  /// Number of zylinders (to model a porous media)
  int N_zyl;
    /// vector of Vec2d which contains the center positions of all zylinders
  /// (one component of the vector is a Vec2d with coordinates of 1 zyl. center)
  vector <Vec2d> all_Zyl_centers;
  /// Vetor of double which contains radii of all zylinders
  /// (position of center and radius of one zylinder are in the same
  /// component of the corresponding vector data structure)
  vector <double> all_Zyl_radii;
};

#endif //POROSITIES_H
