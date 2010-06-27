/// \file sph.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes



/*! \mainpage Smoothed-particle hydrodynamics (SPH) code 
 *
 * \section intro_sec Introduction
 *
 * SPH 2D code 
 *
 * \section install_sec Installation
 * Check the source code from github and compile 
 * \verbatim 
 git clone git://github.com/slitvinov/sph-blitz
 cd sph-blitz
 ./local-install.sh  \endverbatim
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
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "vec2d.h"
#include "interaction.h"
#include "timesolver.h"
#include "initiation.h"
#include "output.h"
#include "boundary.h"
#include "Kernel/quinticspline.h"
#include "Kernel/cubicspline.h"
#include "Kernel/betaspline.h"

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

  time_t bm_start_time = time(NULL);

  //check if project name specified
  if (argc<2)  {
    std::cout << __FILE__ << ':' << __LINE__ << 
      " No Project Name Specified!!\n";
    exit(EXIT_FAILURE);
  }
	
  /// initializations
  std::string aux_string  = std::string(argv[1]);
  Initiation ini(aux_string); ///- global initialization (by defining an object of class Initiation (initialization "automatically" done at this moment (from .cfg or .rst file) by constructor method of Initiation class. That is by the way the reason why the initiation::initiation method does not figure in the call graph of the main function (constructors are not shwon there)

  /// moved initiation of static members to here
  /// TODO: it should be a separate procedure but not 
  /// a constructor
  Particle::number_of_materials = ini.number_of_materials;

  Interaction::number_of_materials = ini.number_of_materials;
  Interaction::supportlength = ini.supportlength;
  Interaction::art_vis = ini.art_vis;
  Interaction::delta = ini.delta;
  Interaction::simu_mode = ini.simu_mode;
  Interaction::alpha_artVis=1.0;
  Interaction::beta_artVis=2.0;
  Interaction::epsilon_artVis=0.1;

  // Kernel
  /// here one can choose which Kernel function to use 
  //QuinticSpline weight_function (ini.supportlength); 
  // (not in runtime)
  CubicSpline weight_function (ini.supportlength); 

  ParticleManager particles(ini); ///- initiate the particle manager
  Hydrodynamics hydro(particles, ini); ///- create materials, forces and real particles
      
  Boundary boundary(ini, hydro, particles); ///- initiate boundary conditions and boundary particles
  TimeSolver timesolver(ini); ///- initialize the time solver
  Output output(ini); ///- initialize output class (should be the last to be initialized)
  ini.VolumeMass(hydro, particles, weight_function); //predict particle volume and mass
  if(ini.simu_mode==1)	
    boundary.BoundaryCondition(particles); //repose the boundary condition

  //start time
  double Time = ini.Start_time;

  //output initial conditions
  output.OutputParticle(hydro, boundary, Time, ini); //particle positions and velocites

  ///\n computation loop starts 
  while(Time < ini.End_time) {
		
    // adjust the last D_time(=output time) in a way that there is an output at last timestep
    if(Time + ini.D_time >=  ini.End_time) ini.D_time = ini.End_time - Time; 
		
    //set the machine random seed
    srand( (unsigned)time( NULL ) );
		

    //control output
    cout<<"\n--------new output intervall beginns:output interval time:"<<ini.D_time<<"\n";
		  
    ///- call the time slover (who iterates over one output time interval)
    timesolver.TimeIntegral_summation(hydro, particles, boundary, Time, 
				      ini.D_time, ini, weight_function);
		
    hydro.UpdateState(ini);///to update p,T,Cs to new values before output 
    //control output
    cout<<"\n time is"<<Time<<"\n";
    ///- output results after a time interval\n\n
    output.OutputParticle(hydro, boundary, Time, ini); //particle positions and velocites
    output.OutRestart(hydro, Time, ini); //restarting file
  }

  cout << time(NULL) - bm_start_time << " seconds.\n";

  cout << __FILE__ << ':' << __LINE__ << " program ends successfully\n" ;
  return EXIT_SUCCESS; //end the program
}
