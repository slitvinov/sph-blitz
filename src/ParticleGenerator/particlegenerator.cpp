#include "ParticleGenerator/particlegenerator.h"

#include "initiation.h"
#include <time.h>
#include <glog/logging.h>

ParticleGenerator::ParticleGenerator():
  engine(time(0)), 
  distrib(-1.0, 1.0),
  random_number(engine, distrib) {
}

Vec2d ParticleGenerator::getPosition(const Initiation& ini, 
				     const int i, const int k, const int j, const int m, 
				     const double delta, const double cll_sz) {
  Vec2d position((i - 1)*cll_sz + (k + 0.5)*delta, 
		 (j - 1)*cll_sz + (m + 0.5)*delta);
  if (ini.initial_perturb > 0.0) {
    position[0] +=  random_number() * delta * ini.initial_perturb;
    position[1] +=  random_number() * delta * ini.initial_perturb;
  }
  return Vec2d(position);
}

