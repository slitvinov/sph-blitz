#ifndef LINEARWALL_H
#define LINEARWALL_H
/// \file linearWall.h
/// \brief  solidObstacles class for linearWall parallel to x coordinate 
///
/// wall position determined by y_wall
/// purpose of this linear wall: test the boundary conditions for the 
/// SolidObstacles, as they are not implemented the same way as the boundary
/// conditions for the domain edges, which are already tested

/// LinearWall class

#include "SolidObstacles/solidObstacles.h"

class LinearWall : public SolidObstacles
{

public:

  ///constructor to initialize the data members (auxiliary factors for solidObstacles calculation)
  LinearWall(const Initiation& ini);

  
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
    ///depth of the linearWall(s)
    double y_wall_1;
    double y_wall_2;
    
};

#endif //LINEARWALL_H
