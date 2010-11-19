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

  // parametres defining the cavity geometry (see README)
  // !!! in order for the cavity geometryto be represented as accurate
  // as possible, ensure that cavity geometry is selected 
  // in a way that there are particles right at the solid wall surfaces!!!
  
  const double y_surface=1.39;//bottom of cavity will be 0.19
  const double depth=0.6;
  const double width=0.3;
  //
  const double rho=1.0;
  const double p=1.0;
  const double m=0;// m is initialized to zero, will be calculated in simulation
  double x=0;
  double y=0;
  const double domain_size_x=1.0;
  const double domain_size_y=2.0;
  const int N_x=50;
  const int N_y=100;
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
  
  ofstream out("../../cases/Cavity.ivs");
  // output first line of .ivs file (geometrical data for cavity)
  out <<setprecision (6)
      <<"   "<<y_surface
      <<"   "<<depth
      <<"   "<<width
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
  cout<<"<<Cavity.ivs>> is successfully written into <<sph-blitz/cases>>\n";
}
