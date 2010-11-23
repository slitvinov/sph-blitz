#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <vector>

using namespace std;

// creates a uniform particle distribution where one set of particles is placed
// exactly on the surface of the  first wall (y_wall_1)
// and if dx=dy are a fraction of 1, the same applies for the second wall!

int main () {
  
  // parameter defining position of linear wall 1
  // (wall is parallel to x-direction and solid part is for y<y_wall_1)
  const double y_wall_1=0.25;

  // parameter defining position of linear wall 2
  // (wall is parallel to x-direction and solid part is for y>y_wall_2)
  const double y_wall_2=1.25;


  const double rho=1000.0;// density 
  const double domain_size_x=0.1;// domain size x-direction
  // domain size in y direction determined automatically in a way
  // that
  const int N_x=4;// number of particles in x direction
  
  const double dx=domain_size_x/N_x;// distance between two particles
  const double dy=dx;//particles equispaced in both directions
  double x=dx/2.0;// initialize x with dx/2 (=x-value of first row of particles)
  double y;// y coordinate of particle
  const double T=0.0;// Temperature
  //vectors containing all particles' data for output in file 
  vector <double> x_array;
  vector <double> y_array;
  vector <double> vx_array;
  vector <double> vy_array;
  vector <double> p_array;
  vector <double> rho_array;
  vector <double> m_array;

  // m is not used in the simulation program
  // it is written in the initiation file
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
  const double p=T*(2-1)*rho*1;
  
 
  //assignment of data to output vector 
  int N=0;// number of particles
  x=dx/2;//initial value for y
  for(int j=0;j<N_x;j++) {
   
    y=y_wall_1-5*dy;// like this one ensures that ghost prtl is placed on solObs surface
    while(y<y_wall_2+5*dy) {
      x_array.push_back(x);
      y_array.push_back(y);
      vx_array.push_back(0);
      vy_array.push_back(0);
      p_array.push_back(p);
      rho_array.push_back(rho);
      m_array.push_back(m);
      y=y+dy;
    };
    x=x+dx;
  }
 
  //output for user:
  cout<<endl<<"The slab has a size of:"<<endl;
  cout<<"       "<<domain_size_x<<" in x-direction"<<endl;
  cout<<"       "<<"position of linear walls: y1= "<<y_wall_1
      <<"   and y2= "<<y_wall_2<<endl;
  
  cout<<"...with a number of particles of:"<<endl;
  cout<<"       "<<N_x<<" in x-direction"<<endl;
  cout<<"       "<< x_array.size()/N_x<<" in y-direction (including solid wall ghost particles)"<<endl;
  cout<<"    ... which makes a total number of particles of: "
      <<x_array.size()<<endl;
  cout<<"This number may include ghost particles which are not needed for \n the simulation as they are further away from the wall surface than ONE supportlength!\n The final number of particles used for the calculation is therefore determined only \n within the simulation program."<<endl<<endl;
    
   
  cout<<"The particle spacing in both directions is: "<<dx<<endl;
  cout<<endl<<"The temperature is:"<<T<<endl<<endl;

  //write initialization data into file
  ofstream out("../../cases/LinearWall_thermal_SolObsBC_on_wall.ivs");
  
  // output first line of .ivs file (geometrical data for wall)
  out <<setprecision (6)
      <<"   "<<y_wall_1
      <<"   "<<y_wall_2
      <<endl;
  // output number of particles as second line in file
  out<<x_array.size()<<endl;
  
  //write particle data
  for(int i=0;i<x_array.size();i++) {
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
  cout<<"<<LinearWall_thermal_SolObsBC_on_wall.ivs>> successfully written in <<sph-blitz/cases>>\n"<<endl;
}
