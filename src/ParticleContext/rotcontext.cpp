/// \file rotcontext.cpp
/// \brief define solid context
#include "ParticleContext/rotcontext.h"
#include "particle.h"
#include "initiation.h"
#include <glog/logging.h>

RotContext::RotContext(const Initiation& ini):
  ini(ini) 
{
  /// procedure must be defined
  assert(ini.interp->isproc("getRot"));
  LOG(INFO) << "Create RotContext";
}

void RotContext::AddParticle(const spParticle prtl) {
  // check if we should registered a particle as a solid 
  const Vec2d position = prtl->R;
  ini.interp->setdouble("x", position[0]);
  ini.interp->setdouble("y", position[1]);
  ini.interp->evalproc("getRot");
  const bool isSolid = ini.interp->getval("isrot");
  if (isSolid) {
      LOG(INFO) << "Particle with position: " << prtl->R  << " is rotating";
      solidIDset.insert(prtl->ID);
  } else {
      LOG(INFO) << "Particle with position: " << prtl->R  << " is NOT rotating";
  }
}

/// remove the particle from the context
void RotContext::RemoveParticle(const spParticle prtl) {
  // particle is not solid any more
  solidIDset.erase(prtl->ID);
}

/// assign a new postions to the particle
void RotContext::UpdatePosition(spParticle prtl, const Vec2d& newR) const {
  prtl->R = newR;
}

/// how velocity is updated depends on the type of particle
/// 'solid' particle is not updated
void RotContext::UpdateVelocity(spParticle prtl, const Vec2d& newU) const {
  if ( solidIDset.find(prtl->ID) == solidIDset.end()  )  {
    // accelerate as usual
    prtl->U = newU;
  } 
  /// for solid particle do nothing, velocity is constant
}

void RotContext::notify() {
  /// here rotation matrix must be updated
}


RotContext::~RotContext() {
  LOG(INFO) << "Destroy RotContext";
}
