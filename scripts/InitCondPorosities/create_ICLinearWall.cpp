#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <assert.h>

using namespace std;

int main () {

  // parameter defining the linear wall position
  // (wall is parallel to x-direction)
  const double y_wall=0.25;
  
  //
  const double rho=1.0;
  const double p=1.0;
  const double m=0;// m is initialized to zero, will be calculated in simulation
  double x=0;
  double y=0;
  const double domain_size_x=0.1;
  const double domain_size_y=1.25;
  const int N_x=4;
  const int N_y=50;
  const int N=N_x*N_y;
  const double dx=domain_size_x/N_x;
  const double dy=dx;
  cout<<"dx=dy="<<dx<<endl;
  cout<<"N"<<N<<endl;
  const double gamma=1.5;
  
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  double m_array[N];
  
  for(int j=0;j<N_y;j++) {
    x=dx/2;
    
    for(int i=j*N_x;i<(j+1)*N_x;i++) {
      x_array[i]=x;
      y=(j+0.5)*dy;
      y_array[i]=y;
      vx_array[i]=0;
	vy_array[i]=0;
      x=x+dx;
      p_array[i]=p;
      rho_array[i]=rho;
      m_array[i]=m;
    };
  }
  
  ofstream out("../../cases/LinearWall.ivs");
  // output first line of .ivs file (geometrical data for cavity)
  out <<setprecision (6)
      <<"   "<<y_wall
      <<endl;
  // output number of particles as second line in file
  out<<N<<endl;
  // write rest of file, one row (x|y|vx|vy|rho|p|m) per particle
  for(int i=0;i<N;i++) {
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
  cout<<"<<LinearWall.ivs>> is successfully written into <<sph-blitz/cases>>\n";
}
