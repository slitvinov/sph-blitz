/// \file initiation.cpp
/// \author author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      initialize the progam
//		initiation.cpp
//----------------------------------------------------------------------------------------
#include <fstream>
#include <glog/logging.h>
#include <boost/foreach.hpp>

// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "Kernel/kernel.h"
#include "initiation.h"

//using namespace std;


//----------------------------------------------------------------------------------------
//							constructor 
//----------------------------------------------------------------------------------------
Initiation::Initiation(const std::string& project_name, const std::string& ivs_file_name) {
        LOG(INFO) << "Run constructor of Initiation class";

	//the project name
	Project_name = project_name;
	//the ivs file name
	Ivs_file_name=ivs_file_name;

	//the input file name
	const std::string inputfile = Project_name + ".tcl";
	std::ifstream tclfilename;
	tclfilename.open (inputfile.c_str());
	if (!tclfilename.is_open()) {
	  LOG(ERROR) << " cannot open project file: " << inputfile;
	  exit(EXIT_FAILURE);
	}

	interp.eval(tclfilename);
	///<li>reading key words and configuration data from configuration file and assign them to the appropriate variable

	initial_condition = interp.eval("[return $INITIAL_CONDITION]");
        assert( (initial_condition == 0) || (initial_condition == 1));
	simu_mode = interp.eval("[return $SIMULATION_MODE]");
	//	assert(simu_mode==1||simu_mode==2); (already tested in sph.cpp)
	density_mode = interp.eval("[return $DENSITY_MODE]");
	assert(density_mode == 1 || density_mode == 2);
	integration_scheme = interp.eval("[return $INTEGRATION_SCHEME]");//(already tested in sph.cpp)
        //assert(integration_scheme == 1 || integration_scheme == 2);

	kernel_type = static_cast<std::string>(interp.eval("[return $KERNEL_TYPE]"));

	/// if gas dynamics
	if (simu_mode == 2) {
	  /// read parameters of artificial viscosity 
	  alpha_artVis = interp.eval("[return $alpha_artVis]");
	  beta_artVis = interp.eval("[return $beta_artVis]");
	  epsilon_artVis = interp.eval("[return $epsilon_artVis]");
	} 
	x_cells = interp.eval ("[return $CELLS(0)]");
        assert(x_cells > 0);
	y_cells = interp.eval ("[return $CELLS(1)]");
        assert(y_cells > 0);

        cell_size = interp.eval("[return $CELL_SIZE]");
        assert(cell_size>0.0);

	supportlength = interp.eval("[return $SUPPORT_LENGTH]");
        assert(supportlength > 0.0);
        
	hdelta = interp.eval("[return $CELL_RATIO]");
        assert(hdelta > 0.0);

	g_force[0] = interp.eval ("[return $G_FORCE(0)]");
	g_force[1] = interp.eval ("[return $G_FORCE(1)]");

	number_of_materials = interp.eval("[return $NUMBER_OF_MATERIALS]");
        assert(number_of_materials > 0);
        
	Start_time = interp.eval("[return $Start_time]");
	End_time = interp.eval("[return $End_time]");
	D_time = interp.eval("[return $D_time]");
        // can be zero for debugging
        assert(D_time>0.0);
	assert(End_time >= Start_time);

	if (initial_condition == 0) {
	  rho0 = interp.eval("[return $rho0]");
	  p0 = interp.eval("[return $p0]");
	  T0 = interp.eval("[return $T0]");
	  U0[0] = interp.eval ("[return $U0(0)]");
	  U0[1] = interp.eval ("[return $U0(1)]");
	}

	///<li>create outdata directory
	const int sys_return = system("mkdir -p outdata");
	if (sys_return) {
	  LOG(ERROR) << "system command faild" << inputfile;
	  exit(EXIT_FAILURE);
	}
	
	///<li>process the data <b>!!!Question!!!</b>
	box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
	delta = cell_size/hdelta;///(line 104) this is only 
        /// true if h=cell_size (which is not necessarily given, as h, cell_size can be initiated independently in configuration file)
	
	///<li>output information to screen
	show_information();
        LOG(INFO) << "Initiation object is created";
}



//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information() const 
{
	///- output general information on screen
  LOG(INFO)<<"The simulation mode is"<<simu_mode<<"! (1=liquids, 2=gas dynamics)\n";
  LOG(INFO)<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
  LOG(INFO)<<"The computational domain size is  "<<box_size[0]<<" micrometers x "<<box_size[1]<<" micrometers\n";
  LOG(INFO)<<"The cell size is "<<cell_size<<" micrometers \n";
  LOG(INFO)<<"The support length is "<<supportlength<<" micrometers \n";
  LOG(INFO)<<"The cell matrix size is "<<x_cells<<" x "<<y_cells<<"\n";
  LOG(INFO)<<"The ratio between cell size and initial particle width is "<<hdelta<<"\n";
  LOG(INFO)<<"The initial particle width is "<<delta<<" micrometers\n";
  LOG(INFO)<<"The g force is "<<g_force[0]<<" m/s^2 x "<<g_force[1]<<" m/s^2 \n";
	///- output the timing information on screen
  LOG(INFO)<<"Ending time is "<<End_time<<" \n";
  LOG(INFO)<<"Output time interval is "<<D_time<<" \n";
  
  LOG(INFO)<<"initial_condition "<< initial_condition <<" \n";
  LOG(INFO)<<" simu_mode "<< simu_mode <<" \n";

  ///- output iniformation on initialization mode (.cfg file or .rst file)
  //Initialize the initial conditions from .cfg file
  if (initial_condition==0) {
    LOG(INFO)<<"The initial flow speed is "<<U0[0]<<" m/s x "<<U0[1]<<" m/s\n";
    LOG(INFO)<<"The initial density is "<<rho0<<" kg/m^3\n";
    LOG(INFO)<<"The initial pressure is "<<p0<<" Pa\n";
    LOG(INFO)<<"The initial temperature is "<<T0<<" K\n";
  }
	
  //Initialize the initial conditions from .rst file
  if (initial_condition == 1)
    LOG(INFO)<<"Read the initial conditions from separated restat file "
	<<Project_name<<".rst \n";
}

//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
			    spKernel weight_function)
{
  LOG(INFO)<<"Initiation::VolumeMass starts";
  ///mass initiation is different of 1DSPH code: 
  ///here: mass is calculated by summing up the kernel function contributions for easch particle, which gives a kind of the inverse volume taken by each particle (not perfectly true at the discontinuity). together with rho (from initialization) a mass for each particle can be obtained.
  ///within the discontinuity zone, this mass varies because of the smoothing effect of the kernel summation.
  ///The mass for each particle  stays constant during the simuation.

  /// <ul><li>iterate particles on the particle list
  BOOST_FOREACH(spParticle prtl_org, hydro.particle_list) {
    ///\todo{initialize particle mass via initiation file...}
    // prtl_org->m=0.001875;
    // /// <ul><li> pick an origin particle
    // assert(prtl_org != NULL);
    // const std::list<spParticle> NNP_list = particles.BuildNNP(prtl_org->R);

    // /// size of the list can be zero in some circumstances
    // /// but in 1D (2D) shock it is not expected
    // assert(NNP_list.size() > 0);
    // double reciprocV = 0.0; 
    // /// <li>iterate this Nearest Neighbor spParticle list
    // BOOST_FOREACH(const spParticle prtl_dest, NNP_list) {
    //   /// <li> calculate distance (origin<-> neighbor)
    // 	const double dstc = v_distance(prtl_org->R, prtl_dest->R);
    // 	/// <li> calculate weight function for given distance (w=0, if dist>supportlengtg) an summ it up </ul> 
    // 	reciprocV += weight_function->w(dstc);
    // }
    // /// <li> calculate volume as reciprocal value of weight function
    // reciprocV = 1.0/reciprocV;
    // /// <li> save volume and mass in the respective particle list node (whih is each a spParticle object with all the particle properties) 
    // prtl_org->V = reciprocV;
    // prtl_org->m = prtl_org->rho*reciprocV;
    LOG_EVERY_N(INFO, 100) <<std::setprecision(10)<< "prtl ID"<<prtl_org->ID<<"prtl m  = " << prtl_org->m;

  }
  LOG(INFO)<<"Initiation::VolumeMass ends";
}
