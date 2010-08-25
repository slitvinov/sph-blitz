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
  double x=0;
  double v,p,rho,T,c_s,M;
  const double p_0=1;
  const double gamma=1.4;// gamma air
  const double rho_0=1;
  const int N=100;// number of particles
  const double domain_size=1.0;
  const double R=287.058;// specific gas constant air
  const double cp=gamma*R/(gamma-1);
  const double dx=domain_size/N;// distance between two particles
  const double m=rho_0*dx;// particle mass (the same for each particle)
  const double T_0=p_0/(rho_0*R);

  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  
  double c_s0=sqrt(gamma*p_0/rho_0);
  for(int i=0;i<N;i++) {
    //sinusoidal velocity profile
    v=0.05*c_s0*sin(2*PI*x);
    //calculate temperature
    T=T_0-pow(v,2)/(2*cp);

    //calculate p, rho with isentropic relation
    p=p_0*pow((T/T_0),gamma/(gamma-1));
    // rho=rho_0*pow((T/T_0),1/(gamma-1));
    
    x_array[i]=x;
    x=x+dx;
    y_array[i]=0.0;
    vx_array[i]=v;
    vy_array[i]=0.0;
    p_array[i]=p;
    rho_array[i]=1.0;
  };
  
  
  ofstream out("../../cases/1DWave.ivs");
  
  out<<N<<endl;
  
  for(int i=0;i<N;i++)
    {
      out <<setprecision (8)
	  <<"   "<<x_array[i]
	  <<"   "<<y_array[i]
	  <<"   "<<vx_array[i]
	  <<"   "<<vy_array[i]
	  <<"   "<<rho_array[i]
	  <<"   "<<p_array[i]
	  <<"   "<<m<<endl;
    };
  
  out.close();
  cout<<"1DWave.ivs successfully written in <<sph-blitz/cases>>\n";
}
