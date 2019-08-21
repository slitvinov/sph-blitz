#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "vec2d.h"
#include "glbfunc.h"
#include "dllist.h"
#include "quinticspline.h"
#include "particlemanager.h"
#include "hydrodynamics.h"
#include "particle.h"

#include "initiation.h"


using namespace std;

//----------------------------------------------------------------------------------------
//							constructor
//----------------------------------------------------------------------------------------
Initiation::Initiation(const char *project_name) {
	
    char Key_word[FILENAME_MAX];

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
}
//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function)
{
    enum {X, Y};
    double reciprocV; //the inverse of volume or volume
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

	reciprocV = 0.0; sumdw[X] = sumdw[Y] = 0.0;
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
	    reciprocV += w(&weight_function, dstc);
	    sumdw = sumdw + eij*F(&weight_function, dstc);
	}
	/// <li> calculate volume as reciprocal value of weight function
	reciprocV = 1.0/reciprocV;

	/// <li> save volume and mass in the respective particle list node (whih is each a Particle object with all the particle properties) 
	prtl_org->V = reciprocV;
	prtl_org->m = prtl_org->rho*reciprocV;
			
	/// <li> clear the NNP_list</ul> </ul>
	particles.NNP_list.clear();
    }
}
