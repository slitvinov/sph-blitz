/// \file gastimesolverLeapFrog.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Time solver class
//			timesolver.cpp
//-----------------------------------------------------------------------
// ***** system includes *****
#include <fstream>
#include <iomanip>
#include <glog/logging.h>
#include <boost/foreach.hpp>

// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "TimeSolver/gastimesolverLeapFrog.h"
#include "initiation.h"
#include "boundary.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
GasTimeSolverLeapFrog::GasTimeSolverLeapFrog():
  ite(0)
{
  ///- initialize the iteration
  std::cerr << "\n initiation gas timesolver leap frog succeeded\n ";
}

void GasTimeSolverLeapFrog::show_information() const {

}

//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
///time integration without density (summation density approach)
void GasTimeSolverLeapFrog::TimeIntegral_summation(Hydrodynamics &hydro,
						   ParticleManager &particles, 
						   Boundary &boundary,
						   double &Time, double D_time,
						   const Initiation &ini,
						   spKernel weight_function,
						   spSolidObstacles obstacles)
{
  double integeral_time = 0.0;
  /// loop as long as time < output interval
  while(integeral_time < D_time) {
    
    // ///<ul><li> call automatic time step control GasDyn or take manual dt (depending on preference specified in .tcl-file)
    // double dt;//time step
    // if(ini.autom_dt_control==1)
    //   dt=hydro.GetTimestepGas(ini);
    // else
    //   dt=ini.manually_choosen_dt;
    
    // //control output
    // LOG(INFO)<<"\n current timestep:"<<dt;
    // LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    // LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    // LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
     ite ++;//increment number of iterations (MUST STAY HERE)
    // integeral_time =integeral_time+ dt;
    
    // Time += dt;
     
    //=>dt assignment moved just after update change rate so that change rates
    // from current step are taken into account
     
    // BEGIN OSCILLATING WALL PASSAGE (please uncomment)
     
    //generate first wave at instant t=0
    if(Time<0.422577127)
      boundary.UxBl[0]=0.05916*sin(14.86873023*Time);
    if(Time>=0.422577127-1e-7)
      boundary.UxBl[0]=0;
     
    // generate second wave as soon as first wave hits RHS wall
    if(Time>1.690308509 && Time<2.112885637)
      boundary.UxBl[0]=0.05916*sin(14.86873023*Time);
    if(Time>=2.112885637-1e-7)
      boundary.UxBl[0]=0;
     
     // END OSCILLATING WALL PASSAGE
     LOG(INFO)<<"ite is "<<ite;
     if(ite!=1)
      {
	hydro.UpdateUe2FullStep(dt);
	
	if(ini.disable_boundary != 1)//check if boundary disabled
	  ///build the boundary particles
	  boundary.BuildBoundaryParticle(particles,hydro, Time);
      }
    ///build interactions
    hydro.BuildInteractions(particles, weight_function, ini);
    ///calculate density (by summation) (and included in method: update state afterwards
    hydro.UpdateDensity(ini, weight_function);


    //renew interaction (so that local copies of particle variables 
    //in interaction are updated everytime a particle variable changes)
    hydro.UpdateInteractions(weight_function);
    // not needed because rho is not locally copied into interaction
    //=> now needed as eta, zeta, k T-dependand and after density update T might change!
    ///\{todo=> alternative would be to remove update of eta, zeta, k from interaction 
    // constructor and method renewInteraction and to assign values locally in
    // the corresponding updateForces method!
    // this way the iteration over all interactions at this place could be avoided
    // but as I did not know how this would affect incompressible implementation I 
    // let it like thos for the moment}

    // just before updateing state of boundary particles for force calculation:
    // set tangent plane to solidObstacle surface for each real particle
    obstacles->set_all_solObs_tangentsAndDistances(hydro);

    ///update the state of the boundary particles (by copying the real particles' state)
    if(ini.disable_boundary != 1)   
      boundary.BoundaryCondition(particles, Time);
    ///calculate change rate for each particle (
    hydro.UpdateChangeRate(ini, Time);
    
    
    ///<ul><li> call automatic time step control GasDyn or take manual dt (depending on preference specified in .tcl-file)
    if(ini.autom_dt_control==1)
      dt=hydro.GetTimestepGas(ini);
    else
      dt=ini.manually_choosen_dt;
    
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt;
    LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
    integeral_time =integeral_time+ dt;
    
    ///<li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: " <<Time<<"	dt: "<<dt<<"\n";

    if(ite==1&&Time==0)//Time==0 condition needed as if initialization from .rst file
      //no first leap-frog step needed (as quantities are output in 
      //.rst shifted by dt/2)  
      hydro.AdvanceFirstStep(dt);
    else 
      hydro.AdvanceStandardStep(dt);
    //increment absolute integration time
    Time += dt;

    //udate particle volume (this is neccerary each time the particle position has changed) (interaction list is build in UpdateVolume)

    // update Volume (builds its own local interaction list and therefore
    // does not use the one created by hydro.BuildInteractions.
    // This is logical, because after the particles have moved, the simple 
    // updating of the interaction list with hydro.UpdateInteractions
    // (where the local copies of theparticle's varaibles in interaction are
    // updated) would of course not take into account particles that have 
    // become new neighbours now through their movement! 
    hydro.UpdateVolume(particles, weight_function);
    
    if  (ini.disable_boundary != 1) {
      ///run away check before cell link lists are updated (due to index purposes)
      boundary.RunAwayCheck(hydro);  
      /// reapply boundary conditions, so they are up-to-date in output-file
      boundary.BoundaryCondition(particles,Time);
    }
    ///update of cell linked lists
    particles.UpdateCellLinkedLists();

  }
}
///time integration including density (continuity density approach)
void GasTimeSolverLeapFrog::TimeIntegral(Hydrodynamics &hydro,
					 ParticleManager &particles, 
					 Boundary &boundary,
					 double &Time, double D_time,
					 const Initiation &ini,
					 spKernel weight_function,
					 spSolidObstacles obstacles)
{
  double integeral_time = 0.0;
  while(integeral_time < D_time) {

    ite ++;//increment number of iterations
    if(ite!=1) {
      hydro.UpdateUeRho2FullStep(dt);
      if  (ini.disable_boundary != 1)//if not 1d (as in 1D now BC needed)
	///build the boundary particles
	boundary.BuildBoundaryParticle(particles,hydro, Time);
    }
    
    ///\todo{change comments to doxygen format, best would probably be to make a list with all if/else statements)}
    //build interactions
    
    hydro.BuildInteractions(particles, weight_function, ini);
    if(ite==1&&ini.smoothDensityProfile==1)
      //smooth density  (at first time step only) (state updated within method)
      hydro.UpdateDensity(ini, weight_function);
    else//update state without smoothing (p,c,...)
      hydro.UpdateState(ini);
   
    //renew interaction (so that local copies of particle variables 
    //in interaction are updated everytime a particle variable changes)
    hydro.UpdateInteractions(weight_function);
    
    // just before updateing state of boundary particles for force calculation:
    // set tangent plane to solidObstacle surface for each real particle
    obstacles->set_all_solObs_tangentsAndDistances(hydro);

    //if boundary condition applicable: update boundary particle states
    if(ini.disable_boundary != 1)   
      boundary.BoundaryCondition(particles,Time);
    //update change rates for U, e AND rho
    hydro.UpdateChangeRateInclRho(ini, Time);
    

    ///<ul><li> call automatic time step control GasDyn or take manual dt (depending on preference specified in .tcl-file)
    if(ini.autom_dt_control==1)
      dt=hydro.GetTimestepGas(ini);
    else
      dt=ini.manually_choosen_dt;
        
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt;
    LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
    integeral_time =integeral_time+ dt;
    Time += dt;
 
    ///<li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";
    
    if(ite==1)  
      hydro.AdvanceFirstStepInclRho(dt);
    else 
      hydro.AdvanceStandardStepInclRho(dt);
    //udate particle volume (this is neccerary each time the particle position has changed)
    hydro.UpdateVolume(particles, weight_function);
    
    
    //perform run away check before updating linked lists (due to possible index issues)
    if  (ini.disable_boundary != 1)   
      boundary.RunAwayCheck(hydro); {
      /// reapply boundary conditions, so they are up-to-date in output-file
      boundary.BoundaryCondition(particles,Time);
    }
    //update cell linked list
    particles.UpdateCellLinkedLists();
  }
}
