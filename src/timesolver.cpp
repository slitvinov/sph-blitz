#include <iostream>
#include <cmath>
#include <stdio.h>
#include "dllist.h"
#include "diagnose.h"
#include "initiation.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "particlemanager.h"
#include "timesolver.h"
using namespace std;
enum {X, Y};
TimeSolver::TimeSolver(Initiation *ini)
{
    cell_size = ini->cell_size;
    box_size[X] = ini->box_size[X];
    box_size[Y] = ini->box_size[Y];
    smoothinglength = ini->smoothinglength;
    ite = 0;
}
void TimeSolver::TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary, double &Time, double D_time, Diagnose &diagnose, Initiation &ini, QuinticSpline &weight_function, MLS &mls)
{
    double integeral_time = 0.0;
    while(integeral_time < D_time) {
	dt = hydro.GetTimestep();
	ite ++;
	integeral_time += dt;
	Time += dt;
	if(ite % 10 == 0) cout<<"N="<<ite<<" Time: "
			      <<Time<<"	dt: "<<dt<<"\n";
	if(ini.diagnose == 1) {
	    diagnose.SaveStates(hydro);
	    diagnose.Average(particles, mls, weight_function);
	}
	if(ini.diagnose == 2 && ite % 10 == 0) diagnose.KineticInformation(Time, hydro);
	hydro.BuildPair(&particles, &weight_function);
	hydro.UpdateDensity();
	boundary.BoundaryCondition(&particles);
	hydro.UpdatePhaseGradient(&boundary);
	boundary.BoundaryCondition(&particles);
	hydro.UpdateSurfaceStress(&boundary);
	hydro.UpdateChangeRate();
	hydro.Predictor_summation(dt);
	boundary.BoundaryCondition(&particles);
	hydro.UpdatePair(&weight_function);
	hydro.UpdateDensity();
	boundary.BoundaryCondition(&particles);
	hydro.UpdatePhaseGradient(&boundary);
	boundary.BoundaryCondition(&particles);
	hydro.UpdateSurfaceStress(&boundary);
	hydro.UpdateChangeRate();
	hydro.UpdateRandom(sqrt(dt));
	hydro.Corrector_summation(dt);
	hydro.RandomEffects();
	boundary.RunAwayCheck(&hydro);
	particles.UpdateCellLinkedLists();
	boundary.BuildBoundaryParticles(&particles, &hydro);
    }
}
