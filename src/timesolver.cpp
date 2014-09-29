// timesolver.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//			Time solver class
//			timesolver.cpp
//-----------------------------------------------------------------------
// ***** system includes *****
//#include <iostream>
//#include <fstream>
//#include <string>

//#include <cstdio>
//#include <cstdlib>
//#include <cmath>
#define NOMULTIPHASE 

// ***** localincludes *****
#include "initiation.h"
#include "timesolver.h"
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "glbfunc.h"
#include "diagnose.h"
#include "boundary.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
TimeSolver::TimeSolver(const Initiation* const ini)
{
	//copy properties from class Initiation
	cell_size = ini->cell_size;
	box_size = ini->box_size;
	smoothinglength = ini->smoothinglength;
	
	//initialize the iteration
	ite = 0;
}

TimeSolver::~TimeSolver() {
}


//----------------------------------------------------------------------------------------
//						advance time interval D_time
//						predictor and corrector method used
//----------------------------------------------------------------------------------------
void TimeSolver::TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
				   double &Time, double D_time, Diagnose &diagnose,
				   const Initiation* const ini, QuinticSpline &weight_function, MLS &mls)
{
	double integeral_time = 0.0;
	
	while(integeral_time < D_time) {

		dt = hydro.GetTimestep();

		ite ++;
		integeral_time += dt;
		Time += dt;
		
		//screen information for the iteration
		if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "<<ini->dms_time(Time)<<"	dt: "<<dt<<"\n";

		//calculating diagonse information
		if(ini->diagnose == 1) {
			diagnose.SaveStates(hydro);
			diagnose.Average(particles, mls, weight_function, ini);
		}
		if(ini->diagnose == 2 && ite % 10 == 0) 
			diagnose.KineticInformation(Time, ini, hydro);

		//predictor and corrector method used
		//the prediction step
		hydro.BuildPair(particles, weight_function);
//		hydro.UpdatePhaseGradient(boundary);
//		hydro.UpdateSurfaceStress(boundary);
//		boundary.BoundaryCondition(particles);

		hydro.UpdateChangeRate(dt);
		hydro.Predictor(dt);
		hydro.UpdateState();

		//the correction step without update the interaction list
		hydro.UpdatePair(weight_function);
		boundary.BoundaryCondition(particles);
//		hydro.UpdatePhaseGradient(boundary);
//		hydro.UpdateSurfaceStress(boundary);
//		boundary.BoundaryCondition(particles);

		hydro.UpdateChangeRate(dt); 
//		hydro.UpdateRandom(sqrt(dt));
		hydro.UpdateRandom(sqrt(dt));
		hydro.Corrector(dt);
//		hydro.RandomEffects();
		hydro.RandomEffects();
		hydro.UpdateState();
		
		//renew boundary particles
		boundary.RunAwayCheck(hydro);
		particles.UpdateCellLinkedLists();
		boundary.BuildBoundaryParticles(particles, hydro);
	}

}
//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
void TimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
					double &Time, double D_time, Diagnose &diagnose,
					const Initiation* const ini, QuinticSpline &weight_function, MLS &mls)
{
  double integeral_time = 0.0;	
#ifdef DEBUG
  cout << "Notify" << '\n';
#endif
  //  Notify(Time);
  while(integeral_time < D_time) {
    
    dt = hydro.GetTimestep();
    
    ite ++;
    integeral_time += dt;
    Time += dt;
    
    //screen information for the iteration
    if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			  <<ini->dms_time(Time)<<"	dt: "
			  <<ini->dms_time(dt)<<"\n";
    
    //calculating diagonse information
    if(ini->diagnose == 1) {
      diagnose.SaveStates(hydro);
      diagnose.Average(particles, mls, weight_function, ini);
    }
    
    //output diagnose information
    if(ini->diagnose == 2 && ite % 10 == 0) diagnose.KineticInformation(Time, ini, hydro);
    
    //predictor and corrector method used
    //the prediction step
    hydro.BuildPair(particles, weight_function);
    hydro.UpdateDensity();
    boundary.BoundaryCondition(particles);
    
    ///Fix::
#ifndef NOMULTIPHASE
    hydro.UpdatePhaseGradient(boundary);
#endif

    boundary.BoundaryCondition(particles);

#ifndef NOMULTIPHASE
    hydro.UpdateSurfaceStress(boundary);
#endif

    hydro.UpdateChangeRate(dt);
    hydro.Predictor_summation(dt);
    
    //the correction step without update the interaction list
    boundary.BoundaryCondition(particles);
    hydro.UpdatePair(weight_function);
    hydro.UpdateDensity();
    boundary.BoundaryCondition(particles);

#ifndef NOMULTIPHASE
    hydro.UpdatePhaseGradient(boundary);
#endif

    boundary.BoundaryCondition(particles);

#ifndef NOMULTIPHASE
    hydro.UpdateSurfaceStress(boundary);
#endif

    hydro.UpdateChangeRate(dt); 
    //FIX:
    hydro.UpdateRandom(sqrt(dt));
    hydro.Corrector_summation(dt); 
    //FIX:
    hydro.RandomEffects();
    
    //renew boundary particles
    boundary.RunAwayCheck(hydro);
    particles.UpdateCellLinkedLists();
    boundary.BuildBoundaryParticles(particles, hydro);
  }
  ///set current time
  ///update observers  
  solvertime_ = Time;  
}
