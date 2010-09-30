#ifndef INTERACTION_H
#define INTERACTION_H
/// \file interaction.h 
/// \brief Defines interaction between particles

#include "src/glbtype.h"

class Initiation;

/// Defines interaction between particles
class Interaction {
protected:
  /// destructor 
  virtual ~Interaction();

  /// local reference to initiation object
  const Initiation& ini;


  //particle pair
  spParticle Org;	///<pointer to particle with larger ID (of particle pair)
  spParticle Dest;	///<pointer to particle with smaller ID (of particle pair)

  const double mi;///<mass particle i
  const double mj;///<mass particle j

  const double rmi;///<reciprocal value of mass particle i
  const double rmj;///<reciprocal value of mass particle j
 
  //distance between the two particles, weight and derivatives
  double rij; ///<distance between 2 particles
  double rrij; ///<reciprocal value of distance between 2 particles
  double Wij; ///<scalar value of the kernel
  double Fij; ///<scalar kernel gradient
  Vec2d gradWij; ///<vector kernel gradient
  Vec2d eij; ///<pair direction from orginal particle to destination particle 
  double Vi;///< volume of particle i (origin particle)
  double Vj;///< volume of particle j (dest. particle)
  double etai;///<(shear) viscosity for particle i
  double etaj;///<(shear) viscosity for particle j
  double zetai;///<bulk viscosity for particle i
  double zetaj;///<bulk viscosity for particle j

public:
  ///constructor
  Interaction(const spParticle prtl_org, const spParticle prtl_dest, 
              spKernel weight_function, const double dstc,
              const Initiation& ini);
	

  ///\brief renew pair parameters and changing pair values
  ///
  ///Changes: Interaction object\n
  ///Depends on: Interaction Object, Org, Dest
  void RenewInteraction(spKernel weight_function);

  //pair interaction

  ///\brief summation of the density
  ///
  ///Changes: Org(rho:summation), Dest(rho:summation)\n
  ///Depends on: Interaction Object, Org(rho), Dest(rho)
  ///Remark: the idea is different from the original sph method
  void SummationDensity();

  ///update forces
  virtual void UpdateForces() = 0; 

  // update forces and rho
  void UpdateForcesAndRho();

  spParticle  getOrigin() const;
  spParticle  getDest() const;
  double getWij() const;
  Vec2d getGradWij() const;
  double get_rij() const;
};

#endif //INTERACTION_H