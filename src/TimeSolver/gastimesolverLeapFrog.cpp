/// \file gastimesolverLeapFrog.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
/// \author changes by: Sergey Litvinov <slitvinov@gmail.com>

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
void GasTimeSolverLeapFrog::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                                           Boundary &boundary,
                                           double &Time, double D_time,
                                           const Initiation &ini, spKernel weight_function)
{
  double integeral_time = 0.0;
  /// loop as long as time < output interval
  while(integeral_time < D_time) {
    
    ///<ul><li> call automatic time step control GasDyn or take manual dt (depending on preference specified in .tcl-file)
    double dt;//time step
    if (ini.autom_dt_control==1)
      dt=hydro.GetTimestepGas(ini);
    else
      dt=ini.manually_choosen_dt;
    
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt;
    LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    
    Time += dt;

    // try oscillating wall

    // //generate first wave at instant t=0
    // if(Time<0.422577127)
    //   boundary.UxBl[0]=0.05916*sin(14.86873023*Time);
    // if(Time>=0.422577127-1e-7)
    //   boundary.UxBl[0]=0;
    
    // // generate second wave as soon as first wave hits RHS wall
    // if(Time>1.690308509 && Time<2.112885637)
    //   boundary.UxBl[0]=0.05916*sin(14.86873023*Time);
    // if(Time>=2.112885637-1e-7)
    //   boundary.UxBl[0]=0;
    
    ///<li>screen information for the iteration
    if (ite % 10 == 0) cout<<"N="<<ite<<" Time: " <<Time<<"	dt: "<<dt<<"\n";
    if (ite!=1) {
      hydro.UpdateUe2Half(dt);
      
      if  (!ini.disable_boundary)//check if boundary disabled
	///build the boundary particles
	boundary.BuildBoundaryParticle(particles,hydro);
    }
    ///build interactions
    hydro.BuildInteractions(particles, weight_function, ini);
    ///calculate density (by summation)
    hydro.UpdateDensity(ini, weight_function);
    ///update the state of the boundary particles (by copying the real particles' state)
    if  (!ini.disable_boundary)
      boundary.BoundaryCondition(particles);
    ///calculate change rate
    hydro.UpdateChangeRate(ini);
    
    if (ite==1)  
      hydro.AdvanceFirstStep(dt);
    else 
      hydro.AdvanceStandardStep(dt);

    //udate particle volume (this is neccerary each time the particle position has changed)
    hydro.UpdateVolume(particles, weight_function);
    
    if  (!ini.disable_boundary)
      ///run away check before cell link lists are updated (due to index purposes)
      boundary.RunAwayCheck(hydro);  
    ///update of cell linked lists
    particles.UpdateCellLinkedLists();
  }
}
///time integration including density (continuity density approach)
void GasTimeSolverLeapFrog::TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, 
					 Boundary &boundary,
					 double &Time, double D_time,
					 const Initiation &ini, spKernel weight_function)
{
  double integeral_time = 0.0;
  while(integeral_time < D_time) {

    ///<ul><li> call automatic time step control GasDyn or take manual dt (depending on preference specified in .tcl-file)
    double dt;//time step
    if (ini.autom_dt_control==1)
      dt=hydro.GetTimestepGas(ini);
    else
      dt=ini.manually_choosen_dt;
        
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt;
    LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
    
    ///<li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";
    
    if(ite!=1) {
      hydro.UpdateUeRho2Half(dt);
      if  (!ini.disable_boundary)//if not 1d (as in 1D now BC needed)
	///build the boundary particles
	boundary.BuildBoundaryParticle(particles,hydro);
    }
    
    ///\todo{change comments to doxygen format, best would probably be to make a list with all if/else statements)}
    //build interactions
    hydro.BuildInteractions(particles, weight_function, ini);
    if(ite==1) //smooth density (only) at first time step  
      hydro.UpdateDensity(ini, weight_function);
    else//update state without smoothing (p,c,...)
      hydro.UpdateState(ini);
    //if boundary condition applicable: update boundary particle states
    if(!ini.disable_boundary)
      boundary.BoundaryCondition(particles);
    //update change rates for U, e AND rho
    hydro.UpdateChangeRateInclRho(ini);
    
    if(ite==1)  
      hydro.AdvanceFirstStepInclRho(dt);
    else 
      hydro.AdvanceStandardStepInclRho(dt);
    //udate particle volume (this is neccerary each time the particle position has changed)
    hydro.UpdateVolume(particles, weight_function);
    
    
    //perform run away check before updating linked lists (due to possible index issues)
    if  (!ini.disable_boundary)   
      boundary.RunAwayCheck(hydro); 
    //update cell linked list
    particles.UpdateCellLinkedLists();
  }
}
