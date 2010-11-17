#ifndef CAVITY_H
#define CAVITY_H
/// \file cavity.h
/// \brief  solidObstacles class for cavity

/// Cavity class

#include "SolidObstacles/solidObstacles.h"

class Cavity : public SolidObstacles
{

public:

  ///constructor to initialize the data members (auxiliary factors for solidObstacles calculation)
  Cavity(const Initiation& ini);

  
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
    ///depth of the cavity
    double depth;
    ///width of the cavity
    double width;
    ///y_position of the cavity surface
    double y_surface;
    ///y_position of the cavity bottom
    double y_bottom;
    ///x-position of RHS wall of cavity
    double x_wall_left;
    ///x-position of LHS wall of cavity
    double x_wall_right;
};

#endif //CAVITY_H
