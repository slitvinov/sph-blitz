/// \file output.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
/// \author changes by: Sergey Litvinov <slitvinov@gmail.com>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <glog/logging.h>
// ***** localincludes *****
#include "src/hydrodynamics.h"
#include "src/particlemanager.h"
#include "src/Output/tecplotoutput.h"
#include "src/initiation.h"
#include "src/boundary.h"
#include "src/ParticleContext/particlecontext.h"

using namespace std;

TecplotOutput::TecplotOutput() {
  LOG(INFO) << "Create TecplotOutput object\n";
}

void TecplotOutput::OutputParticle(const Hydrodynamics &hydro, const Boundary &boundary,
                            const double Time, const Initiation &ini) {
  std::cerr << "Output::OutputParticle\n";
  ///<ul><li>produce output file name
  const double Itime = Time*ini.output_file_format_factor;

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
  if (ini.simu_mode==1)
    out<<"variables=x, y, Ux, Uy, Fx, Fy, contextID, rho\n";
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
      if (hydro.materials[i]->material_name == prtl->mtl->material_name) {
        j ++;
        a++;
        if (ini.simu_mode == 1) {
          if (j == 1)  {
            out<<"zone t='"<<hydro.materials[i]->material_name<<"' \n";
          }
          out << prtl->R[0] << "  " << prtl->R[1]
	      << "  " << prtl->U[0] << "  " << prtl->U[1] 
	      << "  " << prtl->dUdt[0] << "  " << prtl->dUdt[1] 
	      << "  " << ini.context->ContextID(prtl)
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

    /// <li>iterate the boundary partilce list
    BOOST_FOREACH(spParticle prtl, boundary.boundary_particle_list) {
      g++;		
      if (hydro.materials[i]->material_name == prtl->mtl->material_name) { 
	j ++;
	b++;
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
  out.close();
  LOG(INFO)<<"output particle method successfully executed for time"<<Time;
  LOG(INFO)<<"particles on real  particle list  "<<f;
  LOG(INFO)<<"particles on real  particle list with same mat name "<<a;
  LOG(INFO)<<"particles on boundary  particle list "<<g;
  LOG(INFO)<<"particles on boundary  particle list with same mat name "<<b;
}

TecplotOutput::~TecplotOutput() {
}
