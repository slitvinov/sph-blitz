#ifndef SRC_PARTICECONTEXT_SOLIDCONTEXT
#define SRC_PARTICECONTEXT_SOLIDCONTEXT
/// \file nocontext.h
/// \brief define dummy context for particles
#include "ParticleContext/particlecontext.h"
#include <set>
class  Particle;

/// particles move as normal
class SolidContext : public ParticleContext {
 public:
  /// constructor 
  SolidContext();
  
  /// move particles as normal
  virtual const Vec2d MoveParticle(const Vec2d& R, const Vec2d& U, const double dt, const int id) const;

  /// accelerate particles as normal
  virtual const Vec2d AccelerateParticle(const Vec2d& U, const Vec2d& F, const double dt, const int id) const;

  /// add particle to the context (only works for the initial conditions)
  virtual void AddParticle(const spParticle prtl) ;

  /// remove particle from the context
  virtual void RemoveParticle(const spParticle prtl) ;

  /// destructor 
  virtual ~SolidContext();

 private:
  std::set<int> solidIDset;
};

#endif // SRC_PARTICECONTEXT_SOLIDCONTEXT


