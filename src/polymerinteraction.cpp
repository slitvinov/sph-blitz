#include <gsl/gsl_const_mksa.h>
#include "interaction.h"
#include "polymerinteraction.h"
#include "interaction.h"
#include "particle.h"
#include "polymerparticle.h"
#include "initiation.h"
#include "abspolymercreator.h"
#include "simplepolymercreator.h"

extern double k_bltz;

PolymerInteraction::PolymerInteraction(PolymerParticle *prtl_org, 
				       PolymerParticle *prtl_dest, 
				       Force **forces,
				       QuinticSpline &weight_function, 
				       double dstc):

Interaction(prtl_org, 
	    prtl_dest, 
	    forces,
	    weight_function, 
	    dstc) {
  ///regestry new polymer interaction
  //1  Initiation* ini = Initiation::Instance();
//   cout << "******Create polymer interaction******" << '\n';
//   cout << prtl_org->getPolyID() << '\n';
//   cout << prtl_org->getParticleID() << '\n';
//   cout << prtl_dest->getPolyID() << '\n';
//   cout << prtl_dest->getParticleID() << '\n';
//   cout << "************" << '\n';
  assert(abs(prtl_org->getPolyID() - prtl_dest->getPolyID()) == 1);
  //  ini->getPolymerCreator()->push_back(this);
// #ifdef DEBUG

// #endif
  
};

PolymerInteraction::~PolymerInteraction() {
}

void PolymerInteraction::UpdateForces() {
  //pressure, density and inverse density 
  //and middle point pressure
  double pi, rhoi, Vi, rVi, pj, rhoj, Vj, rVj, Uijdoteij; 
  //velocity and velocity difference
  Vec2d Ui, Uj, Uij; 
  
  //define pair values change in sub time steps
  rhoi = Org->rho(); rhoj = Dest->rho();
  Vi = mi/rhoi; Vj = mj/rhoj;
  rVi = 1.0/Vi; rVj = 1.0/Vj;
  pi = Org->getP(); pj = Dest->getP();
  Ui = Org->U(); Uj = Dest->U();
  Uij = Ui - Uj;
  Uijdoteij = dot(Uij, eij);
  
  //pair focres or change rate
  Vec2d dPdti, dUi; //mometum change rate
  double drhodti; //density change rate
  double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
  //artificial viscosity or Neumann_Richtmyer viscosity
  double theta, Csi, Csj, NR_vis;
  Csi = Org->getCs(); Csj = Dest->getCs();
  theta = Uijdoteij*rij*delta/(rij*rij + 0.01*delta*delta);
  NR_vis = Uijdoteij > 0.0 ? 0.0 : art_vis*theta*(rhoi*Csi*mj + rhoj*Csj*mi)/(mi + mj);
  
  //normalize velocity
  dUi = - eij*theta*Wij*art_vis/(rhoi + rhoj);

  //density change rate
  drhodti = - Fij*rij*dot((Ui*Vi2 - Uj*Vj2), eij);
  
  //momentum change rate
  dPdti =   eij*Fij*rij*(pi*Vi2 + pj*Vj2)
    - ((Uij - eij*Uijdoteij)*shear_rij + eij*(Uijdoteij*2.0*bulk_rij + NR_vis))
    *Fij*(Vi2 + Vj2);
  
  // cout << "Particle type: " << Org->getParticleType() 
//        << '\n' 
//        << "Particle ID: " << Org->ID << '\n';
//   cout << "Particle type: " << Dest->getParticleType() 
//        << '\n' 
//        << "Particle ID: " << Dest->ID << '\n';
    
  //surface tension with a simple model
  //	dPdti += eij*frc_ij[noi][noj].sigma*Fij*Wij*rij*(Vi2 + Vj2);
  
  //surface tension with simplified model
  Vec2d Surfi, Surfj, SurfaceForcei, SurfaceForcej;
  Surfi = Org->del_phi(); Surfj = Dest->del_phi();
  
  SurfaceForcei[0] = Surfi[0]*eij[0] + Surfi[1]*eij[1];
  SurfaceForcei[1] = Surfi[1]*eij[0] - Surfi[0]*eij[1];
  SurfaceForcej[0] = Surfj[0]*eij[0] + Surfj[1]*eij[1];
  SurfaceForcej[1] = Surfj[1]*eij[0] - Surfj[0]*eij[1];
  dPdti +=  (SurfaceForcei*Vi2 + SurfaceForcej*Vj2)*rij*Fij;
  // cout << "dPdti = (" << dPdti[0] << ' ' << dPdti[1] << ')'<< endl;
  ///===========
  ///additional polymer force
  Initiation* ini = Initiation::Instance();  
  Vec2d polyForce=ini->getPolymerCreator()->getForce(eij, rij);  
  dPdti += polyForce;
//   cout << "It is Polymerinteraction" << '\n';
//   cout << Org->getParticleID() << '\n';
//   cout << Dest->getParticleID()<< '\n' << '\n';
  ///===========
  
 
  //summation
#ifdef _OPENMP
  _dU1 = dUi*mi;
  _dU2 = dUi*mj;
  drhodt1 = drhodti*rhoi*rVi;
  drhodt2 = drhodti*rhoj*rVj;
  dUdt1 = dPdti*rmi;
  dUdt2 = dPdti*rmj;
#else
  //Org->_dU += dUi*mi;
  Org->increaseRandomU(dUi*mi);
  //Dest->_dU -= dUi*mj;
  Dest->increaseRandomU(- dUi*mj);
  //Org->drhodt += drhodti*rhoi*rVi;
  Org->increasedrhodt(drhodti*rhoi*rVi);
  //Dest->drhodt += drhodti*rhoj*rVj;
  Dest->increasedrhodt(drhodti*rhoj*rVj);
  //Org->dUdt += dPdti*rmi;
  Org->increasedUdt(dPdti*rmi);
  //Dest->dUdt -= dPdti*rmj;
  Dest->increasedUdt(-dPdti*rmj);
#endif
  //  cout << "UpdateForces of PolymerInteraction was called" << "\n";
}

void PolymerInteraction::acceptDataCollector(DataCollector* dc) {
  assert(dc != NULL);
  dc->VisitPolymerInteraction(this);
}


ostream& PolymerInteraction::put(ostream& ostr) const{
  ///get a pointer to initiation Singelton
  Initiation* pini = Initiation::Instance();
  ///output
  ostr<<pini->dms_length(Org->R()[0])<<' ' <<
    pini->dms_length(Org->R()[1])<<'\n'<<
    pini->dms_length(Dest->R()[0])<<' ' <<
    pini->dms_length(Dest->R()[1]) << ' ' <<
    getPolyEnegry()/(pini->T0*k_bltz) << ' ' << 
    pini->dms_length(rij) << '\n' << '\n';
  //rij the distance between two particles
  return ostr;
}


double PolymerInteraction::getPolyEnegry() const {
  Initiation* ini = Initiation::Instance();
  return ini->getPolymerCreator()->getEnergy(eij, rij);
}

