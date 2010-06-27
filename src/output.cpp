/// \file output.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Output the computational results
//		output.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbfunc.h"
#include "material.h"
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "output.h"
#include "initiation.h"
#include "boundary.h"

using namespace std;

//--------------------------------------------------------------------------------------------
//									constructor
//--------------------------------------------------------------------------------------------
Output::Output(Initiation &ini)
{
  ///copy boundary properties from initiation class
  strcpy(Project_name, ini.Project_name);
  number_of_materials = ini.number_of_materials;
  x_cells = ini.x_cells; y_cells = ini.y_cells;
  simu_mode=ini.simu_mode;
  hdelta = ini.hdelta; 
  delta = ini.delta;
  cout<<"\n Output class object sussessfully constructed! \n"; 
}
//--------------------------------------------------------------------------------------------
//				output particle positions respected different materials
//--------------------------------------------------------------------------------------------
void Output::OutputParticle(Hydrodynamics &hydro, Boundary &boundary, 
			     double Time, Initiation &ini)
{
  int i, j;
  double Itime;
  char file_name[50], file_list[11];

  ///<ul><li>produce output file name
  Itime = Time*1.0e6;
  strcpy(file_name,"./outdata/prtl");
  sprintf(file_list, "%.10d", (int)Itime);
  strcat(file_name, file_list);
  strcat(file_name, ".dat");

  ofstream out(file_name);
  ///<li>defining header for tecplot(plot software)
  out<<"title='particle position' \n";
  if( simu_mode==1)
    out<<"variables=x, y, Ux, Uy \n";
  if (simu_mode==2)
    out<<"variables=x, y, rho, p, U, e \n";
  int f=0, g=0, a=0, b=0; 	
  ///<li>output real and soild particles
  for(i = 0; i < number_of_materials; i++) {
    f=0; g=0; a=0; b=0;	
    j = 0; //if there is such material or not
    ///<ul><li>iterate the real partilce list
    for (std::list<spParticle >::iterator p = hydro.particle_list.begin(); 
	 p != hydro.particle_list.end(); 
	 p++) {
      f++;
      spParticle prtl = *p;
       assert(prtl != NULL);
       assert(prtl->mtl != NULL);
       if(hydro.materials[i]->material_name == prtl->mtl->material_name) {
	 j ++;
	 a++;
	 if( simu_mode == 1) {
	   if(j == 1)  {
	     out<<"zone t='"<<hydro.materials[i]->material_name<<"' \n";
	   }
	   out<<prtl->R[0]<<"  "<<prtl->R[1]
	      <<"  "<<prtl->U[0]<<"  "<<prtl->U[1]<<"\n";
	 }
	if (simu_mode == 2)
	  out<<setprecision(6)
	     << ::setw(16)<<prtl->R[0] 
	     << ::setw(16)<<prtl->R[1] 
	     << ::setw(16) <<prtl->rho 
	     << ::setw(16)<<prtl->p
	     << ::setw(16)<<prtl->U[0]
	     << ::setw(16)<<prtl->e
	     <<"  "<<prtl->ID<<"\n";
      }
    }

    /// <li>iterate the boundary partilce list
    for (std::list<spParticle >::iterator p1 = boundary.boundary_particle_list.begin(); 
	 p1 != boundary.boundary_particle_list.end(); 
	 p1++) {
      g++;		
      spParticle prtl = *p1;
      if(hydro.materials[i]->material_name == prtl->mtl->material_name) { 
	j ++;
	b++;
	if(j == 1) 	out<<"zone t='"<<hydro.materials[i]->material_name<<"' \n";
	out<<prtl->R[0]<<"  "<<prtl->R[1]
	   <<"  "<<prtl->U[0]<<"  "<<prtl->U[1]<<"\n";
      }
    }
  }
  cout<<"\n output particle method successfully executed for time"<<Time<<"\n";
 cout<<"\n particles on real  particle list\n "<<f;
 cout<<"\n particles on real  particle list with same mat name\n "<<a;
cout<<"\n particles on boundary  particle list\n "<<g;
 cout<<"\n particles on boundary  particle list with same mat name\n "<<b;
}

//--------------------------------------------------------------------------------------------
//		Output real particle data for restart the computation
//--------------------------------------------------------------------------------------------
void Output::OutRestart(Hydrodynamics &hydro, double Time)
{
  int n;
  char outputfile[25];

  ///- output non-dimensional data
  strcpy(outputfile, Project_name);
  strcat(outputfile,".rst");
  ofstream out(outputfile);

  //calculate the real particle number
  n = 0;
  for (std::list<spParticle >::iterator pp = hydro.particle_list.begin(); 
       pp != hydro.particle_list.end(); 
       pp++) {
			
    spParticle prtl = *pp;
    if(prtl->bd == 0) n ++;
						
  }
  ///- out reinitiation Time
  out<<Time<<"\n";
  out<<n<<"\n";
  ///- output real particles (by iterating the particle list)
  //iterate the partilce list
  for (std::list<spParticle >::iterator p = hydro.particle_list.begin(); 
       p != hydro.particle_list.end(); 
       p++) {
				
    spParticle prtl = *p;
    if(prtl->bd == 0) 
      out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
	 <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
  }
  out.close();
}
