///\file interactionangular.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
///\author changes by: Sergey Litvinov <slitvinov@gmail.com>

//----------------------------------------------------------------------------------------
//		defines interaction between particles
//----------------------------------------------------------------------------------------
#include <glog/logging.h>
#include <assert.h>

// ***** localincludes *****
#include "vec2d.h"
#include "Interaction/interactionangular.h"
#include "particle.h"
#include "initiation.h"

//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void InteractionAngular::UpdateForces() {
      const double rhoi = Org->rho; 
      const double rhoj = Dest->rho;
      const double Vi = mi/rhoi; 
      const double Vj = mj/rhoj;
      assert(Vi>0.0);
      assert(Vj>0.0);
      const double Vi2 = Vi*Vi; 
      const double Vj2 = Vj*Vj;
      const double shear_rij = 2.0*etai*etaj/(etai + etaj);
      const Vec2d Uij = Org->U - Dest->U;
      const double pi = Org->p; 
      const double pj = Dest->p;
      /// viscous forces
      const Vec2d dPdti_visc = -shear_rij*Fij*(Vi2 + Vj2) * Uij;
      /// pressure forces
      const Vec2d dPdti_pre = eij*Fij*rij*(pi*Vi2 + pj*Vj2);
      const Vec2d dPdti = dPdti_visc  + dPdti_pre;
      Org->dUdt += dPdti*rmi;
      Dest->dUdt -= dPdti*rmj;
};

InteractionAngular::InteractionAngular(const spParticle prtl_org, const spParticle prtl_dest, 
	      spKernel weight_function, const double dstc,
	      const Initiation& ini): 
  Interaction(prtl_org, prtl_dest, weight_function, dstc, ini) {
  assert(ini.simu_mode == 1);
};

InteractionAngular::~InteractionAngular() {
}
