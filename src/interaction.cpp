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
    eij = (Org->R - Dest->R)*rrij;
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
    eij = (Org->R - Dest->R)*rrij;
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
    rij = v_abs(Org->R - Dest->R);
    rrij = 1.0/(rij + 1.0e-30);
    eij = (Org->R - Dest->R)*rrij;
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

    double Vi, rVi, Vj, rVj; //mometum change rate
    Vi = mi/Org->rho; Vj = mj/Dest->rho;
    rVi = 1.0/Vi; rVj = 1.0/Vj;
    double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
    Vec2d dphi = eij*Fij*rij*frc_ij[noi][noj].sigma;

    Org->del_phi += dphi*rVi*Vj2;
    Dest->del_phi -= dphi*rVj*Vi2;
}

//----------------------------------------------------------------------------------------
//					update pair forces
//----------------------------------------------------------------------------------------
void Interaction::UpdateForces()
{
    //pressure, density and inverse density and middle point pressure
    double pi, rhoi, Vi, rVi, pj, rhoj, Vj, rVj, Uijdoteij;
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

    //pair focres or change rate
    Vec2d dPdti, dUi; //mometum change rate
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
    Org->_dU += dUi*mi;
    Dest->_dU -= dUi*mj;
    Org->drhodt += drhodti*rhoi*rVi;
    Dest->drhodt += drhodti*rhoj*rVj;
    Org->dUdt += dPdti*rmi;
    Dest->dUdt -= dPdti*rmj;
}

//----------------------------------------------------------------------------------------
//					update random forces
//----------------------------------------------------------------------------------------
void Interaction::RandomForces(double sqrtdt)
{
    //pair particle state values
    double Vi, Vj;
    double Ti, Tj; //temperature
    Vec2d v_eij; //90 degree rotation of pair direction
    double Random_p, Random_v;

    //define particle state values
    Ti =Org->T; Tj = Dest->T;
    if (Ti == 0 && Tj == 0) return;

    Vi = mi/Org->rho; Vj = mj/Dest->rho;

    wiener_gaussian(&Random_p, &Random_v);
    Random_p *= sqrtdt;
    Random_v *= sqrtdt;

    //pair focres or change rate
    Vec2d _dUi; //mometum change rate
    double Vi2 = Vi*Vi, Vj2 = Vj*Vj;

    _dUi = v_eij*Random_p*sqrt(16.0*k_bltz*shear_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij) +
	eij*Random_v*sqrt(16.0*k_bltz*bulk_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij);

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
