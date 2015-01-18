///\file interactioncomp.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
///\author changes by: Sergey Litvinov <slitvinov@gmail.com>

//----------------------------------------------------------------------------------------
//		defines interactioncomp between particles
//		interactioncomp.cpp
//----------------------------------------------------------------------------------------
#include <glog/logging.h>
#include <assert.h>

// ***** localincludes *****
#include "vec2d.h"
#include "interactioncomp.h"
#include "particle.h"
#include "initiation.h"

//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void InteractionComp::UpdateForces() {
  if(ini.simu_mode==2) {
  const double rhoi = Org->rho; 
  const double rhoj = Dest->rho;
  
  /// make sure density is OK
  assert(rhoi>0.0);
  assert(rhoj>0.0);
  
  //const double rVi = 1.0/Vi; 
  //const double rVj = 1.0/Vj;
  
  const double pi = Org->p; 
  const double pj = Dest->p;
  
  /// make sure pressure is OK
  assert(pi>0.0);
  assert(pj>0.0);
  
  const Vec2d Ui = Org->U; 
  const Vec2d Uj = Dest->U;
  const Vec2d Uij = Ui - Uj;
  const double UijdotRij=dot(Uij,(Org->R - Dest->R));
  
  //pair focres or change rate
  //Vec2d dPdti, dUdti, dUdtj; //mometum&velocity change rate
  

    const double supportlength = ini.supportlength;
    assert(supportlength>0.0);
    assert(rij>0.0);
    /// particle must not be that far 
    assert(rij<=2.0*supportlength);
    
    //const double drhodti=mj*dot((Ui-Uj),gradWij);
    //const double drhodtj=mi*dot((Uj-Ui),((-1)*gradWij));
    
    const double hij=supportlength/2.0;//=0.5*(hi+hj)for later (variable smoothing length);
    const double cij=0.5*(Org->Cs+Dest->Cs);
    const double rhoij=0.5*(rhoi+rhoj);
    
    ///Monaghan artificial viscosity
    double piij = 0.0;
    
    //parameter for time step control
    double mue_ab=0.0;

    //control flag for artificial viscosity
    ///\brief control variable for artificial viscosity (to command if-loop):
    ///
    /// -1: arificial viscosity globally turned on
    ///  1: artificial viscosity globally turned off
    ///  UijdotRij: artificial viscosity turned on only for appraoching particles (compression)
    double artVisc_control;
    
    //assign value to art.visc. control flag depending on art. visc marker
    if (ini.artificial_viscosity_marker==0)//(art. visc. should be turned off)
      artVisc_control=1.0;//if-condition will always be false
    else if (ini.artificial_viscosity_marker==1)//(art. visc. for compression)
      artVisc_control=UijdotRij;
    else //this is the case if marker ==2 (as already tested for values 0,1,2)
      artVisc_control=-1;//always enter if loop below->art.visc. globally turned on
    // enter if loop to compute art. visc. depending on the artVisc_control value	
    if (artVisc_control<0) {
      //according to formula monaghan artificial viscosity
      const double phiij=(hij*UijdotRij)/(pow(rij,2)+ini.epsilon_artVis*pow(hij,2)); 
      //according to formula monaghan artificial viscosity
      piij=(-1*ini.alpha_artVis*cij*phiij+ini.beta_artVis*pow(phiij,2))/rhoij; 
      //parameter for automatic time control
      //mue_ab=-phiij;
      mue_ab=abs(phiij);
      //assert(mue_ab>=0);
    }
    else  {
      piij=0;
      mue_ab=0;//parameter for time control, in Monaghan1989:=0, if no compression
    };
        
    //assign value for mue_ab to mue_ab_max, if bigger than former max value.
    Org->mue_ab_max=std::max(Org->mue_ab_max,mue_ab);
    Dest->mue_ab_max=std::max(Dest->mue_ab_max,mue_ab);
    
    //initialize vector for velocity change rate due to physical viscosity
    Vec2d  dUdt_visc(0,0);
    if (ini.physical_viscosity_marker==1) {
      // physical viscosity implementation according to espagnol2003 (eq. 30)
      // where Fij is defined as >= 0 (gradW(r)=-F(r)*r) contary to Monaghan where Fij<=0 (gradW(r)=F(r)*r)
    
      const double d_i=1/Vi;// inverse of particle volume (partice number density)
      const double d_j=1/Vj;// inverse of particle volume (partice number density)
      //mean shear viscosity (in case of non-constant viscosity)
      const  double eta_ij=0.5*(etai+etaj); 
      //mean bulk viscosity (in case of non-constant viscosity)
      const  double zeta_ij=0.5*(zetai+zetaj);
      const double eijdotUij=dot(eij,Uij);// factor for calculation of phys. visc.
      const double Fij_=abs(Fij);//as in Espagnol Fij defined >=0!
   //velocity change rate due to physical viscosity
      dUdt_visc=1/mi*(-1*((5.0*eta_ij)/3.0-zeta_ij)*Fij_/(d_i*d_j)*Uij-5.0*(zeta_ij+eta_ij/3)*Fij_/(d_i*d_j)*eijdotUij*eij);
    } 
  

    // calculate total velocity change rate (due to pressure, art. visc and physical visc.)
    const Vec2d dUdti=-mj*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij+dUdt_visc;
    const Vec2d dUdtj=mi*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij-dUdt_visc;
    
    //energy change rate    
    //(physical viscosity  not (yet) taken into account in energy equation)
    const double dedti=0.5*dot(dUdti,(Uj-Ui));
    const double dedtj=0.5*dot(dUdtj,(Ui-Uj));
    
    //add result to corresponding particle variable (so, an iteration over interact list corresponds to the required summation) 
    Org->dUdt += dUdti;
    Dest->dUdt += dUdtj;
    Org->dedt+=dedti;
    Dest->dedt+=dedtj;
  }
};

InteractionComp::InteractionComp(const spParticle prtl_org, const spParticle prtl_dest, 
				 spKernel weight_function, const double dstc,
				 const Initiation& ini): 
  Interaction(prtl_org, prtl_dest, weight_function, dstc, ini) {
  assert(ini.simu_mode == 1);
  LOG_EVERY_N(INFO, 100) << "Create compressible interaction";
};

InteractionComp::~InteractionComp() {
  LOG_EVERY_N(INFO, 100000) << "Compressible Interaction destroyed" ;
}
