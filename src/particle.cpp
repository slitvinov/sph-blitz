#include <cmath>
#include <cstdio>
#include "vec2d.h"
#include "glbfunc.h"

#include "initiation.h"
#include "material.h"
#include "particle.h"

enum {X, Y};

long particle_ID_max;
int particle_number_of_materials;
//----------------------------------------------------------------------------------------
//	deconstructor particle
//----------------------------------------------------------------------------------------
Particle::~Particle()
{
	int i;

	///- delete phase field
	for(i = 0; i < particle_number_of_materials; i++) {
		delete[] phi[i];
	}
	///- delete pahse field gradient matrix
	delete[] phi;
}
//----------------------------------------------------------------------------------------
//							real particle
//		NOTE the particle mass and volume will be specified initiation::VolumeMass(w)
//----------------------------------------------------------------------------------------
Particle::Particle(Vec2d position, double velocity[2], double density, double pressure, double temperature, 
				   Material &material) : bd(0)
{
	int i, j;

	///- increase the total particle number
	particle_ID_max++;
	
	///- give a new ID number
	ID = particle_ID_max;

	///- point to the material properties
	mtl = &material;

	///- set viscosity
	eta = mtl->eta; zeta = mtl->zeta;

	///- set particle position
	R = position; 
	
	///- set states
	rho = density; p = pressure; T = temperature; Cs = mtl->get_Cs(p, rho);
	U[X] = velocity[X];
	U[Y] = velocity[Y];
	
	U_I = U;
	
	///- set conservative values and their  intermediate values
	m = 0.0; V = 0.0;
	R_I = R; P_I = P; rho_I = rho;
	P_n = P; U_n = U; rho_n = rho;

	///- set up phase field
	phi = new double*[particle_number_of_materials];
	for(i = 0; i < particle_number_of_materials; i++) {
		phi[i] = new double[particle_number_of_materials];
	}
	for(i = 0; i < particle_number_of_materials; i++)
		for(j = 0; j < particle_number_of_materials; j++) {
			phi[i][j] = 0.0;
		}
}
//----------------------------------------------------------------------------------------
//								construct a wall particle
//----------------------------------------------------------------------------------------
Particle::Particle(double x, double y, double u, double v, 
				   double distance, Material &material) : bd(1), bd_type(0)
{

	///- give a new ID number
	ID = 0;

	///- point to the material properties
	mtl = &material;

	///- set particle position
	R[0] = x; R[1] = y; 
	
	///- set states
	U[0] = u; U[1] = v;
	
	///- set distance and normal directions to boundary
	bd_dst = distance;

	///- set states value to avoid error
	rho = 0.0, p = 0.0, T = 0.0;
}
//----------------------------------------------------------------------------------------
//						creat a ghost particle 
//----------------------------------------------------------------------------------------
Particle::Particle(Particle &RealParticle) : bd(1), bd_type(1)
{
	int i, j;
	
	///- give a new ID number
	ID = 0;

	///- point to its real particle
	rl_prtl = &RealParticle;

	///- point to the material properties
	mtl = RealParticle.mtl;

	///- set viscosity
	eta = mtl->eta; zeta = mtl->zeta; 

	///- set states
	R = RealParticle.R; rho = RealParticle.rho; p = RealParticle.p; T = RealParticle.T;
	Cs =RealParticle.Cs; U = RealParticle.U; U_I = RealParticle.U_I;
	ShearRate_x = RealParticle.ShearRate_x, ShearRate_y = RealParticle.ShearRate_y;
	
	///- set conservative values and their  intermediate values
	m = RealParticle.m; V = RealParticle.V; e = RealParticle.e; 
	R_I = RealParticle.R_I;
	P = RealParticle.P; P_I = RealParticle.P_I; rho_I = rho;
	P_n = RealParticle.P_n; U_n = RealParticle.U_n; rho_n = RealParticle.rho_n;
	
	///- set up phase field
	phi = new double*[particle_number_of_materials];
	for(i = 0; i < particle_number_of_materials; i++) {
		phi[i] = new double[particle_number_of_materials];
	}
	for(i = 0; i < particle_number_of_materials; i++)
		for(j = 0; j < particle_number_of_materials; j++) {
			phi[i][j] = 0.0;
		}

}
//----------------------------------------------------------------------------------------
//							creat an image particle
//----------------------------------------------------------------------------------------
Particle::Particle(Particle &RealParticle, Material &material): bd(1), bd_type(0)
{
	int i, j;
	
	///- give a new ID number
	ID = 0;

	///- point to its real particle
	rl_prtl = &RealParticle;

	///- point to the material properties
	mtl = &material;

	///- set viscosity
	eta = RealParticle.eta; zeta = RealParticle.zeta; 


	///- set states
	R = RealParticle.R; rho = RealParticle.rho; p = RealParticle.p; T = RealParticle.T;
	Cs =RealParticle.Cs; U = RealParticle.U; U_I = RealParticle.U_I;
	ShearRate_x = RealParticle.ShearRate_x, ShearRate_y = RealParticle.ShearRate_y;
	
	///- set conservative values and their  intermediate values
	m = RealParticle.m; V = RealParticle.V; e = RealParticle.e; 
	R_I = RealParticle.R_I;
	P = RealParticle.P; P_I = RealParticle.P_I; rho_I = rho;
	P_n = RealParticle.P_n; U_n = RealParticle.U_n; rho_n = RealParticle.rho_n;

	///- set up phase field
	phi = new double*[particle_number_of_materials];
	for(i = 0; i < particle_number_of_materials; i++) {
		phi[i] = new double[particle_number_of_materials];
	}
	for(i = 0; i < particle_number_of_materials; i++)
		for(j = 0; j < particle_number_of_materials; j++) {
			phi[i][j] = 0.0;
		}

}
//----------------------------------------------------------------------------------------
//					particle states copier for boundary particles
//----------------------------------------------------------------------------------------
void Particle::StatesCopier(Particle &RealParticle, int type)
{
	int i, j;

	///- copy states
	R = RealParticle.R; m = RealParticle.m;
	rho = RealParticle.rho; V = RealParticle.V;
	p = RealParticle.p; T = RealParticle.T;
	rho_I = RealParticle.rho_I;
	Cs =RealParticle.Cs; U = RealParticle.U; U_I = RealParticle.U_I;
	ShearRate_x = RealParticle.ShearRate_x, ShearRate_y = RealParticle.ShearRate_y;

	///- set phase field (depending on boundary type: periodic/wall)
	//perodic boundary
	if (type == 1 ) {
		del_phi = RealParticle.del_phi;
		for(i = 0; i < particle_number_of_materials; i++) {
			for(j = 0; j < particle_number_of_materials; j++) {
				phi[i][j] = RealParticle.phi[i][j];
			}
		}
	}
	
	//wall boundary
	if (type == 0) {
		phi[0][0] = 0.0;
		for(i = 1; i < particle_number_of_materials; i++)
                  phi[0][0] += RealParticle.phi[i][i];
	}

}
