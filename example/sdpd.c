#include <stdio.h>
#include <stdlib.h>
#include "sph.h"
int
main(int argc, char *argv[])
{
    double Time;
    int ite;
    struct Ini ini;
    struct Kernel *kernel;

    if (argc < 2) {
      fprintf(stderr, "sdpd: error: no project name specified");
      exit(2);
    }
    srand(12345);
    initiation_ini(argv[1], &ini);
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
