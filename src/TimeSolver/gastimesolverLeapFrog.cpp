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
void GasTimeSolverLeapFrog::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
                                           Boundary &boundary,
                                           double &Time, double D_time,
                                           const Initiation &ini, spKernel weight_function)
{
  double integeral_time = 0.0;
	
  while(integeral_time < D_time) {

    ///\todo{ move into Initiation?...and/or make time step calculation automatically (constant time step was only for testing purposes)}
    //const double dt = 0.0025;
    
    //heree call to timesolver GasDyn
    const double dt=hydro.GetTimestepGas(ini);
    //directly after: reset mue_ab to zero
    hydro.Zero_mue_ab_max();

    //control output
    LOG(INFO)<<"\n current timestep:"<<dt;
    LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
	  
       ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: " <<Time<<"	dt: "<<dt<<"\n";
    if(ite!=1)
      {
	hydro.UpdateUe2Half(dt);

	if  (ini.kernel_type != "CubicSpline1D")//if not 1d (as in 1D now BC needed)
	  ///build the boundary particles
	  boundary.BuildBoundaryParticle(particles,hydro);
      }

    ///build interactions
    hydro.BuildInteractions(particles, weight_function, ini);
    ///calculate density (by summation)
    hydro.UpdateDensity(ini, weight_function);
    ///update the state of the boundary particles (by copying the real particles' state)
    if  (ini.kernel_type != "CubicSpline1D")   
      boundary.BoundaryCondition(particles);
    ///calculate change rate
    hydro.UpdateChangeRate(ini);

    if(ite==1)  
      hydro.AdvanceFirstStep(dt);
    else 
      hydro.AdvanceStandardStep(dt);

    if  (ini.kernel_type != "CubicSpline1D")
      ///run away check before cell link lists are updated (due to index purposes)
      boundary.RunAwayCheck(hydro);  
    ///update of cell linked lists
    particles.UpdateCellLinkedLists();

    /*

    //below is good old code:
 
    //control output
    // cout<<"\n just before build pair\n";
    //predictor and corrector method used
    ///<li>the prediction step
    hydro.BuildInteractions(particles, weight_function, ini);///<ol><li> rebuild interactions
    hydro.UpdateDensity(ini, weight_function);///<li> hydro.UpdateDensity
    //control output
    //	cout<<"\n     --- change rate for predictor:";	
    hydro.UpdateChangeRate(ini);///<li> hydro.UpdateChangeRate
	  
    hydro.Predictor_summation(dt);///<li>hydro.Predictor_summation</ol>
	  
    ///<li> the correction step without update the interaction list
  
 hydro.BuildInteractions(particles, weight_function, ini);///<ol><li> rebuild interactions   

 //hydro.UpdateInteractions(weight_function);///<li> update interactions
    hydro.UpdateDensity(ini, weight_function);///<li>hydro.UpdateDensity

    //control output
    LOG(INFO)<<"change rate for corrector:";
    hydro.UpdateChangeRate(ini); ///<li>hydro.UpdateChangeRate
    hydro.Corrector_summation(dt);///<li>hydro.Corrector_summation</ol>
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists

    //above is good old code

    */
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

    ///\todo{ move into Initiation?...and/or make time step calculation automatically (constant time step was only for testing purposes)}
    const double dt = 0.0025;
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt;
    LOG(INFO)<<"\n current absolute integraltime:"<<Time;
    LOG(INFO)<<"\n current (relative) integraltime:"<<integeral_time;
    LOG(INFO)<<"\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
	  
       ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";

    if(ite!=1)
      {
      hydro.UpdateUeRho2Half(dt);
      if  (ini.kernel_type != "CubicSpline1D")//if not 1d (as in 1D now BC needed)
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
    if  (ini.kernel_type != "CubicSpline1D")   
      boundary.BoundaryCondition(particles);
    //update change rates for U, e AND rho
    hydro.UpdateChangeRateInclRho(ini);

    if(ite==1)  
      hydro.AdvanceFirstStepInclRho(dt);
    else 
      hydro.AdvanceStandardStepInclRho(dt);
    //perform run away check before updating linked lists (due to index purposes)
    if  (ini.kernel_type != "CubicSpline1D")   
      boundary.RunAwayCheck(hydro); 
    //update cell linked list
    particles.UpdateCellLinkedLists();
  }
}
