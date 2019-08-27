#include <stdio.h>
#include "err.h"
#include "particle.h"
#include "step.h"
#include "mls.h"
#include "diagnose.h"
#include "output.h"
#include "quinticspline.h"
#include "initiation.h"
#include "interaction.h"
#include "manager.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "volume.h"
#include "wiener.h"
#include "material.h"
extern double interaction_art_vis;
extern double interaction_delta;
extern long particle_ID_max;
extern int particle_number_of_materials;
int
main(int argc, char *argv[])
{
    struct Boundary *boundary;
    double Time;
    struct Initiation ini;
    int ite;
    struct Diagnose *diagnose;
    struct Manager *particles;
    struct MLS *mls;
    struct Output *output;
    struct QuinticSpline weight_function;

    if (argc < 2)
	ERR(2, ("no project name specified"));
    wiener_seed(12345);
    initiation_ini(argv[1], &ini);
    interaction_art_vis = ini.art_vis;
    interaction_delta = ini.delta;
    particle_number_of_materials = ini.number_of_materials;
    particle_ID_max = 0;
    quinticspline_ini(ini.smoothinglength, &weight_function);
    mls = mls_ini(ini.MLS_MAX);
    particles = manager_ini(&ini);
    Hydrodynamics hydro(&ini);

    manager_build_particles(particles, hydro.materials,
			    hydro.particle_list, &ini);
    boundary = boundary_ini(&ini);
    boundary_build(boundary, particles->cell_lists, hydro.materials);
    output = output_ini(&ini);
    VolumeMass(hydro.particle_list, particles, &weight_function);
    boundary_condition(boundary, particles->cell_lists);
    diagnose = diag_ini(&ini, hydro.particle_list, hydro.materials);

    Time = ini.Start_time;
    output_particles(output, hydro.particle_list, hydro.materials,
		     boundary, Time);
    output_states(output, particles, mls, &weight_function, Time);
    if (ini.diagnose == 2)
	KineticInformation(diagnose, Time, hydro.particle_list,
			   hydro.materials);

    ite = 0;
    while (Time < ini.End_time) {
	if (Time + ini.D_time >= ini.End_time)
	    ini.D_time = ini.End_time - Time;
	step(&ite, &hydro, particles, boundary, &Time, ini.D_time,
	     diagnose, &ini, &weight_function, mls);
	output_particles(output, hydro.particle_list, hydro.materials,
			 boundary, Time);
	output_restart(output, hydro.particle_list, Time);
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
    return 0;
}
