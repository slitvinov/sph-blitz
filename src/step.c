#include <stdio.h>
#include <math.h>
#include "sph/ini.h"
#include "sph/step.h"

void
step(int *pite, struct Ini *ini,
     double *Time, double D_time, struct Kernel *kernel)
{
    double integeral_time;
    double dt;
    int ite;

    ite = *pite;

    integeral_time = 0;
    while (integeral_time < D_time) {
        dt = GetTimestep(ini);
        ite++;
        integeral_time += dt;
        *Time += dt;
        if (ite % 10 == 0)
            printf("N=%d Time: %g	dt: %g\n", ite, *Time, dt);
        manager_build_pair(ini, ini->pair_list,
                           ini->particle_list, ini->forces, kernel);
        UpdateDensity(ini);
        boundary_condition(ini, ini->cell_lists);
        UpdatePhaseGradient(ini);
        boundary_condition(ini, ini->cell_lists);
        UpdateSurfaceStress(ini);
        UpdateChangeRate(ini);
        Predictor_summation(ini, dt);
        boundary_condition(ini, ini->cell_lists);
        UpdatePair(ini, kernel);
        UpdateDensity(ini);
        boundary_condition(ini, ini->cell_lists);
        UpdatePhaseGradient(ini);
        boundary_condition(ini, ini->cell_lists);
        UpdateSurfaceStress(ini);
        UpdateChangeRate(ini);
        UpdateRandom(ini, sqrt(dt));
        Corrector_summation(ini, dt);
        RandomEffects(ini);
        boundary_check(ini, ini->particle_list);
        manager_update_list(ini);
        boundary_build(ini, ini->cell_lists, ini->materials);
    }
    *pite = ite;
}
