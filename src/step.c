#include <stdio.h>
#include <math.h>
#include "sph/ini.h"
#include "sph/hydro.h"
#include "sph/boundary.h"
#include "sph/manager.h"
#include "sph/step.h"

void
step(int *pite, struct Hydro *hydro, struct Ini *manager,
     struct Boundary *boundary, double *Time, double D_time,
     struct Kernel *kernel)
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
        manager_build_pair(manager, hydro->pair_list,
                           hydro->particle_list, hydro->forces, kernel);
        UpdateDensity(hydro);
        boundary_condition(boundary, manager->cell_lists);
        UpdatePhaseGradient(hydro, boundary);
        boundary_condition(boundary, manager->cell_lists);
        UpdateSurfaceStress(hydro, boundary);
        UpdateChangeRate(hydro);
        Predictor_summation(hydro, dt);
        boundary_condition(boundary, manager->cell_lists);
        UpdatePair(hydro, kernel);
        UpdateDensity(hydro);
        boundary_condition(boundary, manager->cell_lists);
        UpdatePhaseGradient(hydro, boundary);
        boundary_condition(boundary, manager->cell_lists);
        UpdateSurfaceStress(hydro, boundary);
        UpdateChangeRate(hydro);
        UpdateRandom(hydro, sqrt(dt));
        Corrector_summation(hydro, dt);
        RandomEffects(hydro);
        boundary_check(boundary, hydro->particle_list);
        manager_update_list(manager);
        boundary_build(boundary, manager->cell_lists, hydro->materials);
    }
    *pite = ite;
}
