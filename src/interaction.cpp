///\file interaction.cpp
///\author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//		defines interaction between particles
//		interaction.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbcls.h"
#include "glbfunc.h"
#include "material.h"
#include "Kernel/kernel.h"
#include "interaction.h"

#include <assert.h>

using namespace std;

int Interaction::number_of_materials = 0;
double Interaction::supportlength = 0.0;
double Interaction::art_vis = 0.0;
double Interaction::delta = 0.0;
int Interaction::simu_mode =0;
double Interaction::alpha_artVis=0.0;
double Interaction::beta_artVis=0.0;
double Interaction::epsilon_artVis=0.0;


//----------------------------------------------------------------------------------------
//					constructor
//----------------------------------------------------------------------------------------
Interaction::Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				Kernel &weight_function, double dstc)
{
        ///- assign the original and the destinate particle in the reaction pair
	Org = prtl_org;
	Dest = prtl_dest;
	
	///- determine interaction parameters
	noi = Org->mtl->number;
	noj = Dest->mtl->number; 
	frc_ij = forces;

	///- define pair values (mass, viscosity), do not change in sub time steps
	mi = Org->m; mj = Dest->m;
	rmi = 1.0/mi; rmj =1.0/mj;
	etai = Org->eta; etaj = Dest->eta; 
	zetai = Org->zeta; zetaj = Dest->zeta; 


	///- calculate pair parameters (weight functions, shear- and bulk-)
	rij = dstc;
	rrij = 1.0/(rij + 1.0e-30);
	eij = (Org->R - Dest->R)*rrij;
	Wij = weight_function.w(rij);
	gradWij=weight_function.gradW(rij,Dest->R-Org->R);
//	Fij = weight_function.F(rij); //for BetaSpline weight fuction
	Fij = weight_function.F(rij)*rrij; //for Kernel wight fuction

}

//-------------------getter for origin-----------------
Particle* Interaction::getOrigin()
{
  return this->Org;
}
//--------------------getter for destination---------------------
Particle* Interaction::getDest()
 
{ return this->Dest;
}
//-----------getter for Wij
double Interaction::getWij() const
 
{ return this->Wij;
}

//----------getter for GradWij
 Vec2d Interaction::getGradWij() const
 
 { return this->gradWij;
}

//----------------------------------------------------------------------------------------
//	use old interaction object for new interaction
//----------------------------------------------------------------------------------------
void Interaction::NewInteraction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				Kernel &weight_function, double dstc)
{
	///- assign the original and the destinate particle in the reaction pair
	Org = prtl_org;
	Dest = prtl_dest;
	
	///- determine interaction parameters
	noi = Org->mtl->number;
	noj = Dest->mtl->number; 
	frc_ij = forces;

	///- define pair values(mass, viscosity), do not change in sub time steps
	mi = Org->m; mj = Dest->m;
	rmi = 1.0/mi; rmj =1.0/mj;
	etai = Org->eta; etaj = Dest->eta; 
	zetai = Org->zeta; zetaj = Dest->zeta; 

	///- calculate pair parameters (weight functions, shear- and bulk-)
	rij = dstc;
	rrij = 1.0/(rij + 1.0e-30);
	eij = (Org->R - Dest->R)*rrij;
	Wij = weight_function.w(rij);
	gradWij=weight_function.gradW(rij,Dest->R-Org->R);
//	Fij = weight_function.F(rij); //for BetaSpline wight fuction
	Fij = weight_function.F(rij)*rrij; //for Kernel wight fuction
}


//----------------------------------------------------------------------------------------
					//renew pair parameters and changing pair values
//----------------------------------------------------------------------------------------
// Changes: Interaction object
// Depends on: Interaction Object, Org, Dest
void Interaction::RenewInteraction(Kernel &weight_function)
{
	///- calculate pair parameters (weight functions, shear- and bulk-)
	rij = v_abs(Org->R - Dest->R);
	rrij = 1.0/(rij + 1.0e-30);
	eij = (Org->R - Dest->R)*rrij;
	Wij = weight_function.w(rij);
	gradWij=weight_function.gradW(rij,Dest->R-Org->R);
//	Fij = weight_function.F(rij); //for BetaSpline wight fuction
	Fij = weight_function.F(rij)*rrij; //for Kernel fuction

}
//----------------------------------------------------------------------------------------
//					summation of the density
//					the idea is different from the original sph method
//----------------------------------------------------------------------------------------
// Changes: Org(rho:summation), Dest(rho:summation)
// Depends on: Interaction Object, Org(rho), Dest(rho)
void Interaction::SummationDensity()
{
	//summation according to: rho_i=sum{m_j*W_ij} (here only the contribution of the pair in questiion)
	Org->rho += mi*Wij;
	if(Org->ID != Dest->ID) Dest->rho += mj*Wij; 

}


//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces()
{	
  //contol output
  //   cout<<"\n am in update forces and simu_mode is:"<<simu_mode<<"\n";
  	//pressure, density and inverse density and middle point pressure
        double pi, rVi, pj, rVj, Uijdoteij,UijdotRij; 
	//velocity and velocity difference
	Vec2d Ui, Uj, Uij; 

	//define pair values change in sub time steps
	const double rhoi = Org->rho; 
	const double rhoj = Dest->rho;
	assert(rhoi>0.0);
	assert(rhoj>0.0);
	
	const double Vi = mi/rhoi; 
	const double Vj = mj/rhoj;
	assert(Vi>0.0);
	assert(Vj>0.0);
	rVi = 1.0/Vi; rVj = 1.0/Vj;

	pi = Org->p; pj = Dest->p;
	Ui = Org->U; Uj = Dest->U;
	Uij = Ui - Uj;
	Uijdoteij = dot(Uij, eij);
	UijdotRij=dot(Uij,(Org->R - Dest->R));

	//pair focres or change rate
	Vec2d dPdti, dUi, dUdti, dUdtj; //mometum&velocity change rate

	if(simu_mode==2)
	{
	  //control output
	  // cout<<"\n am in update forces simu_mode =2\n";
	  const double drhodti=mj*dot((Ui-Uj),gradWij);
	  const double drhodtj=mi*dot((Uj-Ui),((-1)*gradWij));

	  const double hij=supportlength/2.0;//=0.5*(hi+hj)for later (variable smoothing length);
	  const double cij=0.5*(Org->Cs+Dest->Cs);
          const double rhoij=0.5*(rhoi+rhoj);
	
          if (UijdotRij<0)//that means: whenever in compression (as only then artificial viscosity applies for a shock tube problem)
          {
            const double phiij=(hij*UijdotRij)/(pow(rij,2)+epsilon_artVis*pow(hij,2)); //according to formula monaghan artificial viscosity
	    piij=(-1*alpha_artVis*cij*phiij+beta_artVis*pow(phiij,2))/rhoij; //according to formula monaghan artificial viscosity
          }
	  else //if no compression: artificial viscosity is zero
	  {
	    piij=0;
	  };
	  // cout<<"\n art v0isc Piij"<<piij;
	  dUdti=-mj*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;
          dUdtj=mi*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;

	  const double dedti=0.5*dot(dUdti,(Uj-Ui));//could also be the other way round: (Ui-Uj)has to be tried out
          const double dedtj=0.5*dot(dUdtj,(Ui-Uj));

	  //control output
	  //cout<<"\n dUdti:\n"<<dUdti[0];


          Org->drhodt +=drhodti;
          Dest->drhodt += drhodtj;
          Org->dUdt += dUdti;
          Dest->dUdt += dUdtj;
	  Org->dedt+=dedti;
	  Dest->dedt+=dedtj;
	};

      	if(simu_mode==1)
	{
	  // cout<<"am in simu_mode=1 section of update forces";
	  double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
	  ///- calculate artificial viscosity or Neumann_Richtmyer viscosity
	  double theta, Csi, Csj, NR_vis;
	  Csi = Org->Cs; Csj = Dest->Cs;
	  theta = Uijdoteij*rij*delta/(rij*rij + 0.01*delta*delta);
	  NR_vis = Uijdoteij > 0.0 ? 0.0 : art_vis*theta*(rhoi*Csi*mj + rhoj*Csj*mi)/(mi + mj);
	
	  //normalize velocity
	  dUi = - eij*theta*Wij*art_vis/(rhoi + rhoj);
	
	  ///- calculate density change rate
	  const double drhodti = - Fij*rij*dot((Ui*Vi2 - Uj*Vj2), eij);
	
	  ///- calculate momentum change rate
	  dPdti =   eij*Fij*rij*(pi*Vi2 + pj*Vj2)
	    - (NR_vis)*Fij*(Vi2 + Vj2);
		
	Org->drhodt += drhodti*rhoi*rVi;
	Dest->drhodt += drhodti*rhoj*rVj;
	Org->dUdt += dPdti*rmi;
	Dest->dUdt -= dPdti*rmj;
	}
	
	
}

