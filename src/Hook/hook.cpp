#include "src/Hook/hook.h"
#include <boost/foreach.hpp>
#include <glog/logging.h>
#include "src/initiation.h"
#include "src/particle.h"
#include "src/ParticleContext/particlecontext.h"

Hook::Hook (const Initiation& ini): 
  ini(ini), wasUsed(false)
{ }

void Hook::Filter(std::list<spParticle> particle_list) {
  LOG(INFO) << "applaying hook";
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ini.interp->setdouble("x", prtl->R[0]);
    ini.interp->setdouble("y", prtl->R[1]);
    ini.interp->setdouble("vx", prtl->U[0]);
    ini.interp->setdouble("vy", prtl->U[1]);
    ini.interp->evalproc("filter_hook");
    prtl->U[0] = ini.interp->getval("vx");
    prtl->U[1] = ini.interp->getval("vy");
    bool issolid = ini.interp->getval("issolid");
    if (!issolid) {
      ini.context->RemoveParticle(prtl);
    }
  }
}

bool Hook::UseHook(const double time) {
  if ( (!wasUsed) && (time>ini.Hook_time) ) {
    wasUsed = true;
    return true;
  } else {
    return false;
  }
}
