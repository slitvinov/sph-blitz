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

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Initiation::Initiation(const std::string& project_name) {
	
  std::string  Key_word;

	//the project name
	Project_name = project_name;

	//the input file name
	inputfile = Project_name + ".cfg";
	
	///<ul><li>check if inputfile exists (if not exit the program)
	ifstream fin(inputfile.c_str(), ios::in);
	if (!fin) {
		cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
		std::cout << __FILE__ << ':' << __LINE__ << std::endl;
		exit(1);
	}
	else cout<<"Initialtion: Read the global configuration data from "<< inputfile <<" \n"; 

	///<li>reading key words and configuration data from configuration file and assign them to the appropriate variable
	while(!fin.eof()) {
		
		//read a string block
		fin>>Key_word;
		
		//comparing the key words for simulation mode
		//1: liquids
		//2: gas dynamics
		if(Key_word == "SIMULATION_MODE") fin>>simu_mode;

		//comparing the key words for initial condition input
		//0: Initialize the initial conditions from .cfg file
		//1: restart from a .rst file
		if(Key_word == "INITIAL_CONDITION") fin>>initial_condition;

		//comparing the key words for domian size
		if(Key_word == "CELLS") fin>>x_cells>>y_cells;

		//comparing the key words for cell size
		if(Key_word == "CELL_SIZE") fin>>cell_size;

		//comparing the key words for supportlength
		if(Key_word == "SUPPORT_LENGTH") fin>>supportlength;

		//comparing the key words for the ratio between cell size and initial particle width
		if(Key_word == "CELL_RATIO") fin>>hdelta;

		//comparing the key words for the g force
		if(Key_word == "G_FORCE") fin>>g_force[0]>>g_force[1];
 
		//comparing the key words for the artificial viscosity
		if(Key_word == "ARTIFICIAL_VISCOSITY") fin>>art_vis;

		//comparing the key words for dimension
		if(Key_word == "DIMENSION") fin>>_length>>_v>>_rho>>_T;
		
		//comparing the key words for number ofmaterials
		if(Key_word == "NUMBER_OF_MATERIALS") fin>>number_of_materials;

		//comparing the key words for timing
		if(Key_word == "TIMING") fin>>Start_time>>End_time>>D_time;

		//Initialize the initial conditions from .cfg file
		if (initial_condition==0) {
			//comparing the key words for the initial state
			if(Key_word == "INITIAL_STATES") fin>>U0[0]>>U0[1]>>rho0>>p0>>T0;
		}

	}
	fin.close();

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
  cout<<"The dimensionless reference length, speed, density and temperature are \n"
      <<_length<<" micrometer, "<<_v<<" m/s, "<<_rho<<" kg/m^3, "<<_T<<" K\n";

	///- output the timing information on screen
  cout<<"\nInitialtion: Time controlling:\nStarting time is "<<Start_time<<" \n";
  cout<<"Ending time is "<<End_time<<" \n";
  cout<<"Output time interval is "<<D_time<<" \n";

  ///- output iniformation on initialization mode (.cfg file or .rst file)
  //Initialize the initial conditions from .cfg file
  if (initial_condition==0) {
    cout<<"\nInitialize the initial conditions from "<<inputfile<<" \n";
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
			    Kernel &weight_function)
{
  ///mass initiation is different of 1DSPH code: 
  ///here: mass is calculated by summing up the kernel function contributions for easch particle, which gives a kind of the inverse volume taken by each particle (not perfectly true at the discontinuity). together with rho (from initialization) a mass for each particle can be obtained.
  ///within the discontinuity zone, this mass varies because of the smoothing effect of the kernel summation.
  ///The mass for each particle  stays constant during the simuation.

  /// <ul><li>iterate particles on the particle list
  for (std::list<spParticle >::iterator p = hydro.particle_list.begin(); 
       p != hydro.particle_list.end(); 
       p++) {
					
    /// <ul><li> pick an origin particle
    spParticle prtl_org = *p;
    /// <li> build the nearest neighbor particle list for chosen origin particle
    assert(prtl_org != NULL);
    const std::list<spParticle> NNP_list = particles.BuildNNP(prtl_org->R);

    /// size of the list can be zero in some circumstances
    /// but in 1D (2D) shock it is not expected
    assert(NNP_list.size() > 0);

    double reciprocV = 0.0; 
    /// <li>iterate this Nearest Neighbor spParticle list
    for (std::list<spParticle >::const_iterator p1 = NNP_list.begin(); 
	 p1 != NNP_list.end(); 
	 p1++) {
			
      /// <ul><li> get a particle
      spParticle prtl_dest = *p1;

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
