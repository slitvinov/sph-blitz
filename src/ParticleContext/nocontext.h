#ifndef SRC_PARTICECONTEXT_NONTEXT
#define SRC_PARTICECONTEXT_NONTEXT
/// \file nocontext.h
/// \brief define dummy context for particles
/// Particle moves with prescribed velocity
#include "ParticleContext/particlecontext.h"
class  Particle;

/// particles move as normal
class NoContext : public ParticleContext {
 public:
  /// constructor 
  NoContext();
  
  /// how we move particles depends on the position, velocity, and ID
  virtual void UpdatePosition(spParticle prtl, const Vec2d& newR) ;

  /// set a new velocity of the particle based on the context
  virtual void UpdateVelocity(spParticle prtl, const Vec2d& newU) const;

  /// set a new energy of the particle based on the context
  virtual void UpdateEnergy(spParticle prtl, const double newE) const;

  /// is particle interacting?
  virtual bool Interacting(spParticle Org, spParticle Dest) const;

  /// return context ID: 0 for nocontext and >0 for the special contextd
  /// used to in output.cpp
  virtual int ContextID(spParticle Org) const;

  /// destructor 
  virtual ~NoContext();
};
#endif // SRC_PARTICECONTEXT_NONTEXT
