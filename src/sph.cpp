#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "timesolver.h"
#include "dllist.h"
#include "mls.h"
#include "diagnose.h"
#include "output.h"
#include "quinticspline.h"
#include "initiation.h"
#include "particle.h"
#include "interaction.h"
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "volume.h"
#include "wiener.h"

extern double interaction_art_vis;
extern double interaction_delta;

extern long particle_ID_max;
extern int particle_number_of_materials;

using namespace std;
int main(int argc, char *argv[]) {
    double Time;
    Initiation ini;
    QuinticSpline weight_function;

    if (argc<2)  {
	std::cout<<"No Project Name Specified!!\n";
	std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	exit(1);
    }
	
    wiener_seed(12345);
    initiation_ini(argv[1], &ini);
    interaction_art_vis = ini.art_vis;
    interaction_delta = ini.delta;

    particle_number_of_materials = ini.number_of_materials;
    particle_ID_max = 0;

    quinticspline_ini(ini.smoothinglength, &weight_function);
    MLS mls(ini.MLS_MAX); ///- initiate the Moving Least Squares approximation
    ParticleManager particles(ini);
    Hydrodynamics hydro(particles, ini); ///- create materials, forces and real particles
    particles.BuildRealParticles(hydro, ini);
    Boundary boundary(ini, hydro, particles);
    TimeSolver timesolver(ini);
    Output output(ini);
    VolumeMass(hydro, particles, weight_function); //predict particle volume and mass
    boundary.BoundaryCondition(particles); //repose the boundary condition
    Diagnose diagnose(ini, hydro);

    Time = ini.Start_time;
    output.OutputParticles(hydro, boundary, Time);
    output.OutputStates(particles, mls, weight_function, Time);
    if(ini.diagnose == 2)
      diagnose.KineticInformation(Time, hydro);

    while(Time < ini.End_time) {
	if(Time + ini.D_time >=  ini.End_time) ini.D_time = ini.End_time - Time;
	timesolver.TimeIntegral_summation(hydro, particles, boundary, Time,
					  ini.D_time, diagnose, ini, weight_function, mls);
	output.OutputParticles(hydro, boundary, Time);
	output.OutRestart(hydro, Time);
	if(ini.diagnose == 1) {
	    diagnose.OutputProfile(Time);
	    diagnose.OutputAverage(Time);
	}
    }
    return 0;
}
