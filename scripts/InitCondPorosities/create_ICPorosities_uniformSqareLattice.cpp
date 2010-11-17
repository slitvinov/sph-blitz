#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <assert.h>


using namespace std;

//this program generates a uniform particle distribution where particles
// are arranged in a continuous rectangular lattice, no matter if
// they are located within a cylinder or in the actual calculation domain...

// the porosity is generated here by for cylinders with
// center point =domain corners and same radius
int main () {
  
  const double rho=1.0;
  const double p=1.0;
  const double m=0;// m is initialized to zero, will be calculated in simulation
  double x=0;
  double y=0;
  const double domain_size_x=1.0;
  const double domain_size_y=domain_size_x;
  const int N_x=50;
  const int N_y=N_x;
  const int N=N_x*N_y;
  const double dx=domain_size_x/N_x;
  const double dy=dx;
  cout<<"dx=dy="<<dx<<endl;
  cout<<"N"<<N<<endl;
  
  //geometrical cylinder data
  const double N_cyl=4;// number of cylinders;
  const double rad=0.3; //radius of one cylinder
  const double Pos_c1[2]={0.0,0.0};
  const double Pos_c2[2]={0.0,domain_size_y};
  const double Pos_c3[2]={domain_size_x,0.0};
  const double Pos_c4[2]={domain_size_x,domain_size_y};


  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  double m_array[N];
  

  // place particles (one contimuous rectangular lattice no matter
  // if in zylinder or not
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
  
  ofstream out("../../cases/Porosities_uniformSquareLattice.ivs");
  // output file header with geometrical infomration for zylinders
  // first line: number of zylinders
  // then: one further line for each zylinder with format:
  // position center x, positioon center y, radius 
  out<<N_cyl<<endl;
  out<<setprecision (6)
     <<"   "<<Pos_c1[0]
     <<"   "<<Pos_c1[1]
     <<"   "<<rad
     <<endl;
 out<<setprecision (6)
    <<"   "<<Pos_c2[0]
    <<"   "<<Pos_c2[1]
    <<"   "<<rad
    <<endl;
 out<<setprecision (6)
    <<"   "<<Pos_c3[0]
    <<"   "<<Pos_c3[1]
    <<"   "<<rad
    <<endl;
 out<<setprecision (6)
   <<"   "<<Pos_c4[0]
   <<"   "<<Pos_c4[1]
   <<"   "<<rad
   <<endl;

  // output number of particles in separate line after header
  out<<N<<endl;
  // write rest of file, one line (x|y|vx|vy|rho|p|m) per particle
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
  cout<<"<<Porosities_uniformSquareLattice.ivs>> is successfully written into <<sph-blitz/cases>>\n";
}
