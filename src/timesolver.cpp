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
#include "vec2d.h"
#include "glbfunc.h"

#include "dllist.h"
#include "diagnose.h"

#include "initiation.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "particlemanager.h"
#include "timesolver.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
TimeSolver::TimeSolver(Initiation &ini)
{
        ///- copy properties from class Initiation
	cell_size = ini.cell_size;
	box_size = ini.box_size;
	smoothinglength = ini.smoothinglength;
	
	///- initialize the iteration
	ite = 0;
}
//----------------------------------------------------------------------------------------
//					advance time interval D_time with summation for density
//					predictor and corrector method used
//----------------------------------------------------------------------------------------
void TimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
				   double &Time, double D_time, Diagnose &diagnose,
				   Initiation &ini, QuinticSpline &weight_function, MLS &mls)
{
	double integeral_time = 0.0;
	
	while(integeral_time < D_time) {

		dt = hydro.GetTimestep();

		ite ++;
		integeral_time += dt;
		Time += dt;
		
		  ///<ul><li>screen information for the iteration
		if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
							 <<Time<<"	dt: "<<dt<<"\n";

		///<li>calculating diagnose information
		if(ini.diagnose == 1) {
			diagnose.SaveStates(hydro);
			diagnose.Average(particles, mls, weight_function, ini);
		}

		///<li>output diagnose information
		if(ini.diagnose == 2 && ite % 10 == 0) diagnose.KineticInformation(Time, ini, hydro);

		//predictor and corrector method used
		///<li>the prediction step
		hydro.BuildPair(particles, weight_function);///<ol><li>hydro.buildPair
		hydro.UpdateDensity();///<li> hydro.UpdateDensity
		boundary.BoundaryCondition(particles);///<li> boundary.BoundaryCondition
		hydro.UpdatePhaseGradient(boundary);///<li>hydro.UpdatePhaseGradient
		boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
		hydro.UpdateSurfaceStress(boundary);///<li>hydro.UpdateSurfaceStress
		hydro.UpdateChangeRate();///<li> hydro.UpdateChangeRate
		hydro.Predictor_summation(dt);///<li>hydro.Predictor_summation</ol>

		///<li> the correction step without update the interaction list
		boundary.BoundaryCondition(particles);///<ol><li>boundary.BoundaryCondition
		hydro.UpdatePair(weight_function);///<li>hydro.UpdatePair
		hydro.UpdateDensity();///<li>hydro.UpdateDensity
		boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
		hydro.UpdatePhaseGradient(boundary);///<li>hydro.UpdatePhaseGradient
		boundary.BoundaryCondition(particles);///<li>boundary.BoundaryCondition
		hydro.UpdateSurfaceStress(boundary);///<li>hydro.UpdateSurfaceStress
		hydro.UpdateChangeRate(); ///<li>hydro.UpdateChangeRate
                hydro.UpdateRandom(sqrt(dt));///
		hydro.Corrector_summation(dt);///<li>hydro.Corrector_summation</ol>
                hydro.RandomEffects();

		///<li> renew boundary particles
		boundary.RunAwayCheck(hydro);///<ol><li>boundary.RunAwayCheck
		particles.UpdateCellLinkedLists();///<li>particles.UpdateCellLinkedLists
		boundary.BuildBoundaryParticles(particles, hydro);///<li>boundary.BuildBoundaryParticles</ol></ul>
	}
}


