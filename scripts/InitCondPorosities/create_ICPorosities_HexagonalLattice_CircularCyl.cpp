#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <glog/logging.h>
#include <assert.h>
#include <vector> 
#include <stdlib.h>
#include "../../src/vec2d.h"


using namespace std;

// this program generates a uniform particle distribution where particles
// are arranged in a continuous rectangular lattice, no matter if
// they are located within a cylinder or in the actual calculation domain...

// the porosity is generated here by for cylinders with
// center point = domain corners and same radius

int main (int argc, char *argv[]) {

  // inizialize google logger
  google::InitGoogleLogging(argv[0]);
  cout<<"Log messages printed into file INFO in tmp-folder"<<endl;
  

  const double PI=3.1415926535897932;
  const double rho=1.0;
  const double p=1.0;
 
  const double domain_size_x=1.0;
  const double domain_size_y=domain_size_x;
  const int N_x=50;
  const int N_y=58;//choosen in a way that dy is closest to sqrt(3)/2*dx (hexagonal)

  const double dx=domain_size_x/N_x;
  const double dy=domain_size_y/N_y;
  cout<<"dx="<<dx<<endl;
  cout<<"dy="<<dx<<endl;
  // due to discontinuity in lattice structure arond cylinder surface,
  // there would be different mass values for different particles when
  // initializing via the interpolation formula: Mass is therefore initialized
  // externally (causing fluctuations in density) but these can be
  // encountered with an initial relaxing time in simulation, where particles
  // can find their equilibrium
  const double m=domain_size_x*domain_size_y/(N_x*N_y);
  
  // margin between cyliner surface and closest real particle placement
  // is set to the same value as distance of two particle layers within cylinder
  // dx was considered a bit to much...
  double margin=sqrt(3)/2*dx; 
  

  // supportlength is needed as cylinders are filled with ghost particles up
  // to a thickness of 2 supportlengths to the wall. If a simulation set with
  // constant spacing but variable supportlength is to be conducted, one can
  // specify here the maximum supportlength. This the particle distribution can
  // be used for all simulations (the simulation prorgam will discard 
  // particles beyond 2*supLen automatically...)
  const double supportlength=4*dx;
  
  // geometrical cylinder data
  const double N_cyl=4;// number of cylinders;
  const double rad=0.3; //radius of one cylinder

  // vector of  components of double containing all cylinders' radii
  // to make it easier to use variable radii
  // in that case: just initialize all components of  All_Cyl_rad with
  // different values, rest of program is adapted to variable radii
  vector <double> All_Cyl_rad(4,rad);
  // vector of 4 components of vec2d containing all cylinders' center positions 
  vector <Vec2d> All_Cyl_Pos_c(4,(0.0,0.0));
  // set center positions for the 4 cylinders
  Vec2d Cyl_Pos_c1(0.0,0.0);
  Vec2d Cyl_Pos_c2(domain_size_x,0.0);
  Vec2d Cyl_Pos_c3(0.0,domain_size_y);
  Vec2d Cyl_Pos_c4(domain_size_x,domain_size_y);
  
  All_Cyl_Pos_c[0]=Cyl_Pos_c1;
  All_Cyl_Pos_c[1]=Cyl_Pos_c2;
  All_Cyl_Pos_c[2]=Cyl_Pos_c3;
  All_Cyl_Pos_c[3]=Cyl_Pos_c4;
  LOG(INFO)<<" All_Cyl_Pos_c[0]: "<< All_Cyl_Pos_c[0];
  LOG(INFO)<<" All_Cyl_Pos_c[1]: "<< All_Cyl_Pos_c[1];
  LOG(INFO)<<" All_Cyl_Pos_c[2]: "<< All_Cyl_Pos_c[2];
  LOG(INFO)<<" All_Cyl_Pos_c[3]: "<< All_Cyl_Pos_c[3];

 
  
  // variables containing all particles' data
  vector <double> x_array;
  vector <double> y_array;
  vector <double> vx_array;
  vector <double> vy_array;
  vector <double> p_array;
  vector <double> rho_array;
  vector <double> m_array;
  
  //--------------------- place particles forming the cylinders------------- 
  
  // according to Morris1999 (pseudo-hexagonal form)
  // see also thesis where it's explained as well...
  
  //iterate each cylinder
  for(int i=0;i<N_cyl;i++) {
    
    // for each cylinder place particles in layers parallel to 
    // cylidner surface according to Morris1999 until a distance 
    // of more than 2 supportlengths (2 is needed in  case that desnity
    // will be evolved within the simulation program) to the
    // cylinder surface is reached
    
    
    // for each cylinder calculate first arc length of cylinder boundary
    // which is in domain (here: a quarter of a cylinder) and with arc length
    // determine number of particles per layer
    // see Morris1999: particle distance about dx 
    // NOTE: the following approximation is done:
    // the section of the arc between two particles is considered as dx 
    // and not the actual distance
    // but this does not matter:
    //  a) as radius>>dx
    //  b) as anyway Morris1999 suggests only distance AROUND dx
    const double l_arc= All_Cyl_rad[i]*2*PI;
    // determine number of particles per layer (assuming a 360° placement)
    // (remains constant for all layers)
    const int N_p_layer=round(l_arc/dx);
    // determine angle (polar coordinates with cylinder center as origin)
    // increment for particle placement (remains constant for all layers
    // as number of particles remains constant)
    const double d_phi=2*PI/(N_p_layer);
    
    // now start placement of particles for each layer
    
    // place particles layer after layer and diminuish radius until an area
    // of 2 supportengths away from the cylinder surface is covered with
    // (ghost) particles
    int layer_iteration_counter=0;//to alternate phi_start (see below)
    
    // iteration over all layers as long as current layer radius is >
    // external radius-2*supportlength
    // distance between the layers is sqrt(3)/2*dx (Morris1999) 
    // (pseudo hexagonal)
    
    for(double current_rad=All_Cyl_rad[i];current_rad>All_Cyl_rad[i]-2*supportlength;current_rad-=sqrt(3)/2*dx) {
      
      // phi_start is angle for first particle's position
      // (in polar coordinates)
      // phi start will alternate between 0 and d_phi/2 from layer to layer
      // seeMorris1999
      double phi_start;
      if(layer_iteration_counter%2==0)
	phi_start=0;
      else
	phi_start=d_phi/2;
      
      // places all particles in one layer by incrementing angle phi
      // "-d_phi*1e-5" is needed due to accuracy problems of double:
      // to ensure particles are not placed twice at the same spot
      // (once for phi=0 and once for phi~=2*PI...)
      for (double current_phi=phi_start;current_phi<2*PI+phi_start-d_phi*1e-5; 
	   current_phi+=d_phi) {
	//place current particle if position within calculation domain
	const double x=All_Cyl_Pos_c[i][0]+current_rad*cos(current_phi);
	const double y=All_Cyl_Pos_c[i][1]+current_rad*sin(current_phi);
	if((x>=0&&x<=domain_size_x)&&(y>=0&&y<=domain_size_y)) {
	  x_array.push_back(All_Cyl_Pos_c[i][0]+current_rad*cos(current_phi));
	  y_array.push_back(All_Cyl_Pos_c[i][1]+current_rad*sin(current_phi));
	  vx_array.push_back(0);
	  vy_array.push_back(0);
	  p_array.push_back(p);
	  rho_array.push_back(rho);
	  m_array.push_back(m);
	}
      }
      //one layer is iterated->increment counter (needed for phi_start)
      layer_iteration_counter++;
    }
  }
  //---------------------------END of cylinder (ghost) particle placement
  
  //-------------------place real particles around cylinders-----------
  // (in a hexagonal lattice)
  
  //iterate the whole domain...
  double x_start=0;
  //iteration countern
  int iteration_counter2=0;
  for(double y=dy/2;y<=domain_size_y;y+=dy) {
    for(double x=x_start;x<=domain_size_x;x+=dx) {
      LOG(INFO)<<"current x: "<<x<<"  current y: "<<y;
      // ...and if current position is not within a cylinder; place a particle

      // test if position inside one of the cylinders or outside but closer than dx
      // to the cylinder surface (to prevent that particles are located to close)
      int current_pos_inside_cyl=0;//if variable >0 current pos. is inside cylinder
      for(int i =0;i<N_cyl;i++) {
	const Vec2d current_pos(x,y); //vector with current position
	if(v_abs(All_Cyl_Pos_c[i]-current_pos)<All_Cyl_rad[i]+margin)
	  current_pos_inside_cyl++;
      }
      LOG(INFO)<<" current_pos_inside_cyl value; "<< current_pos_inside_cyl;
      //if position NOT inside one f cylinds:
      if(current_pos_inside_cyl==0) {
	//create real particle
	x_array.push_back(x);
	y_array.push_back(y);
	vx_array.push_back(0);
	vy_array.push_back(0);
	p_array.push_back(p);
	rho_array.push_back(rho);
	m_array.push_back(m);
      }
    }
    if(iteration_counter2%2==0)
      x_start=dx/2;
    else
      x_start=0;
    iteration_counter2++;
  }
  //now number of particles can be determined:
  const int N=x_array.size();

  ofstream out("../../cases/Porosities_HexagonalLatticeRealPrtl_CircularCyl.ivs");
  // output file header with geometrical infomration for cylinders
  // first line: number of cylinders
  // then: one further line for each cylinder with format:
  // position center x, positioon center y, radius 
  out<<N_cyl<<endl;
  for(int i=0;i<N_cyl;i++) {
    out<<setprecision (6)
       <<"   "<<All_Cyl_Pos_c[i][0]
       <<"   "<<All_Cyl_Pos_c[i][1]
       <<"   "<<All_Cyl_rad[i]
       <<endl;
  }
  
  // output number of particles in separate line after header
  out<<N<<endl;
  // write rest of file, one line (x|y|vx|vy|rho|p|m) per particle
  for(int i=0;i<x_array.size();i++) {
    out <<setprecision (6)
	<<"   "<<x_array[i]
	<<"   "<<y_array[i]
	<<"   "<<vx_array[i]
	<<"   "<<vy_array[i]
	<<"   "<<rho_array[i]
	<<"   "<<p_array[i]
	<<"   "<<m_array[i]
	<<endl;
  };
  
  out.close();
  cout<<"<<Porosities_HexagonalLatticeRealPrtl_CircularCyl.ivs>> is successfully written into <<sph-blitz/cases>>\n";
}

