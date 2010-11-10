/// \file particle.h 
/// \brief a sph particle

#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2d.h"
#include "initiation.h"
#include "glbtype.h"
#include <stdint.h>
#include <vector>

using namespace std;

/// Particle class 
class Particle {
 public:
	///\brief construct a real particle
	///NOTE the particle mass and volume will be specified in initiation::VolumeMass(w)
	Particle (Vec2d position, Vec2d velocity, double density, 
		  double pressure, double temperature, spMaterial material);

	///construct a real particle* including mass (used for gasdynamcis where mass initialized via external file, *: constructor also used for these ghost partices which form a <<SolidObstacle>> within the calculation domain. So, in case one would like to evolute the density, they have an ID and they can interact like a normal particle (i.e. they can be origin and destination of an interaction). The fact of being a ghost particle is marked later (directly after the particle's construction) by setting the flag <<solidObstacle_ghostParticle>>. 
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

	/// increments value of density depending on particle's type
	/// i.e. modification if real particle or ghost prtl with density evolution
	/// no modification if ghost particle and no density evolution selected
	// method is needed for summation density approach
	void increment_rho_depOnType(double rho_increment);

	/// sets value of density depending on particle's type
	/// i.e. modification if real particle or ghost prtl with density evolution
	/// no modification if ghost particle and no density evolution selected
	// method is needed for continuity density approach
	void set_rho_depOnType(double rho_);


	/// \brief boundary particle or not (click for mor info)
	///
	///- 0: inside the boundary
	///- 1: on the boundary
	const int bd; 

	///\brief indicates if this is a ghost particle formong a solid obstacle
	///
	/// 0: NOT a ghostparticle for solid obstacle (can be any other particle type: real particle, boundary particle ghost particle for te boundary conditions at the domein edge...)
	/// 1: this is a ghost particle forming a solid obstacle (other than the  ones at the domain edes) (i.e cavity, porisity,...)
	int solidObstacle_ghostParticle;

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

	// variables for particle values at full timestep needed for output when
	// leapfrog integration scheme applied
	Vec2d U_output;///<U at full timestep for output (needed for leapfrog integration)
	double e_output;///<e at full timestep for output (needed for leapfrog integration)
	double rho_output;///<rho at full timestep for output (needed for leapfrog integration)

	double eta; ///<(shear) viscosity of each particle
	double zeta; ///<bulk viscosity of each particle
	double k;///< thermal conductivity
	double cv;///< heat capacity at constant volume 
	//change rate for real particles
	double drhodt; ///<density change rate for real particles
        double dedt; ///<internal energy change rate for real particles
	Vec2d dUdt;///<acceleration change for real particles <b>or is it the other wa round</b>

	///\brief solid Obstacle tangent plane ( line in 2D) for this particle
	///
	/// consists of two 2D vectors, the first giving the origin of the line (x,y)
	/// and the second giving the direction (x,y) (orientation does not matter).
	/// If the particle is not within one supportlength to the solidObstacle,
	/// no tangent plane is needed. In this case the default values are (0,0) (0,0)
	vector <Vec2d> SolObs_tangent;

	///\brief distance from this (real) particle to solidObstacle surface
	///
	/// distance given as absolute value (always positive)
       	double d_realPart_solObs;


	///\brief ID number (click for more info)
	///
	///- a real particle has a unique positive ID
	///- a wall particle has zero ID
	///- an ghost particle (for periodic boundary condition)
	///has a negtive ID of its corresponding real particle
	///\todo{this is not true: all ghost particles have ID=0!!!!}
	int64_t ID;
	
	///maximum ID number for non-ghost particles (real or wall particles) in the simulation
	static int64_t ID_max;
};

#endif //PARTICLE_H
