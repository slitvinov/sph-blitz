#include <stdio.h>
#include "err.h"
#include "particle.h"
#include "step.h"
#include "mls.h"
#include "diag.h"
#include "output.h"
#include "kernel.h"
#include "ini.h"
#include "pair.h"
#include "manager.h"
#include "hydro.h"
#include "boundary.h"
#include "volume.h"
#include "wiener.h"
#include "material.h"
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
    struct Diag *diag;
    struct Hydro *hydro;
    struct Ini ini;
    struct Kernel kernel;
    struct Manager *manager;
    struct MLS *mls;
    struct Output *output;

    if (argc < 2)
	ERR(2, ("no project name specified"));
    wiener_seed(12345);
    initiation_ini(argv[1], &ini);
    pair_art_vis = ini.art_vis;
    pair_delta = ini.delta;
    particle_number_of_materials = ini.number_of_materials;
    particle_ID_max = 0;
    kernel_ini(ini.smoothinglength, &kernel);
    mls = mls_ini(ini.MLS_MAX);
    manager = manager_ini(&ini);
    hydro = hydro_ini(&ini);

    manager_build_particles(manager, hydro->materials,
			    hydro->particle_list, &ini);
    boundary = boundary_ini(&ini);
    boundary_build(boundary, manager->cell_lists, hydro->materials);
    output = output_ini(&ini);
    VolumeMass(hydro->particle_list, manager, &kernel);
    boundary_condition(boundary, manager->cell_lists);
    diag = diag_ini(&ini, hydro->particle_list, hydro->materials);

    Time = ini.Start_time;
    output_particles(output, hydro->particle_list, hydro->materials,
		     boundary, Time);
    output_states(output, manager, mls, &kernel, Time);
    if (ini.diag == 2)
	KineticInformation(diag, Time, hydro->particle_list,
			   hydro->materials);

    ite = 0;
    while (Time < ini.End_time) {
	if (Time + ini.D_time >= ini.End_time)
	    ini.D_time = ini.End_time - Time;
	step(&ite, hydro, manager, boundary, &Time, ini.D_time,
	     diag, &ini, &kernel, mls);
	output_particles(output, hydro->particle_list, hydro->materials,
			 boundary, Time);
	output_restart(output, hydro->particle_list, Time);
	if (ini.diag == 1) {
	    OutputProfile(diag, Time);
	    OutputAverage(diag, Time);
	}
    }

    boundary_fin(boundary);
    manager_fin(manager);
    mls_fin(mls);
    output_fin(output);
    diag_fin(diag);
    hydro_fin(hydro);
    return 0;
}
