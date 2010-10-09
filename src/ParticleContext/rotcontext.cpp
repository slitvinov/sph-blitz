/// \file rotcontext.cpp
/// \brief define a context for rotating particle
#include "ParticleContext/rotcontext.h"
#include "particle.h"
#include "initiation.h"
#include <glog/logging.h>

RotContext::RotContext(const Initiation& ini):
  ini(ini) {
  /// create 3D objects from user input
  centerRot = ini.interp->getat("centerRot", 1), ini.interp->getat("centerRot", 2), 0.0;
  omegaRot = ini.interp->getval("omegaRot");
  if (ini.interp->exist("axRot")) {
    axRot = ini.interp->getat("axRot", 1), 
      ini.interp->getat("axRot", 2), 
      ini.interp->getat("axRot", 3);
  } else {
    /// default value for rotation axis
    axRot = 0, 0, 1;
  }
  /// getRot procedure in TCL file must be defined
  assert(ini.interp->isproc("getRot"));
  LOG(INFO) << "centerRot : " << centerRot;
  LOG(INFO) << "omegaRot : " << omegaRot;
  LOG(INFO) << "axRot : " << axRot;
  LOG(INFO) << "Create RotContext";
  const double time = ini.timer->getTime();
  assert(time > -1e-12);
  posRotMat = getRotMat(axRot, omegaRot * time);
  LOG(INFO) << "at time " << time;
  LOG(INFO) << "Rot matrix is: " << posRotMat;
}

void RotContext::AddParticle(const spParticle prtl) {
  // check if we should registered a particle as a solid 
  const Vec2d position = prtl->R;
  ini.interp->setdouble("x", position[0]);
  ini.interp->setdouble("y", position[1]);
  ini.interp->evalproc("getRot");
  const bool isRot = ini.interp->getval("isrot");
  if (isRot) {
      LOG(INFO) << "Particle with position: " << prtl->R  << " is rotating";
      rotIDset.insert(prtl->ID);
  } else {
      LOG(INFO) << "Particle with position: " << prtl->R  << " is NOT rotating";
  }
}

/// remove the particle from the context
void RotContext::RemoveParticle(const spParticle prtl) {
  // particle is not rotating any more
  rotIDset.erase(prtl->ID);
}

/// assign a new postions to the particle
void RotContext::UpdatePosition(spParticle prtl, const Vec2d& newR) const {
  if ( rotIDset.find(prtl->ID) == rotIDset.end()  )  {
      prtl->R = newR;
  } else {
    /// it is rotating particle --- ignore newR and updated position in specified way
    /// build 3 dimensional vector for the postions
    const blitz::TinyVector<double, 3> oldPos(prtl->R[0], prtl->R[1], 0.0);
    const blitz::TinyVector<double, 3> dpos = oldPos - centerRot;
    /// rotate it 
    const blitz::TinyVector<double, 3> newPos = centerRot + 
      product(posRotMat, dpos);
    /// and plug it back
    prtl->R = newPos[0], newPos[1];
  }
  
}

/// how velocity is updated depends on the type of particle
/// 'rotating' particle is not updated
void RotContext::UpdateVelocity(spParticle prtl, const Vec2d& newU) const {
  if ( rotIDset.find(prtl->ID) == rotIDset.end()  )  {
    // accelerate as usual
    prtl->U = newU;
  }  else {
    /// it is rotating particle --- ignore newU and updated velocity in specified way
    /// build 3 dimensional vector for the postions
    const blitz::TinyVector<double, 3> pos(prtl->R[0], prtl->R[1], 0.0);
    /// get liniar velocity
    const blitz::TinyVector<double, 3> dpos = pos - centerRot;
    const blitz::TinyVector<double, 3> newVel = omegaRot*cross(axRot, dpos);
    /// and plug it back
    prtl->U = newVel[0], newVel[1];
  }
}

void RotContext::notify() {
  /// here rotation matrix must be updated
  const double time = ini.timer->getTime();
  assert(time > 0.0);
  const double pi = 3.1415926;
  posRotMat = getRotMat(axRot, -2.0*pi*omegaRot * time);
  LOG(INFO) << "at time " << time;
  LOG(INFO) << "Rot matrix is: " << posRotMat;
}

RotContext::~RotContext() {
  LOG(INFO) << "Destroy RotContext";
}

blitz::TinyMatrix<double, 3, 3> getRotMat(const blitz::TinyVector<double, 3> u, 
					  const double theta) {
  const double cost = cos(theta);
  const double sint = sin(theta);
  const double omcos = 1 - cos(theta);
  const double ux = u[0];
  const double uy = u[1];
  const double uz = u[2];
  blitz::TinyMatrix<double, 3, 3> R;
  R = 
    cost + ux*ux*omcos, ux*uy*omcos-uz*sint, ux*uz*omcos + uy*sint,
     uy*ux*omcos + uz*sint, cost+uy*uy*omcos, uy*uz*omcos - ux*sint,
     uz*ux*omcos - uy*sint, uz*uy*omcos+ux*sint, cost+uz*uz*omcos
    ;
  return R;
}
