// initiation.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

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

using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Initiation::Initiation(const char *project_name) {
	
	char Key_word[125];
	g_only = -1;
	tstep = -1;

	//the project name
	strcpy(Project_name, project_name);

	//the input file name
	strcpy(inputfile, Project_name);
	strcat(inputfile, ".cfg");
	
	//check if inputfile exist
	ifstream fin(inputfile, ios::in);
	if (!fin) {
		cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
		std::cout << __FILE__ << ':' << __LINE__ << std::endl;
		exit(1);
	}
	else cout<<"Initialtion: Read the global configuration data from "<< inputfile <<" \n"; 
	sim_special = 0;
        use_phase_transform = 0;

	//reading key words and configuration data
	while(!fin.eof()) {
		
		//read a string block
		fin>>Key_word;

		//is simulation special?
		if(!strcmp(Key_word, "SIM_SPECIAL")) fin>>sim_special;

		//is simulation special
		if(!strcmp(Key_word, "USE_PAHASE_TRANSFORM")) fin>>use_phase_transform;


		// a fraction of the domain in y direction where 
		// force is not applyed
		if(!strcmp(Key_word, "TUBE_NO_FORCE_REGION")) fin>> tube_no_force_region;
		
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

		//comparing the key words for smoothinglength
		if(!strcmp(Key_word, "SMOOTHING_LENGTH")) fin>>smoothinglength;

		//comparing the key words for the ratio between cell size and initial particle width
		if(!strcmp(Key_word, "CELL_RATIO")) fin>>hdelta;

		//comparing the key words for the g force
		if(!strcmp(Key_word, "G_FORCE")) fin>>g_force[0]>>g_force[1];
 
		//comparing the key words for the artificial viscosity
		if(!strcmp(Key_word, "ARTIFICIAL_VISCOSITY")) fin>>art_vis;

		//comparing the key words for number ofmaterials
		if(!strcmp(Key_word, "NUMBER_OF_MATERIALS")) fin>>number_of_materials;

		//comparing the key words for g only
		if(!strcmp(Key_word, "G_ONLY")) fin>>g_only;

		//comparing the key words for g only
		if(!strcmp(Key_word, "TSTEP")) fin>> tstep;

		//comparing the key words for timing
		if(!strcmp(Key_word, "TIMING")) fin>>Start_time>>End_time>>D_time;

		//Premitted max particle number for MLS approximation
		if(!strcmp(Key_word, "MLS_MAX")) fin>>MLS_MAX;

		//Initialize the initial conditions from .cfg file
		if (initial_condition==0) {
			//comparing the key words for the initial state
			if(!strcmp(Key_word, "INITIAL_STATES")) fin>>U0[0]>>U0[1]>>rho0>>p0>>energy0;
		}

	}
	fin.close();

	//create outdata directory
	system("mkdir -p outdata");
	
	//process the data
	box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
	delta = cell_size/hdelta;
	
	//output information to screen
	show_information();
}
//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information()
{
	//output information to screen
	cout<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
	cout<<"The computational domain size is  "<<box_size[0]<<" micrometers x "<<box_size[1]<<" micrometers\n";
	cout<<"The cell size is "<<cell_size<<" micrometers \n";
	cout<<"The smoothing length is "<<smoothinglength<<" micrometers \n";
	cout<<"The cell matrix size is "<<x_cells<<" x "<<y_cells<<"\n";
	cout<<"The ratio between cell size and initial particle width is "<<hdelta<<"\n";
	cout<<"The initial particle width is "<<delta<<" micrometers\n";
	cout<<"The g force is "<<g_force[0]<<" m/s^2 x "<<g_force[1]<<" m/s^2 \n";
	//output the timing on screen
	cout<<"\nInitialtion: Time controlling:\nStarting time is "<<Start_time<<" \n";
	cout<<"\nuse_phase_transform "<<use_phase_transform<<" \n";
	cout<<"Ending time is "<<End_time<<" \n";
	cout<<"Output time interval is "<<D_time<<" \n";

	
	//Initialize the initial conditions from .cfg file
	if (initial_condition==0) {
		cout<<"\nInitialize the initial conditions from "<<inputfile<<" \n";
		cout<<"The initial flow speed is "<<U0[0]<<" m/s x "<<U0[1]<<" m/s\n";
		cout<<"The initial density is "<<rho0<<" kg/m^3\n";
		cout<<"The initial pressure is "<<p0<<" Pa\n";
		cout<<"The initial energy is "<<energy0<<" K\n";

	}
	
	//Initialize the initial conditions from .rst file
	if (initial_condition == 1)
		cout<<"Read the initial conditions from separated restat file "<<Project_name<<".rst \n";
}
//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function)
{

	double reciprocV; //the inverse of volume or volume
	double dstc;
	Vec2d eij, sumdw;

	//iterate particles on the particle list
	for (LlistNode<Particle> *p = hydro.particle_list.first(); 
		!hydro.particle_list.isEnd(p); 
		p = hydro.particle_list.next(p)) {
					
			//origin particle
			Particle *prtl_org = hydro.particle_list.retrieve(p);
			//build the nearest particle list
			particles.BuildNNP(prtl_org->R);

			reciprocV = 0.0; sumdw = 0.0;
			//iterate this Nearest Neighbor Particle list
			for (LlistNode<Particle> *p1 = particles.NNP_list.first(); 
			!particles.NNP_list.isEnd(p1); 
			p1 = particles.NNP_list.next(p1)) {
			
				//get a particle
				Particle *prtl_dest = particles.NNP_list.retrieve(p1);
				
				//summation the weights
				dstc = v_distance(prtl_org->R, prtl_dest->R);
				eij = (prtl_org->R - prtl_dest->R)/(dstc + 1.e-30);
				
				reciprocV += weight_function.w(dstc);
				sumdw = sumdw + eij*weight_function.F(dstc);
			}
			//calculate volume
			reciprocV = 1.0/reciprocV;

			//predict particle volume and mass
			prtl_org->V = reciprocV;
			prtl_org->m = prtl_org->rho*reciprocV;
			
			//clear the NNP_list
			particles.NNP_list.clear();
	}
}
