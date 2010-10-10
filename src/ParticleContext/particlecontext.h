#ifndef SRC_PARTICLECONTEXT_PARTICECONTEXT
#define SRC_PARTICLECONTEXT_PARTICECONTEXT
/// \file particlecontext.h
/// \brief define abstract particle context class
#include "src/vec2d.h"
#include "src/glbtype.h"
#include "src/Timer/timeobserver.h"

/// defines how particle moves and accelerates 
class ParticleContext : public TimeObserver{
 public:
  /// constructor 
  ParticleContext();

  /// how we move particles depends on the position, velocity, and ID
  virtual void UpdatePosition(spParticle prtl, const Vec2d& newR) = 0;

  /// get a new velocity of the particle based on the context
  virtual void UpdateVelocity(spParticle prtl, const Vec2d& newU) const = 0;

  /// get a new velocity of the particle based on the context
  virtual bool Interacting(spParticle Org, spParticle Dest) const = 0;

  /// return context ID: 0 for nocontext and >0 for the special contextd
  /// used to in output.cpp
  virtual int ContextID(spParticle Org) const = 0;


  /// add particle to the context
  virtual void AddParticle(const spParticle prtl) ;

  /// remove particle from the context
  virtual void RemoveParticle(const spParticle prtl) ;

  /// destructor 
  virtual ~ParticleContext();
 private:
  virtual void notify();
};

#endif // SRC_PARTICLECONTEXT_PARTICECONTEXT


