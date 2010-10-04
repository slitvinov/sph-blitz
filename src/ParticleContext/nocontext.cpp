#include "ParticleContext/nocontext.h"
#include <glog/logging.h>

NoContext::NoContext() {
  LOG(INFO) << "Create NoContext";
}

const Vec2d NoContext::MoveParticle(const Vec2d& R, 
					const Vec2d& U, 
					const double dt, const int) const {
  // new position 
  return R + U * dt;
}

const Vec2d NoContext::AccelerateParticle(const Vec2d& U, 
					  const Vec2d& F,
					  const double dt, const int) const {
  // new velocity
  return U + F *dt;
}

NoContext::~NoContext() {
  LOG(INFO) << "Destroy NoContext";
}
