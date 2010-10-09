#ifndef SRC_PARTICECONTEXT_NONTEXT
#define SRC_PARTICECONTEXT_NONTEXT
/// \file nocontext.h
/// \brief define dummy context for particles
#include "ParticleContext/particlecontext.h"
class  Particle;

/// particles move as normal
class NoContext : public ParticleContext {
 public:
  /// constructor 
  NoContext();
  
  /// how we move particles depends on the position, velocity, and ID
  virtual void UpdatePosition(spParticle prtl, const Vec2d& newR) ;

  /// get a new velocity of the particle based on the context
  virtual void UpdateVelocity(spParticle prtl, const Vec2d& newU) const;

  /// destructor 
  virtual ~NoContext();
};
#endif // SRC_PARTICECONTEXT_NONTEXT
