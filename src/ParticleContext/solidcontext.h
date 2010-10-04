#ifndef SRC_PARTICECONTEXT_SOLIDCONTEXT
#define SRC_PARTICECONTEXT_SOLIDCONTEXT
/// \file nocontext.h
/// \brief define dummy context for particles
#include "ParticleContext/particlecontext.h"
#include <set>
class  Particle;
class Initiation;

/// A class to move particle if a part of them is solid
class SolidContext : public ParticleContext {
 public:
  /// constructor
  explicit SolidContext(const Initiation& ini);
  
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
  /// a set with IDs of solid particles
  std::set<int> solidIDset;

  /// the class stores it own reference to Initiation
  const Initiation& ini;
};

#endif // SRC_PARTICECONTEXT_SOLIDCONTEXT


