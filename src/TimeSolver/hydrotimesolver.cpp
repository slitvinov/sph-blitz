/// \file timesolver.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Time solver class
//			timesolver.cpp
//-----------------------------------------------------------------------
#include <glog/logging.h>

// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "TimeSolver/hydrotimesolver.h"
#include "initiation.h"
#include "boundary.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
HydroTimeSolver::HydroTimeSolver():
  ite(0)
{
  ///- initialize the iteration
  LOG(INFO) <<"Creating HydroTimeSolver object";
}

void HydroTimeSolver::show_information() const {

}


//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
void HydroTimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, double D_time,	const Initiation &ini, spKernel weight_function)
{
  LOG(INFO) << "Start TimeIntegral_summation";
  double integeral_time = 0.0;
	
  while(integeral_time < D_time)
 {
    const double dt = hydro.GetTimestep(ini);
    assert(dt>0.0);
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt<<
        "\n current absolute integraltime:"<<Time<<
        "\n current (relative) integraltime:"<<integeral_time<<
        "\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
	  
    ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";
	  
    //predictor and corrector method used
    ///<li>the prediction step
    hydro.BuildInteractions(particles, weight_function, ini);///<ol><li> rebuild interactions
    hydro.UpdateDensity(ini, weight_function);///<li> hydro.UpdateDensity
    
    boundary.BoundaryCondition(particles);///<li> boundary.BoundaryCondition
    //control output
    hydro.UpdateChangeRate(ini);///<li> hydro.UpdateChangeRate
	  
    hydro.Predictor_summation(dt);///<li>hydro.Predictor_summation</ol>
    ///<li> the correction step without update the interaction list
    boundary.BoundaryCondition(particles);///<ol><li>boundary.BoundaryCondition

    hydro.UpdateInteractions(weight_function);///<li> update interactions
    hydro.UpdateDensity(ini, weight_function);///<li>hydro.UpdateDensity
    
    boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
    //control output
    LOG(INFO)<<"change rate for corrector:";
    hydro.UpdateChangeRate(ini); ///<li>hydro.UpdateChangeRate
    hydro.Corrector_summation(dt);///<li>hydro.Corrector_summation</ol>

    ///<li> renew boundary particles
    boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
    boundary.BuildBoundaryParticle(particles, hydro);///<li>boundary.BuildBoundaryspParticle</ol></ul>
  }
}


void HydroTimeSolver::TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, double D_time, const Initiation &ini, spKernel weight_function)
{
  LOG(INFO) << "Start TimeIntegral_summation";
  double integeral_time = 0.0;
	
  while(integeral_time < D_time)
  {
    const double dt = hydro.GetTimestep(ini);
    assert(dt>0.0);
    //control output
    LOG(INFO)<<"\n current timestep:"<<dt<<
        "\n current absolute integraltime:"<<Time<<
        "\n current (relative) integraltime:"<<integeral_time<<
        "\n current (absolute) iterations:"<<ite;
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
	  
    ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<Time<<"	dt: "<<dt<<"\n";

	
    //predictor and corrector method used
    ///<li> the prediction step
    hydro.BuildInteractions(particles, weight_function, ini);///<ol><li>hydro.BuildInteractions
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
    boundary.BuildBoundaryParticle(particles, hydro);///<li>boundary.BuildBoundaryParticles</ol></ul>
  }
}

HydroTimeSolver::~HydroTimeSolver() {
  LOG(INFO) << "destructor of HydroTimeSolver is called";
}
