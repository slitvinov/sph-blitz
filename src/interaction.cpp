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
#include "initiation.h"
#include "Kernel/kernel.h"
#include "particle.h"
#include "force.h"


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
Interaction::Interaction(Initiation &ini) 
{
        ///- copy properties from initiation
	number_of_materials = ini.number_of_materials;
	supportlength = ini.supportlength;
	simu_mode = ini.simu_mode;
	art_vis = ini.art_vis;
	delta = ini.delta;
	alpha_artVis=1.0;
	beta_artVis=2.0;
	epsilon_artVis=0.1;

}
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
	shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
							 + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
	bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
							   + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
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
double Interaction::getWij()
 
{ return this->Wij;
}

//----------getter for GradWij
 Vec2d Interaction::getGradWij()
 
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
	shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
							 + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
	bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
							   + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
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
	shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
							 + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
	bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
							   + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
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
//					summation of the shear rates
//----------------------------------------------------------------------------------------
// Changes: Org(ShearRate_x, ShearRate_y:summation), Dest(ShearRate_x, ShearRate_y:summation)
// Depends on: Interaction Object, Org(ShearRate_x, ShearRate_y, U, rho), Dest(ShearRate_x, ShearRate_y, U, rho)
void Interaction::SummationShearRate()
{
	//pair particle state values
	double vi, vj; //particle volumes
	Vec2d Uij; //velocity, velocity difference and midddle point velocity
	Vec2d ShearRate_xi, ShearRate_yi; //shear rates
		
	///- define particle state values
	vi = mi/Org->rho; vj = mj/Dest->rho;
	Uij = Org->U - Dest->U;
	ShearRate_xi = Uij*eij[0]*Fij*rij;
	ShearRate_yi = Uij*eij[1]*Fij*rij;
	
	///- summation of shear rates
	Org->ShearRate_x = Org->ShearRate_x + ShearRate_xi*vj;
	Org->ShearRate_y = Org->ShearRate_y + ShearRate_yi*vj;
	Dest->ShearRate_x = Dest->ShearRate_x + ShearRate_xi*vi;
	Dest->ShearRate_y = Dest->ShearRate_y + ShearRate_yi*vi;
}
//----------------------------------------------------------------------------------------
//						phase field
//----------------------------------------------------------------------------------------
// Changes: Org(phi:summation), Dest(phi:summation)
// Depends on: Interaction Object, Org(phi, rho), Dest(phi, rho)
void Interaction::SummationPhaseField()
{
	double vi, vj; //particle volumes
	vi = mi/Org->rho; vj = mj/Dest->rho;

	Org->phi[noi][noj] += Wij*vj;
	if(Org->ID != Dest->ID) Dest->phi[noj][noi] += Wij*vi;
}
//----------------------------------------------------------------------------------------
//						density or phase gradient
//----------------------------------------------------------------------------------------
// Changes: Org(del_phi:summation), Dest(del_phi:summation)
// Depends on: Interaction Object, Org(del_phi,rho), Dest(del_phi,rho)
void Interaction::SummationPhaseGradient()
{

	double Vi, rVi, Vj, rVj; //mometum change rate
	Vi = mi/Org->rho; Vj = mj/Dest->rho;
	rVi = 1.0/Vi; rVj = 1.0/Vj;
	double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
	Vec2d dphi = eij*Fij*rij*frc_ij[noi][noj].sigma;

	Org->del_phi += dphi*rVi*Vj2;
	Dest->del_phi -= dphi*rVj*Vi2;
}
//----------------------------------------------------------------------------------------
//					Curvature
//----------------------------------------------------------------------------------------
void Interaction::SummationCurvature()
{
	double vi, vj; //particle volumes
	vi = mi/Org->rho; vj = mj/Dest->rho;
	double phii = Fij*rij;

		Org->phi[noi][noj] += phii*vj;
		Dest->phi[noj][noi] += phii*vi;
}
//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces()
{	
  //contol output
  //   cout<<"\n am in update forces and simu_mode is:"<<simu_mode<<"\n";
  	//pressure, density and inverse density and middle point pressure
        double pi, rhoi, Vi, rVi, pj, rhoj, Vj, rVj, Uijdoteij,UijdotRij; 
	//velocity and velocity difference
	Vec2d Ui, Uj, Uij; 

	//define pair values change in sub time steps
	rhoi = Org->rho; rhoj = Dest->rho;
	Vi = mi/rhoi; Vj = mj/rhoj;
	rVi = 1.0/Vi; rVj = 1.0/Vj;
	pi = Org->p; pj = Dest->p;
	Ui = Org->U; Uj = Dest->U;
	Uij = Ui - Uj;
	Uijdoteij = dot(Uij, eij);
	UijdotRij=dot(Uij,(Org->R - Dest->R));
	//pair focres or change rate
	Vec2d dPdti, dUi, dUdti, dUdtj; //mometum&velocity change rate
        double drhodti,drhodtj,dedti,dedtj; //density change rate

	if(simu_mode==2)
	{
	  //control output
	  // cout<<"\n am in update forces simu_mode =2\n";
	  drhodti=mj*dot((Ui-Uj),gradWij);
	  drhodtj=mi*dot((Uj-Ui),((-1)*gradWij));

	  hij=supportlength/2;//=0.5*(hi+hj)for later (variable smoothing length);
	  cij=0.5*(Org->Cs+Dest->Cs);
          rhoij=0.5*(rhoi+rhoj);
	
          if (UijdotRij<0)//that means: whenever in compression (as only then artificial viscosity applies for a shock tube problem)
          {
            phiij=(hij*UijdotRij)/(pow(rij,2)+epsilon_artVis*pow(hij,2)); //according to formula monaghan artificial viscosity
	    piij=(-1*alpha_artVis*cij*phiij+beta_artVis*pow(phiij,2))/rhoij; //according to formula monaghan artificial viscosity
          }
	  else //if no compression: artificial viscosity is zero
	  {
	    piij=0;
	  };
	  // cout<<"\n art v0isc Piij"<<piij;
	  dUdti=-mj*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;
          dUdtj=mi*(pi/pow(rhoi,2)+pj/pow(rhoj,2)+piij)*gradWij;

	  dedti=0.5*dot(dUdti,(Uj-Ui));//could also be the other way round: (Ui-Uj)has to be tried out
          dedtj=0.5*dot(dUdtj,(Ui-Uj));

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
	  drhodti = - Fij*rij*dot((Ui*Vi2 - Uj*Vj2), eij);
	
	  ///- calculate momentum change rate
	  dPdti =   eij*Fij*rij*(pi*Vi2 + pj*Vj2)
			- ((Uij - eij*Uijdoteij)*shear_rij + eij*(Uijdoteij*2.0*bulk_rij + NR_vis))
			*Fij*(Vi2 + Vj2);
	
	  //surface tension with a simple model
    //	dPdti += eij*frc_ij[noi][noj].sigma*Fij*Wij*rij*(Vi2 + Vj2);

	  ///- calculate additional momentum change rate contribution due to surface tension (with simplified model)
	  Vec2d Surfi, Surfj, SurfaceForcei, SurfaceForcej;
	  Surfi = Org->del_phi; Surfj = Dest->del_phi;

	  SurfaceForcei[0] = Surfi[0]*eij[0] + Surfi[1]*eij[1];
	  SurfaceForcei[1] = Surfi[1]*eij[0] - Surfi[0]*eij[1];
	  SurfaceForcej[0] = Surfj[0]*eij[0] + Surfj[1]*eij[1];
	  SurfaceForcej[1] = Surfj[1]*eij[0] - Surfj[0]*eij[1];
	  dPdti +=  (SurfaceForcei*Vi2 + SurfaceForcej*Vj2)*rij*Fij;
	
	

	//summation
#ifdef _OPENMP
	_dU1 = dUi*mi;
	_dU2 = dUi*mj;
	drhodt1 = drhodti*rhoi*rVi;
	drhodt2 = drhodti*rhoj*rVj;
	dUdt1 = dPdti*rmi;
	dUdt2 = dPdti*rmj;
#else
	Org->_dU += dUi*mi;
	Dest->_dU -= dUi*mj;
	Org->drhodt += drhodti*rhoi*rVi;
	Dest->drhodt += drhodti*rhoj*rVj;
	Org->dUdt += dPdti*rmi;
	Dest->dUdt -= dPdti*rmj;
#endif
	}
}

#ifdef _OPENMP
void Interaction::SummationUpdateForces()
{
	Org->_dU += _dU1;
	Dest->_dU -= _dU2;
	Org->drhodt += drhodt1;
	Dest->drhodt += drhodt2;
	Org->dUdt += dUdt1;
	Dest->dUdt -= dUdt2;
}
#endif

//----------------------------------------------------------------------------------------
//				update forces with summation viscosity
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces_vis()
{
	//pressure, density and inverse density and middle point pressure
	double pi, rhoi, rrhoi, pj, rhoj, rrhoj, _pij; 
	//velocity, velocity difference and midddle point velocity
	Vec2d Ui, Uj, Uij, _Uij; 

	//define pair values change in sub time steps
	rhoi = Org->rho; rhoj = Dest->rho;
	rrhoi = 1.0/rhoi; rrhoj = 1.0/rhoj;
	pi = Org->p; pj = Dest->p;
	Ui = Org->U; Uj = Dest->U;
	Uij = Org->U - Dest->U;
	_pij = (pi + pj)*0.5;
	_Uij = (Ui + Uj)*0.5;

	//shear rates
	Vec2d ShearRate_xi, ShearRate_yi;
	Vec2d ShearRate_xj, ShearRate_yj;
	double ShearStress[2][2], CompressRate;
	Vec2d ShearForce;

	//pair focres or change rate
	Vec2d dPdti; //mometum change rate

	///- calculate shear force
	ShearRate_xi = Org->ShearRate_x; ShearRate_yi =  Org->ShearRate_y;
	ShearRate_xj = Dest->ShearRate_x; ShearRate_yj =  Dest->ShearRate_y;

	ShearStress[0][0] = (ShearRate_xi[0] + ShearRate_xj[0]);
	ShearStress[0][1] = ((ShearRate_xi[1] + ShearRate_xj[1]) + (ShearRate_yi[0] + ShearRate_yj[0]))*0.5;
	ShearStress[1][0] = ShearStress[0][1];
	ShearStress[1][1] = (ShearRate_yi[1] + ShearRate_yj[1]);
	CompressRate = (ShearStress[0][0] + ShearStress[1][1])/3.0;
	ShearStress[0][0] -= CompressRate; 	ShearStress[1][1] -= CompressRate;

	ShearForce[0] = ShearStress[0][0]*eij[0] + ShearStress[1][0]*eij[1]; 
	ShearForce[1] = ShearStress[0][1]*eij[0] + ShearStress[1][1]*eij[1]; 
	ShearForce = ShearForce*2.0*etai*etaj/(etai + etaj) 
			   + eij*CompressRate*2.0*zetai*zetaj/(zetai + zetaj); 

	
	///- define pair force or momentum change rate
	dPdti =   eij*Fij*rij*_pij*(rrhoi*rrhoi + rrhoj*rrhoj)
			- ShearForce*Fij*rij*(rrhoi*rrhoi + rrhoj*rrhoj);
	///summation (acceleration (=velovity change rate)=force (=momentum change rate)* mass
	Org->dUdt = Org->dUdt + dPdti*mj;
	Dest->dUdt = Dest->dUdt - dPdti*mi;

}
//----------------------------------------------------------------------------------------
//					update random forces
//----------------------------------------------------------------------------------------
void Interaction::RandomForces(Wiener &wiener, double sqrtdt)
{
	//pair particle state values
	double Vi, Vj; 
	double Ti, Tj; //temperature
	Vec2d v_eij; //90 degree rotation of pair direction


	//define particle state values
	Vi = mi/Org->rho; Vj = mj/Dest->rho;
	Ti =Org->T; Tj = Dest->T;
	
	wiener.get_wiener(sqrtdt);

	//pair focres or change rate
	Vec2d _dUi; //mometum change rate
	double Vi2 = Vi*Vi, Vj2 = Vj*Vj;

	extern double k_bltz;
	_dUi = v_eij*wiener.Random_p*sqrt(16.0*k_bltz*shear_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij) +
		   eij*wiener.Random_v*sqrt(16.0*k_bltz*bulk_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij);

	//summation
	//modify for perodic boundary condition
	if(Dest->bd_type == 1) {
		Org->_dU	= Org->_dU + _dUi*rmi*0.5;
		Dest->rl_prtl->_dU	= Dest->rl_prtl->_dU - _dUi*rmj*0.5;
	}
	else {
		Org->_dU = Org->_dU + _dUi*rmi;
		Dest->_dU = Dest->_dU - _dUi*rmj;
	}
}
//----------------------------------------------------------------------------------------
//					update random forces with Espanol's method
//----------------------------------------------------------------------------------------
void Interaction::RandomForces_Espanol(Wiener &wiener, double sqrtdt)
{
	//pair particle state values
	double smimj, smjmi, rrhoi, rrhoj; 
	double Ti, Tj; //temperature
	Vec2d v_eij; //90 degree rotation of pair direction

	//pair focres or change rate
	Vec2d _dUi, random_force; //mometum change rate

	//define particle state values
	smimj = sqrt(mi/mj); smjmi = 1.0/smimj;
	rrhoi = 1.0/Org->rho; rrhoj = 1.0/Dest->rho;
	Ti =Org->T; Tj = Dest->T;
	
	wiener.get_wiener_Espanol(sqrtdt);

	random_force[0] = wiener.sym_trclss[0][0]*eij[0] + wiener.sym_trclss[0][1]*eij[1];
	random_force[1] = wiener.sym_trclss[1][0]*eij[0] + wiener.sym_trclss[1][1]*eij[1];

	extern double k_bltz;
	_dUi = random_force*sqrt(16.0*k_bltz*etai*etaj/(etai + etaj)*Ti*Tj/(Ti + Tj)*(rrhoi*rrhoi + rrhoj*rrhoj)*Fij) +
		   eij*wiener.trace_d*sqrt(16.0*k_bltz*zetai*zetaj/(zetai + zetaj)*Ti*Tj/(Ti + Tj)*(rrhoi*rrhoi + rrhoj*rrhoj)*Fij);

	//summation
	//modify for perodic boundary condition
	if(Dest->bd_type == 1) {
		Org->_dU	= Org->_dU + _dUi*smjmi*0.5;
		Dest->rl_prtl->_dU	= Dest->rl_prtl->_dU - _dUi*smimj*0.5;
	}
	else {
		Org->_dU	= Org->_dU + _dUi*smjmi;
		Dest->_dU	= Dest->_dU - _dUi*smimj;
	}

}
