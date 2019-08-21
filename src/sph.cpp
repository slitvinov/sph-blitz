#include <cmath>
#include <iostream>

#include "vec2d.h"
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

using namespace std;
///
/// \brief The main program
///
/// Starts the initialization methods and contains the main computation loop
/// \param argc The number of command line arguments, should be two: program name (by default) and project name
/// \param argv The command line arguments array: by default program name at first position (index 0), and then the project( which is specified when calling the program name (e.g. s./sph ../cases/couette) at index 1
int main(int argc, char *argv[]) {
    //the following line of comment is for doxygen only
    ///\n <b>below  the rough structure of the main function:</b>
    //computation time
    double Time;
    Initiation ini;

    //check if project name specified
    if (argc<2)  {
	std::cout<<"No Project Name Specified!!\n";
	std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	exit(1);
    }
	
    wiener_seed(12345);
    /// initializations
    initiation_ini(argv[1], &ini);
    
    //a sample particle and interaction for static numbers
    Particle sample(ini);
    Interaction interaction(ini);

    QuinticSpline weight_function;
    quinticspline_ini(ini.smoothinglength, &weight_function);
    MLS mls(ini.MLS_MAX); ///- initiate the Moving Least Squares approximation
    ParticleManager particles(ini); ///- initiate the particle manager
    Hydrodynamics hydro(particles, ini); ///- create materials, forces and real particles
    Boundary boundary(ini, hydro, particles); ///- initiate boundary conditions and boundary particles
    TimeSolver timesolver(ini); ///- initialize the time solver
    Output output(ini); ///- initialize output class (should be the last to be initialized)
    VolumeMass(hydro, particles, weight_function); //predict particle volume and mass
    boundary.BoundaryCondition(particles); //repose the boundary condition
    Diagnose diagnose(ini, hydro); //initialize the diagnose applications

    //start time
    Time = ini.Start_time;

    //output initial conditions
    output.OutputParticles(hydro, boundary, Time); //particle positions and velocites
    output.OutputStates(particles, mls, weight_function, Time); //initial states on uniform grid
    //output diagnose information
    if(ini.diagnose == 2 ) diagnose.KineticInformation(Time, hydro);

    ///\n computation loop starts

    //set the machine random seed
    srand( (unsigned)time( NULL ) );
    while(Time < ini.End_time) {

	// adjust the last D_time(=output time) in a way that there is an output at last timestep
	if(Time + ini.D_time >=  ini.End_time) ini.D_time = ini.End_time - Time;

	///- call the time slover (who iterates over one output time interval)
	//		timesolver.TimeIntegral(hydro, particles, boundary, Time,
	//			ini.D_time, diagnose, ini, weight_function, mls);
	timesolver.TimeIntegral_summation(hydro, particles, boundary, Time,
					  ini.D_time, diagnose, ini, weight_function, mls);

	///- output results after a time interval\n\n
	output.OutputParticles(hydro, boundary, Time); //particle positions and velocites
	//		output.OutputStates(particles, mls, weight_function, Time, ini); //states on uniform grid
	//		output.OutAverage(particles, mls, weight_function, Time, ini);
	output.OutRestart(hydro, Time); //restarting file

	//output diagnose information
	if(ini.diagnose == 1) {
	    diagnose.OutputProfile(Time);
	    diagnose.OutputAverage(Time);
	}
    }
    return 0;
}
