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

int ParticleGenerator::getParticleMaterialNo(Initiation& ini ,
					     const Vec2d& position) {
  // if no proc in the tcl file set default material number 
  if (!ini.interp->isproc("getmatNo") ) {
    const int default_materail_number = 1;
    LOG(INFO) << "return default material number" ;
    return default_materail_number;
  } else {
    // set position of the particle and call the function
    ini.interp->setdouble("x", position[0]);
    ini.interp->setdouble("y", position[1]);
    ini.interp->evalproc("getmatNo");
    const int no = ini.interp->getval("no");
    if (no>ini.number_of_materials - 1) {
      LOG(ERROR) << "number of material is " << no << '\n' << 
	"maximum material number is " << ini.number_of_materials - 1;
      std::exit(EXIT_FAILURE);
    } 
    if (no < 0) {
      LOG(ERROR) << "number of material is " << no << '\n';
      std::exit(EXIT_FAILURE);
    }
    LOG(INFO) << "for particle " << position << " return material number " << no ;
    return no;
  } 
}

Vec2d ParticleGenerator::getParticleVelocity(Initiation& ini ,
					     const Vec2d& position) {
  // if no proc in the tcl file set default material number 
  if (!ini.interp->isproc("getVelocity") ) {
    LOG(INFO) << "return default velocity: " << ini.U0;
    return Vec2d(ini.U0);
  } else {
    // set position of the particle and call the function
    ini.interp->setdouble("x", position[0]);
    ini.interp->setdouble("y", position[1]);
    ini.interp->evalproc("getVelocity");
    const double vx  = ini.interp->getval("vx");
    const double vy  = ini.interp->getval("vy");
    const Vec2d velocity(vx, vy);
    LOG(INFO) << "for particle " << position << " return velocity " << velocity;
    return velocity;
  } 
}

