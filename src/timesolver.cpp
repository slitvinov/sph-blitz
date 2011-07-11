// timesolver.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//-----------------------------------------------------------------------
//                      Time solver class
//                      timesolver.cpp
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
#include "timesolver.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "particlemanager.h"
#include "mls.h"
#include "diagnose.h"
#include "initiation.h"
#include "quinticspline.h"
#include "debug.h"

using namespace std;

//----------------------------------------------------------------------------------------
//                                                      constructor
//----------------------------------------------------------------------------------------
TimeSolver::TimeSolver(Initiation &ini)
{
    //copy properties from class Initiation
    cell_size = ini.cell_size;
    box_size = ini.box_size;
    smoothinglength = ini.smoothinglength;
        
    //initialize the iteration
    ite = 0;
}
//----------------------------------------------------------------------------------------
//                                      advance time interval D_time with summation for density
//                                      predictor and corrector method used
//----------------------------------------------------------------------------------------
void TimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
                                        double &Time, double D_time, Diagnose &diagnose,
                                        Initiation &ini, QuinticSpline &weight_function, MLS &mls)
{
  Debug dbg(ini);
    double integeral_time = 0.0;
    while(integeral_time < D_time) {
        dt = hydro.GetTimestep();
        ite ++;
        integeral_time += dt;
        Time += dt;
                
        //screen information for the iteration
        if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
                              <<Time<<"   dt: "<<dt 
			      << "   max_time: " <<ini.End_time << std::endl;

        //calculating diagonse information
        if(ini.diagnose == 1) {
            diagnose.SaveStates(hydro);
            diagnose.Average(particles, mls, weight_function, ini);
        }

        //output diagnose information
        if(ini.diagnose == 2 && ite % 10 == 0) diagnose.KineticInformation(Time, ini, hydro);
        //predictor and corrector method used
        //the prediction step
        hydro.BuildPair(particles, weight_function);
        hydro.UpdateDensity();
        boundary.BoundaryCondition(particles);
        hydro.UpdatePhaseGradient(boundary);
        boundary.BoundaryCondition(particles);
        hydro.UpdateSurfaceStress(boundary);
        hydro.UpdateChangeRate();
        hydro.Predictor_summation(dt);

        //the correction step without update the interaction list
        boundary.BoundaryCondition(particles);
        hydro.UpdatePair(weight_function);
        hydro.UpdateDensity();
        boundary.BoundaryCondition(particles);
        hydro.UpdatePhaseGradient(boundary);
        boundary.BoundaryCondition(particles);
        hydro.UpdateSurfaceStress(boundary);
        hydro.UpdateChangeRate(); 
	hydro.UpdateRandom(sqrt(dt));
        hydro.Corrector_summation(dt);
	dbg.checkVelocity(hydro.particle_list, dt, __FILE__, __LINE__);
	hydro.RandomEffects();
	dbg.checkVelocity(hydro.particle_list, dt, __FILE__, __LINE__);

        //renew boundary particles
	dbg.checkVelocity(hydro.particle_list, dt, __FILE__, __LINE__);
	dbg.checkPosition(hydro.particle_list, __FILE__, __LINE__);
        boundary.RunAwayCheck(hydro);
        particles.UpdateCellLinkedLists();
        boundary.BuildBoundaryParticles(particles, hydro);
    }
}


