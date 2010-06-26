/// \file partilce.h 
/// \brief a sph particle

#ifndef PARTICLE_H
#define PARTICLE_H
///note: reference a particle by pointer or adress
///never reference a particle directly!


#include "vec2d.h"
#include "glbtype.h"

class Initiation;

/// Particle class 
class Particle {
 public:
	static int number_of_materials;
	
	///\brief construct a real particle
	///NOTE the particle mass and volume will be specified in initiation::VolumeMass(w)
	Particle (Vec2d position, Vec2d velocity, double density, 
		 double pressure, double temperature, spMaterial material);
	///construct a wall particle
	Particle (double x, double y, double u, double v, 
		 double distance, double normal_x, double normal_y, 
		 spMaterial material);
	
	///ghost particle creator
	Particle (spParticle RealParticle );
	///Mirror image particle creator
	Particle (spParticle RealParticle , spMaterial material);

	///deconstructor particle
	~Particle ();
	
	///particle states copier for boundary particles
	void StatesCopier(spParticle RealParticle , int type);


	int cell_i;///<i-position in cells
        int cell_j; ///<j-position in cells
	
	///a shared pointer  to the material
	spMaterial mtl; 

	///pointer to a real particle
	spParticle rl_prtl;

	//Physical data
	Vec2d R;///<position
        Vec2d P;///<momentum
        Vec2d U; ///<velocityy
        double rho;///<density
        double p;///<pressure
        double T;///<Temperature
        double Cs;///<do not know what this is <b>!!!Question!!!</b>
        double rho_I;///<intermediate value for density (needed for integration)
        double rho_n; ////<do not know what this is ("conservative value") <b>!!!Question!!!</b>
	double m;///<mass
	double V;///<volume
	double e; ///<internal energy
	Vec2d R_I;///<intermediate position
	Vec2d P_I;///<intermediate momentim
	Vec2d U_I;///<intermediate velocity
	Vec2d P_n;///<do not knwo what this is n=?conservative???<b>!!!Question!!!</b>
	Vec2d U_n; ///<do not knwo what this is n=?conservative???<b>!!!Question!!!</b>
	double e_I;///<intermediate value of internal enegry (used in the integrator)
        double e_n; ///intermediate volume, internal energy used in integrator

	//for multimaterials
	double eta; ///particle.h(line 69-74) viscosity of each particle<b>!!!Question!!!</b>
	
	//change rate for real particles
	double drhodt; ///<density change rate for real particles
        double dedt; ///<internal energy change rate for real particles
	Vec2d dUdt;///<acceleration change for real particles <b>or is it the other wa round</b>

	//other data
	
	/// \brief boundary particle or not
	///
	///- 0: inside the boundary
	///- 1: on the boundary
	int bd; 
	
	///boundary type if bd = 1
	///- 0 wall particle with zero or constant velocity but never move its position
	///- 1 ghost particle for perodic boundary
	int bd_type; 

	///\brief ID number
	///
	///- a real particle has a unique positive ID
	///- a wall particle has zero ID
	///- an ghost particle (for perodic boundary condition)
	///has a negtive ID of its corresponding real particle
	long ID; 
	
	///maximum ID number for non-ghost particles (real or wall particles) in the simulation
	static long ID_max;

	//for wall boundary particles
	double bd_dst;///<for wall boundary particles
	Vec2d  nrml;///<for wall boundary particles

};

#endif //PARTICLE_H
