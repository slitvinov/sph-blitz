#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "vec2d.h"
#include "glbfunc.h"
#include "quinticspline.h"
#include "wiener.h"
#include "initiation.h"
#include "particle.h"
#include "material.h"
#include "force.h"

#include "interaction.h"

enum {X, Y};
using namespace std;

static double k_bltz  = 1.380662e-023/0.02/0.02/0.02;

double interaction_art_vis;
double interaction_delta;

Interaction::Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
			 QuinticSpline &weight_function, double dstc)
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

    eij[X] = (Org->R[X] - Dest->R[X])*rrij;
    eij[Y] = (Org->R[Y] - Dest->R[Y])*rrij;

    Wij = w(&weight_function, rij);
    Fij = F(&weight_function, rij)*rrij;
    shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip)
				   + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
    bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip)
				     + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}

void Interaction::NewInteraction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				 QuinticSpline &weight_function, double dstc)
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
    eij[X] = (Org->R[X] - Dest->R[X])*rrij;
    eij[Y] = (Org->R[Y] - Dest->R[Y])*rrij;
    Wij = w(&weight_function, rij);
    Fij = F(&weight_function, rij)*rrij; //for QuinticSpline wight fuction
    shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip)
				   + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
    bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip)
				     + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}


void Interaction::RenewInteraction(QuinticSpline &weight_function)
{
    ///- calculate pair parameters (weight functions, shear- and bulk-)
    rij = vv_distance(Org->R, Dest->R);
    rrij = 1.0/(rij + 1.0e-30);
    eij[X] = (Org->R[X] - Dest->R[X])*rrij;
    eij[Y] = (Org->R[Y] - Dest->R[Y])*rrij;
    Wij = w(&weight_function, rij);
    Fij = F(&weight_function, rij)*rrij;
    shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip)
				   + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
    bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip)
				     + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}

void Interaction::SummationDensity()
{
    //summation according to: rho_i=sum{m_j*W_ij} (here only the contribution of the pair in questiion)
    Org->rho += mi*Wij;
    if(Org->ID != Dest->ID) Dest->rho += mj*Wij;
}

void Interaction::SummationPhaseGradient()
{
    double c;
    double Vi, rVi, Vj, rVj; //mometum change rate
    double dphi[2];
    Vi = mi/Org->rho; Vj = mj/Dest->rho;
    rVi = 1.0/Vi; rVj = 1.0/Vj;
    double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
    c = Fij*rij*frc_ij[noi][noj].sigma;
    dphi[X] = eij[X]*c;
    dphi[Y] = eij[Y]*c;

    Org->del_phi[X] += dphi[X]*rVi*Vj2;
    Org->del_phi[Y] += dphi[Y]*rVi*Vj2;
    
    Dest->del_phi[X] -= dphi[X]*rVj*Vi2;
    Dest->del_phi[Y] -= dphi[Y]*rVj*Vi2;
}

//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces()
{
    //pressure, density and inverse density and middle point pressure
    double pi, rhoi, Vi, rVi, pj, rhoj, Vj, rVj, Uijdoteij, c, dx, dy;
    //velocity and velocity difference
    double Ui[2], Uj[2], Uij[2];

    //define pair values change in sub time steps
    rhoi = Org->rho; rhoj = Dest->rho;
    Vi = mi/rhoi; Vj = mj/rhoj;
    rVi = 1.0/Vi; rVj = 1.0/Vj;
    pi = Org->p;
    pj = Dest->p;
    
    Ui[X] = Org->U[X];
    Ui[Y] = Org->U[Y];
    
    Uj[X] = Dest->U[X];
    Uj[Y] = Dest->U[Y];
    
    Uij[X] = Ui[X] - Uj[X];
    Uij[Y] = Ui[Y] - Uj[Y];
    
    Uijdoteij = Uij[X]*eij[X] + Uij[Y]*eij[Y];

    //pair focres or change rate
    double dPdti[2], dUi[2]; //mometum change rate
    double drhodti; //density change rate
    double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
    ///- calculate artificial viscosity or Neumann_Richtmyer viscosity
    double theta, Csi, Csj, NR_vis;
    double delta = interaction_delta;
    double art_vis = interaction_art_vis;

    Csi = Org->Cs; Csj = Dest->Cs;
    theta = Uijdoteij*rij*delta/(rij*rij + 0.01*delta*delta);
    NR_vis = Uijdoteij > 0.0 ? 0.0 : art_vis*theta*(rhoi*Csi*mj + rhoj*Csj*mi)/(mi + mj);

    //normalize velocity
    c = theta*Wij*art_vis/(rhoi + rhoj);
    dUi[X] = - eij[X]*c;
    dUi[Y] = - eij[Y]*c;    

    ///- calculate density change rate
    dx = Ui[X]*Vi2 - Uj[X]*Vj2;
    dy = Ui[Y]*Vi2 - Uj[Y]*Vj2;
    drhodti = - Fij*rij*(dx*eij[X] + dy*eij[Y]);

    ///- calculate momentum change rate
    dPdti[X] =   eij[X]*Fij*rij*(pi*Vi2 + pj*Vj2)
	- ((Uij[X] - eij[X]*Uijdoteij)*shear_rij + eij[X]*(Uijdoteij*2.0*bulk_rij + NR_vis))
	*Fij*(Vi2 + Vj2);
    dPdti[Y] =   eij[Y]*Fij*rij*(pi*Vi2 + pj*Vj2)
	- ((Uij[Y] - eij[Y]*Uijdoteij)*shear_rij + eij[Y]*(Uijdoteij*2.0*bulk_rij + NR_vis))
	*Fij*(Vi2 + Vj2);

    //surface tension with a simple model
    //	dPdti += eij*frc_ij[noi][noj].sigma*Fij*Wij*rij*(Vi2 + Vj2);

    ///- calculate additional momentum change rate contribution due to surface tension (with simplified model)
    double Surfi[2], Surfj[2], SurfaceForcei[2], SurfaceForcej[2];
    Surfi[X] = Org->del_phi[X];
    Surfi[Y] = Org->del_phi[Y];
    
    Surfj[X] = Dest->del_phi[X];
    Surfj[Y] = Dest->del_phi[Y];    

    SurfaceForcei[X] = Surfi[X]*eij[X] + Surfi[Y]*eij[Y];
    SurfaceForcei[Y] = Surfi[Y]*eij[X] - Surfi[X]*eij[Y];
    SurfaceForcej[X] = Surfj[X]*eij[X] + Surfj[Y]*eij[Y];
    SurfaceForcej[Y] = Surfj[Y]*eij[X] - Surfj[X]*eij[Y];
    
    dPdti[X] +=  (SurfaceForcei[X]*Vi2 + SurfaceForcej[X]*Vj2)*rij*Fij;
    dPdti[Y] +=  (SurfaceForcei[Y]*Vi2 + SurfaceForcej[Y]*Vj2)*rij*Fij;    

    //summation
    Org->_dU[X] += dUi[X]*mi;
    Org->_dU[Y] += dUi[Y]*mi;    
    
    Dest->_dU[X] -= dUi[X]*mj;
    Dest->_dU[Y] -= dUi[Y]*mj;    
    
    Org->drhodt += drhodti*rhoi*rVi;
    Dest->drhodt += drhodti*rhoj*rVj;
    
    Org->dUdt[X] += dPdti[X]*rmi;
    Org->dUdt[Y] += dPdti[Y]*rmi;    
    
    Dest->dUdt[X] -= dPdti[X]*rmj;
    Dest->dUdt[Y] -= dPdti[Y]*rmj;
}

//----------------------------------------------------------------------------------------
//					update random forces
//----------------------------------------------------------------------------------------
void Interaction::RandomForces(double sqrtdt)
{
    //pair particle state values
    double Vi, Vj;
    double Ti, Tj; //temperature
    double v_eij[2]; //90 degree rotation of pair direction
    double Random_p, Random_v;

    //define particle state values
    Ti =Org->T; Tj = Dest->T;
    if (Ti == 0 && Tj == 0) return;

    Vi = mi/Org->rho; Vj = mj/Dest->rho;

    wiener_gaussian(&Random_p, &Random_v);
    Random_p *= sqrtdt;
    Random_v *= sqrtdt;

    //pair focres or change rate
    double _dUi[2]; //mometum change rate
    double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
    v_eij[X] = v_eij[Y] = 0;
    

    _dUi[X] = v_eij[X]*Random_p*sqrt(16.0*k_bltz*shear_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij) +
	eij[X]*Random_v*sqrt(16.0*k_bltz*bulk_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij);
    _dUi[Y] = v_eij[Y]*Random_p*sqrt(16.0*k_bltz*shear_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij) +
	eij[Y]*Random_v*sqrt(16.0*k_bltz*bulk_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij);

    //summation
    //modify for perodic boundary condition
    if(Dest->bd_type == 1) {
	Org->_dU[X]	= Org->_dU[X] + _dUi[X]*rmi*0.5;
	Org->_dU[Y]	= Org->_dU[Y] + _dUi[Y]*rmi*0.5;
	
	Dest->rl_prtl->_dU[X]	= Dest->rl_prtl->_dU[X] - _dUi[X]*rmj*0.5;
	Dest->rl_prtl->_dU[Y]	= Dest->rl_prtl->_dU[Y] - _dUi[Y]*rmj*0.5;
    }
    else {
	Org->_dU[X] = Org->_dU[X] + _dUi[X]*rmi;
	Org->_dU[Y] = Org->_dU[Y] + _dUi[Y]*rmi;
	
	Dest->_dU[X] = Dest->_dU[X] - _dUi[X]*rmj;
	Dest->_dU[Y] = Dest->_dU[Y] - _dUi[Y]*rmj;	
    }
}
