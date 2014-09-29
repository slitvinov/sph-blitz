/// \file main.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief The main program
///
/// $Date: 2006-08-30 11:52:59 +0200 (Wed, 30 Aug 2006) $
/// $Revision: 3 $
// ***** local includes *****
#include "main.h"
#include <ctime>
#include <boost/program_options.hpp>
//#include "glbcls.h"

using namespace std;
namespace po = boost::program_options;

//-----------------------------------------------------------------------
//					Basic global physical values
//-----------------------------------------------------------------------
///Bltzmann constant
/// will be non-dimensionalized in the program
//double k_bltz  = 1.380662e-023; //[J/K]

/// \brief The main program
///
/// Starts the initialization methods and contains the main computation loop. <BR>
/// 
/// Initiation::Initiation <BR>
/// ParticleManager::ParticleManager <BR>
/// 
/// 
/// \param argc The number of command line arguments, should be two
/// \param argv The command line arguments array, should be the project name at index 1
int main(int argc, char *argv[]) {

  ///read the options 
  po::options_description desc("Allowed options");

  desc.add_options()
    ("help,h", "produce help message")
    ("pconf", po::value<string>(), "get the name of polymer configuration file")
    ("input-file", po::value<string>(), "input file")
    ;
  
  
  po::positional_options_description pd; 
  pd.add("input-file", 1);

  po::variables_map vm;
   po::store(po::command_line_parser(argc, argv)
	     .options(desc)
	     .positional(pd).run(), 
	     vm);
  po::notify(vm);
  
  if (vm.count("help")) {
    cout << desc << "\n";
    return EXIT_SUCCESS;
  }

  //  time_t bm_start_time = time(NULL);
  //computation time
  double Time;
  
  string project_name;
  if (vm.count("input-file")) {
    project_name = vm["input-file"].as<string>();
  }
  else {
    cerr << "The project file name should be given" << endl;
    return 1;
  }
  

  Initiation* ini;

  AbsPolymerCreator* apc;
  if (vm.count("pconf")) {
    string polymerconf(vm["pconf"].as<string>());
    ini = Initiation::Instance(project_name, polymerconf);
    apc = new SimplePolymerCreator(polymerconf);

  }
  else {
    ini = Initiation::Instance(project_name);
    apc = new SimplePolymerCreator();
  }


  ini->addPolymerCreator(apc);
  Node sample(new Particle(ini));
  InteractionState(new Interaction(ini));
  
  QuinticSpline weight_function(ini->smoothinglength); //initiate the weight function
  MLS mls(ini); //initiate the Moving Least Squares approximation
  ParticleManager particles(ini); //initiate the particle manager
  Hydrodynamics hydro(particles, ini); //create materials, forces and real particles
  Boundary boundary(ini, hydro, particles); //initiate boundary conditions and boundary particles
        
  TimeSolver timesolver(ini); //initialize the time solver
  
  ///create a new datastream
  OutputStream* datast = OutputStream::Instance();
  timesolver.Attach(datast);


  ///add data collector to the ini object
  
//   datast->AddTimeStepAttribute("a", co);
//   datast->NewTimeStep();
  
  CompositeDataCollector* dc = new CompositeDataCollector;  
  dc->Add(datast);
  dc->Add(new SimpleDataCollector(datast));
  dc->Add(new TorRgDataCollector(datast));
  //  dc->Add(new NewRgDataCollector(datast));
  dc->Add(new RgDataCollector(datast));
  //  dc->Add(new PolymerDataCollector(datast));
  //   dc->Add(new MassDataCollector(datast));

  ini->addDataCollector(dc);

  Output output(ini); //output class should be the last one being initialized
  ini->VolumeMass(hydro, particles, weight_function); //predict particle volume and mass
  boundary.BoundaryCondition(particles); //repose the boundary condition
  Diagnose diagnose(ini, hydro); //initialize the diagnose applications
  //start time
  Time = ini->Start_time;

  ///initialize the outputstream 
  datast->Initialize();

  //output initial 
  if (ini->initial_condition == 0) {
    hydro.BuildPair(particles, weight_function);
    output.OutputParticles(hydro, boundary, Time, ini); //particle positions and velocites
    timesolver.Notify(Time);
  }
  ///output.OutputInteractions(hydro, Time); //interactions
  //   output.OutputStates(particles, mls, weight_function, Time, ini); //initial states on uniform grid
  //   output.CreatParticleMovie(); //the particle moive file head
  //   output.WriteParticleMovie(hydro, Time, ini); //the first frame of the movie
  //output diagnose information
  if(ini->diagnose == 2 ) diagnose.KineticInformation(Time, ini, hydro);
  //computation starts

  //set the machine random seed
  srand( (unsigned)time( NULL ) );

  Timer wallTimer;

  ///zero time
//   output.OutputParticles(hydro, boundary, 
// 			 Time, ini); 
//   timesolver.Notify(Time);

  while ((Time < ini->End_time) && (!wallTimer.isEnd())) {
    // adjust the last D_time
    if(Time + ini->D_time >=  ini->End_time) ini->D_time = ini->End_time - Time; 
    
    
    timesolver.TimeIntegral_summation(hydro, particles, boundary, Time, 
				      ini->D_time, diagnose, 
				      ini, weight_function, mls);
    output.OutputParticles(hydro, boundary, 
			   Time, ini); 
    timesolver.Notify(Time);

    if(ini->diagnose == 1) {
      diagnose.OutputProfile(Time, ini);
      diagnose.OutputAverage(Time, ini);	
    }
  }  
  delete datast;
#ifndef NOLOG
  LOG4CXX_DEBUG(rootLogger, "Execution time: " +
		stringify<long int>(time(NULL) - bm_start_time) + 
		" second");
  LOG4CXX_DEBUG(rootLogger, "Exiting program");
#endif
  return 0; //end the program
}
