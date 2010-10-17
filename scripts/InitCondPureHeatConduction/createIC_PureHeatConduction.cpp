#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>

using namespace std;

// creates a slab of size (domain_size_x,domain_size_y) with equal
// particle spacing in both directions (according to Cleary1999, test-case 5.1)

// the temperature profile is T_l=const. in the left half and T_r=cosnt.
// in the right half of the slab.

int main () {
  
  //
  const double rho=1000.0;// density 
  const double domain_size_x=1.0;// domain size x-direction
  const double domain_size_y=0.05;// domain size y-direction
  const int N_x=40;// number of particles in x direction
  const int N_y=2;
 // const int N_y=N_x*(domain_size_y/domain_size_x);// number of particles in y directon
  const int N=N_x*N_y;// total number of particles
  const double dx=domain_size_x/N_x;// distance between two particles
  const double dy=dx;//particles equispaced in both directions
  double x=dx/2.0;// initialize x with dx/2 (=x-value of first row of particles)
  double y=0;// y coordinate of particle
  const double T_l=0.0;// LHS Temperature
  const double T_r=1.0;// RHS Temperature
  //vectors containing all particles' data for output in file 
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  double m_array[N];

  // m is not used in the simulation program
  // it is written in theinitiation file
  // only to maintain input-file structure
  const double m=rho*dx*dy;

  // p is not needed for the simulation either, BUT:
  // I need p to create the desired Temperature profile because
  // there is no direct initialiation with T or the internal energy.
  // The Internal Energy or T are calculated within the simulation program
  // based on rho, p and gamma (ideal gas equation of state)
  // therefore I initialize p and rho in a way to obtain the desired 
  // Temperatures T_l and T_r
  // ( for simplicity, I choose gamma=2, cv=1 in the configuration (.tcl) file)
  const double p_l=T_l*(2-1)*rho*1;
  const double p_r=T_r*(2-1)*rho*1;
  

  //output for user:
  cout<<endl<<"The slab has a size of:"<<endl;
  cout<<"       "<<domain_size_x<<" in x-direction"<<endl;
  cout<<"       "<<domain_size_y<<" in y-direction"<<endl<<endl;
  cout<<"...with a number of particles of:"<<endl;
  cout<<"       "<<N_x<<" in x-direction"<<endl;
  cout<<"       "<<N_y<<" in y-direction"<<endl;
  cout<<"...which makes a total number of particles of: "<<N<<endl<<endl;
  cout<<"The particle spacing in both directions is: "<<dx<<endl<<endl;
  cout<<endl<<"The left hand side temperature is:"<<T_l<<endl;
  cout<<endl<<"The right hand side temperature is:"<<T_r<<endl<<endl;
 
  
 
    
  for(int j=0;j<N_y;j++) {
    x=dx/2;
    
    for(int i=j*N_x;i<(j+1)*N_x;i++) {
      x_array[i]=x;
      y=(j+0.5)*dy;
      y_array[i]=y;
      vx_array[i]=0;
      vy_array[i]=0;
      if(x<=domain_size_x/2)
	p_array[i]=p_l;
      else
	p_array[i]=p_r;
      rho_array[i]=rho;
      m_array[i]=m;
      x=x+dx;
      
    };
  }
 
  //write initialization data into file
  ofstream out("../../cases/PureHeatConduction.ivs");
  
  out<<N<<endl;// write numer of particles
  
  //write particle data
  for(int i=0;i<N;i++) {
    out <<setprecision (8)
	<<"   "<<x_array[i]
	<<"   "<<y_array[i]
	<<"   "<<vx_array[i]
	<<"   "<<vy_array[i]
	<<"   "<<rho_array[i]
	<<"   "<<p_array[i]
	<<"   "<<m
	<<endl;
  };
  
  out.close();
  cout<<"<<PureHeatConduction.ivs>> successfully written in <<sph-blitz/cases>>\n"<<endl;
}
