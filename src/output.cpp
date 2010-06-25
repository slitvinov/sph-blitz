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
#include "glbcls.h"
#include "glbfunc.h"
#include "material.h"

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
void Output::OutputParticles(Hydrodynamics &hydro, Boundary &boundary, 
			     double Time, Initiation &ini)
{
  int i, j;
  double Itime;
  char file_name[50], file_list[11];

  ///<ul><li>produce output file name
  Itime = ini.dms_time(Time)*1.0e6;
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
    for (LlistNode<Particle> *p = hydro.particle_list.first(); 
	 !hydro.particle_list.isEnd(p); 
	 p = hydro.particle_list.next(p)) {
      f++;
       Particle *prtl = hydro.particle_list.retrieve(p);
      if(strcmp(hydro.materials[i].material_name, prtl->mtl->material_name) == 0) {
	j ++;
	a++;
	if( simu_mode == 1)
	{ 
	  if(j == 1) 
	    	out<<"zone t='"<<hydro.materials[i].material_name<<"' \n";
	      out<<ini.dms_length(prtl->R[0])<<"  "<<ini.dms_length(prtl->R[1])
		 <<"  "<<ini.dms_velocity(prtl->U[0])<<"  "<<ini.dms_velocity(prtl->U[1])<<"\n";
	   
	}
	if (simu_mode == 2)
	  out<<setprecision(6)
	     << ::setw(16)<<ini.dms_length(prtl->R[0]) 
	     << ::setw(16)<<ini.dms_length(prtl->R[1]) 
	     << ::setw(16) <<ini.dms_length(prtl->rho) 
	     << ::setw(16)<<ini.dms_velocity(prtl->p)
	     << ::setw(16)<<ini.dms_velocity(prtl->U[0])
	     << ::setw(16)<<ini.dms_velocity(prtl->e)
	     <<"  "<<prtl->ID<<"\n";
      }
    }

    /// <li>iterate the boundary partilce list
    for (LlistNode<Particle> *p1 = boundary.boundary_particle_list.first(); 
	 !boundary.boundary_particle_list.isEnd(p1); 
	 p1 = boundary.boundary_particle_list.next(p1)) {
      g++;		
      Particle *prtl = boundary.boundary_particle_list.retrieve(p1);
      if(strcmp(hydro.materials[i].material_name, prtl->mtl->material_name) == 0) { 
	j ++;
	b++;
	if(j == 1) 	out<<"zone t='"<<hydro.materials[i].material_name<<"' \n";
	out<<ini.dms_length(prtl->R[0])<<"  "<<ini.dms_length(prtl->R[1])
	   <<"  "<<ini.dms_velocity(prtl->U[0])<<"  "<<ini.dms_velocity(prtl->U[1])<<"\n";
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
  for (LlistNode<Particle> *pp = hydro.particle_list.first(); 
       !hydro.particle_list.isEnd(pp); 
       pp = hydro.particle_list.next(pp)) {
			
    Particle *prtl = hydro.particle_list.retrieve(pp);
    if(prtl->bd == 0) n ++;
						
  }
  ///- out reinitiation Time
  out<<Time<<"\n";
  out<<n<<"\n";
  ///- output real particles (by iterating the particle list)
  //iterate the partilce list
  for (LlistNode<Particle> *p = hydro.particle_list.first(); 
       !hydro.particle_list.isEnd(p); 
       p = hydro.particle_list.next(p)) {
				
    Particle *prtl = hydro.particle_list.retrieve(p);
    if(prtl->bd == 0) 
      out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
	 <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
  }
  out.close();
}
//--------------------------------------------------------------------------------------------
//					creat a head file for a movie of particle motion
//--------------------------------------------------------------------------------------------
void Output::CreatParticleMovie()
{
  char file_name[50];
  //produce output file name
  strcpy(file_name,"./outdata/prtl_movie.dat");

  ofstream out(file_name);
  out<<"title='particle movie' \n";
  out<<"variables=x, y, material, size \n";

  out.close();

}
//--------------------------------------------------------------------------------------------
//						write the data for a movie of particle motion
//						output the real and wall particles
//--------------------------------------------------------------------------------------------
void Output::WriteParticleMovie(Hydrodynamics &hydro, double Time, Initiation &ini)
{
  int k, m;
  char file_name[50];

  ///- produce output file name
  strcpy(file_name,"./outdata/prtl_movie.dat");

  ofstream out(file_name, ios::out | ios::ate);
  //zone names
  out<<"zone t='"<<ini.dms_time(Time)<<"' \n";
  ///- iterate the partilce list
  for (LlistNode<Particle> *p = hydro.particle_list.first(); 
       !hydro.particle_list.isEnd(p); 
       p = hydro.particle_list.next(p)) {
			
    Particle *prtl = hydro.particle_list.retrieve(p);
    m = -1;
    //find the number of the material
    for(k = 0;  k < number_of_materials; k++) 
      if(strcmp(prtl->mtl->material_name, hydro.materials[k].material_name) == 0) m = k;
    out<<ini.dms_length(prtl->R[0])<<"  "<<ini.dms_length(prtl->R[1])
       <<"  "<<m<<"  "<<ini.dms_rho(prtl->rho)<<"\n";
  }
  out.close();

}
