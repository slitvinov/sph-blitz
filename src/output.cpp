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

#include <glog/logging.h>

// ***** localincludes *****
#include "glbfunc.h"
#include "material.h"
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "output.h"
#include "initiation.h"
#include "boundary.h"

#include <boost/format.hpp>

using namespace std;

//--------------------------------------------------------------------------------------------
//									constructor
//--------------------------------------------------------------------------------------------
Output::Output()
{
}
//--------------------------------------------------------------------------------------------
//				output particle positions respected different materials
//--------------------------------------------------------------------------------------------
void Output::OutputParticle(Hydrodynamics &hydro, Boundary &boundary, 
			     double Time, const Initiation &ini)
{
  ///<ul><li>produce output file name
  const double Itime = Time*1.0e6;

  /// generate file name with leading zeros
  const std::string file_list = boost::str(boost::format("%08d") % static_cast<int>(Itime));
  const std::string file_name = "./outdata/prtl" + file_list + ".dat";

  ofstream out(file_name.c_str());
  ///<li>defining header for tecplot(plot software)
  out<<"title='particle position' \n";
  if( ini.simu_mode==1)
    out<<"variables=x, y, Ux, Uy \n";
  if (ini.simu_mode==2)
    out<<"variables=x, y, rho, p, U, e \n";
  int f=0, g=0, a=0, b=0; 	
  ///<li>output real and soild particles
  for(int i = 0; i < ini.number_of_materials; i++) {
    f=0; g=0; a=0; b=0;	
    int j = 0; //if there is such material or not
    ///<ul><li>iterate the real partilce list
    for (std::list<spParticle >::const_iterator p = hydro.particle_list.begin(); 
	 p != hydro.particle_list.end(); 
	 p++) {
      f++;
      spParticle prtl = *p;
       assert(prtl != NULL);
       assert(prtl->mtl != NULL);
       if(hydro.materials[i]->material_name == prtl->mtl->material_name) {
	 j ++;
	 a++;
	 if( ini.simu_mode == 1) {
	   if(j == 1)  {
	     out<<"zone t='"<<hydro.materials[i]->material_name<<"' \n";
	   }
	   out<<prtl->R[0]<<"  "<<prtl->R[1]
	      <<"  "<<prtl->U[0]<<"  "<<prtl->U[1]<<"\n";
	 }
	if (ini.simu_mode == 2)
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
    for (std::list<spParticle >::const_iterator p1 = boundary.boundary_particle_list.begin(); 
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
  LOG(INFO)<<"output particle method successfully executed for time"<<Time;
  LOG(INFO)<<"particles on real  particle list  "<<f;
  LOG(INFO)<<"particles on real  particle list with same mat name "<<a;
  LOG(INFO)<<"particles on boundary  particle list "<<g;
  LOG(INFO)<<"particles on boundary  particle list with same mat name "<<b;
}

//--------------------------------------------------------------------------------------------
//		Output real particle data for restart the computation
//--------------------------------------------------------------------------------------------
void Output::OutRestart(Hydrodynamics &hydro, double Time, const Initiation& ini)
{
  std::string outputfile;

  ///- output non-dimensional data
  outputfile = ini.Project_name + ".rst";
  ofstream out(outputfile.c_str());

  //calculate the real particle number
  int n = 0;
  for (std::list<spParticle >::const_iterator pp = hydro.particle_list.begin(); 
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
  for (std::list<spParticle >::const_iterator p = hydro.particle_list.begin(); 
       p != hydro.particle_list.end(); 
       p++) {
				
    spParticle prtl = *p;
    if(prtl->bd == 0) 
      out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
	 <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
  }
  out.close();
}
