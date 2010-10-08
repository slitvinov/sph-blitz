#ifndef SRC_PARTICLECONTEXT_PARTICECONTEXT
#define SRC_PARTICLECONTEXT_PARTICECONTEXT
/// \file particlecontext.h
/// \brief define abstract particle context class
#include "vec2d.h"
#include "glbtype.h"

/// defines how particle moves and accelerates 
class ParticleContext {
 public:
  /// constructor 
  ParticleContext();

  /// how we move particles depends on the position, velocity, and ID
  virtual void UpdatePosition(spParticle prtl, const Vec2d& newR) const = 0;

  /// get a new velocity of the particle based on the context
  virtual void UpdateVelocity(spParticle prtl, const Vec2d& newU) const = 0;

  /// add particle to the context
  virtual void AddParticle(const spParticle prtl) ;

  /// remove particle from the context
  virtual void RemoveParticle(const spParticle prtl) ;

  /// destructor 
  virtual ~ParticleContext();
};

#endif // SRC_PARTICLECONTEXT_PARTICECONTEXT


