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
  double m=1.73611111111111111e-5;
  char inputfile[25]="1DST.dat";
  char Key_word[125];
  double vl=0,vr=0,pl=0,pr=0,rhol=0,rhor=0;
  double x=0;
  double domain_size_x=2.0;
  double domain_size_y=0.025;//should correspond to suport length
  double pert_x=0;// perturbation
  double pert_y=0;// perturbation
  double sum_pert_x=0;// to control if mean is equal (or at least around) 0
  double sum_pert_y=0;// to control if mean is equal (or at least around) 0
  double dx_l,dx_r,dy_l,dy_r;
  int N_rx, N_lx, N_x,N_y,N_l,N_r;
  int N_ry,N_ly;
  
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

  
  //reading characteristic data for shock tube problem from file 1DST.dat
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"Creating initial condition file q1DShockMConst.ivs from initial conditions specified in "<< inputfile <<" \n"; 
  
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
  
  dx_l=sqrt(m/rhol);
  dy_l=dx_l;
  cout<<"dx_l=dyl="<<dx_l<<endl;
  dx_r=sqrt(m/rhor);
  dy_r=dx_r;
  cout<<"dx_r=dyl="<<dx_r<<endl;
  N_rx=domain_size_x/2/dx_r+1;
  cout<<"N_rx"<<N_rx<<endl;
  N_lx=domain_size_x/2/dx_l;
  cout<<"N_lx"<<N_lx<<endl;
  N_ry=domain_size_y/dy_r;
  cout<<"N_ry"<<N_ry<<endl;
  N_ly=domain_size_y/dy_l;
  cout<<"N_ly"<<N_ly<<endl;
  
  int N;
  N=N_lx*N_ly+N_rx*N_ry;
  cout<<"N"<<N<<endl;
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  
  for(int j=0;j<N_ly;j++) {
    x=2-N_lx*dx_l;
    for(int i=j*N_lx;i<(j+1)*N_lx;i++) {
      // create random perturbation
      
      // as random numbers are generated as integers in a range from -200 to 200
      // they have to be divided by a factor to obtain the desired range
      
      pert_x = (rand() % 401 -200)/200.0*dx_l*fac;
      pert_y = (rand() % 401 -200)/200.0*dy_l*fac;
      //cout<<pert_x<<endl;
      sum_pert_x=sum_pert_x+pert_x;
      sum_pert_y=sum_pert_y+pert_y;
      
      x_array[i]=x+pert_x;
      x=x+dx_l;
      y_array[i]=(j+0.5)*dy_l+pert_y;
      vx_array[i]=vl;
      vy_array[i]=0;
      p_array[i]=pl;
      rho_array[i]=rhol;
    };
  };
  for(int j=0;j<N_ry;j++) {
    x=2;
    for(int i=N_lx*N_ly+j*N_rx;i<N_lx*N_ly+(j+1)*N_rx;i++) {

      // create random perturbation
      
      // as random numbers are generated as integers in a range from -200 to 200
      // they have to be divided by a factor to obtain the desired range
      
      pert_x = (rand() % 401 -200)/200.0*dx_r*fac;
      pert_y = (rand() % 401 -200)/200.0*dy_r*fac;
      //cout<<pert_x<<endl;
      sum_pert_x=sum_pert_x+pert_x;
      sum_pert_y=sum_pert_y+pert_y;
      
      x_array[i]=x+pert_x;
      x=x+dx_r;
      y_array[i]=(j+0.5)*dy_r+pert_y;
      vx_array[i]=vr;
      vy_array[i]=0;
      p_array[i]=pr;
      rho_array[i]=rhor;
    };  
  };
  
  //output for user information
  cout<<endl<<"sum (=integral value) of perturbations in x direction:  "
      <<sum_pert_x<<endl;
  cout<<endl<<"mean value of perturbations in x direction:  "
      <<sum_pert_x/N<<endl;
  
  cout<<endl<<"sum (=integral value) of perturbations in y direction:  "
      <<sum_pert_y<<endl;
  cout<<endl<<"mean value of perturbations in y direction:  "
      <<sum_pert_y/N<<endl;
  
    ofstream out("../../cases/q1DshockMConstRAND.ivs");
  
  out<<N<<endl;
  
  for(int i=0;i<N;i++) {
    out <<setprecision (6)
	<<"  "<<x_array[i]
	<<"  "<<y_array[i]
	<<"  "<<vx_array[i]
	<<"  "<<vy_array[i]
	<<"  "<<rho_array[i]
	<<"  "<<p_array[i]
	<<"  "<<m<<endl;
  };
  
  out.close();
  cout<<"q1DshockMConstRAND.ivs is successfully written in <<sph-blitz/cases>> \n \n";
}
