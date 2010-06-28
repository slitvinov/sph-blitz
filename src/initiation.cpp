/// \file initiation.cpp
/// \author author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      initialize the progam
//		initiation.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbfunc.h"
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "Kernel/kernel.h"
#include "initiation.h"
#include <boost/foreach.hpp>
using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Initiation::Initiation(const std::string& project_name) {
	
  std::string  Key_word;

	//the project name
	Project_name = project_name;

	//the input file name
	const std::string inputfile = Project_name + ".tcl";
	std::ifstream myfile;
	myfile.open (inputfile.c_str());

	interp.eval(myfile);
	///<li>reading key words and configuration data from configuration file and assign them to the appropriate variable

	initial_condition = interp.eval("[return $INITIAL_CONDITION]");
	simu_mode = interp.eval("[return $SIMULATION_MODE]");

	/// if gas dynamics
	if (simu_mode == 2) {
	  /// read parameters of artificial viscosity 
	  alpha_artVis = interp.eval("[return $alpha_artVis]");
	  beta_artVis = interp.eval("[return $beta_artVis]");
	  epsilon_artVis = interp.eval("[return $epsilon_artVis]");
	} 
	x_cells = interp.eval ("[return $CELLS(0)]");
	y_cells = interp.eval ("[return $CELLS(1)]");
	cell_size = interp.eval("[return $CELL_SIZE]");
	supportlength = interp.eval("[return $SUPPORT_LENGTH]");
	hdelta = interp.eval("[return $CELL_RATIO]");

	g_force[0] = interp.eval ("[return $G_FORCE(0)]");
	g_force[1] = interp.eval ("[return $G_FORCE(1)]");

	number_of_materials = interp.eval("[return $NUMBER_OF_MATERIALS]");
	Start_time = interp.eval("[return $Start_time]");
	End_time = interp.eval("[return $End_time]");
	D_time = interp.eval("[return $D_time]");

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
	  std::cerr<<"system command faild"<< inputfile <<" \n";
	  std::cerr << __FILE__ << ':' << __LINE__ << std::endl;
	  exit(EXIT_FAILURE);
	}
	
	///<li>process the data <b>!!!Question!!!</b>
	box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
	delta = cell_size/hdelta;///(line 104) this is only true if h=cell_size (which is not necessarily given, as h, cell_size can be initiated independently in configuration file)
	
	///<li>output information to screen
	show_information();
}
//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information() const 
{
	///- output general information on screen
  cout<<"The simulation mode is"<<simu_mode<<"! (1=liquids, 2=gas dynamics)\n";
  cout<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
  cout<<"The computational domain size is  "<<box_size[0]<<" micrometers x "<<box_size[1]<<" micrometers\n";
  cout<<"The cell size is "<<cell_size<<" micrometers \n";
  cout<<"The support length is "<<supportlength<<" micrometers \n";
  cout<<"The cell matrix size is "<<x_cells<<" x "<<y_cells<<"\n";
  cout<<"The ratio between cell size and initial particle width is "<<hdelta<<"\n";
  cout<<"The initial particle width is "<<delta<<" micrometers\n";
  cout<<"The g force is "<<g_force[0]<<" m/s^2 x "<<g_force[1]<<" m/s^2 \n";

	///- output the timing information on screen
  cout<<"\nInitialtion: Time controlling:\nStarting time is "<<Start_time<<" \n";
  cout<<"Ending time is "<<End_time<<" \n";
  cout<<"Output time interval is "<<D_time<<" \n";

  ///- output iniformation on initialization mode (.cfg file or .rst file)
  //Initialize the initial conditions from .cfg file
  if (initial_condition==0) {
    cout<<"The initial flow speed is "<<U0[0]<<" m/s x "<<U0[1]<<" m/s\n";
    cout<<"The initial density is "<<rho0<<" kg/m^3\n";
    cout<<"The initial pressure is "<<p0<<" Pa\n";
    cout<<"The initial temperature is "<<T0<<" K\n";
  }
	
  //Initialize the initial conditions from .rst file
  if (initial_condition == 1)
    cout<<"Read the initial conditions from separated restat file "
	<<Project_name<<".rst \n";
}

//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
			    const Kernel &weight_function)
{
  ///mass initiation is different of 1DSPH code: 
  ///here: mass is calculated by summing up the kernel function contributions for easch particle, which gives a kind of the inverse volume taken by each particle (not perfectly true at the discontinuity). together with rho (from initialization) a mass for each particle can be obtained.
  ///within the discontinuity zone, this mass varies because of the smoothing effect of the kernel summation.
  ///The mass for each particle  stays constant during the simuation.

  /// <ul><li>iterate particles on the particle list
  BOOST_FOREACH(spParticle prtl_org, hydro.particle_list) {
    /// <ul><li> pick an origin particle
    assert(prtl_org != NULL);
    const std::list<spParticle> NNP_list = particles.BuildNNP(prtl_org->R);

    /// size of the list can be zero in some circumstances
    /// but in 1D (2D) shock it is not expected
    assert(NNP_list.size() > 0);

    double reciprocV = 0.0; 
    /// <li>iterate this Nearest Neighbor spParticle list
    BOOST_FOREACH(const spParticle prtl_dest, NNP_list) {
      /// <li> calculate distance (origin<-> neighbor)
      if ( prtl_dest->ID != prtl_dest->ID) {
	const double dstc = v_distance(prtl_org->R, prtl_dest->R);
	assert(dstc>0.0);
	/// <li> calculate weight function for given distance (w=0, if dist>supportlengtg) an summ it up </ul> 
	reciprocV += weight_function.w(dstc);
      } else {
	/// particle with itself
	reciprocV += weight_function.w(0.0);
      }
    }
    /// <li> calculate volume as reciprocal value of weight function
    reciprocV = 1.0/reciprocV;
    /// <li> save volume and mass in the respective particle list node (whih is each a spParticle object with all the particle properties) 
    prtl_org->V = reciprocV;
    prtl_org->m = prtl_org->rho*reciprocV;
  }
  cout<<"\n Volume and Mass successfully calculated\n ";
}
