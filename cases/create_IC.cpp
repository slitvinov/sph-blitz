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
  double delta_l=0.001875;
  double delta_r=0.001875*8;
  int N_r;
  N_r=domain_size/2/delta_r+1;
  int  N_l;
  N_l=domain_size/2/delta_l;
  int N;
  N=N_l+N_r;
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
  else cout<<"Creating initial condition file 1DShock.ivs"<< inputfile <<" \n"; 

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

  x=2-N_l*delta_l;

  for(int i=0;i<N_l;i++)
  {
       x_array[i]=x;
       x=x+delta_l;
       y_array[i]=0;
       vx_array[i]=vl;
       vy_array[i]=0;
       p_array[i]=pl;
       rho_array[i]=rhol;
      
  };
  x=2;
 for(int i=N_l;i<N;i++)
 {
       x_array[i]=x;
       x=x+delta_r;
       y_array[i]=0;
       vx_array[i]=vr;
       vy_array[i]=0;
       p_array[i]=pr;
       rho_array[i]=rhor;
 };  

ofstream out("1Dshock.ivs");

 out<<N<<endl;

for(int i=0;i<N;i++)
   {
      out <<setprecision (6)<<"  "<<x_array[i]<<"  "<<y_array[i]<<"   "<<vx_array[i]<<"   "<<vy_array[i]<<"   "<<rho_array[i]<<"   "<<p_array[i]<<endl;
   };

 out.close();
}
