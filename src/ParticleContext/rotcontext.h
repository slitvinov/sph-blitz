#ifndef SRC_PARTICECONTEXT_ROTCONTEXT
#define SRC_PARTICECONTEXT_ROTCONTEXT
/// \file rotcontext.h
/// \brief define rotating object
#include <blitz/tinymat.h>
#include <set>
#include "ParticleContext/particlecontext.h"
#include "Timer/timeobserver.h"
class  Particle;
class Initiation;

/// A class to move particle if a part of them is solid
class RotContext : public ParticleContext , public TimeObserver {
 public:
  /// constructor
  explicit RotContext(const Initiation& ini);
  
  /// move particles as normal
  virtual void UpdatePosition(spParticle prtl, const Vec2d& newUR) const;

  /// update velocity as normal
  virtual void UpdateVelocity(spParticle prtl, const Vec2d& newU) const;

  /// add particle to the context (only works for the initial conditions)
  virtual void AddParticle(const spParticle prtl) ;

  /// remove particle from the context
  virtual void RemoveParticle(const spParticle prtl) ;

  /// destructor 
  virtual ~RotContext();

 private:
  /// this function is called then simulation time is updated
  /// RotContext class must be 'attached' to Timer
  virtual void notify();
  
  /// a set with IDs of rotating particles
  std::set<int> rotIDset;

  /// the class stores its own reference to Initiation
  const Initiation& ini;

  /// rotation matrix to get postion of the particle
  blitz::TinyMatrix<double, 3, 3> posRotMat;

  /// rotation axis
  blitz::TinyVector<double, 3> axRot;
  
  /// angular velocity (scalar)
  double omegaRot;

  /// center of rotation
  blitz::TinyVector<double, 3> centerRot;
};

#endif // SRC_PARTICECONTEXT_ROTCONTEXT


