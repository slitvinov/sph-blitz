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
#include "interaction.h"
#include "particle.h"
#include "initiation.h"
#include "glbfunc.h"

//----------------------------------------------------------------------------------------
//					constructor
//----------------------------------------------------------------------------------------
Interaction::Interaction(const spParticle prtl_org, const spParticle prtl_dest, 
			 spKernel weight_function, 
			 const double dstc,
			 const Initiation& ini):
  ini(ini),   Org(prtl_org), Dest(prtl_dest), mi(Org->m), mj(Dest->m), 
  rmi(1.0/mi), rmj(1.0/mj),   etai(Org->eta), etaj(Dest->eta),
  zetai(Org->zeta), zetaj(Dest->zeta),   rij(dstc) {

  assert(prtl_dest != NULL);
  assert(prtl_org != NULL);
  /// particle distance should be in this range
  assert(rij>0.0);
  /// particle must not be that far 
  assert(rij<=2.0*ini.supportlength);
  rrij = 1.0/rij;
  Vi=Org->V;
  Vj=Dest->V;
  eij = (Org->R - Dest->R)*rrij;
  Wij = weight_function->w(rij);
  gradWij=weight_function->gradW(rij,/*Dest->R-Org->R*/eij);
  Fij = weight_function->F(rij)*rrij; //for Kernel weight fuction
   LOG_EVERY_N(INFO, 100000) << "Interaction created,interaction pair: " 
			     <<Org->ID<<"  "<<Dest->ID<<"org_x: "
			     <<Org->R[0]<<"  Dest_x: "<<Dest->R[0] 
			     <<"  org_y: "<<Org->R[1]<<"Dest_y: "<<Dest->R[1];
}

//-------------------getter for origin-----------------
spParticle  Interaction::getOrigin() const {
  return Org;
}

//-------------------getter for distance-----------------
double Interaction::get_rij() const {
  return rij;
}
//--------------------getter for destination---------------------
spParticle  Interaction::getDest() const {
  return Dest;
}
//-----------getter for Wij
double Interaction::getWij() const {
  return Wij;
}
//----------getter for GradWij
Vec2d Interaction::getGradWij() const {
   return gradWij;
}

//----------------------------------------------------------------------------------------
					//renew pair parameters and changing pair values
//----------------------------------------------------------------------------------------
// Changes: Interaction object
// Depends on: Interaction Object, Org, Dest
void Interaction::RenewInteraction(spKernel weight_function) {
  LOG_EVERY_N(INFO, 10000) << "call Interaction::RenewInteraction()";
  ///- calculate pair parameters (weight functions, shear- and bulk-)
  rij = v_abs(Org->R - Dest->R);
  etai=Org->eta;
  zetai=Org->zeta;
  etaj=Dest->eta;
  zetaj=Dest->zeta;
  assert(rrij>0.0);
  rrij = 1.0/rij;
  Vi=Org->V;
  Vj=Dest->V;
  eij = (Org->R - Dest->R)*rrij;
  Wij = weight_function->w(rij);
  gradWij=weight_function->gradW(rij,/*Dest->R-Org->R*/eij);
  Fij = weight_function->F(rij)*rrij; //for Kernel fuction
}
//----------------------------------------------------------------------------------------
//					summation of the density
//					the idea is different from the original sph method
//----------------------------------------------------------------------------------------
// Changes: Org(rho:summation), Dest(rho:summation)
// Depends on: Interaction Object, Org(rho), Dest(rho)
void Interaction::SummationDensity() {
  //summation according to: rho_i=sum{m_j*W_ij} (here only the contribution of the pair in question)
  /// shell note be called with interaction of the particle
  /// with itself
  assert(Org->ID >= Dest->ID);
  Org->rho += mj*Wij;//changed from mi to mj (07/19/10)
  Dest->rho += mi*Wij; //changed from mj to mi (07/19/10)
}


void Interaction::UpdateForcesAndRho() {
  LOG_EVERY_N(INFO, 1000) << "Interaction::UpdateForcesANDRHO()";
  
  //define pair values change in sub time steps
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
  
  if(ini.simu_mode==2) {
    const double supportlength = ini.supportlength;
    assert(supportlength>0.0);
    assert(rij>0.0);
    /// particle must not be that far 
    assert(rij<=2.0*supportlength);
    
    const double drhodti=mj*dot((Ui-Uj),gradWij);
    const double drhodtj=mi*dot((Uj-Ui),((-1)*gradWij));
    
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
      mue_ab=0;//parameter for time control, in Monaghan1989
    };
    
    //assign value for mue_ab to mue_ab_max, if bigger than former max value.
    Org->mue_ab_max=AMAX1(Org->mue_ab_max,mue_ab);
    Dest->mue_ab_max=AMAX1(Dest->mue_ab_max,mue_ab);
    
    //initialize vectors for velocity change rate due to physical viscosity
    Vec2d  dUdti_visc(0,0);
    Vec2d  dUdtj_visc(0,0);
    // control output for one interaction pair
    if (ini.physical_viscosity_marker==1) {
      // physical viscosity implementation according to espanol2003 (eq. 30)
      // where Fij is defined as >= 0 (gradW(r)=-F(r)*r) contrary to Monaghan 
      // where Fij<=0 (gradW(r)=F(r)*r)
      
      const double d_i=1/Vi;// inverse of particle volume (partice number density)
      if(Org->ID==2 && Dest->ID==1)
	LOG(INFO)<<"d_i :"<<d_i;
      const double d_j=1/Vj;// inverse of particle volume (partice number density)
      if(Org->ID==2 && Dest->ID==1)
	LOG(INFO)<<"d_j :"<<d_j;
      // mean shear viscosity (in case of non-constant viscosity)
      const  double eta_ij=0.5*(etai+etaj); 
      if(Org->ID==2 && Dest->ID==1)
	LOG(INFO)<<" eta_ij :"<< eta_ij;
      // mean bulk viscosity (in case of non-constant viscosity)
      const  double zeta_ij=0.5*(zetai+zetaj);
      if(Org->ID==2 && Dest->ID==1)
	LOG(INFO)<<" zeta_ij :"<< zeta_ij;
      const double eijdotUij=dot(eij,Uij);// factor for calculation of phys. visc.
      // again control output for first interaction pair
      if(Org->ID==2 && Dest->ID==1) {
	LOG(INFO)<<" eij :"<< eij;
	LOG(INFO)<<" Ri :"<< Org->R;
	LOG(INFO)<<" Rj :"<< Dest->R;
	LOG(INFO)<<" Uij :"<< Uij;
	LOG(INFO)<<" Ui :"<< Org->U;
	LOG(INFO)<<" Uj :"<< Dest->U;
	LOG(INFO)<<" eijdotUij :"<< eijdotUij;
      }
      const double Fij_=abs(Fij);//as in Espanol Fij defined >=0!
      if(Org->ID==2 && Dest->ID==1)
	LOG(INFO)<<" Fij_ :"<< Fij_;
      // velocity change rate due to physical viscosity
      dUdti_visc=1/mi*(-1*((5.0*eta_ij)/3.0-zeta_ij)*Fij_/(d_i*d_j)*Uij
		       -5.0*(zeta_ij+eta_ij/3)*Fij_/(d_i*d_j)*eijdotUij*eij);
      // velocity change rate due to physical viscosity
      dUdtj_visc=1/mj*(((5.0*eta_ij)/3.0-zeta_ij)*Fij_/(d_i*d_j)*Uij
		       +5.0*(zeta_ij+eta_ij/3)*Fij_/(d_i*d_j)*eijdotUij*eij);
      
      // formulation from Ellero2007 paper
      // (neglecting bulk viscosity)(is even more wrong)
      // dUdti_visc=1/mi*(-1*eta_ij/3.0*Fij_/(d_i*d_j)*(5.0*Uij+4.0*eijdotUij*eij));
      
    } 
    // again control output for first interaction pair
    if(Org->ID==2 && Dest->ID==1) {
      LOG(INFO)<<"dUdti_visc after : ("<<dUdti_visc[0]<<","<<dUdti_visc[1]<<")";
      LOG(INFO)<<"dUdtj_visc after : ("<<dUdtj_visc[0]<<","<<dUdtj_visc[1]<<")";
    }
    
    
    // calculate total velocity change rate (due to pressure, art. visc and physical visc.)
    //velocity change rate due to pressure
    const Vec2d dUdti_p=-mj*(pi/pow(rhoi,2)+pj/pow(rhoj,2))*gradWij;
    const Vec2d dUdtj_p=mi*(pi/pow(rhoi,2)+pj/pow(rhoj,2))*gradWij;
    //velocity change rate due to artificial viscosity
    const Vec2d dUdti_artVisc=-mj*piij*gradWij;
    const Vec2d dUdtj_artVisc=mi*piij*gradWij;
    //velocity change rate due to physical viscosity already determined above
    
    //total velocity change rate
    const Vec2d dUdti=dUdti_p+dUdti_artVisc+dUdti_visc;
    const Vec2d dUdtj=dUdtj_p+dUdtj_artVisc+dUdtj_visc;
    
    //energy change rate    
    
    //energy change rate contribution  due to thermal conduction (Cleary1999)
    const double dedti_cond=4.0*mj/(rhoi*rhoj)*ki*kj/((ki+kj)+1e-35)*(Ti-Tj)*Fij;
    const double dedtj_cond=4.0*mi/(rhoi*rhoj)*ki*kj/((ki+kj)+1e-35)*(Tj-Ti)*Fij;
    //energy change rate contribution due to pressure
    const double dedti_p=0.5*dot(dUdti_p,(Uj-Ui));
    const double dedtj_p=0.5*dot(dUdtj_p,(Ui-Uj));
    // energy change rate contribution due to artificial viscosity
    const double dedti_artVisc=0.5*dot(dUdti_artVisc,(Uj-Ui));
    const double dedtj_artVisc=0.5*dot(dUdtj_artVisc,(Ui-Uj));
    // energy change rate contribution due to phsyical viscosity
    const double dedti_visc=0.5*dot(dUdti_visc,(Uj-Ui));
    const double dedtj_visc=0.5*dot(dUdtj_visc,(Ui-Uj));
    if(Org->ID==2 && Dest->ID==1) {
      LOG(INFO)<<"dedti_visc: "<< dedti_visc<<","<< "dedtj_visc: "<<dedtj_visc;
    }
    
    // now complete energy change rate
    const double dedti=dedti_p+dedti_artVisc+dedti_visc;
    const double dedtj=dedtj_p+dedtj_artVisc+dedtj_visc;
  
    // add result to corresponding particle variable 
    // (so, an iteration over the interaction list corresponds
    // to the required summation) 
    Org->dUdt += dUdti;
    Dest->dUdt += dUdtj;
    Org->dedt+=dedti;
    Dest->dedt+=dedtj;
    Org->drhodt += drhodti;
    Dest->drhodt += drhodtj;
  };
}

void Interaction::UpdateEnergyPureConduction(){
 LOG_EVERY_N(INFO, 100000) << "Interaction::UpdateForces()";
 //define pair values change in sub time steps
 const double rhoi = Org->rho; 
 const double rhoj = Dest->rho;
 
 //energy change rate    
 //(physical viscosity  not (yet) taken into account in energy equation)
 
 //first energy change rate contribution  due to thermal conduction (Cleary1999)
 const double dedtij_cond=4.0*mj/(rhoi*rhoj)*ki*kj/(ki+kj)*(Ti-Tj)*Fij;
 //now complete energy equation
 const double dedti=+dedtij_cond;
 const double dedtj=-dedtij_cond;
 
 //add result to particle's energy variable (so, an iteration over the interaction list corresponds to the required summation
 Org->dedt+=dedti;
 Dest->dedt+=dedtj;

 //reset pressure to a positive value: 
 //pressure is actually not important (as not taken into account for 
 //pure conduction). However, as I wanted to implement the pureConduction case
 //in a way which can easily be extended to a flow problem, the program 
 //runs all the methods (which are not used for the pure conduction).
 // to prevent a program interuption due to an assertion of p (<0),
 // I reset p here to a value >0 foe each iteration.
 Org->p=1000.0;
 Dest->p=1000.0;
}

Interaction::~Interaction() {
  LOG_EVERY_N(INFO, 100000) << "Interaction destroyed" ;
}

