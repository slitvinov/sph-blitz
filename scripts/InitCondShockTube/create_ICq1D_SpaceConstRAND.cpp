#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <assert.h>

#include <time.h>

using namespace std;

int main () {

  char inputfile[25]="1DST.dat";
  char Key_word[125];
  double vl=0,vr=0,pl=0,pr=0,rhol=0,rhor=0,ml=0,mr=0;
  double x=0;
  double domain_size_x=2.0;
  double domain_size_y=0.025;
  double pert_x=0;// perturbation
  double pert_y=0;// perturbation
  double sum_pert_x=0;// to control if mean is equal (or at least around) 0
  double sum_pert_y=0;// to control if mean is equal (or at least around) 0
  double dx,dy;
  int N_rx, N_lx, N_x,N_ly,N_y,N_l,N_r;
  double N_ry;

  // here constant spacing !!dx must be chosen in a way that supLen is multiple
  // of it (here: e.g. dx= 0.005,0.01,...)
  dx=0.005;
  dy=dx;
  cout<<"dx=dy="<<dx<<endl;
    

  // initialize random seed
  srand ( time(NULL) );

  // factor to adjust the interval of the random number generator
  // fac of 0.1 means that the fluctuations are[-0.1dx;+0.1dx]
  // ATTENTION: do not choose a factor greater than 0.5:
  //    1. there is no sense in choosing such a big factor, because for 0,5
  //       the whole area between two unperturbed positions is a potential
  //       location for the perturbed particle position!
  //       Therefore fac>0.5 does not increase disorder any more
  //    2. for fac>0.5 it might happen that particles are placed at an y
  //       position, which is outside the calculation domain. This would lead
  //       to a segmentation fault when the initiation file is read into the
  //       main program
  
  double fac=0.30;

  if(fac<0 || fac>0.5) {
    cout<<"\n the perturbation factor is not within the valid range (0<=fac<=0.5) please try again \n";
    exit(1);
  };
  
  // reading characteristic data for shock tube problem from file 1DST.dat
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"Creating initial condition file q1DShockSpaceConst.ivs (2D particle distribution with constant spacing) from initial vaules specified in"<< inputfile <<" \n"; 
  
  //reading key words and configuration data from configuration file and assign them to the appropriate variable
  while(!fin.eof()) {
    //read a string block
    fin>>Key_word;
    
    //comparing the key words and assigning value to corresponding variable
    if(!strcmp(Key_word, "pl")) fin>>pl;
    if(!strcmp(Key_word, "pr")) fin>>pr;
    if(!strcmp(Key_word, "vl")) fin>>vl;
    if(!strcmp(Key_word, "vr")) fin>>vr;  
    if(!strcmp(Key_word, "rhol")) fin>>rhol;
    if(!strcmp(Key_word, "rhor")) fin>>rhor;  
  }  
  fin.close();
  // ATTENTION: rounding errors (or better truncation errors, as N_rx is int,
  // does not work as expected, for example: 0.015/0.005=2 and not 3 for
  // N_y , made N_y double, and one has to pay attention that domainsize_y 
  // is a multiple of dy!
  
  N_rx=domain_size_x/2/dx+1;
  cout<<"N_rx"<<N_rx<<endl;
  N_lx=N_rx-1;
  
  N_ry=domain_size_y/dy;
  cout<<"N_ry"<<N_ry<<endl;
  N_ly=N_ry;
  
  int N;
  N=N_lx*N_ly+N_rx*N_ry;
  cout<<"N"<<N<<endl;
  
  ml=rhol*dx*dy;
  cout<<"ml"<<ml<<endl;
  mr=rhor*dx*dy;
  cout<<"mr"<<mr<<endl;
  
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  double m_array[N];
  
  for(int j=0;j<N_ly;j++) {
    x=2-N_lx*dx;
    for(int i=j*N_lx;i<(j+1)*N_lx;i++) {
      
      // create random perturbation
      
      // as random numbers are generated as integers in a range from -200 to 200
      // they have to be divided by a factor to obtain the desired range
      
      pert_x = (rand() % 401 -200)/200.0*dx*fac;
      pert_y = (rand() % 401 -200)/200.0*dy*fac;
      //cout<<pert_x<<endl;
      sum_pert_x=sum_pert_x+pert_x;
      sum_pert_y=sum_pert_y+pert_y;
      x_array[i]=x+pert_x;
      x=x+dx;
      y_array[i]=(j+0.5)*dy+pert_y;
      vx_array[i]=vl;
      vy_array[i]=0;
      p_array[i]=pl;
      rho_array[i]=rhol;
      m_array[i]=ml;
      
    };
  }
  for(int j=0;j<N_ry;j++) {
    x=2;
    for(int i=N_lx*N_ly+j*N_rx;i<N_lx*N_ly+(j+1)*N_rx;i++) {

      
      // create random perturbation
      
      // as random numbers are generated as integers in a range from -200 to 200
      // they have to be divided by a factor to obtain the desired range
      
      pert_x = (rand() % 401 -200)/200.0*dx*fac;
      pert_y = (rand() % 401 -200)/200.0*dy*fac;
      sum_pert_x=sum_pert_x+pert_x;
      sum_pert_y=sum_pert_y+pert_y;
      x_array[i]=x+pert_x;
      x=x+dx;
      y_array[i]=(j+0.5)*dy+pert_y;
      vx_array[i]=vr;
      vy_array[i]=0;
      p_array[i]=pr;
      rho_array[i]=rhor;
      m_array[i]=mr;
      
    };  
  }
  //output for user information
  cout<<endl<<"sum (=integral value) of perturbations in x direction:  "<<sum_pert_x<<endl;
  cout<<endl<<"mean value of perturbations in x direction:  "<<sum_pert_x/N<<endl;

  cout<<endl<<"sum (=integral value) of perturbations in y direction:  "<<sum_pert_y<<endl;
  cout<<endl<<"mean value of perturbations in y direction:  "<<sum_pert_y/N<<endl;
  
  ofstream out("../../cases/q1DshockSpaceConstRAND.ivs");
  
  out<<N<<endl;
  
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
  cout<<"q1DshockSpaceConstRAND.ivs is successfully written into  <<sph-blitz/cases>>\n";
}
