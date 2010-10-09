#include <glog/logging.h>
#include <boost/smart_ptr/make_shared.hpp>
#include "src/initiation.h"
#include "src/material.h"
#include "src/ParticleContext/rotcontext.h"
#include "src/particle.h"
int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  Initiation ini("rotating-cylinder", std::string(""));
  spMaterial  mtl = spMaterial(new Material(ini, 1));
    
  /// create a particle 
  Vec2d R(0.6, 0.5);
  spParticle prtl = boost::make_shared<Particle>(R, Vec2d(0, 0), 1.0, 1.0, 1.0, mtl);

  /// create a new objects of class RotContext
  RotContext rc(ini) ;

  rc.AddParticle(prtl);
  rc.UpdatePosition(prtl, Vec2d(0.0, 0.0));
  LOG(ERROR) << "prtl->R = " << prtl->R;
  LOG(ERROR) << "prtl->U = " << prtl->U;

  rc.UpdateVelocity(prtl, Vec2d(0.0, 0.0));
  LOG(ERROR) << "prtl->R = " << prtl->R;
  LOG(ERROR) << "prtl->U = " << prtl->U;

  ini.timer->updateTime(1.0);
  rc.UpdatePosition(prtl, Vec2d(0.0, 0.0));
  LOG(ERROR) << "prtl->R = " << prtl->R;
}
