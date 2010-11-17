#ifndef NOOBSTACLES_H
#define NOOBSTACLES_H
/// \file noObstacles.h
/// \brief  cubic spline solidObstacles 1D

/// NoObstacles class

#include "SolidObstacles/solidObstacles.h"

class NoObstacles : public SolidObstacles
{

public:

  ///constructor (does NOTHING in the case for NO obstacles)
  NoObstacles(const Initiation& ini);

  /// \brief checks if the particle (given by its coordinates) lies within the solid obstacle
  ///
  /// returns the following values:
  /// 0: if particle is located outslde the wall (i.e real particle)
  /// 1: if particle located inside the solid wall wih a distance of <=
  /// one supportlength to the wall surface(i.e particle is ghost particle)
  /// 2: if particle is located further inside the solid obstacle:
  /// in this case particle does not need to be taken into account for the simulation
  ///=> method returns always "0" for NoObstacle class
  int prtl_in_solid(const Vec2d& coordinates) const;

  void cut_ivs_file_header(std::ifstream& inputfile) const;

  void set_solObs_tangentAndDistance(spParticle& prtl)const;

  void show_information() const;
    
};

#endif //NOOBSTACLES_H
