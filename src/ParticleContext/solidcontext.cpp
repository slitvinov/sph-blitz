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

const Vec2d SolidContext::MoveParticle(const Vec2d& R, 
				       const Vec2d& U, 
				       const double dt, const int) const {
  // move solid particle as usual, id is not used
  return R + U * dt;
}


const Vec2d SolidContext::AccelerateParticle(const Vec2d& U, 
					     const Vec2d& F,
					     const double dt, const int id) const {
  if ( solidIDset.find(id) == solidIDset.end()  )  {
    // accelerate as usual
    return U + F *dt;
  } else {
      // if it is solid do not change velocity
    return U; 
  }
}

SolidContext::~SolidContext() {
  LOG(INFO) << "Destroy SolidContext";
}
