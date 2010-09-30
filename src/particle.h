/// \file particle.h 
/// \brief a sph particle

#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2d.h"
#include "glbtype.h"
#include <stdint.h>

/// Particle class 
class Particle {
 public:
	///\brief construct a real particle
	///NOTE the particle mass and volume will be specified in initiation::VolumeMass(w)
	Particle (Vec2d position, Vec2d velocity, double density, 
		  double pressure, double temperature, spMaterial material);

	///construct a real particle including mass (used forgasdynamcis where mass 
	Particle (Vec2d position, Vec2d velocity, double density, 
		    double pressure, double mass,double temperature, 
		  spMaterial material);


	///construct a wall particle
	Particle (double x, double y, double u, double v, 
		  spMaterial material);
	
	///ghost particle creator
	Particle (spParticle RealParticle );

	///Mirror image particle creator
	Particle (spParticle RealParticle , spMaterial material);

	///destructor particle
	~Particle ();
	
	///particle states copier for boundary particles
	void StatesCopier(spParticle RealParticle , const int type);

	/// \brief boundary particle or not (click for mor info)
	///
	///- 0: inside the boundary
	///- 1: on the boundary
	const int bd; 

	///a shared pointer  to the material
	spMaterial mtl; 

	int cell_i;///<i-position in cells
        int cell_j; ///<j-position in cells
	
	///for ghost particles: pointer to their real particle
	spParticle rl_prtl;

	///\brief for time step control (click for more info)
	///
	/// max value (over all interaction partners) of
	/// mue_ab (paramter for monaghan art. viscosity,
	/// cf. Monaghan 1992 SPH review
	/// (mue_ab has the units of a dynamic viscosity: [Pa s])
	double mue_ab_max;

	//Physical data
	Vec2d R;///<position
        Vec2d P;///<momentum
        Vec2d U; ///<velocityy
        double rho;///<density
        double p;///<pressure
        double T;///<Temperature
        double Cs;///<sound speed
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
        double e_n; //intermediate volume, internal energy used in integrator


	double eta; ///<(shear) viscosity of each particle
	double zeta; ///<bulk viscosity of each particle
	//change rate for real particles
	double drhodt; ///<density change rate for real particles
        double dedt; ///<internal energy change rate for real particles
	Vec2d dUdt;///<acceleration change for real particles <b>or is it the other wa round</b>


	///\brief ID number (click for more info)
	///
	///- a real particle has a unique positive ID
	///- a wall particle has zero ID
	///- an ghost particle (for periodic boundary condition)
	///has a negtive ID of its corresponding real particle
	///\todo{at least this is not true for my simulation where all ghost particles have ID=0!!!!}
	int64_t ID;
	
	///maximum ID number for non-ghost particles (real or wall particles) in the simulation
	static int64_t ID_max;
};

#endif //PARTICLE_H
