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

/// set a new energy of the particle based on the context
void NoContext::UpdateEnergy(spParticle prtl, const double newE) const {
  prtl->e = newE;
}

/// get a new acceleration of the particle based on the context
bool NoContext::Interacting(spParticle, spParticle) const {
  return true;
}

int NoContext::ContextID(spParticle) const {
  return 0;
}

NoContext::~NoContext() {
  LOG(INFO) << "Destroy NoContext";
}
