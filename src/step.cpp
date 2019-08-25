#include <stdio.h>
#include <tgmath.h>
#include "particle.h"
#include "list.h"
#include "dllist.h"
#include "diagnose.h"
#include "initiation.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "particlemanager.h"
#include "step.h"

void step(int ite, Hydrodynamics *hydro, ParticleManager *particles, Boundary *boundary, double *Time, double D_time, Diagnose *diagnose, Initiation *ini, QuinticSpline *weight_function, MLS *mls)
{
    double integeral_time;
    double dt;

    integeral_time = 0;
    while(integeral_time < D_time) {
	dt = hydro->GetTimestep();
	ite ++;
	integeral_time += dt;
	*Time += dt;
	if(ite % 10 == 0)
	    printf("N=%d Time: %g	dt: %g\n", ite, *Time, dt);
	if(ini->diagnose == 1) {
	    diagnose->SaveStates(hydro);
	    diagnose->Average(particles, mls, weight_function);
	}
	if(ini->diagnose == 2  && ite % 10 == 0)
	    diagnose->KineticInformation(*Time, hydro);
	manager_build_interaction(particles, hydro->interaction_list, hydro->particle_list, hydro->forces, weight_function);
	hydro->UpdateDensity();
	boundary_condition(boundary, particles->cell_lists);
	hydro->UpdatePhaseGradient(boundary);
	boundary_condition(boundary, particles->cell_lists);
	hydro->UpdateSurfaceStress(boundary);
	hydro->UpdateChangeRate();
	hydro->Predictor_summation(dt);
	boundary_condition(boundary, particles->cell_lists);
	hydro->UpdatePair(weight_function);
	hydro->UpdateDensity();
	boundary_condition(boundary, particles->cell_lists);
	hydro->UpdatePhaseGradient(boundary);
	boundary_condition(boundary, particles->cell_lists);
	hydro->UpdateSurfaceStress(boundary);
	hydro->UpdateChangeRate();
	hydro->UpdateRandom(sqrt(dt));
	hydro->Corrector_summation(dt);
	hydro->RandomEffects();
	boundary_check(boundary, hydro->particle_list);
	manager_update_list(particles);
	boundary_build(boundary, particles->cell_lists, hydro->materials);
    }
}
