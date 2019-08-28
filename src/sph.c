#include <stdio.h>
#include "err.h"
#include "particle.h"
#include "step.h"
#include "mls.h"
#include "diagnose.h"
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
    struct Boundary *boundary;
    double Time;
    struct Ini ini;
    int ite;
    struct Diagnose *diagnose;
    struct Manager *particles;
    struct MLS *mls;
    struct Output *output;
    struct Kernel kernel;
    struct Hydro *hydro;

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
    particles = manager_ini(&ini);
    hydro = hydro_ini(&ini);

    manager_build_particles(particles, hydro->materials,
			    hydro->particle_list, &ini);
    boundary = boundary_ini(&ini);
    boundary_build(boundary, particles->cell_lists, hydro->materials);
    output = output_ini(&ini);
    VolumeMass(hydro->particle_list, particles, &kernel);
    boundary_condition(boundary, particles->cell_lists);
    diagnose = diag_ini(&ini, hydro->particle_list, hydro->materials);

    Time = ini.Start_time;
    output_particles(output, hydro->particle_list, hydro->materials,
		     boundary, Time);
    output_states(output, particles, mls, &kernel, Time);
    if (ini.diagnose == 2)
	KineticInformation(diagnose, Time, hydro->particle_list,
			   hydro->materials);

    ite = 0;
    while (Time < ini.End_time) {
	if (Time + ini.D_time >= ini.End_time)
	    ini.D_time = ini.End_time - Time;
	step(&ite, hydro, particles, boundary, &Time, ini.D_time,
	     diagnose, &ini, &kernel, mls);
	output_particles(output, hydro->particle_list, hydro->materials,
			 boundary, Time);
	output_restart(output, hydro->particle_list, Time);
	if (ini.diagnose == 1) {
	    OutputProfile(diagnose, Time);
	    OutputAverage(diagnose, Time);
	}
    }

    boundary_fin(boundary);
    manager_fin(particles);
    mls_fin(mls);
    output_fin(output);
    diag_fin(diagnose);
    hydro_fin(hydro);
    return 0;
}
