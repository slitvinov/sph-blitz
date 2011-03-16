// interaction.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//              defines interaction between particles
//              interaction.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbcls.h"
#include "glbfunc.h"
#include "interaction.h"
#include "particle.h"
#include "quinticspline.h"
#include "force.h"
#include "initiation.h"
#include "material.h"

using namespace std;

int Interaction::number_of_materials = 0;
double Interaction::smoothinglength = 0.0;
double Interaction::art_vis = 0.0;
double Interaction::delta = 0.0;
//----------------------------------------------------------------------------------------
//                                      constructor
//----------------------------------------------------------------------------------------
Interaction::Interaction(Initiation &ini):
ini(ini)
{
    //copy properties from initiation
    number_of_materials = ini.number_of_materials;
    smoothinglength = ini.smoothinglength;
    art_vis = ini.art_vis;
    delta = ini.delta;
}
//----------------------------------------------------------------------------------------
//                                      constructor
//----------------------------------------------------------------------------------------
Interaction::Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
						 QuinticSpline &weight_function, double dstc, Initiation& ini):
ini(ini)
{
    //the original and the destinate particle in the reaction pair
    Org = prtl_org;
    Dest = prtl_dest;
        
    //interaction parameters
    noi = Org->mtl->number;
    noj = Dest->mtl->number; 
    frc_ij = forces;

    //define pair values do not change in sub time steps
    mi = Org->m; mj = Dest->m;
    rmi = 1.0/mi; rmj =1.0/mj;
    etai = Org->eta; etaj = Dest->eta; 
    zetai = Org->zeta; zetaj = Dest->zeta; 

    //the pair parameters
    rij = dstc;
    rrij = 1.0/(rij + 1.0e-30);
    eij = (Org->R - Dest->R)*rrij;
    Wij = weight_function.w(rij);
//      Fij = weight_function.F(rij); //for BetaSpline wight fuction
    Fij = weight_function.F(rij)*rrij; //for QuinticSpline wight fuction
    LapWij = weight_function.LapW(rij); //for QuinticSpline fuction
    shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
                                   + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
    bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
                                     + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}

//----------------------------------------------------------------------------------------
//      use old interaction object for new interaction
//----------------------------------------------------------------------------------------
void Interaction::NewInteraction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
                                 QuinticSpline &weight_function, double dstc)
{
    //the original and the destinate particle in the reaction pair
    Org = prtl_org;
    Dest = prtl_dest;
        
    //interaction parameters
    noi = Org->mtl->number;
    noj = Dest->mtl->number; 
    frc_ij = forces;

    //define pair values do not change in sub time steps
    mi = Org->m; mj = Dest->m;
    rmi = 1.0/mi; rmj =1.0/mj;
    etai = Org->eta; etaj = Dest->eta; 
    zetai = Org->zeta; zetaj = Dest->zeta; 

    //the pair parameters
    rij = dstc;
    rrij = 1.0/(rij + 1.0e-30);
    eij = (Org->R - Dest->R)*rrij;
    Wij = weight_function.w(rij);
//      Fij = weight_function.F(rij); //for BetaSpline wight fuction
    Fij = weight_function.F(rij)*rrij; //for QuinticSpline wight fuction
    LapWij = weight_function.LapW(rij); //for QuinticSpline fuction
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
void Interaction::RenewInteraction(QuinticSpline &weight_function)
{
    //the pair parameters
    rij = v_abs(Org->R - Dest->R);
    rrij = 1.0/(rij + 1.0e-30);
    eij = (Org->R - Dest->R)*rrij;
    Wij = weight_function.w(rij);
//      Fij = weight_function.F(rij); //for BetaSpline wight fuction
    Fij = weight_function.F(rij)*rrij; //for QuinticSpline fuction
    LapWij = weight_function.LapW(rij); //for QuinticSpline fuction
    shear_rij = 2.0*etai*etaj*rij/(etai*(rij + 2.0*frc_ij[noj][noi].shear_slip) 
                                   + etaj*(rij + 2.0*frc_ij[noi][noj].shear_slip) + 1.0e-30);
    bulk_rij =  2.0*zetai*zetaj*rij/(zetai*(rij + 2.0*frc_ij[noj][noi].bulk_slip) 
                                     + zetaj*(rij + 2.0*frc_ij[noi][noj].bulk_slip) + 1.0e-30);
}
//----------------------------------------------------------------------------------------
//                                      summation the density
//                                      the idea is different from the original sph method
//----------------------------------------------------------------------------------------
// Changes: Org(rho:summation), Dest(rho:summation)
// Depends on: Interaction Object, Org(rho), Dest(rho)
void Interaction::SummationDensity()
{
    //summation
    Org->rho += mi*Wij;
    if(Org->ID != Dest->ID) Dest->rho += mj*Wij; 

}
//----------------------------------------------------------------------------------------
//                                      summation of the shear rates
//----------------------------------------------------------------------------------------
// Changes: Org(ShearRate_x, ShearRate_y:summation), Dest(ShearRate_x, ShearRate_y:summation)
// Depends on: Interaction Object, Org(ShearRate_x, ShearRate_y, U, rho), Dest(ShearRate_x, ShearRate_y, U, rho)
void Interaction::SummationShearRate()
{
    //pair particle state values
    double vi, vj; //particle volumes
    Vec2d Uij; //velocity, velocity difference and midddle point velocity
    Vec2d ShearRate_xi, ShearRate_yi; //shear rates
                
    //define particle state values
    vi = mi/Org->rho; vj = mj/Dest->rho;
    Uij = Org->U - Dest->U;
    ShearRate_xi = Uij*eij[0]*Fij*rij;
    ShearRate_yi = Uij*eij[1]*Fij*rij;
        
    //summation
    Org->ShearRate_x = Org->ShearRate_x + ShearRate_xi*vj;
    Org->ShearRate_y = Org->ShearRate_y + ShearRate_yi*vj;
    Dest->ShearRate_x = Dest->ShearRate_x + ShearRate_xi*vi;
    Dest->ShearRate_y = Dest->ShearRate_y + ShearRate_yi*vi;
}
//----------------------------------------------------------------------------------------
//                                              phase field
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
//                                              density or phase gradient
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
//                                              phase field Laplacian
//----------------------------------------------------------------------------------------
void Interaction::SummationPhaseLaplacian()
{
    //pair particle state values
    double vi, vj; //particle volumes
    double lapi;
                
    //define particle state values
    vi = mi/Org->rho; vj = mj/Dest->rho;
    lapi = LapWij;
        
    //summation
    Org->lap_phi[noi][noj] += lapi*vj;
    Dest->lap_phi[noj][noi] += lapi*vi;
}
//----------------------------------------------------------------------------------------
//                                      Curvature
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
//                                      update pair forces
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
    //artificial viscosity or Neumann_Richtmyer viscosity
    double theta, Csi, Csj, NR_vis;
    extern double k_bltz;
    Csi = Org->Cs; Csj = Dest->Cs;
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
	
	// polymer force
	if ( Org->polyID>0  && Dest->polyID>0 ) {

		if ( abs(Org->polyID - Dest->polyID) == 1 ) {
			//std::cerr << "Org->polyID = " << Org->polyID << " Dest->polyID = " << Dest->polyID << '\n';
			const double relR = rij/ini.polymer_r0;
                        if (relR>1.0) {
                          std::cerr << __FILE__ << ':' << __LINE__ << ": ERROR: polymer is broken\n" ;
                           std::cerr << "rij  = " << rij << std::endl;
                           std::cerr << "ini.box_size:  " << ini.box_size << std::endl;
                           std::cerr << "ini.polymer_r0  = " << ini.polymer_r0 << std::endl;
                           std::cerr << "ini.polymer_H  = " << ini.polymer_H << std::endl;
                           std::cerr << "H*r0^2/kt  = " << ini.polymer_H * ini.polymer_r0 * ini.polymer_r0 / (k_bltz * Org->T) << std::endl;
                          std::cerr << "relR  = " << relR << std::endl;
                          std::cerr << "Org->R: " << Org->R << std::endl;
                          std::cerr << "Dest->R: " << Dest->R << std::endl;
                          std::cerr << "Org->polyID: " << Org->polyID << std::endl;
                          std::cerr << "Dest->polyID: " << Dest->polyID << std::endl;
                          exit(EXIT_FAILURE);
                        }
			dPdti += ini.polymer_H / ( 1 -  relR*relR) * (rij * eij);
			
		}
	}
        
    //surface tension with a simple model
//      dPdti += eij*frc_ij[noi][noj].sigma*Fij*Wij*rij*(Vi2 + Vj2);

    //surface tension with simplified model
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
//                              update forces with summation viscosity
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

    //shear force
    ShearRate_xi = Org->ShearRate_x; ShearRate_yi =  Org->ShearRate_y;
    ShearRate_xj = Dest->ShearRate_x; ShearRate_yj =  Dest->ShearRate_y;

    ShearStress[0][0] = (ShearRate_xi[0] + ShearRate_xj[0]);
    ShearStress[0][1] = ((ShearRate_xi[1] + ShearRate_xj[1]) + (ShearRate_yi[0] + ShearRate_yj[0]))*0.5;
    ShearStress[1][0] = ShearStress[0][1];
    ShearStress[1][1] = (ShearRate_yi[1] + ShearRate_yj[1]);
    CompressRate = (ShearStress[0][0] + ShearStress[1][1])/3.0;
    ShearStress[0][0] -= CompressRate;  ShearStress[1][1] -= CompressRate;

    ShearForce[0] = ShearStress[0][0]*eij[0] + ShearStress[1][0]*eij[1]; 
    ShearForce[1] = ShearStress[0][1]*eij[0] + ShearStress[1][1]*eij[1]; 
    ShearForce = ShearForce*2.0*etai*etaj/(etai + etaj) 
        + eij*CompressRate*2.0*zetai*zetaj/(zetai + zetaj); 

        
    //define pair force or change rates
    dPdti =   eij*Fij*rij*_pij*(rrhoi*rrhoi + rrhoj*rrhoj)
        - ShearForce*Fij*rij*(rrhoi*rrhoi + rrhoj*rrhoj);
    //summation
    Org->dUdt = Org->dUdt + dPdti*mj;
    Dest->dUdt = Dest->dUdt - dPdti*mi;

}
//----------------------------------------------------------------------------------------
//                                      update random forces
//----------------------------------------------------------------------------------------
void Interaction::RandomForces(Wiener &wiener, double sqrtdt)
{
    //pair particle state values
    double Vi, Vj; 
    double Ti, Tj; //temperature
    Vec2d v_eij; //90 degree rotation of pair direction

    extern double k_bltz;

    //define particle state values
    Vi = mi/Org->rho; Vj = mj/Dest->rho;
    Ti =Org->T; Tj = Dest->T;
        
    wiener.get_wiener(sqrtdt);

    //pair focres or change rate
    Vec2d _dUi; //mometum change rate
    double Vi2 = Vi*Vi, Vj2 = Vj*Vj;

    _dUi = v_eij*wiener.Random_p*sqrt(16.0*k_bltz*shear_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij) +
        eij*wiener.Random_v*sqrt(16.0*k_bltz*bulk_rij*Ti*Tj/(Ti + Tj)*(Vi2 + Vj2)*Fij);

    //summation
    //modify for perodic boundary condition
    if(Dest->bd_type == 1) {
        Org->_dU        = Org->_dU + _dUi*rmi*0.5;
        Dest->rl_prtl->_dU      = Dest->rl_prtl->_dU - _dUi*rmj*0.5;
    }
    else {
        Org->_dU = Org->_dU + _dUi*rmi;
        Dest->_dU = Dest->_dU - _dUi*rmj;
    }
}
//----------------------------------------------------------------------------------------
//                                      update random forces with Espanol's method
//----------------------------------------------------------------------------------------
void Interaction::RandomForces_Espanol(Wiener &wiener, double sqrtdt)
{
    //pair particle state values
    double smimj, smjmi, rrhoi, rrhoj; 
    double Ti, Tj; //temperature
    Vec2d v_eij; //90 degree rotation of pair direction

    extern double k_bltz;

    //pair focres or change rate
    Vec2d _dUi, random_force; //mometum change rate

    //define particle state values
    smimj = sqrt(mi/mj); smjmi = 1.0/smimj;
    rrhoi = 1.0/Org->rho; rrhoj = 1.0/Dest->rho;
    Ti =Org->T; Tj = Dest->T;
        
    wiener.get_wiener_Espanol(sqrtdt);

    random_force[0] = wiener.sym_trclss[0][0]*eij[0] + wiener.sym_trclss[0][1]*eij[1];
    random_force[1] = wiener.sym_trclss[1][0]*eij[0] + wiener.sym_trclss[1][1]*eij[1];

    _dUi = random_force*sqrt(16.0*k_bltz*etai*etaj/(etai + etaj)*Ti*Tj/(Ti + Tj)*(rrhoi*rrhoi + rrhoj*rrhoj)*Fij) +
        eij*wiener.trace_d*sqrt(16.0*k_bltz*zetai*zetaj/(zetai + zetaj)*Ti*Tj/(Ti + Tj)*(rrhoi*rrhoi + rrhoj*rrhoj)*Fij);

    //summation
    //modify for perodic boundary condition
    if(Dest->bd_type == 1) {
        Org->_dU        = Org->_dU + _dUi*smjmi*0.5;
        Dest->rl_prtl->_dU      = Dest->rl_prtl->_dU - _dUi*smimj*0.5;
    }
    else {
        Org->_dU        = Org->_dU + _dUi*smjmi;
        Dest->_dU       = Dest->_dU - _dUi*smimj;
    }

}
