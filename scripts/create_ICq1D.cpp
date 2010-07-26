#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main ()
{

  char inputfile[25]="1DST.dat";
  char Key_word[125];
  double vl=0,vr=0,pl=0,pr=0,rhol=0,rhor=0;
  double x=0;
  double domain_size_x=2.0;
  double domain_size_y=0.03;
  double delta_l=0.001875;
  double delta_r=0.001875*8;
  double m=0.001875;
  int N_rx;
  N_rx=domain_size_x/2/delta_r+1;
  int  N_lx;
  N_lx=domain_size_x/2/delta_l;
  int N_x;
  int N_y;
  N_x=N_lx+N_rx;
  double dy=delta_r;
  N_y=domain_size_y/dy;
  int N=N_y*N_x;
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];

  //reading characteristic data for shock tube problem from file 1DST.dat
  ifstream fin(inputfile, ios::in);
  if (!fin)
  {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"Creating initial condition file 2DShock.ivs"<< inputfile <<" \n"; 

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

  
  for(int j=0;j<N_y;j++)
    {
      x=2-N_lx*delta_l;
      for(int i=j*N_x;i<(j*N_x+N_lx);i++)
	{
	  x_array[i]=x;
	  x=x+delta_l;
	  y_array[i]=(j+0.5)*dy;
	  vx_array[i]=vl;
	  vy_array[i]=0;
	  p_array[i]=pl;
	  rho_array[i]=rhol;
      
	};
      x=2;
      for(int i=(j*N_x+N_lx);i<((j+1)*N_x);i++)
	{
	  x_array[i]=x;
	  x=x+delta_r;
	  y_array[i]=(j+0.5)*dy;
	  vx_array[i]=vr;
	  vy_array[i]=0;
	  p_array[i]=pr;
	  rho_array[i]=rhor;
	};  
    }

ofstream out("q1Dshock.ivs");

 out<<N<<endl;

for(int i=0;i<N;i++)
   {
     out <<setprecision (6)<<"  "<<x_array[i]<<"  "<<y_array[i]<<"   "<<vx_array[i]<<"   "<<vy_array[i]<<"   "<<rho_array[i]<<"   "<<p_array[i]<<"  "<<m<<endl;
   };

 out.close();
}
