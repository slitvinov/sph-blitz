#ifndef INTERACTIONCOMP_H
#define INTERACTIONCOMP_H
/// \file interaction.h 
/// \brief Defines interaction between particles
#include "Interaction/interaction.h"

class Initiation;

/// Defines interaction between particles
class InteractionComp : public Interaction {
public:
  ///constructor
  InteractionComp(const spParticle prtl_org, const spParticle prtl_dest, 
		  spKernel weight_function, const double dstc,
		  const Initiation& ini);
  virtual ~InteractionComp();
  void UpdateForces();
};

#endif //INTERACTIONCOMP_H
