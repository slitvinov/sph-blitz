#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <assert.h>

using namespace std;

int main ()
{
  //double m=0.00001875;
  const char inputfile[25]="1DST.dat";
  char Key_word[125];
  double vl=0,vr=0,pl=0,pr=0,rhol=0,rhor=0,ml=0,mr=0;
  double x=0;
  const double domain_size_x=2.0;
  const double domain_size_y=0.03;//should correspond to suport length
  double dx,dy;
  int N_rx, N_lx, N_ry, N_ly;
  
  //reading characteristic data for shock tube problem from file 1DST.dat
  ifstream fin(inputfile, ios::in);
  if (!fin)
  {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"Creating initial condition file q1DShockSpaceConst.ivs (2D particle distribution with constant spacing) from initial vaules specified in"<< inputfile <<" \n"; 

  //reading key words and configuration data from configuration file and assign them to the appropriate variable
  while(!fin.eof())
  {
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

   //here constant spacing !!dx must be chosen in a way that h is multiple of it (here: e.g. dx= 0.005,0.01,...)
   dx=0.005;
     dy=dx;
   cout<<"dx=dy="<<dx<<endl;

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

  for(int j=0;j<N_ly;j++)
    {
      x=2-N_lx*dx;
      for(int i=j*N_lx;i<(j+1)*N_lx;i++)
	{
	  x_array[i]=x;
	  x=x+dx;
	  y_array[i]=(j+0.5)*dy;
	  vx_array[i]=vl;
	  vy_array[i]=0;
	  p_array[i]=pl;
	  rho_array[i]=rhol;
	  m_array[i]=ml;
	  
	};
    }
 for(int j=0;j<N_ry;j++)
   {
      x=2;
      for(int i=N_lx*N_ly+j*N_rx;i<N_lx*N_ly+(j+1)*N_rx;i++)
	{
	  x_array[i]=x;
	  x=x+dx;
	  y_array[i]=(j+0.5)*dy;
	  vx_array[i]=vr;
	  vy_array[i]=0;
	  p_array[i]=pr;
	  rho_array[i]=rhor;
	  m_array[i]=mr;
	  
	};  
    }


ofstream out("../cases/q1DshockSpaceConst.ivs");

 out<<N<<endl;

for(int i=0;i<N;i++)
   {
     out <<setprecision (6)<<"  "<<x_array[i]<<"  "<<y_array[i]<<"   "<<vx_array[i]<<"   "<<vy_array[i]<<"   "<<rho_array[i]<<"   "<<p_array[i]<<"  "<<m_array[i]<<endl;
   };

 out.close();
 cout<<"q1DshockSpaceConst.ivs is successfully written into  <<sph-blitz/cases>>\n";
}
