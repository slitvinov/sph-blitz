/// \file gastimesolverPredCorr.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Time solver class
//			timesolver.cpp
//-----------------------------------------------------------------------
// ***** system includes *****
#include <iostream>
#include <fstream>
#include <string>
#include <boost/foreach.hpp>
#include <iomanip>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <glog/logging.h>

// ***** localincludes *****
#include "glbfunc.h"
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "TimeSolver/gastimesolverPredCorr.h"
#include "initiation.h"
#include "boundary.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
GasTimeSolverPredCorr::GasTimeSolverPredCorr():
  ite(0)
{
  ///- initialize the iteration
  std::cerr << "\n initiation gas timesolver leap frog succeeded\n ";
}

void GasTimeSolverPredCorr::show_information() const {

}

//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
///time integration without density (summation density approach)
void GasTimeSolverPredCorr::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, 
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
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: " <<Time<<"	dt: "<<dt<<"\n";
     
    ///<li>the prediction step
    hydro.BuildInteractions(particles, weight_function, ini);///<ol><li> rebuild interactions
    hydro.UpdateDensity(ini, weight_function);///<li> hydro.UpdateDensity
    //control output
    //	cout<<"\n     --- change rate for predictor:";	
    hydro.UpdateChangeRate(ini);///<li> hydro.UpdateChangeRate
	  
    hydro.Predictor_summation(dt);///<li>hydro.Predictor_summation</ol>
	  
    ///<li> the correction step without updating the interaction list
  
    // hydro.BuildInteractions(particles, weight_function, ini);///<ol><li> rebuild interactions (just a test to see, if results are different from UpdateInteractions where only interactiondata (rij, Wij,...) are renewed, but no new interaction search is performed...)

    hydro.UpdateInteractions(weight_function);///<li> update interactions
    hydro.UpdateDensity(ini, weight_function);///<li>hydro.UpdateDensity

    //control output
    LOG(INFO)<<"change rate for corrector:";
    hydro.UpdateChangeRate(ini); ///<li>hydro.UpdateChangeRate
    hydro.Corrector_summation(dt);///<li>hydro.Corrector_summation</ol>
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists  
 }
}

///time integration including density (continuity density approach)
void GasTimeSolverPredCorr::TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, 
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
    if(ite % 10 == 0) cout<<"N= "<<ite<<" Time: " <<Time<<"  dt: "<<dt<<"\n";

    hydro.BuildInteractions(particles, weight_function,ini);///<ol><li>hydro.BuildPair
    hydro.UpdateChangeRate(ini);///<li>hydro.UpdateChangeRate
    hydro.Predictor(dt);///<li>hydro.Predictor
    hydro.UpdateState(ini);///<li>hydro.UpdateState</ol>
    ///<li> the correction step without update the interaction list
    hydro.UpdateInteractions(weight_function);///<ol><li>hydro.UpdatePair
    boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
    hydro.UpdateChangeRate(ini);///<li>hydro.UpdateChangeRate
    hydro.Corrector(dt);///<li>hydro.Corrector
    hydro.UpdateState(ini);///<li>hydro.UpdateState</ol>
    ///<li> renew boundary particles
    boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
    boundary.BuildBoundaryParticle(particles, hydro);
  }
}
