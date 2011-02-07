#include "src/Hook/hook.h"
#include "src/initiation.h"
#include <boost/foreach.hpp>
#include "src/particle.h"

Hook::Hook (const Initiation& ini): 
  ini(ini), wasUsed(false)
{
}

void Hook::Filter(std::list<spParticle> particle_list) {
  BOOST_FOREACH(spParticle prtl, particle_list) {
    ini.interp->setdouble("x", prtl->R[0]);
    ini.interp->setdouble("y", prtl->R[1]);
    ini.interp->setdouble("vx", prtl->U[0]);
    ini.interp->setdouble("vy", prtl->U[1]);
    ini.interp->evalproc("filter_hook");
    prtl->U[0] = ini.interp->getval("vx");
    prtl->U[1] = ini.interp->getval("vy");
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
