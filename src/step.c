#include <stdio.h>
#include <math.h>
#include "diag.h"
#include "ini.h"
#include "hydro.h"
#include "boundary.h"
#include "manager.h"
#include "step.h"

void
step(int *pite, struct Hydro *hydro, struct Manager *manager,
     struct Boundary *boundary, double *Time, double D_time,
     struct Diag *diag, struct Ini *ini,
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
        if (ini->diag == 1) {
            SaveStates(diag, hydro->particle_list);
            Average(diag, manager, mls, kernel);
        }
        if (ini->diag == 2 && ite % 10 == 0)
            KineticInformation(diag, *Time, hydro->particle_list,
                               hydro->materials);
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
