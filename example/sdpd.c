#include <stdio.h>
#include <stdlib.h>
#include "sph/err.h"
#include "sph/boundary.h"
#include "sph/hydro.h"
#include "sph/ini.h"
#include "sph/kernel.h"
#include "sph/manager.h"
#include "sph/material.h"
#include "sph/output.h"
#include "sph/pair.h"
#include "sph/particle.h"
#include "sph/step.h"
#include "sph/volume.h"
#include "sph/random.h"
extern double pair_art_vis;
extern double pair_delta;
extern long particle_ID_max;
extern int particle_number_of_materials;
int
main(int argc, char *argv[])
{
    double Time;
    int ite;
    struct Boundary *boundary;
    struct Hydro *hydro;
    struct Ini ini;
    struct Kernel *kernel;
    struct Manager *manager;
    struct Output *output;

    if (argc < 2)
        ERR(2, ("no project name specified"));
    random_seed(12345);
    initiation_ini(argv[1], &ini);
    pair_art_vis = ini.art_vis;
    pair_delta = ini.delta;
    particle_number_of_materials = ini.number_of_materials;
    particle_ID_max = 0;
    kernel = kernel_ini(ini.smoothinglength);
    manager = manager_ini(&ini);
    hydro = hydro_ini(&ini);

    manager_build_particles(manager, hydro->materials,
                            hydro->particle_list, &ini);
    boundary = boundary_ini(&ini);
    boundary_build(boundary, manager->cell_lists, hydro->materials);
    output = output_ini(&ini);
    VolumeMass(hydro->particle_list, manager, kernel);
    boundary_condition(boundary, manager->cell_lists);

    Time = ini.Start_time;
    output_particles(output, hydro->particle_list, hydro->materials,
                     boundary, Time);
    ite = 0;
    while (Time < ini.End_time) {
        if (Time + ini.D_time >= ini.End_time)
            ini.D_time = ini.End_time - Time;
        step(&ite, hydro, manager, boundary, &Time, ini.D_time, kernel);
        output_particles(output, hydro->particle_list, hydro->materials,
                         boundary, Time);
        output_restart(output, hydro->particle_list, Time);
    }

    boundary_fin(boundary);
    manager_fin(manager);
    output_fin(output);
    hydro_fin(hydro);
    kernel_fin(kernel);
    return 0;
}
