/// \file solidcontext.cpp
/// \brief define solid context
#include "ParticleContext/solidcontext.h"
#include "particle.h"
#include <glog/logging.h>

SolidContext::SolidContext() {
  LOG(INFO) << "Create SolidContext";
}

void SolidContext::AddParticle(const spParticle prtl) {
  // regestre  particle as a solid 
  LOG(INFO) << "Particle with position: " << prtl->R  << " is solid";
  solidIDset.insert(prtl->ID);
}

/// remove particle from the context
void SolidContext::RemoveParticle(const spParticle prtl) {
  // particle is not solid any more
  solidIDset.erase(prtl->ID);
}

const Vec2d SolidContext::MoveParticle(const Vec2d& R, 
				       const Vec2d& U, 
				       const double dt, const int id) const {
  // move solid particle as usual
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
