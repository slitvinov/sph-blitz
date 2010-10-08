/// \file solidcontext.cpp
/// \brief define solid context
#include "ParticleContext/solidcontext.h"
#include "particle.h"
#include "initiation.h"
#include <glog/logging.h>

SolidContext::SolidContext(const Initiation& ini):
  ini(ini) 
{
  /// procedure must be defined
  assert(ini.interp->isproc("getSolid"));
  LOG(INFO) << "Create SolidContext";
}

void SolidContext::AddParticle(const spParticle prtl) {
  // check if we should registered a particle as a solid 
  const Vec2d position = prtl->R;
  ini.interp->setdouble("x", position[0]);
  ini.interp->setdouble("y", position[1]);
  ini.interp->evalproc("getSolid");
  const bool isSolid = ini.interp->getval("issolid");
  if (isSolid) {
      LOG(INFO) << "Particle with position: " << prtl->R  << " is solid";
      solidIDset.insert(prtl->ID);
  } else {
      LOG(INFO) << "Particle with position: " << prtl->R  << " is NOT solid";
  }
}

/// remove particle from the context
void SolidContext::RemoveParticle(const spParticle prtl) {
  // particle is not solid any more
  solidIDset.erase(prtl->ID);
}

/// just assign a new postions to particle
void SolidContext::UpdatePosition(spParticle prtl, const Vec2d& newR) const {
  prtl->R = newR;
}

/// how velocity is updated depends on the type of particle
/// 'solid' particle is not updated
void SolidContext::UpdateVelocity(spParticle prtl, const Vec2d& newU) const {
  if ( solidIDset.find(prtl->ID) == solidIDset.end()  )  {
    // accelerate as usual
    prtl->U = newU;
  } 
  /// for solid particle do nothing
}

SolidContext::~SolidContext() {
  LOG(INFO) << "Destroy SolidContext";
}
