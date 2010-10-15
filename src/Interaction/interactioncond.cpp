///\file interaction.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//		defines interaction between particles
//		interaction.cpp
//----------------------------------------------------------------------------------------
#include <glog/logging.h>
#include <assert.h>

// ***** localincludes *****
#include "src/Kernel/kernel.h"
#include "src/Interaction/interactioncond.h"
#include "src/ParticleContext/particlecontext.h"
#include "src/particle.h"
#include "src/initiation.h"
#include "src/material.h"

//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void InteractionCond::UpdateForces() {
  ///  \todo{This condition check is very slow}
  if (ini.context->Interacting(Org, Dest)) {
    const double rhoi = Org->rho; 
    const double rhoj = Dest->rho;

    const double ki = Org->k_thermal;
    const double kj = Dest->k_thermal;

    /// \todo{should be updated outside}
    const double Ti = (Org->e)/(Org->mtl->cv);
    const double Tj = (Dest->e)/(Org->mtl->cv);

    /// see eq. (28) in Cleary1999 
    const double dedt_local = 4.0* mj / (rhoi*rhoj) * (ki*kj)/(ki+kj) * (Ti - Tj) * (-Fij);

    Org->dedt += dedt_local;
    Dest->dedt -= dedt_local;
  }
}

InteractionCond::InteractionCond(const spParticle prtl_org, const spParticle prtl_dest, 
	      spKernel weight_function, const double dstc,
	      const Initiation& ini): 
  Interaction(prtl_org, prtl_dest, weight_function, dstc, ini) {
  assert(ini.simu_mode == 3);
}

InteractionCond::~InteractionCond() {
  
}
