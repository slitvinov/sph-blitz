///\file particle.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: 

//-------------------------------------------------------------------
//				Particle data type definition
//				particle.cpp
//----------------------------------------------------------------

// ***** local includes *****
#include "glbfunc.h"
#include "material.h"


#include "particle.h"

long Particle ::ID_max = 0;
int Particle ::number_of_materials = 0;

//----------------------------------------------------------------------------------------
//	deconstructor particle
//----------------------------------------------------------------------------------------
Particle::~Particle ()
{

}
//----------------------------------------------------------------------------------------
//							real particle
//		NOTE the particle mass and volume will be specified initiation::VolumeMass(w)
//----------------------------------------------------------------------------------------
Particle::Particle (Vec2d position, Vec2d velocity, double density, 
		   double pressure, double temperature, 
		   spMaterial material) 
  : bd(0),
    mtl(material)
{
  // only 2D position is accepted
  assert(position.size() == 2);

  ///- increase the total particle number
  ID_max++;
	
  ///- give a new ID number
  ID = ID_max;

  ///- point to the material properties


  ///- set viscosity
  eta = mtl->eta;

  ///- set particle position
  R = position; 
	
  ///- set states
  rho = density; p = pressure; T = temperature; Cs = mtl->get_Cs(p, rho);
  U = velocity; U_I = U;
	
  ///- set conservative values (mass and volume determined lateron) and their  intermediate values
  m = 0.0; V = 0.0; e = mtl->get_e(T); e_I = e;
  R_I = R; P_I = P; rho_I = rho;
  P_n = P; U_n = U; rho_n = rho; e_n = e; 

}
//----------------------------------------------------------------------------------------
//								construct a wall particle
//----------------------------------------------------------------------------------------
Particle::Particle (double x, double y, double u, double v, 
		   double distance, double normal_x, double normal_y, 
		   spMaterial material) : 
  bd(1), bd_type(0),
  mtl(material)
{

  ///- give a new ID number
  ID = 0;

  ///- point to the material properties
	

  ///- set particle position
  R[0] = x; R[1] = y; 
	
  ///- set states
  U[0] = u; U[1] = v;
	
  ///- set distance and normal directions to boundary
  bd_dst = distance;
  nrml[0] = normal_x; nrml[1] = normal_y;

  ///- set states value to avoid error
  rho = 0.0, p = 0.0, T = 0.0;
}
//----------------------------------------------------------------------------------------
//						creat a ghost particle 
//----------------------------------------------------------------------------------------
Particle::Particle (spParticle RealParticle ) : 
  bd(1), bd_type(1),
  mtl(RealParticle->mtl)
{
  ///- give a new ID number
  ID = 0;

  ///- point to its real particle
  rl_prtl = RealParticle ;

  ///- set viscosity
  eta = mtl->eta;

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
//							creat an image particle
//----------------------------------------------------------------------------------------
Particle::Particle (spParticle RealParticle , spMaterial material): 
  bd(1), 
  bd_type(0),
  mtl(material),
  rl_prtl(RealParticle)
{
  ///- give a new ID number
  ID = 0;

  ///- point to its real particle



  ///- set viscosity
  eta = RealParticle->eta;


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
void Particle ::StatesCopier(spParticle RealParticle , int type)
{
  ///- copy states
  R = RealParticle->R; m = RealParticle->m;
  rho = RealParticle->rho; V = RealParticle->V;
  p = RealParticle->p; T = RealParticle->T;
  e = RealParticle->e;
  rho_I = RealParticle->rho_I;
  Cs =RealParticle->Cs; U = RealParticle->U; U_I = RealParticle->U_I;
}
