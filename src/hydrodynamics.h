#ifndef HYDRODYNAMICS_H
#define HYDRODYNAMICS_H
/// \file hydrodynamics.h
/// \brief  Definition of  materials and their hydrodynamical interactions

#include "material.h"
#include "vec2d.h"
#include "glbtype.h"
#include <list>

class Interaction;
class Particle ;
class ParticleManager;
class Kernel;
namespace blast = boost::numeric::ublas;

/// Definition of  materials and their hydrodynamical interactions
class Hydrodynamics
{	
  double dt_g_vis;

  ///the interaction (particle pair) list
  std::list<spInteraction> interaction_list;

public:
	///the materials used
	/// store a shared pointers to the 
	/// material class
	vecMaterial materials;

	///the interaction force used
	std::list<spParticle> particle_list; ///<particle list for all particles

	///constructor
	Hydrodynamics(ParticleManager &particles, Initiation &ini);

	///get the time step
	double GetTimestep(const Initiation& ini) const;

	///build new pairs
	void BuildInteractions(ParticleManager &particles, const Kernel &weight_function);
	///update new parameters in pairs
	void UpdateInteractions(const Kernel &weight_function);

	//manupilate the particle physics
	///initiate particle change rate
	void ZeroChangeRate();
	///add the gravity effects
	void AddGravity(const Initiation& ini);
	///calculate interaction with updating interaction list
	void UpdateChangeRate(ParticleManager &particles, 
			      const Kernel &weight_function,
			      const Initiation& ini);
	///calculate interaction without updating interaction list
	void UpdateChangeRate(const Initiation& ini);
	///initiate particle density to zero
	void Zero_density();
	/// initiate particle density to the contributions of the 
	/// particle itself
	void Self_density(const Kernel& weight_function);
	///summation for particles density (with updating interaction list)
	void UpdateDensity(ParticleManager &particles, const Kernel &weight_function,
			   const Initiation &ini);
	///currently no shear rate calculated  without updating interaction list
	void UpdateDensity(const Initiation &ini, const Kernel &weight_function);///???

	///calculate states from conservatives
	void UpdateState(const Initiation &ini);
	///calculate partilce volume
	void UpdateVolume(ParticleManager &particles, const Kernel &weight_function);

	/// predictor method, density evaluated directly
	void Predictor(double dt);
	/// corrector method, density evaluated directly:<b> corrector advances p, rho, U</b>
	void Corrector(double dt);

	///for predictor method, density evaluated with summation (that means: no density update within this method)
	void Predictor_summation(double dt);
        ///for corrector method, density evaluated with summation (that means: no density update within this method)
	void Corrector_summation(double dt);

	///special uitilities
	void Zero_Velocity();

};

#endif //HYDRODYNAMICS_H
