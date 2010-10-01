#ifndef SRC_PARTICLECONTEXT_PARTICECONTEXT
#define SRC_PARTICLECONTEXT_PARTICECONTEXT
/// \file particlecontext.h
/// \brief define abstract particle context class
#include "vec2d.h"
#include "glbtype.h"

class  Particle;

/// defines how particle moves and accelerates 
class ParticleContext {
 public:
  /// constructor 
  ParticleContext();
  
  /// how we move particles depends on the position, velocity, and ID
  /// it is enough to model immobile particles
  /// the method returns a new postion 
  /// It can be better to just take a particle and transform it by context
  virtual const Vec2d MoveParticle(const Vec2d& R, const Vec2d& U, const double dt, const int id) const = 0;

  /// get a new velocity of the particle based on the context
  virtual const Vec2d AccelerateParticle(const Vec2d& U, const Vec2d& F, const double dt, const int id) const = 0;

  /// add particle to the context
  virtual void AddParticle(const spParticle prtl) ;

  /// remove particle from the context
  virtual void RemoveParticle(const spParticle prtl) ;

  /// destructor 
  virtual ~ParticleContext();
};

#endif // SRC_PARTICLECONTEXT_PARTICECONTEXT


