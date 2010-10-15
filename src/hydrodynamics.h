#ifndef HYDRODYNAMICS_H
#define HYDRODYNAMICS_H
/// \file hydrodynamics.h
/// \brief  Definition of  materials and their hydrodynamical interactions

#include <list>
#include "material.h"
#include "vec2d.h"
#include "glbtype.h"


class Interaction;
class Particle ;
class ParticleManager;
class Kernel;
namespace blast = boost::numeric::ublas;

/// Definition of  materials and their hydrodynamical interactions
class Hydrodynamics
{	
  //  double dt_g_vis;

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

  ///get the time step for hydro
  double GetTimestep(const Initiation& ini) const;
  ///get the time step for gas dyanamics
  double GetTimestepGas(const Initiation& ini);
  /// get the time step for thermal conductivity simulations
  double GetTimestepThermo(const Initiation& ini) const;
  ///build new pairs
  void BuildInteractions(ParticleManager &particles, spKernel weight_function, const Initiation& ini);
  ///update new parameters in pairs
  void UpdateInteractions(spKernel weight_function);

  //manipulate the particle physics
  ///initiate particle change rate
  void ZeroChangeRate();
  ///add the gravity effects
  void AddGravity(const Initiation& ini);
  ///calculate interaction with updating interaction list
  void UpdateChangeRate(ParticleManager &particles, 
			spKernel weight_function,
			const Initiation& ini);
  ///calculate interaction without updating interaction list
  void UpdateChangeRate(const Initiation& ini);
  void UpdateChangeRateInclRho(const Initiation& ini);
  ///initiate particle density to zero
  void Zero_density();
  /// initiate particle density to the contributions of the 
  /// particle itself
  void Self_density(spKernel  weight_function);
  ///summation for particles density (with updating interaction list)
  void UpdateDensity(ParticleManager &particles, spKernel weight_function,
		     const Initiation &ini);
  ///currently no shear rate calculated  without updating interaction list
  void UpdateDensity(const Initiation &ini, spKernel weight_function);///???

  ///calculate states from conservatives
  void UpdateState(const Initiation &ini);
  ///calculate particle volume
  void UpdateVolume(ParticleManager &particles, spKernel weight_function);

  /// predictor method, density evaluated directly
  void Predictor(const double dt);
  /// corrector method, density evaluated directly:<b> corrector advances p, rho, U</b>
  void Corrector(const double dt);

  ///for predictor method, density evaluated with summation (that means: no density update within this method)
  void Predictor_summation(const double dt);
  ///for corrector method, density evaluated with summation (that means: no density update within this method)
  void Corrector_summation(const double dt);

  ///special utilities
  void Zero_Velocity();
  ///sets art.vis parameter mue_ab_max (which is needed for time control) to zero 
  void Zero_mue_ab_max();

  //everything that comes below this, is new:
  void AdvanceFirstStep(const double dt);
  void AdvanceFirstStepInclRho(const double dt);
  void AdvanceStandardStep(const double dt);
  void AdvanceStandardStepInclRho(const double dt);
  void UpdateUe2Half(const double dt);
  void UpdateUeRho2Half(const double dt);
private:
  /// local reference to Initiation
  const Initiation& ini;
};

#endif //HYDRODYNAMICS_H
