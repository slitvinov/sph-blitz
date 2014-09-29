#include "input.h"
#include "material.h"
#include "polymerparticle.h"
#include "vec2d.h"
#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif


Input::Input(string filename,
	     Material* mtl):
  iparticle_(0),
  mtl_(mtl)
{  
  ///netCDF file
  NcFile nc(filename.c_str());
  long maxtime = nc.get_dim("timestep")->size();
  maxiparticle_ = nc.get_dim("iparticle")->size();
  ndim = nc.get_dim("space")->size();
  ///get the snapshot of the last timestep
  NcVar* t = nc.get_var("t");
  NcVar* R = nc.get_var("R");
  NcVar* U = nc.get_var("U");
  NcVar* rho = nc.get_var("rho");
  NcVar* type = nc.get_var("type");
  NcVar* T = nc.get_var("T");
  
  const long idx[3] = {1, maxiparticle_, ndim};
  //  const long time_idx[2] = {1, maxiparticle_};
  const long ctime_idx[1] = {1};
  t->set_cur(maxtime-1);
  R->set_cur(maxtime-1, 0, 0);
  U->set_cur(maxtime-1, 0, 0);
  rho->set_cur(maxtime-1, 0);
  T->set_cur(maxtime-1, 0);
  type->set_cur(maxtime-1, 0);

  
  t->get(&ctime, ctime_idx);

  typec = new double[maxiparticle_];
  type->get(typec, idx);


  rhoc = new double[maxiparticle_];
  rho->get(rhoc, idx);

  Tc = new double[maxiparticle_];
  T->get(Tc, idx);    

  Rc = new double[maxiparticle_*ndim];
  //  double Rc[1][maxiparticle_][ndim];
  R->get(Rc, idx);

  Uc = new double[maxiparticle_*ndim];
  //  double Uc[1][maxiparticle_][ndim];
  U->get(Uc, idx);
  
//   for (long q=0; q<maxiparticle_; q++) {
//     cout << typec[q] << '\n';
//   }
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("input");
  LOG4CXX_DEBUG(Logger, "Start with time level: " + 
		stringify(ctime));
#endif
  //  cout << "ctime = " << ctime << '\n';
}

Particle* Input::Next() {
  Particle* pa;
  double eps = 1e-3;
  Vec2d pos;

  pos[0] = Rc[ndim*iparticle_];
  pos[1] = Rc[ndim*iparticle_ + 1];
// #ifdef DEBUG
//   cout << pos << '\n';
// #endif

  Vec2d vel;
  vel[0] = Uc[ndim*iparticle_];
  vel[1] = Uc[ndim*iparticle_ + 1];

  double pressure = mtl_->get_p(rhoc[iparticle_]);
  if (abs(typec[iparticle_]) < eps) {
    ///create plane particle
    ///Fix::
    pa = new Particle(pos, vel, 
		      rhoc[iparticle_],
		      pressure,
		      Tc[iparticle_],
		      *mtl_);
  }
  else {
    ///create polymer particle
    pa = new PolymerParticle(pos, vel, 
			     rhoc[iparticle_],
			     pressure,
			     Tc[iparticle_],
			     *mtl_);
  }      
  iparticle_++;  
  return pa;
}

bool Input::isEnd() const{
  return (iparticle_ == (maxiparticle_));
}

double Input::getTime() const {
  return ctime;
}

Input::~Input() {
  delete[] typec;
  delete[] rhoc;
  delete[] Tc;
  delete[] Rc;
  delete[] Uc;
}
