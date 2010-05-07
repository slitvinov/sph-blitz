/// \file main.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief The main program
///
/// Starts the initialization methods and contains the main computation loop


/*! \mainpage Smoothed-particle hydrodynamics (SPH) code 
 *
 * \section intro_sec Introduction
 *
 * SPH and SDPD 2D code 
 *
 * \section install_sec Installation
 * Check the source code from github and compile 
 * \verbatim 
   git clone git://github.com/slitvinov/sph-blitz
   cd sph-blitz
   ./local-install.sh  \endverbatim
 * To generate documentation in html format
 * \verbatim
   cd src
   doxygen
 * \endverbatim 
 *
 * \section restart_file Restart file format 
 * 
 * \section input_file Input file format 
 * 
 * \section sim Runnig simulations
 * \verbatim
   cd src
   ./sph ../cases/couette \endverbatim 
 * \section post Postprocessing
 * To combine all time snapshots in one file
 \verbatim 
   cd outdata/
   ../../scripts/dat2punto.sh > punto.dat
 \endverbatim
 * 
 * \section vis Visuzalization 
 * 
 * \subsection vis_gnuplot gnuplot
 * \image html pognuplot.png "Poiseuille flow: velocites of the particles visualization with gnuplot"
 *
 * \subsection vis_punto punto 

 * \verbatim
    punto -D 2 -c 4 -B 0:0:0.04:0.04 -G -0.6:0.6 -s 8 -lc black -bg white  punto.dat \endverbatim
 * \image html couette.png "Couette flow: particle visualization with punto"
 * \image html poiseuille.png "Poiseuille flow: particle visualization with punto"
 *
 *  
 */



#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

// ***** local includes *****
#include "glbfunc.h"
#include "glbcls.h"

using namespace std;

//-----------------------------------------------------------------------
//					Basic global physical values
//-----------------------------------------------------------------------
///Bltzmann constant, will be non-dimensionalized in the program
double k_bltz  = 1.380662e-023; //[J/K]


/// \brief The main program
///
/// Starts the initialization methods and contains the main computation loop
/// \param argc The number of command line arguments, should be two
/// \param argv The command line arguments array, should be the project name at index 1

int main(int argc, char *argv[]) {

	time_t bm_start_time = time(NULL);

	//computation time
	double Time;

	//check if project name specified
	if (argc<2)  {
		cout<<"No Project Name Specified!!\n";
		std::cout << __FILE__ << ':' << __LINE__ << std::endl;
		exit(1);
    }
	
	//initializatioinins
	Initiation ini(argv[1]); //global initialization

	//a sample particle and interaction for static numbers
	Particle sample(ini);
	Interaction interaction(ini);

	QuinticSpline weight_function(ini.smoothinglength); //initiate the weight function
	MLS mls(ini); //initiate the Moving Least Squares approximation
	ParticleManager particles(ini); //initiate the particle manager
	Hydrodynamics hydro(particles, ini); //create materials, forces and real particles
	Boundary boundary(ini, hydro, particles); //initiate boundary conditions and boundary particles
	TimeSolver timesolver(ini); //initialize the time solver
	Output output(ini); //output class should be the last one being initialized
	ini.VolumeMass(hydro, particles, weight_function); //predict particle volume and mass
	boundary.BoundaryCondition(particles); //repose the boundary condition
	Diagnose diagnose(ini, hydro); //initialize the diagnose applications

	//start time
	Time = ini.Start_time;

	//output initial conditions
	output.OutputParticles(hydro, boundary, Time, ini); //particle positions and velocites
	output.OutputStates(particles, mls, weight_function, Time, ini); //initial states on uniform grid
	output.CreatParticleMovie(); //the particle moive file head
	output.WriteParticleMovie(hydro, Time, ini); //the first frame of the movie
	//output diagnose information
	if(ini.diagnose == 2 ) diagnose.KineticInformation(Time, ini, hydro);

	//computation starts
	while(Time < ini.End_time) {
		
		// adjust the last D_time
		if(Time + ini.D_time >=  ini.End_time) ini.D_time = ini.End_time - Time; 
		
		//set the machine random seed
		srand( (unsigned)time( NULL ) );
		
		//call the time slover
//		timesolver.TimeIntegral(hydro, particles, boundary, Time, 
//			ini.D_time, diagnose, ini, weight_function, mls);
		timesolver.TimeIntegral_summation(hydro, particles, boundary, Time, 
			ini.D_time, diagnose, ini, weight_function, mls);
		
		//output results after a time interval
		output.OutputParticles(hydro, boundary, Time, ini); //particle positions and velocites
//		output.OutputStates(particles, mls, weight_function, Time, ini); //states on uniform grid
//		output.OutAverage(particles, mls, weight_function, Time, ini);
		output.WriteParticleMovie(hydro, Time, ini); //a frame of the particle movie
		output.OutRestart(hydro, Time, ini); //restarting file

		//output diagnose information
		if(ini.diagnose == 1) {
			diagnose.OutputProfile(Time, ini);
			diagnose.OutputAverage(Time, ini);	
		}
	}

	cout << time(NULL) - bm_start_time << " seconds.\n";

	return 0; //end the program
}
