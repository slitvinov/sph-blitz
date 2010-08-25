#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>

using namespace std;

int main () {
  
  const double PI= 3.1415926535;
  char Key_word[125];
  
 
  const double p_0=1.0;
  const double gamma=1.4;// gamma air
  const double rho_0=1.0;// density (considered constant)
  const int N=200;// number of particles
  const double domain_size=2.0;
  const double dx=domain_size/N;// distance between two particles
  const double m=rho_0*dx;// particle mass (the same for each particle)
  double x=dx/2.0;// initialize x with dx/2 (=x-value of first row of particles)
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  
  const double c_s0=sqrt(gamma*p_0/rho_0);
 
  cout<<setprecision (8)<<"sound speed is: "<<c_s0<<endl;

  // initialize wave of 1 wavelength (with p perturbation only),
  //  rest of domain: unperturbed flow

  for(int i=0;i<N;i++) {
    x_array[i]=x;
    x=x+dx;
    y_array[i]=0;
    vx_array[i]=0;
    vy_array[i]=0;
    p_array[i]=p_0 ;
    rho_array[i]=rho_0;
  };
  
  //write initialization data into file
  ofstream out("../../cases/1DunperturbedDomain.ivs");
  
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
  cout<<"1DunperturbedDomain.ivs successfully written in <<sph-blitz/cases>>\n";
}
