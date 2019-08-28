#include <stdio.h>
#include <math.h>
#include "particle.h"
#include "diagnose.h"
#include "ini.h"
#include "hydro.h"
#include "boundary.h"
#include "manager.h"
#include "step.h"

void
step(int *pite, struct Hydro *hydro, struct Manager *particles,
     struct Boundary *boundary, double *Time, double D_time,
     struct Diagnose *diagnose, struct Ini *ini,
     struct Kernel *kernel, struct MLS *mls)
{
    double integeral_time;
    double dt;
    int ite;

    ite = *pite;

    integeral_time = 0;
    while (integeral_time < D_time) {
	dt = GetTimestep(hydro);
	ite++;
	integeral_time += dt;
	*Time += dt;
	if (ite % 10 == 0)
	    printf("N=%d Time: %g	dt: %g\n", ite, *Time, dt);
	if (ini->diagnose == 1) {
	    SaveStates(diagnose, hydro->particle_list);
	    Average(diagnose, particles, mls, kernel);
	}
	if (ini->diagnose == 2 && ite % 10 == 0)
	    KineticInformation(diagnose, *Time, hydro->particle_list,
			       hydro->materials);
	manager_build_pair(particles, hydro->pair_list,
				  hydro->particle_list, hydro->forces,
				  kernel);
	UpdateDensity(hydro);
	boundary_condition(boundary, particles->cell_lists);
	UpdatePhaseGradient(hydro, boundary);
	boundary_condition(boundary, particles->cell_lists);
	UpdateSurfaceStress(hydro, boundary);
	UpdateChangeRate(hydro);
	Predictor_summation(hydro, dt);
	boundary_condition(boundary, particles->cell_lists);
	UpdatePair(hydro, kernel);
	UpdateDensity(hydro);
	boundary_condition(boundary, particles->cell_lists);
	UpdatePhaseGradient(hydro, boundary);
	boundary_condition(boundary, particles->cell_lists);
	UpdateSurfaceStress(hydro, boundary);
	UpdateChangeRate(hydro);
	UpdateRandom(hydro, sqrt(dt));
	Corrector_summation(hydro, dt);
	RandomEffects(hydro);
	boundary_check(boundary, hydro->particle_list);
	manager_update_list(particles);
	boundary_build(boundary, particles->cell_lists, hydro->materials);
    }
    *pite = ite;
}
