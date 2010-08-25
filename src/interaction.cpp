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
  ini(ini),
  Org(prtl_org), Dest(prtl_dest),
  mi(Org->m), mj(Dest->m), 
  rmi(1.0/mi), rmj(1.0/mj),
  etai(Org->eta), etaj(Dest->eta),
  rij(dstc) {
  assert(prtl_dest != NULL);
  assert(prtl_org != NULL);
  /// particle distance should be in this range
  assert(rij>0.0);
  /// particle must not be that far 
  assert(rij<=2.0*ini.supportlength);
  rrij = 1.0/rij;
  eij = (Org->R - Dest->R)*rrij;
  Wij = weight_function->w(rij);
  gradWij=weight_function->gradW(rij,/*Dest->R-Org->R*/eij);
  Fij = weight_function->F(rij)*rrij; //for Kernel wight fuction
  LOG_EVERY_N(INFO, 100000) << "Interaction created,interaction pair: "<<Org->ID<<"  "<<Dest->ID<<"org_x: "<<Org->R[0]<<"  Dest_x: "<<Dest->R[0]<<"  org_y: "<<Org->R[1]<<"Dest_y: "<<Dest->R[1];
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
  assert(rrij>0.0);
  rrij = 1.0/rij;
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


//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces() {
  LOG_EVERY_N(INFO, 100000) << "Interaction::UpdateForces()";
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
    
    //const double drhodti=mj*dot((Ui-Uj),gradWij);
    //const double drhodtj=mi*dot((Uj-Ui),((-1)*gradWij));
    
    const double hij=supportlength/2.0;//=0.5*(hi+hj)for later (variable smoothing length);
    const double cij=0.5*(Org->Cs+Dest->Cs);
    const double rhoij=0.5*(rhoi+rhoj);
    
    ///Monaghan artificial viscosity
    double piij = 0.0;
    
    //parameter for time step control
    double mue_ab=0.0;

    if (/*UijdotRij*/-1<0)//that means: whenever in compression (as only then artificial viscosity applies for a shock tube problem)
      {
	//according to formula monaghan artificial viscosity
	const double phiij=(hij*UijdotRij)/(pow(rij,2)+ini.epsilon_artVis*pow(hij,2)); 
	//according to formula monaghan artificial viscosity
	piij=(-1*ini.alpha_artVis*cij*phiij+ini.beta_artVis*pow(phiij,2))/rhoij; 
	//parameter for time control
	//mue_ab=-phiij;
	mue_ab=abs(phiij);
	assert(mue_ab>=0);
      }
    else //if no compression: artificial viscosity is zero
      {
	piij=0;
	mue_ab=0;//parameter for time control, in Monaghan1989:=0, if no compression
      };
    //assign value for mue_ab to mue_ab_max, if bigger than former max value.
    Org->mue_ab_max=AMAX1(Org->mue_ab_max,mue_ab);
    Dest->mue_ab_max=AMAX1(Dest->mue_ab_max,mue_ab);
    //LOG_EVERY_N(INFO, 1)<<Org->ID<<"  "<<Dest->ID<<" artvis: "<<piij;
    const Vec2d dUdti=-mj*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;
    const Vec2d dUdtj=mi*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;
    
    const double dedti=0.5*dot(dUdti,(Uj-Ui));
    const double dedtj=0.5*dot(dUdtj,(Ui-Uj));
    
    //control output
    Org->dUdt += dUdti;
    Dest->dUdt += dUdtj;
    Org->dedt+=dedti;
    Dest->dedt+=dedtj;
  };
  
  if(ini.simu_mode==1)
    {
      LOG_EVERY_N(INFO, 10000) << "Interaction::UpdateForces(), simu_mode=1";
      const double Vi = mi/rhoi; 
      const double Vj = mj/rhoj;
      
      assert(Vi>0.0);
      assert(Vj>0.0);
      const double Vi2 = Vi*Vi; 
      const double Vj2 = Vj*Vj;
      
      ///- calculate density change rate
      const double shear_rij = 2.0*etai*etaj/(etai + etaj);
      LOG_EVERY_N(INFO, 10000) << "etai = " << etai;
      LOG_EVERY_N(INFO, 10000) << "shear_rij = " << shear_rij;
      
      /// viscous and pressure parts
      const Vec2d dPdti_visc = -shear_rij*Fij*(Vi2 + Vj2) * Uij;
      const Vec2d dPdti_pre = - eij*Fij*rij*(pi*Vi2 + pj*Vj2);
      
      const Vec2d dPdti = dPdti_visc  + dPdti_pre;
      LOG_EVERY_N(INFO, 10000) << "Ui = " << Ui;
      LOG_EVERY_N(INFO, 10000) << "Uj = " << Uj;
      LOG_EVERY_N(INFO, 10000) << "dPdti = " << dPdti;
      
      Org->dUdt += dPdti*rmi;
      Dest->dUdt -= dPdti*rmj;
    }
}

void Interaction::UpdateForcesAndRho() {
  LOG_EVERY_N(INFO, 1000) << "Interaction::UpdateForces()";
  
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

          if (UijdotRij<0)//that means: whenever in compression (as only then artificial viscosity applies for a shock tube problem)
	    {
	      //according to formula monaghan artificial viscosity
	      const double phiij=(hij*UijdotRij)/(pow(rij,2)+ini.epsilon_artVis*pow(hij,2)); 
	      //according to formula monaghan artificial viscosity
	      piij=(-1*ini.alpha_artVis*cij*phiij+ini.beta_artVis*pow(phiij,2))/rhoij; 
	      //parameter for time control
	      mue_ab=-phiij;
	      assert(mue_ab>=0);
	    }
	  else //if no compression: artificial viscosity is zero
	    {
	      piij=0;
	      mue_ab=0;//parameter for time control, in Monaghan1989:=0, if no compression
	  };
	  LOG_EVERY_N(INFO, 100000)<<Org->ID<<"  "<<Dest->ID<<" artvis: "<<piij;
	  const Vec2d dUdti=-mj*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;
          const Vec2d dUdtj=mi*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;

	  const double dedti=0.5*dot(dUdti,(Uj-Ui));//could also be the other way round: (Ui-Uj)has to be tried out
          const double dedtj=0.5*dot(dUdtj,(Ui-Uj));

	  //control output
          Org->dUdt += dUdti;
          Dest->dUdt += dUdtj;
	  Org->dedt+=dedti;
	  Dest->dedt+=dedtj;
	  Org->drhodt += drhodti;
          Dest->drhodt += drhodtj;
	};
}

Interaction::~Interaction() {
  LOG_EVERY_N(INFO, 100000) << "Interaction destroyed" ;
}

