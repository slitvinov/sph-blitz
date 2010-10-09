#include <glog/logging.h>
#include <boost/smart_ptr/make_shared.hpp>
#include "src/initiation.h"
#include "src/material.h"
#include "src/ParticleContext/rotcontext.h"
#include "src/particle.h"
#include "src/glbtype.h"
int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  Initiation ini("rotating-cylinder", std::string(""));
  spMaterial  mtl = spMaterial(new Material(ini, 1));

  
  /// should be the same as in tcl file
  const double omega = 1.0;
  const Vec2d Rcenter(0.5, 0.5);

  /// create a particle 
  Vec2d R(0.48, 0.65);
  spParticle prtl = boost::make_shared<Particle>(R, Vec2d(0, 0), 1.0, 1.0, 1.0, mtl);

  /// create a new objects of class RotContext
  spParticleContext rc = boost::make_shared<RotContext>(ini) ;
  ini.timer->addTimeObserver(rc);

  rc->AddParticle(prtl);
  rc->UpdatePosition(prtl, Vec2d(0.0, 0.0));
  LOG(ERROR) << "prtl->R = " << prtl->R;
  LOG(ERROR) << "prtl->U = " << prtl->U;

  rc->UpdateVelocity(prtl, Vec2d(0.0, 0.0));
  LOG(ERROR) << "prtl->R = " << prtl->R;
  LOG(ERROR) << "prtl->U = " << prtl->U;

  ini.timer->updateTime(0.0);
  ini.timer->update_dt(1.0);
  const Vec2d oldR(prtl->R);

  rc->UpdatePosition(prtl, Vec2d(0.0, 0.0));
  LOG(ERROR) << "prtl->R = " << prtl->R;

  const Vec2d dR1 = oldR - Rcenter;
  const Vec2d dR2 = prtl->R - Rcenter;
  LOG(ERROR) << "dR1 = " << dR1;
  LOG(ERROR) << "dR2 = " << dR2;
  const double cosp = dot(dR1, dR2)/(norm(dR1) * norm(dR2));
  LOG(ERROR) << "cosp = " << cosp;
  LOG(ERROR) << "cos(omega * dt) = " << cos(omega * ini.timer->get_dt());
  
}
