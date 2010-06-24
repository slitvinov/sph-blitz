/// \file timesolver.cpp
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

#include <cstdio>
#include <cstdlib>
#include <cmath>

// ***** localincludes *****
#include "glbcls.h"
#include "glbfunc.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
TimeSolver::TimeSolver(Initiation &ini)
{
  ///- copy properties from class Initiation
  cell_size = ini.cell_size;
  box_size = ini.box_size;
  supportlength = ini.supportlength;
	
  ///- initialize the iteration
  ite = 0;
  cout<<"\n initiation of time solver succeeded\n ";
}
//---------------------------------------------------------------------------------------------
//				       	advance time interval D_time(=output time interval)
//					predictor and corrector method used
//-------------------------------------------------------------------------------------
void TimeSolver::TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
			      double &Time, double D_time, Diagnose &diagnose,
			      Initiation &ini, Kernel &weight_function, MLS &mls)
{
  double integeral_time = 0.0;
	
  //integrate time (loop) until the next output time
  while(integeral_time < D_time) {

    dt = hydro.GetTimestep();
    //control output
    cout<<"\n current timestep:"<<dt<<"\n";
    ite ++;
    integeral_time += dt;
    Time += dt;
		
    ///<ul><li> print out screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "<<ini.dms_time(Time)<<"	dt: "<<dt<<"\n";

    ///<li> calculating diagonse information
    if(ini.diagnose == 1) {
      diagnose.SaveStates(hydro);
      diagnose.Average(particles, mls, weight_function);
    }
    if(ini.diagnose == 2 && ite % 10 == 0) 
      diagnose.KineticInformation(Time, ini, hydro);

    //predictor and corrector method used
    ///<li> the prediction step
    hydro.BuildPair(particles, weight_function);///<ol><li>hydro.BuildPair
    //		hydro.UpdatePhaseGradient(boundary);
    //		hydro.UpdateSurfaceStress(boundary);
    //		boundary.BoundaryCondition(particles);

    hydro.UpdateChangeRate();///<li>hydro.UpdateChangeRate
    hydro.Predictor(dt);///<li>hydro.Predictor
    hydro.UpdateState(ini);///<li>hydro.UpdateState</ol>

    ///<li> the correction step without update the interaction list
    hydro.UpdatePair(weight_function);///<ol><li>hydro.UpdatePair
    boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
    //		hydro.UpdatePhaseGradient(boundary);
    //		hydro.UpdateSurfaceStress(boundary);
    //		boundary.BoundaryCondition(particles);

    hydro.UpdateChangeRate();///<li>hydro.UpdateChangeRate
    //		hydro.UpdateRandom(sqrt(dt));
    hydro.UpdateRandom(sqrt(dt));///<li>hydro.UpdateRandom
    hydro.Corrector(dt);///<li>hydro.Corrector
    //		hydro.RandomEffects();
    hydro.RandomEffects();///<li>hydro.RandomEffects
    hydro.UpdateState(ini);///<li>hydro.UpdateState</ol>

    ///<li> renew boundary particles
    boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
    boundary.BuildBoundaryParticles(particles, hydro);///<li>boundary.BuildBoundaryParticles</ol></ul>
  }
}
//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
void TimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
					double &Time, double D_time, Diagnose &diagnose,
					Initiation &ini, Kernel &weight_function, MLS &mls)
{
  double integeral_time = 0.0;
	
  while(integeral_time < D_time) {

    dt =0.0025/* hydro.GetTimestep()*/;
    //control output
    cout<<"\n current timestep:"<<dt<<"\n";
    cout<<"\n current absolute integraltime:"<<Time<<"\n";	
    cout<<"\n current (relative) integraltime:"<<integeral_time<<"\n";
    cout<<"\n current (absolute) iterations:"<<ite<<"\n";
    ite ++;
    integeral_time =integeral_time+ dt;
    Time += dt;
	  
    ///<ul><li>screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<ini.dms_time(Time)<<"	dt: "<<ini.dms_time(dt)<<"\n";
	  
    ///<li>calculating diagnose information
    if(ini.diagnose == 1) {
      diagnose.SaveStates(hydro);
      diagnose.Average(particles, mls, weight_function);
    }
	  
    ///<li>output diagnose information
    if(ini.diagnose == 2 && ite % 10 == 0) diagnose.KineticInformation(Time, ini, hydro);
    //control output
    // cout<<"\n just before build pair\n";
    //predictor and corrector method used
    ///<li>the prediction step
    hydro.BuildPair(particles, weight_function);///<ol><li>hydro.buildPair
    hydro.UpdateDensity(ini);///<li> hydro.UpdateDensity
    if(ini.simu_mode==1)
      {
	boundary.BoundaryCondition(particles);///<li> boundary.BoundaryCondition
	boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
      };
    //control output
    //	cout<<"\n     --- change rate for predictor:";	
    hydro.UpdateChangeRate();///<li> hydro.UpdateChangeRate
	  
    hydro.Predictor_summation(dt);///<li>hydro.Predictor_summation</ol>
	  
    ///<li> the correction step without update the interaction list
    if(ini.simu_mode==1)
      boundary.BoundaryCondition(particles);///<ol><li>boundary.BoundaryCondition
    hydro.UpdatePair(weight_function);///<li>hydro.UpdatePair
    hydro.UpdateDensity(ini);///<li>hydro.UpdateDensity
    if(ini.simu_mode==1)
      {
	boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
	boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
      }
    //control output
    cout<<"\n     --- change rate for corrector:";
    hydro.UpdateChangeRate(); ///<li>hydro.UpdateChangeRate
    //		hydro.UpdateRandom(sqrt(dt));//
    hydro.Corrector_summation(dt);///<li>hydro.Corrector_summation</ol>
    //		hydro.RandomEffects();

    ///<li> renew boundary particles
    if(ini.simu_mode==1)
      boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
    particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
    if(ini.simu_mode==1)
      boundary.BuildBoundaryParticles(particles, hydro);///<li>boundary.BuildBoundaryParticles</ol></ul>
  }
}
