#include <stdio.h>
#include <stdlib.h>
#include "sph/err.h"
#include "sph/hydro.h"
#include "sph/ini.h"
#include "sph/kernel.h"
#include "sph/material.h"
#include "sph/pair.h"
#include "sph/particle.h"
#include "sph/step.h"
#include "sph/volume.h"
extern double pair_art_vis;
extern double pair_delta;
extern long particle_ID_max;
extern int particle_number_of_materials;
int
main(int argc, char *argv[])
{
    double Time;
    int ite;
    struct Hydro *hydro;
    struct Ini ini;
    struct Kernel *kernel;
    struct Manager *manager;

    if (argc < 2)
        ERR(2, ("no project name specified"));
    srand(12345);
    initiation_ini(argv[1], &ini);
    pair_art_vis = ini.art_vis;
    pair_delta = ini.delta;
    particle_number_of_materials = ini.number_of_materials;
    particle_ID_max = 0;
    kernel = kernel_ini(ini.smoothinglength);
    hydro = hydro_ini(&ini);

    manager_build_particles(&ini, hydro->materials,
                            hydro->particle_list, &ini);
    boundary_build(&ini, ini.cell_lists, hydro->materials);
    VolumeMass(hydro->particle_list, &ini, kernel);
    boundary_condition(&ini, ini.cell_lists);

    Time = ini.Start_time;
    output_particles(&ini, hydro->particle_list, hydro->materials, Time);
    ite = 0;
    while (Time < ini.End_time) {
        if (Time + ini.D_time >= ini.End_time)
            ini.D_time = ini.End_time - Time;
        step(&ite, hydro, &ini, &Time, ini.D_time, kernel);
        output_particles(&ini, hydro->particle_list, hydro->materials,
                         Time);
        output_restart(&ini, hydro->particle_list, Time);
    }

    manager_fin(&ini);
    hydro_fin(hydro);
    kernel_fin(kernel);
    return 0;
}
