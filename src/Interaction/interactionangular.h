#ifndef INTERACTION_INTERACTIONANGULAR_H
#define INTERACTION_INTERACTIONANGULAR_H
/// \file interaction.h 
/// \brief Defines interaction between particles

#include "Interaction/interaction.h"
class Initiation;

/// Defines interaction between particles
class InteractionAngular : public Interaction {
public:
  InteractionAngular(const spParticle prtl_org, const spParticle prtl_dest, 
		spKernel weight_function, const double dstc,
		const Initiation& ini);
  virtual ~InteractionAngular();
  void UpdateForces();
};

#endif // INTERACTION_INTERACTIONANGULAR_H
