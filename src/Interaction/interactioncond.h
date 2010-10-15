#ifndef SRC_INTERACTION_INTERACTIONCOND_H
#define SRC_INTERACTION_INTERACTIONCOND_H
/// \file interaction.h 
/// \brief Defines interaction between particles
#include "src/Interaction/interaction.h"
class Initiation;

/// Defines interaction between particles
class InteractionCond : public Interaction {
public:
  InteractionCond(const spParticle prtl_org, const spParticle prtl_dest, 
		spKernel weight_function, const double dstc,
		const Initiation& ini);
  virtual ~InteractionCond();
  void UpdateForces();
};

#endif //SRC_INTERACTION_INTERACTIONCOND_H
