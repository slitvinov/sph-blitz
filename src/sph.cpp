/// \file sph.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
#include <glog/logging.h>
#include <boost/smart_ptr/make_shared.hpp>

// main page for doxygen is in a separate file
#include "main.doxygen"

// ***** local includes *****
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "TimeSolver/gastimesolverLeapFrog.h"
#include "TimeSolver/gastimesolverPredCorr.h"
#include "TimeSolver/hydrotimesolver.h"
#include "vec2d.h"
#include "interaction.h"
#include "initiation.h"
#include "output.h"
#include "boundary.h"
#include "Kernel/quinticspline.h"
#include "Kernel/cubicspline.h"
#include "Kernel/cubicspline1D.h"
#include "Kernel/betaspline.h"

//using namespace std;

///
/// \brief The main program
///
/// Starts the initialization methods and contains the main computation loop
/// \param argc The number of command line arguments, should be two: program name (by default) and project name
/// \param argv The command line arguments array: by default program name at first position (index 0), and then the project( which is specified when calling the program name (e.g. s./sph ../cases/couette) at index 1
int main(int argc, char *argv[]) {
  //the following line of comment is for doxygen only
  ///\n <b>below  the rough structure of the main function:</b> 

  /// inizialize google logger
  google::InitGoogleLogging(argv[0]);

  std::cerr << "Check files /tmp/sph.ERROR /tmp/seph.WARNING /tmp/sph.INFO for the last log messages\n"  
            << "Use ==tail -f /tmp/sph.INFO== to follow the output\n" 
            << "To print log mesags to the stderr use \n"  
            << "==GLOG_logtostderr=1 ./sph <project name>==\n";

  LOG(INFO) << "sph program starts";
 
  //check if project name specified
  if (argc<2)  {
    LOG(INFO) << " No Project Name Specified!!\n";
    exit(EXIT_FAILURE);
  }

 
  /// initializations
  const std::string aux_string  = std::string(argv[1]);
  std::string aux_string2 = std::string();

  ///if second input parameter exists, write it in auxiliary varaible
  if (argc==3)  {
    //call compressible initiation constructor
     aux_string2  = argv[2];
  }
  if (argc>3)
    {
      LOG(INFO) << "too many input parameters to main function specified!";
      exit(EXIT_FAILURE);
    };
  ///- global initialization 
  /// (by defining an object of class Initiation (initialization "automatically" done at this moment (from .tcl or .rst file) by constructor method of Initiation class. 
  /// That is by the way the reason why the initiation::initiation method does not figure in the call graph of the main function (constructors are not shwon there)
  Initiation ini(aux_string, aux_string2);


//for gas dynamics (simu_mode=2) check if second input parameter to main (initial condition file .ivs) exists
   if (argc<3 && ini.simu_mode==2)  {
    LOG(INFO) << " No Initiation File Specified (program runs in gas dynamics mode)!!\n";
    exit(EXIT_FAILURE);
  }

  /// choose a kernel
  spKernel weight_function;
  if  (ini.kernel_type == "CubicSpline")   {
      weight_function = boost::make_shared<CubicSpline>(ini.supportlength); 
  } 
  else if (ini.kernel_type == "BetaSpline")   {
      weight_function = boost::make_shared<BetaSpline>(ini.supportlength); 
  } 
  else if (ini.kernel_type == "QuinticSpline")   {
      weight_function = boost::make_shared<QuinticSpline>(ini.supportlength);
  } 
  else if (ini.kernel_type == "CubicSpline1D")   {
      weight_function = boost::make_shared<CubicSpline1D>(ini.supportlength);
  }
 else {
   LOG(ERROR) << " unknown kernel type (KERNEL_TYPE in configuration file)\n" 
	      << " KERNEL_TYPE: " << ini.kernel_type;
   exit(EXIT_FAILURE);
 }

  assert(weight_function != NULL);
  weight_function->show_information();


  ParticleManager particles(ini); ///< - initiate the particle manager
  Hydrodynamics hydro(particles, ini); ///< - create materials, forces and real particles

  //define variable which indicates if the particle distribution for 1D simulation is purely 1D (where no bounady conditions are needed) or 2D (need to implement periodic BC in y-direction) 
  ///\todo{this is only a temporary solution, when code works, the variable can either be moved into external initiation file, or the purely 1D case can be  removed completely (but not as long as the 2D particle distribution does not work!!!)} 
  //0 means: no BC (for 1D particle distribution)
  //1 means: with BC (for 2D particle distribution)
  // int boundCond=0;
  // if (boundCond!=0) 
  //--> does not work, as instance of boundary class is needed for many methods...
    Boundary boundary(ini, particles); ///< - initiate boundary conditions and boundary particles
  
  /// a smart pointer to timesolver
  spTimeSolver timesolver;
  switch (ini.simu_mode) 
  {
    case 1: 
      /// call a HydroTimeSolver constructor and get a shared_ptr 
      timesolver = boost::make_shared<HydroTimeSolver>();
      break;
    case 2:
       switch (ini.integration_scheme)
       {
         case 1: 
	   /// call a GasTimeSolverLeapFrog constructor and get a shared_ptr 
	   timesolver = boost::make_shared<GasTimeSolverLeapFrog>();
	   break;
         case 2:
	   /// call a GasTimeSolverPredCorr constructor and get a shared_ptr 
	   timesolver = boost::make_shared<GasTimeSolverPredCorr>();
	   break;
         default:
	  std::cerr << __FILE__ << ':' << __LINE__ << " unknown time solver scheme, must be 1: leap frog, or 2: Predictor Corrector (INTEGRATION_SCHEME parameter in configuration file)\n" ;
	  exit(EXIT_FAILURE);
       }
       break;
      default:
      std::cerr << __FILE__ << ':' << __LINE__ << " unknown simulation mode (SIMULATION_MODE in configuration file)\n" ;
      exit(EXIT_FAILURE);
  }
  /// make sure the pointer is created
  assert(timesolver != NULL);
  timesolver->show_information();

  //BuildBoundaryParticle moved here from boundary constructor in order to be able to switch it of for the 1D case
  if  (ini.kernel_type != "CubicSpline1D")
    boundary.BuildBoundaryParticle(particles, hydro);

  Output output; ///- initialize output class (should be the last to be initialized)
  ini.VolumeMass(hydro, particles, weight_function); //predict particle volume and mass

  //for 2D particle distribution BC is needed
  ///\todo{define a variable which controls the use of boundary conditions and solve it smarter than just testing  if  (ini.kernel_type != "CubicSpline1D") }
  if  (ini.kernel_type != "CubicSpline1D")
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
    srand( static_cast<unsigned int>(time( NULL ) ));
		
    //control output
    LOG(INFO)<< "new output intervall begins:output interval time:" << ini.D_time;
		  
    ///- call the time slover (who iterates over one output time interval)
    if(ini.density_mode==1)  //summation density
      timesolver->TimeIntegral_summation(hydro, particles, boundary, Time, 
				      ini.D_time, ini, weight_function);
    else//continuity density (density integrated)
      timesolver->TimeIntegral(hydro, particles, boundary, Time, 
				      ini.D_time, ini, weight_function);
		
    // hydro.UpdateState(ini);///to update p,T,Cs to new values before output 
    //control output
    LOG(INFO)<<"time is "<<Time<<"\n";
    ///- output results after a time interval\n\n
    output.OutputParticle(hydro, boundary, Time, ini); //particle positions and velocites
    output.OutRestart(hydro, Time, ini); //restarting file
  }

  LOG(INFO) << "sph program successfully ends";
  return EXIT_SUCCESS; //end the program
}
