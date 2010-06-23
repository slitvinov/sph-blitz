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
#include "glbcls.h"
#include "glbfunc.h"
#include "Kernel/kernel.h"

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Initiation::Initiation(const char *project_name) {
	
	char Key_word[25];

	//the project name
	strcpy(Project_name, project_name);

	//the input file name
	strcpy(inputfile, Project_name);
	strcat(inputfile, ".cfg");
	
	///<ul><li>check if inputfile exists (if not exit the program)
	ifstream fin(inputfile, ios::in);
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
		if(!strcmp(Key_word, "SIMULATION_MODE")) fin>>simu_mode;

		//comparing the key words for initial condition input
		//0: Initialize the initial conditions from .cfg file
		//1: restart from a .rst file
		if(!strcmp(Key_word, "INITIAL_CONDITION")) fin>>initial_condition;

		//output diagnose information
		if(!strcmp(Key_word, "DIAGNOSE")) fin>>diagnose;

		//comparing the key words for domian size
		if(!strcmp(Key_word, "CELLS")) fin>>x_cells>>y_cells;

		//comparing the key words for cell size
		if(!strcmp(Key_word, "CELL_SIZE")) fin>>cell_size;

		//comparing the key words for supportlength
		if(!strcmp(Key_word, "SUPPORT_LENGTH")) fin>>supportlength;

		//comparing the key words for the ratio between cell size and initial particle width
		if(!strcmp(Key_word, "CELL_RATIO")) fin>>hdelta;

		//comparing the key words for the g force
		if(!strcmp(Key_word, "G_FORCE")) fin>>g_force[0]>>g_force[1];
 
		//comparing the key words for the artificial viscosity
		if(!strcmp(Key_word, "ARTIFICIAL_VISCOSITY")) fin>>art_vis;

		//comparing the key words for dimension
		if(!strcmp(Key_word, "DIMENSION")) fin>>_length>>_v>>_rho>>_T;
		
		//comparing the key words for number ofmaterials
		if(!strcmp(Key_word, "NUMBER_OF_MATERIALS")) fin>>number_of_materials;

		//comparing the key words for timing
		if(!strcmp(Key_word, "TIMING")) fin>>Start_time>>End_time>>D_time;

		//Premitted max particle number for MLS approximation
		if(!strcmp(Key_word, "MLS_MAX")) fin>>MLS_MAX;

		//Initialize the initial conditions from .cfg file
		if (initial_condition==0) {
			//comparing the key words for the initial state
			if(!strcmp(Key_word, "INITIAL_STATES")) fin>>U0[0]>>U0[1]>>rho0>>p0>>T0;
		}

	}
	fin.close();

	///<li>create outdata directory
	system("mkdir -p outdata");
	
	///<li>process the data <b>!!!Question!!!</b>
	box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
	delta = cell_size/hdelta;///(line 104) this is only true if h=cell_size (which is not necessarily given, as h, cell_size can be initiated independently in configuration file)
	
	///<li>output information to screen
	show_information();

	///<li>non-dimensionalize \n\n
	non_dimensionalize();

}
//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information()
{
	///- output general information on screen
  cout<<"The simulation mode is"<<simu_mode<<"! (1=liquids, 2=gas dynamics)\n";
	cout<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
	cout<<"The computational domain size is  "<<box_size[0]<<" micrometers x "<<box_size[1]<<" micrometers\n";
	cout<<"The cell size is "<<cell_size<<" micrometers \n";
	cout<<"The smoothing length is "<<supportlength<<" micrometers \n";
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
		cout<<"Read the initial conditions from separated restat file "<<Project_name<<".rst \n";
}
//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, Kernel &weight_function)
{

  ///mass initiation is different of 1DSPH code: 
  ///here: mass is calculated by summing up the kernel function contributions for easch particle, which gives a kind of the inverse volume taken by each particle (not perfectly true at the discontinuity). together with rho (from initialization) a mass for each particle can be obtained.
  ///within the discontinuity zone, this mass varies because of the smoothing effect of the kernel summation.
  ///The mass for each particle  stays constant during the simuation.

	double reciprocV; //the inverse of volume 
	double dstc;
	Vec2d eij, sumdw;

	/// <ul><li>iterate particles on the particle list
	for (LlistNode<Particle> *p = hydro.particle_list.first(); 
		!hydro.particle_list.isEnd(p); 
		p = hydro.particle_list.next(p)) {
					
			/// <ul><li> pick an origin particle
			Particle *prtl_org = hydro.particle_list.retrieve(p);
			/// <li> build the nearest neighbor particle list for chosen origin particle
			particles.BuildNNP(prtl_org->R);

			reciprocV = 0.0; sumdw = 0.0;
			/// <li>iterate this Nearest Neighbor Particle list
			for (LlistNode<Particle> *p1 = particles.NNP_list.first(); 
			!particles.NNP_list.isEnd(p1); 
			p1 = particles.NNP_list.next(p1)) {
			
				/// <ul><li> get a particle
				Particle *prtl_dest = particles.NNP_list.retrieve(p1);
				
				/// <li> calculate distance (origin<-> neighbor)
				dstc = v_distance(prtl_org->R, prtl_dest->R);
				eij = (prtl_org->R - prtl_dest->R)/(dstc + 1.e-30);
				/// <li> calculate weight function for given distance (w=0, if dist>supportlengtg) an summ it up </ul> 
				reciprocV += weight_function.w(dstc);
				sumdw = sumdw + eij*weight_function.F(dstc);
			}
			/// <li> calculate volume as reciprocal value of weight function
			reciprocV = 1.0/reciprocV;

			/// <li> save volume and mass in the respective particle list node (whih is each a Particle object with all the particle properties) 
			prtl_org->V = reciprocV;
			prtl_org->m = prtl_org->rho*reciprocV;
			std::cerr<<" \n rho:  "<<prtl_org->rho;
			std::cerr<<" \n mass:  "<<prtl_org->m;
			/// <li> clear the NNP_list</ul> </ul>
			particles.NNP_list.clear();
	}
	cout<<"\n Volume and Mass successfully calculated\n ";
}
//----------------------------------------------------------------------------------------
//				Non-dimensionalize the initial condition and parameters
//----------------------------------------------------------------------------------------
void Initiation::non_dimensionalize()
{
        ///method calls the individual non_dms_methods vor each variable\n
        ///remark:to avoid confusion: the non dimensional variables have the same identifiers like the dimensional ones!!!\n\n
	box_size = non_dms_box_size(box_size);
	cell_size = non_dms_length(cell_size);
	supportlength = non_dms_length(supportlength);
	delta = non_dms_length(delta); 
	g_force = non_dms_acceleration(g_force);
	Start_time = non_dms_time(Start_time);
	End_time = non_dms_time(End_time);
	D_time = non_dms_time(D_time);

	//Bltzmann constant
	extern double k_bltz;
	k_bltz = non_dms_Boltzmann(k_bltz);
	
	//non-dimensionalize initial states
	if(initial_condition==0) {

		U0 = non_dms_velocity(U0);
		rho0 = non_dms_rho(rho0);
		p0 = non_dms_p(p0);
		T0 = non_dms_T(T0);
	}
}
//-------------------------------------------------------
//			Non_dimensionalize pressure
//-------------------------------------------------------
double Initiation::non_dms_p(double p)
{
	return p/_v/_v/_rho;
}
//-------------------------------------------------------
//			Non_dimensionalize temperature
//-------------------------------------------------------
double Initiation::non_dms_T(double T)
{
	return T/_T;
}
//-------------------------------------------------------
//			Non_dimensionalize density
//-------------------------------------------------------
double Initiation::non_dms_rho(double rho)
{
	return rho/_rho;
}
//-------------------------------------------------------
//			Non_dimensionalize mass
//			in 2-dimension 
//-------------------------------------------------------
double Initiation::non_dms_mass(double mass)
{
	return mass/_rho/_length/_length/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize time
//-------------------------------------------------------
double Initiation::non_dms_time(double time)
{
	return time*_v/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize length
//-------------------------------------------------------
double Initiation::non_dms_length(double length)
{
	return length/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize boxsize in 2-d
//-------------------------------------------------------
Vec2d Initiation::non_dms_box_size(Vec2d box_size)
{
	return box_size/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize velocity
//-------------------------------------------------------
double Initiation::non_dms_velocity(double velocity)
{
	return velocity/_v;
}
//-------------------------------------------------------
//			Non_dimensionalize vector velocity
//-------------------------------------------------------
Vec2d Initiation::non_dms_velocity(Vec2d velocity)
{
	return velocity/_v;
}
//-------------------------------------------------------
//			Non_dimensionalize acceleration vector
//-------------------------------------------------------
Vec2d Initiation::non_dms_acceleration(Vec2d acceleration)
{
	 return acceleration*_length/_v/_v;
}
//-------------------------------------------------------
//			Non_dimensionalize surface tension coefficient
//-------------------------------------------------------
double Initiation::non_dms_surface(double sigma)
{
	return sigma/_rho/_v/_v/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize viscosity
//-------------------------------------------------------
double Initiation::non_dms_viscosity(double mu)
{
	return mu/_v/_rho/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize kinetic viscosity
//-------------------------------------------------------
double Initiation::non_dms_kinetic_viscosity(double nu)
{
	return nu/_v/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize heat ratio
//-------------------------------------------------------
double Initiation::non_dms_heat_ratio(double cv)
{
	return cv*_T/_v/_v;

}
//-------------------------------------------------------
//			Non_dimensionalize heat conduction rate
//-------------------------------------------------------
double Initiation::non_dms_heat_conduction(double kappa)
{
	return kappa*_T/_v/_v/_v/_rho;
}
//-------------------------------------------------------
//			Non_dimensionalize Boltzmann constant
//-------------------------------------------------------
double Initiation::non_dms_Boltzmann(double k_bltz)
{
	return k_bltz*_T/_v/_v/_rho/_length/_length/_length;
}
//-------------------------------------------------------
//			Dimensionalize functions
//-------------------------------------------------------
double Initiation::dms_p(double p_non)
{
	return p_non*_v*_v*_rho;
}
//-------------------------------------------------------
double Initiation::dms_T(double T_non)
{
	return T_non*_T;
}
//-------------------------------------------------------
double Initiation::dms_rho(double rho_non)
{
	return rho_non*_rho;
}
//-------------------------------------------------------
double Initiation::dms_mass(double mass_non)
{
	return mass_non*_rho*_length*_length;
}
//-------------------------------------------------------
double Initiation::dms_time(double time_non)
{
	return time_non/_v*_length;
}
//-------------------------------------------------------
double Initiation::dms_length(double length_non)
{
	return length_non*_length;
}
//-------------------------------------------------------
Vec2d Initiation::dms_box_size(Vec2d box_size_non)
{
	return box_size_non*_length;
}
//-------------------------------------------------------
double Initiation::dms_velocity(double velocity_non)
{
	return velocity_non*_v;
}
//-------------------------------------------------------
Vec2d Initiation::dms_velocity(Vec2d velocity_non)
{
	return velocity_non*_v;
}
//-------------------------------------------------------
double Initiation::dms_energy(double energy_non)
{
	return energy_non*_v*_v;
}
//-------------------------------------------------------
Vec2d Initiation::dms_acceleration(Vec2d acceleration_non)
{
	 return acceleration_non*_v*_v/_length;
}
//-------------------------------------------------------
double Initiation::dms_viscosity(double mu_non)
{
	return mu_non*_v*_rho*_length;
}
//-------------------------------------------------------
