/// \file output.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <glog/logging.h>
// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "output.h"
#include "initiation.h"
#include "boundary.h"

using namespace std;

Output::Output() {
  LOG(INFO) << "Create Output object\n";
}

void Output::OutputParticle(const Hydrodynamics &hydro, const Boundary &boundary,
                            const double Time, const Initiation &ini) {
  LOG(INFO) << "Output::OutputParticle";
  ///<ul><li>produce output file name
  const double Itime = Time*1.0e6;

  /// generate file name with leading zeros
  const std::string file_list = boost::str(boost::format("%08d") % static_cast<int>(Itime));
  const std::string file_name = ini.outdir + "/prtl" + file_list + ".dat";

  ofstream out(file_name.c_str());
  if (!out.is_open()) {
    LOG(INFO) << "Cannot open file: " << file_name;
    exit(EXIT_FAILURE);
  }
  /// check if file is OK
  

  ///<li>defining header for tecplot(plot software)
  out<<"title='particle position' \n";
  if( ini.simu_mode==1)
    out<<"variables=x, y, Ux, Uy rho\n";
  if (ini.simu_mode==2) {
    if (ini.splash_optimized_output==0)
      out<<"variables=x, y, rho, p, Ux, e, ID, m \n";
    else 
      out<<"variables=x, y, Ux, Uy, rho, e, p, h=supportlength/2, m, V, ID \n";
  }
  int f=0, g=0, a=0, b=0; 	
  ///<li>output real and solid particles
  for(int i = 0; i < ini.number_of_materials; i++) {
    f=0; g=0; a=0; b=0;	
    int j = 0; //if there is such material or not
    ///<ul><li>iterate the real particle list
    BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
      f++;
      assert(prtl != NULL);
      assert(prtl->mtl != NULL);
      if(hydro.materials[i]->material_name == prtl->mtl->material_name) {
        j ++;
        a++;
        if( ini.simu_mode == 1) {
          if(j == 1)  {
            out<<"zone t='"<<hydro.materials[i]->material_name<<"' \n";
          }
          out << prtl->R[0] << "  " << prtl->R[1]
	      << "  " << prtl->U[0] << "  " << prtl->U[1]
	      << "  " << prtl->rho << '\n';
        }
	if (ini.simu_mode == 2) {
	  if (ini.splash_optimized_output==0)
	    out<<setprecision(9)
	       << ::setw(17)<<prtl->R[0] 
	       << ::setw(17)<<prtl->R[1] 
	       << ::setw(17) <<prtl->rho 
	       << ::setw(17)<<prtl->p
	       << ::setw(17)<<prtl->U[0]
	       << ::setw(17)<<prtl->e
	       <<"  "<<prtl->ID
	       <<"  "<<prtl->m
	       <<"\n";
	  else
	    out<<setprecision(9)
	       << ::setw(17)<<prtl->R[0] 
	       << ::setw(17)<<prtl->R[1] 
	       << ::setw(17)<<prtl->U[0]
	       << ::setw(17)<<prtl->U[1]
	       << ::setw(17) <<prtl->rho 
	       << ::setw(17)<<prtl->e
	       << ::setw(17)<<prtl->p
	       << ::setw(17)<<ini.supportlength/2
	       <<"  "<<prtl->m
	       <<"  "<<prtl->V
	       <<"  "<<prtl->ID
	       <<"\n";
	}
      }
    }
    // if(ini.simu_mode==2&&ini.splash_optimized_output==1) {
    //   out<<endl;
    //   out<<"Boudnary Particles"<<endl;
    // }

    /// <li>iterate the boundary partilce list
    BOOST_FOREACH(spParticle prtl, boundary.boundary_particle_list) {
      g++;		
      if(hydro.materials[i]->material_name == prtl->mtl->material_name) { 
	j ++;
	b++;
	if( ini.simu_mode == 1) {
	  if(j == 1)  {
	    //out<<"zone t='"<<hydro.materials[i]->material_name<<"' \n";
	  }
	  //out << prtl->R[0] << "  " << prtl->R[1]
	  //    << "  " << prtl->U[0] << "  " << prtl->U[1]
	  //    << "  " << prtl->rho << '\n';
	}
	if (ini.simu_mode == 2) {
	  if (ini.splash_optimized_output==0)
	    out<<setprecision(9)
	       << ::setw(17)<<prtl->R[0] 
	       << ::setw(17)<<prtl->R[1] 
	       << ::setw(17) <<prtl->rho 
	       << ::setw(17)<<prtl->p
	       << ::setw(17)<<prtl->U[0]
	       << ::setw(17)<<prtl->e
	       <<"  "<<prtl->ID
	       <<"  "<<prtl->m
	       <<"\n";
	  else
	    out<<setprecision(9)
	       << ::setw(17)<<prtl->R[0] 
	       << ::setw(17)<<prtl->R[1] 
	       << ::setw(17)<<prtl->U[0]
	       << ::setw(17)<<prtl->U[1]
	       << ::setw(17) <<prtl->rho 
	       << ::setw(17)<<prtl->e
	       << ::setw(17)<<prtl->p
	       << ::setw(17)<<ini.supportlength/2
	       <<"  "<<prtl->m
	       <<"  "<<prtl->V
	       <<"  "<<prtl->ID
	       <<"\n";
	}
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
void Output::OutRestart(const Hydrodynamics &hydro, const double Time, const Initiation& ini) {
  ///- output non-dimensional data
  std::string outputfile = ini.Project_name + ".rst";
  ofstream out(outputfile.c_str());

  //calculate the real particle number
  int n = 0;
  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    if(prtl->bd == 0) n ++;
  }

  ///- out reinitiation Time
  out<<Time<<"\n";
  out<<n<<"\n";
  ///- output real particles (by iterating the particle list)
  //iterate the partilce list
  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    if(prtl->bd == 0)  {
      out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
	 <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
    }
  }
  out.close();
}
