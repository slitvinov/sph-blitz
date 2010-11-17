#ifndef SOLIDOBSTACLES_H
#define SOLIDOBSTACLES_H

/// \file solidObstacles.h 
/// \brief SolidObstacles abstract base

/// SolidObstacles abstract base
#include <fstream>
#include <iostream>
#include <list>
#include "vec2d.h"
#include "initiation.h"
#include "particle.h"
#include "glbtype.h"
#include <blitz/array.h>
#include <glog/logging.h>
#include "hydrodynamics.h"

class SolidObstacles
{
  
 public:

  ///Constructor
  SolidObstacles(const Initiation& ini);
  
  ///Base classes with virtual member functions should have a virtual destructor
  virtual ~SolidObstacles();
  
  /// \brief checks if the particle (given by its coordinates) lies within the solid obstacle
  ///
  /// returns the following values:
  /// 0: if particle is located outslde the wall (i.e real particle)
  /// 1: if particle located inside the solid wall wih a distance of <=
  /// one supportlength to the wall surface(i.e particle is ghost particle)
  /// 2: if particle is located further inside the solid obstacle:
  /// in this case particle does not need to be taken into account for the simulation
  virtual int prtl_in_solid(const Vec2d& coordinates) const = 0;

  ///\brief function to cut off .ivs file header containing geometrical data for SolidObstacles in order for the particlemanager to get a filestream starting at the point where particle information starts!
  ///
  /// as required geometrical information depends on SolidObstacles type,
  /// an individual method has to be implemented for each of them
  virtual void cut_ivs_file_header(std::ifstream& inputfile) const = 0;

  ///\brief function that calculates tangent plane for one real particle and sets its distance to solidobstacle surface
  ///
  /// tangent plane (line) calculated if real particle closer than 
  /// 1 supportlength to the SolidObstacle
  /// tangent plane is attribute of each particle object
  virtual void set_solObs_tangentAndDistance(spParticle& prtl)const=0;

  ///\brief function that sets tangent plane and distance to solid obstacle surface for all real particles
  ///
  /// (by iterating particle list and calling set_solObs_tangent for each prtl)
  void set_all_solObs_tangentsAndDistances(Hydrodynamics &hydro);

  ///\brief sets flag <<solidObstacle_ghostParticle>>, 
  /// which is an attribute of each particle object.
  ///
  /// this way the particles, which are constructed with a real particle
  /// constructor, are marked as ghost particles constituting solid obstacles
  /// within the calculation domain 
  void set_ghostPrtlSolidObstacle_flag(spParticle& prtl);
  
  
  ///\brief  sets  virtual viscosity needed for solid obstacles particles to model the no--slip boundary condition
  ///
  ///\param org_prtl: origin particle of the interaction (always a real particle, carries information of tangent plane
  ///\param dest_prtl: destination particle of interaction, can either be real particle, or boundary particle from domain edges or ghost particle for solid obstacles (SolObs). If ghost particle SolObs: assign virtual velocity  value  according to Morris1997 for other particle types just set virtual velocity equal to real velocity
  Vec2d set_virtual_velocity(spParticle& org_prtl, spParticle& dest_prtl);
 
  /// initialize ghost particle temperature with T_w 
  /// (wall temperature for isothermal boundary condition)
  void set_initial_Temperature_solObs_prtl(spParticle& prtl);


/// set Temperature for destination particle if it's a ghost particle
/// (for isothermal BC) according to the booundary condition
/// implementation method. 
/// i.e. depedning on settingseither linear extrapolation
/// or just maintain constant ghost prtl Temperature T_w
  double set_Temperature_SolObs_isothermal(spParticle& org_prtl, spParticle& dest_prtl);

  ///list for ghost particles forming solid obstacles within the calculation domain
  std::list<spParticle> ghost_prtl_SolObs_list; 
  
 protected:
  ///A local copy of the domain size
  const Vec2d domain_size;
  ///A local copy of the supportlength
  const double supportlength;
  /// A local copy of flag for virtual velocity type
  const int solObs_virt_veloc_type;
  /// a local copy of initiation member...
  const double d_realPart_solObs_min;
  /// a local copy of temperature boundary condition type for solid Obstacles
  const int solObs_thermal_BC_type;
  /// a local copy of wall surface temperature for isothermal BC solObs
  const double T_w_solObs_isothermal;
};

#endif //SOLIDOBSTACLES_H
