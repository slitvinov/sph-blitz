#ifndef INTERACTIONS1_H
#define INTERACTIONS1_H
/// \file interaction.h 
/// \brief Defines interaction between particles

#include "Interaction/interaction.h"
class Initiation;

/// Defines interaction between particles
class InteractionS1 : public Interaction {
public:
  InteractionS1(const spParticle prtl_org, const spParticle prtl_dest, 
		spKernel weight_function, const double dstc,
		const Initiation& ini);
  virtual ~InteractionS1();
  void UpdateForces();
};

#endif //INTERACTIONS1_H
