// initiation.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      initialize the progam
//		initiation.cpp
//----------------------------------------------------------------------------------------

#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

// ***** localincludes *****
#include "ConfigFile.h"
#include "initiation.h"
#include "particle.h"
#include "hydrodynamics.h"
#include "quinticspline.h"
#include "particlemanager.h"
#include "abspolymercreator.h"
#include "stdlib.h"
#include <cstdio>
#include <cstdlib>

using namespace std;
///
Initiation* Initiation::_instance = NULL;

Initiation* Initiation::Instance(const string& project_name, 
				 const string& poly_conf)
{
  cout << "calling new instance" << '\n';
  if (_instance == NULL) {
    _instance = new Initiation(project_name, poly_conf);
    
    if (_instance->pcreator_==NULL) {
      cout << "_instance->pcreator_==0" << '\n';
    }
  }
  return _instance;  
}

///call without argument
Initiation* Initiation::Instance() {
  return _instance;
}

void Initiation::addPolymerCreator(AbsPolymerCreator* newpcreator) {
  cout << "Add AbsPolymerCreator\n";
  //  newpcreator->showName();
  _instance->pcreator_ = newpcreator;  
}

void Initiation::addDataCollector(DataCollector* newdatacollector) {
  //  newpcreator->showName();
  _instance->datacollector_ = newdatacollector;  
}

/// constructor 
Initiation::Initiation(const string& project_name, 
		       const string& poly_conf):
  
  ///Fix::
  poly_conf(poly_conf),
  spacedim_(2)
{	
  char Key_word[25];

  //the project name
  strcpy(Project_name, project_name.c_str());

  //the input file name
  strcpy(inputfile, Project_name);
  //  strcat(inputfile, ".cfg");
	
  //check if inputfile exist
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"Initialtion: Read the global configuration data from "<< inputfile <<" \n"; 

  //reading key words and configuration data
  ///read timestep coefficient from the environment variable
  const char* temp_env = getenv("TIMESTEP_CO");
  if (temp_env==NULL) {
    timestep_co = 1.0;
  }
  else {
    timestep_co = strtod(temp_env, NULL);
    cout << "Timestep coefficient is " << timestep_co << '\n';
  }  
  
  while(!fin.eof()) {
    //read a string block
    fin>>Key_word;
    //comparing the key words for initial condition input
    //0: Initialize the initial conditions from .cfg file
    //1: restart from a .rst file
//     if(!strcmp(Key_word, "INITIAL_CONDITION")) {
//       fin>>initial_condition;
//       ///overrisde from the environment variable    
//       temp_env = getenv ("INITIAL_CONDITION");
//       if (temp_env!=NULL) {
// 	const string INITIAL_CONDITION_VAR = temp_env;
// 	cout << "INITIAL_CONDITION_VAR = " << INITIAL_CONDITION_VAR << '\n';
// 	if (INITIAL_CONDITION_VAR == "1") {
// 	  initial_condition = 1;
// 	}
//       }
//     }

    //output diagnose information
    //if(!strcmp(Key_word, "DIAGNOSE")) fin>>diagnose;
    //    cout << "Hi!" << endl;
    //comparing the key words for domian size
    //if(!strcmp(Key_word, "CELLS")) fin>>x_cells>>y_cells;
		  
    //comparing the key words for cell size
    //    if(!strcmp(Key_word, "CELL_SIZE")) fin>>cell_size;
		  
    //comparing the key words for smoothinglength
    //if(!strcmp(Key_word, "SMOOTHING_LENGTH")) fin>>smoothinglength;
		  
    //comparing the key words for the ratio between cell size and initial particle width
    //if(!strcmp(Key_word, "CELL_RATIO")) fin>>hdelta;
		  
    //comparing the key words for the g force
    //    if(!strcmp(Key_word, "G_FORCE")) fin>>g_force[0]>>g_force[1];
		  
    //comparing the key words for the artificial viscosity
    //    if(!strcmp(Key_word, "ARTIFICIAL_VISCOSITY")) fin>>art_vis;
		  
    //comparing the key words for dimension
    //if(!strcmp(Key_word, "DIMENSION")) fin>>_length>>_v>>_rho>>_T;
		  
    //comparing the key words for number ofmaterials
    //    if(!strcmp(Key_word, "NUMBER_OF_MATERIALS")) fin>>number_of_materials;
		  
    //comparing the key words for timing
    //if(!strcmp(Key_word, "TIMING")) fin>>Start_time>>End_time>>D_time;
		  
    //Premitted max particle number for MLS approximation
    //if(!strcmp(Key_word, "MLS_MAX")) fin>>MLS_MAX;
		  
    //Initialize the initial conditions from .cfg file
    if (initial_condition==0) {
      //comparing the key words for the initial state
      //    if(!strcmp(Key_word, "INITIAL_STATES")) fin>>U0[0]>>U0[1]>>rho0>>p0>>T0;
    }		
  }

  ConfigFile config(poly_conf);
  //
  config.readInto(MLS_MAX, "MLS_MAX");
  config.readInto(number_of_materials, "number_of_materials");
  config.readInto(art_vis, "art_vis");

  //dimenshions
  config.readInto(_length, "length_base");
  config.readInto(_v, "v_base");
  config.readInto(_rho, "rho_base");
  config.readInto(_T, "T_base");


  ///read additional parameters from polymer.cfg

  config.readInto(output_dir, "OUTPUT_DIR");
  config.readInto(U0[0], "U0_0");
  config.readInto(U0[1], "U0_1");
  config.readInto(rho0, "rho0");
  config.readInto(T0, "T0");
  config.readInto(p0, "p0");

  config.readInto(Start_time, "start_time");
  config.readInto(End_time, "end_time");
  config.readInto(D_time, "saving_time");
  config.readInto(MAX_TIME, "MAX_TIME");

  config.readInto(diagnose, "diagnose");
  config.readInto(x_cells, "ncell_x");
  config.readInto(y_cells, "ncell_y");
  config.readInto(cell_size, "cell_size");

  config.readInto(smoothinglength, "smoothinglength");  
  config.readInto(hdelta, "hdelta");
  
  config.readInto(initial_condition, "initial_condition");
  config.readInto(outputstream, "outputstream");

  //g-force
  config.readInto(g_force[0], "g_x");
  config.readInto(g_force[1], "g_y");
  
  //boundaries
  config.readInto(xBl, "xBl");
  config.readInto(xBr, "xBr");
  config.readInto(yBd, "yBd");
  config.readInto(yBu, "yBu");

  config.readInto(UxBl, "UxBl");
  config.readInto(UxBr, "UxBr");
  config.readInto(UyBd, "UyBd");
  config.readInto(UyBu, "UyBu");

  bool useRandom(true);
  config.readInto(useRandom, "UseRandomForce");
  cerr << "useRandom = " << useRandom << endl;
      
  fin.close();
	
  //process the data
  box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
  delta = cell_size/hdelta;
	
  //output information to screen
  show_information();

  //non-dimensionalize
  non_dimensionalize();

}
//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information() const
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
  cout<<"The dimensionless reference length, speed, density and temperature are \n"
      <<_length<<" micrometer, "<<_v<<" micrometer/s, "<<_rho<<" kg/m^3, "<<_T<<" K\n";

  //output the timing on screen
  cout<<"\nInitialtion: Time controlling:\nStarting time is "<<Start_time<<" \n";
  cout<<"Ending time is "<<End_time<<" \n";
  cout<<"Output time interval is "<<D_time<<" \n";

	
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
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
			    QuinticSpline &weight_function) const
{

  double reciprocV; //the inverse of volume or volume
  double dstc;
  Vec2d eij, sumdw;

  //iterate particles on the particle list
  for (LlistNode<Node> *p = hydro.particle_list.first(); 
       !hydro.particle_list.isEnd(p); 
       p = hydro.particle_list.next(p)) {
					
    //origin particle
    Node *prtl_org = hydro.particle_list.retrieve(p);
    //build the nearest particle list
    particles.BuildNNP(prtl_org->R());

    reciprocV = 0.0; sumdw = 0.0;
    //iterate this Nearest Neighbor Particle list
    for (LlistNode<Node> *p1 = particles.NNP_list.first(); 
	 !particles.NNP_list.isEnd(p1); 
	 p1 = particles.NNP_list.next(p1)) {
			
      //get a particle
      Node *prtl_dest = particles.NNP_list.retrieve(p1);
				
      //summation the weights
      dstc = v_distance(prtl_org->R(), prtl_dest->R());
      eij = (prtl_org->R() - prtl_dest->R())/(dstc + 1.e-30);
				
      reciprocV += weight_function.w(dstc);
      sumdw = sumdw + eij*weight_function.F(dstc);
    }
    //calculate volume
    reciprocV = 1.0/reciprocV;

    //predict particle volume and mass
    //prtl_org->V = reciprocV;
    prtl_org->setVolume(reciprocV);
    prtl_org->setMass(prtl_org->rho()*reciprocV);
			
    //clear the NNP_list
    particles.NNP_list.clear();
  }
}

int Initiation::getDim() const {
  return spacedim_;
}

//----------------------------------------------------------------------------------------
//				Non-dimensionalize the initial condition and parameters
//----------------------------------------------------------------------------------------
void Initiation::non_dimensionalize()
{
  box_size = non_dms_box_size(box_size);
  cell_size = non_dms_length(cell_size);
  smoothinglength = non_dms_length(smoothinglength);
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
double Initiation::non_dms_p(double p) const
{
  return p/_v/_v/_rho;
}
//-------------------------------------------------------
//			Non_dimensionalize temperature
//-------------------------------------------------------
double Initiation::non_dms_T(double T) const
{
  return T/_T;
}
//-------------------------------------------------------
//			Non_dimensionalize density
//-------------------------------------------------------
double Initiation::non_dms_rho(double rho) const
{
  return rho/_rho;
}
//-------------------------------------------------------
//			Non_dimensionalize mass
//			in 2-dimension 
//-------------------------------------------------------
double Initiation::non_dms_mass(double mass) const
{
  return mass/_rho/_length/_length/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize time
//-------------------------------------------------------
double Initiation::non_dms_time(double time) const
{
  return time*_v/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize length
//-------------------------------------------------------
double Initiation::non_dms_length(double length) const
{
  return length/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize boxsize in 2-d
//-------------------------------------------------------
Vec2d Initiation::non_dms_box_size(Vec2d box_size) const
{
  return box_size/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize velocity
//-------------------------------------------------------
double Initiation::non_dms_velocity(double velocity) const
{
  return velocity/_v;
}
//-------------------------------------------------------
//			Non_dimensionalize vector velocity
//-------------------------------------------------------
Vec2d Initiation::non_dms_velocity(Vec2d velocity) const
{
  return velocity/_v;
}
//-------------------------------------------------------
//			Non_dimensionalize acceleration vector
//-------------------------------------------------------
Vec2d Initiation::non_dms_acceleration(Vec2d acceleration) const
{
  return acceleration*_length/_v/_v;
}
//-------------------------------------------------------
//			Non_dimensionalize surface tension coefficient
//-------------------------------------------------------
double Initiation::non_dms_surface(double sigma) const
{
  return sigma/_rho/_v/_v/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize viscosity
//-------------------------------------------------------
double Initiation::non_dms_viscosity(double mu) const
{
  return mu/_v/_rho/_length; // Dynamic Viscosity [kg/ (m s)]

}
//-------------------------------------------------------
//			Non_dimensionalize kinetic viscosity
//-------------------------------------------------------
double Initiation::non_dms_kinetic_viscosity(double nu) const
{
  return nu/_v/_length;
}
//-------------------------------------------------------
//			Non_dimensionalize heat ratio
//-------------------------------------------------------
double Initiation::non_dms_heat_ratio(double cv) const
{
  return cv*_T/_v/_v;

}
//-------------------------------------------------------
//			Non_dimensionalize heat conduction rate
//-------------------------------------------------------
double Initiation::non_dms_heat_conduction(double kappa) const
{
  return kappa*_T/_v/_v/_v/_rho;
}
//-------------------------------------------------------
//			Non_dimensionalize Boltzmann constant
//-------------------------------------------------------
double Initiation::non_dms_Boltzmann(double k_bltz) const
{
  ///Fix:
  //  return k_bltz*_T/_v/_v/_rho/_length/_length/_length ;
  // for 2D case 
  cout << "delta = " << delta << '\n';
  return k_bltz*_T/_v/_v/_rho/_length/_length/_length / delta ;
}

double Initiation::non_dms_elasticity(double k) const
{
  return  k / (_rho*_v*_v*_length);
}
//-------------------------------------------------------
//			Dimensionalize functions
//-------------------------------------------------------
Vec2d Initiation::dms_R(Vec2d& R) const
{
  return _length*R;
}

double Initiation::dms_p(double p_non) const
{
  return p_non*_v*_v*_rho;
}
//-------------------------------------------------------
double Initiation::dms_T(double T_non) const
{
  return T_non*_T;
}
//-------------------------------------------------------
double Initiation::dms_rho(double rho_non) const
{
  return rho_non*_rho;
}
//-------------------------------------------------------
double Initiation::dms_mass(double mass_non) const
{
  return mass_non*_rho*_length*_length;
}
//-------------------------------------------------------
double Initiation::dms_time(double time_non) const
{
  return time_non/_v*_length;
}
//-------------------------------------------------------
double Initiation::dms_length(double length_non) const
{
  return length_non*_length;
}

double Initiation::dms_volume(double v) const 
{
  return v * _length * _length * _length;
}

//-------------------------------------------------------
Vec2d Initiation::dms_box_size(Vec2d box_size_non) const
{
  return box_size_non*_length;
}
//-------------------------------------------------------
double Initiation::dms_velocity(double velocity_non) const
{
  return velocity_non*_v;
}
//-------------------------------------------------------
Vec2d Initiation::dms_velocity(Vec2d velocity_non) const
{
  return velocity_non*_v;
}
//-------------------------------------------------------
double Initiation::dms_energy(double energy_non) const
{
  return energy_non*_rho*_length*_length*_length*_v*_v;
}
//-------------------------------------------------------
Vec2d Initiation::dms_acceleration(Vec2d acceleration_non) const
{
  return acceleration_non*_v*_v/_length;
}
//-------------------------------------------------------
double Initiation::dms_viscosity(double mu_non) const
{
  return mu_non*_v*_rho*_length;
}

AbsPolymerCreator* Initiation::getPolymerCreator() const
{
  return _instance->pcreator_;
}

DataCollector* Initiation::getDataCollector() const
{
  return _instance->datacollector_;
}

Boundary* Initiation::getBoundary() const {
  return _instance->boundary_;
}

void Initiation::setBoundary(Boundary* inb) {
  _instance->boundary_ = inb;
}
//-------------------------------------------------------

