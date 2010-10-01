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
  
  /// move particles as normal
  virtual const Vec2d MoveParticle(const Vec2d& R, const Vec2d& U, const double dt, const int id) const;

  /// accelerate particles as normal
  virtual const Vec2d AccelerateParticle(const Vec2d& U, const Vec2d& F, const double dt, const int id) const;

  /// destructor 
  virtual ~NoContext();
};

#endif // SRC_PARTICECONTEXT_NONTEXT
