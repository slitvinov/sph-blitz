#include <glog/logging.h>
#include "ParticleContext/nocontext.h"
#include "particle.h"

NoContext::NoContext() {
  LOG(INFO) << "Create NoContext";
}

/// just assign a new postions to particle
void NoContext::UpdatePosition(spParticle prtl, const Vec2d& newR) {
  prtl->R = newR;
}

/// just assign a new velocity to particle
void NoContext::UpdateVelocity(spParticle prtl, const Vec2d& newU) const {
  prtl->U = newU;
}

NoContext::~NoContext() {
  LOG(INFO) << "Destroy NoContext";
}
