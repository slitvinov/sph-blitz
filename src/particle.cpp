///\file particle.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: 

//-------------------------------------------------------------------
//				Particle data type definition
//				particle.cpp
//----------------------------------------------------------------
#include <glog/logging.h>


// ***** local includes *****
#include "material.h"
#include "particle.h"

int64_t Particle ::ID_max = 0;

// particle destructor
Particle::~Particle () {
}
//----------------------------------------------------------------------------------------
//							real particle (constructor for liquids mode (as mass calculated afterwards)
//		NOTE the particle mass and volume will be specified initiation::VolumeMass(w)
//----------------------------------------------------------------------------------------
Particle::Particle (Vec2d position, Vec2d velocity, double density, 
		   double pressure, double temperature, 
		   spMaterial material) 
  : bd(0),
    mtl(material)
{

  ///- increase the total particle number
  ID_max++;
	
  ///- give a new ID number
  ID = ID_max;

  ///- set viscosity
  eta = mtl->eta;

  ///- set particle position
  R = position; 
	
  ///- set states
  rho = density; p = pressure; T = temperature; Cs = mtl->get_Cs(p, rho);
  U = velocity; U_I = U;
	
  ///- set conservative values (mass and volume determined lateron) and their  intermediate values
  // m = 0.0; // for 2D shock tube mass is initialized from the external
 V = 0.0; e = mtl->get_e(T); e_I = e;
  R_I = R; P_I = P; rho_I = rho;
  P_n = P; U_n = U; rho_n = rho; e_n = e; 

}



//----------------------------------------------------------------------------------------
//							real particle (constructor for gas dynamicss mode (as mass initilaized from external file and so hs to be assigned in within the construtor)
//	
//----------------------------------------------------------------------------------------
Particle::Particle (Vec2d position, Vec2d velocity, double density, 
		    double pressure, double mass, double temperature, 
		    spMaterial material) 
  : bd(0),
    mtl(material)
{

  ///- increase the total particle number
  ID_max++;
	
  ///- give a new ID number
  ID = ID_max;

  ///- set viscosities and conductivity 
  
  ///TODO{integrate  viscosity(T), calculate individual eta for each particle: DONE}
  eta = mtl->get_eta(temperature);//(shear) (either constant or variable, depending on selection)
  zeta=mtl->zeta;//(bulk)
  k = mtl->get_k(temperature);//thermal conductivity (constant or variable, depending on selection)
  cv=mtl->cv;
  
  LOG_EVERY_N(INFO,100)<<"particle eta: "<<eta;
  ///- initialize mue_ab_max to zero
  mue_ab_max=0;
  ///- set particle position
  R = position; 
  
  ///- set states
  rho = density; m=mass; p = pressure; T = temperature; Cs = mtl->get_Cs(p, rho);  U = velocity; U_I = U;
	
  ///- set conservative values (mass and volume determined lateron) and their  intermediate values
  // m = 0.0; // for 2D shock tube mass is initialized from the external
 V = 0.0; e = mtl->get_e(T); e_I = e;
  R_I = R; P_I = P; rho_I = rho;
  P_n = P; U_n = U; rho_n = rho; e_n = e; 

}

//----------------------------------------------------------------------------------------
//								construct a wall particle
//----------------------------------------------------------------------------------------
Particle::Particle (double x, double y, double u, double v, 
		   spMaterial material) : 
  bd(1),
  mtl(material)
{

  ///- give a new ID number
  ID = 0;

  ///- set particle position
  R[0] = x; R[1] = y; 
	
  ///- set states
  U[0] = u; U[1] = v;

  ///- set states value to avoid error
  rho = 0.0, p = 0.0, T = 0.0;
}
//----------------------------------------------------------------------------------------
//						creat a ghost particle 
//----------------------------------------------------------------------------------------
Particle::Particle (spParticle RealParticle ) : 
  bd(1), 
  mtl(RealParticle->mtl)
{
  ///- give a new ID number
  ID = 0;

  ///- point to its real particle
  rl_prtl = RealParticle ;

  ///- set viscosity
  // eta = mtl->eta;
  

  ///- set states
  R = RealParticle->R; rho = RealParticle->rho; p = RealParticle->p; T = RealParticle->T;
  Cs =RealParticle->Cs; U = RealParticle->U; U_I = RealParticle->U_I;
	
  ///- set conservative values and their  intermediate values
  m = RealParticle->m; V = RealParticle->V; e = RealParticle->e; 
  R_I = RealParticle->R_I;	e_I = RealParticle->e_I;
  P = RealParticle->P; P_I = RealParticle->P_I; rho_I = rho;
  P_n = RealParticle->P_n; U_n = RealParticle->U_n; rho_n = RealParticle->rho_n;
  e_n = RealParticle->e_n;
  //viscosities copied as well for ghost particles (as they can be variable)
  eta = RealParticle->eta;
  zeta=RealParticle->zeta;
  k=RealParticle->k;
	
}
//----------------------------------------------------------------------------------------
//							create an image particle
//----------------------------------------------------------------------------------------
Particle::Particle (spParticle RealParticle , spMaterial material): 
  bd(1), 
  mtl(material),
  rl_prtl(RealParticle)
{
  ///- give a new ID number
  ID = 0;

  ///- point to its real particle



  ///- set viscosity
  eta = RealParticle->eta;
  zeta= RealParticle->zeta;
  k=RealParticle->k;


  ///- set states
  R = RealParticle->R; rho = RealParticle->rho; p = RealParticle->p; T = RealParticle->T;
  Cs =RealParticle->Cs; U = RealParticle->U; U_I = RealParticle->U_I;
	
  ///- set conservative values and their  intermediate values
  m = RealParticle->m; V = RealParticle->V; e = RealParticle->e; 
  R_I = RealParticle->R_I;	e_I = RealParticle->e_I;
  P = RealParticle->P; P_I = RealParticle->P_I; rho_I = rho;
  P_n = RealParticle->P_n; U_n = RealParticle->U_n; rho_n = RealParticle->rho_n;
  e_n = RealParticle->e_n; 
  
}
//----------------------------------------------------------------------------------------
//					particle states copier for boundary particles
//----------------------------------------------------------------------------------------
void Particle ::StatesCopier(spParticle RealParticle , const int type)
{
  ///- copy states
  R = RealParticle->R; m = RealParticle->m;
  rho = RealParticle->rho; V = RealParticle->V;
  p = RealParticle->p; T = RealParticle->T;
  e = RealParticle->e; e_I=RealParticle->e_I;
  rho_I = RealParticle->rho_I;
  Cs =RealParticle->Cs; U = RealParticle->U; U_I = RealParticle->U_I;
  //add viscosity copier (for the case of varaible viscosity)
  eta = RealParticle->eta;
  zeta=RealParticle->zeta;
  k=RealParticle->k;
}
