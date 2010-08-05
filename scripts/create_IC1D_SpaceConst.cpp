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
  double domain_size=2.0;
  double m_l=0;
  double m_r=0;
  double dx=0.005;
  int N_r=0;
  int N_l=0;
  int N=0;

  //reading characteristic data for shock tube problem from file 1DST.dat
  ifstream fin(inputfile, ios::in);
  if (!fin)
  {
    cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
    exit(1);
  }
  else cout<<"Creating initial condition file 1DShockSpaceConst.ivs ( purely 1D particle distribution with constant particle spacing) from initial conditions specified in "<< inputfile <<" \n"; 

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

  m_l=rhol*dx;
  m_r=rhor*dx;
  N_r=domain_size/2/dx+2;
  N_l=domain_size/2/dx+1;
  N=N_l+N_r;
  double x_array[N];
  double y_array[N];
  double vx_array[N];
  double vy_array[N];
  double p_array[N];
  double rho_array[N];
  double m_array[N];

  x=2-N_l*dx;

  for(int i=0;i<N_l;i++)
  {
       x_array[i]=x;
       x=x+dx;
       y_array[i]=0;
       vx_array[i]=vl;
       vy_array[i]=0;
       p_array[i]=pl;
       rho_array[i]=rhol;
       m_array[i]=m_l;
  };
  x=2;
 for(int i=N_l;i<N;i++)
 {
       x_array[i]=x;
       x=x+dx;
       y_array[i]=0;
       vx_array[i]=vr;
       vy_array[i]=0;
       p_array[i]=pr;
       rho_array[i]=rhor;
       m_array[i]=m_r;
 };  

 ofstream out("../cases/1DshockSpaceConst.ivs");

 out<<N<<endl;

for(int i=0;i<N;i++)
   {
     out <<setprecision (8)<<"  "<<x_array[i]<<"  "<<y_array[i]<<"   "<<vx_array[i]<<"   "<<vy_array[i]<<"   "<<rho_array[i]<<"   "<<p_array[i]<<"  "<<m_array[i]<<endl;
   };

 out.close();
 cout<<"1DshockSpaceConst.ivs successfully written in <<sph-blitz/cases>>\n";
}
