#ifndef INTERACTIONIN_H
#define INTERACTIONIN_H
/// \file interaction.h 
/// \brief Defines interaction between particles

#include "Interaction/interaction.h"
class Initiation;

/// Defines interaction between particles
class InteractionIn : public Interaction {
public:
  InteractionIn(const spParticle prtl_org, const spParticle prtl_dest, 
		spKernel weight_function, const double dstc,
		const Initiation& ini, const spSolidObstacles obstacles);
  virtual ~InteractionIn();
  void UpdateForces();
};

#endif //INTERACTIONIN_H
