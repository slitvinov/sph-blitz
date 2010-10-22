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
#include "Kernel/kernel.h"
#include "interactionin.h"
#include "particle.h"
#include "initiation.h"
#include "glbfunc.h"


//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void InteractionIn::UpdateForces() {
      const double rhoi = Org->rho; 
      const double rhoj = Dest->rho;

      LOG_EVERY_N(INFO, 10000) << "Interaction::UpdateForces(), simu_mode=1";
      const double Vi = mi/rhoi; 
      const double Vj = mj/rhoj;
      
      assert(Vi>0.0);
      assert(Vj>0.0);
      const double Vi2 = Vi*Vi; 
      const double Vj2 = Vj*Vj;
      const double shear_rij = 2.0*etai*etaj/(etai + etaj);
      LOG_EVERY_N(INFO, 10000) << "etai = " << etai;
      LOG_EVERY_N(INFO, 10000) << "shear_rij = " << shear_rij;
      
      /// viscous and pressure parts
      const Vec2d Ui = Org->U; 
      const Vec2d Uj = Dest->U;
      const Vec2d Uij = Ui - Uj;

      const double pi = Org->p; 
      const double pj = Dest->p;
      const Vec2d dPdti_visc = -shear_rij*Fij*(Vi2 + Vj2) * Uij;
      const Vec2d dPdti_pre = - eij*Fij*rij*(pi*Vi2 + pj*Vj2);
      
      const Vec2d dPdti = dPdti_visc  + dPdti_pre;
      LOG_EVERY_N(INFO, 10000) << "Ui = " << Ui;
      LOG_EVERY_N(INFO, 10000) << "Uj = " << Uj;
      LOG_EVERY_N(INFO, 10000) << "dPdti = " << dPdti;
      
      Org->dUdt += dPdti*rmi;
      Dest->dUdt -= dPdti*rmj;
};

InteractionIn::InteractionIn(const spParticle prtl_org, const spParticle prtl_dest, 
	      spKernel weight_function, const double dstc,
	      const Initiation& ini): 
  Interaction(prtl_org, prtl_dest, weight_function, dstc, ini)
{
  assert(ini.simu_mode == 1);
  LOG_EVERY_N(INFO, 10000) << "Create incompressible interaction";
};



InteractionIn::~InteractionIn() {
  LOG_EVERY_N(INFO, 100000) << "Incompressible Interaction destroyed" ;
}


