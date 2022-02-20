#include <stdio.h>
#include <stdlib.h>
#include "sph/err.h"
#include "sph/ini.h"
#include "sph/kernel.h"
#include "sph/material.h"
#include "sph/pair.h"
#include "sph/particle.h"
extern double pair_art_vis;
extern double pair_delta;
extern long particle_ID_max;
extern int particle_number_of_materials;
int
main(int argc, char *argv[])
{
    double Time;
    int ite;
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

    manager_build_particles(&ini, ini.materials, ini.particle_list, &ini);
    boundary_build(&ini, ini.cell_lists, ini.materials);
    VolumeMass(ini.particle_list, &ini, kernel);
    boundary_condition(&ini, ini.cell_lists);

    Time = ini.Start_time;
    output_particles(&ini, ini.particle_list, ini.materials, Time);
    ite = 0;
    while (Time < ini.End_time) {
        if (Time + ini.D_time >= ini.End_time)
            ini.D_time = ini.End_time - Time;
        step(&ite, &ini, &Time, ini.D_time, kernel);
        output_particles(&ini, ini.particle_list, ini.materials, Time);
        output_restart(&ini, ini.particle_list, Time);
    }

    initiation_fin(&ini);
    kernel_fin(kernel);
    return 0;
}
