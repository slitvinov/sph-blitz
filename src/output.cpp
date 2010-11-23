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
#include "glbtype.h"

using namespace std;

Output::Output() {
  LOG(INFO) << "Create Output object\n";
}

void Output::OutputParticle(const Hydrodynamics &hydro, const Boundary &boundary,
                            const double Time, const Initiation &ini, const spSolidObstacles &obstacles) {
  LOG(INFO) << "Output::OutputParticle";
  ///<ul><li>produce output file name
  
  /// create timestamp with correct unit (depending on user selection)
  double Itime;// variable for time(stamp)
  if(ini.high_res_timestamp_marker==0)//normal unit [ms]
    Itime = Time*1.0e6;
  else// high resolution unit [1e-10]
    Itime = Time*1.0e10;
  /// generate file name with leading zeros
  string file_list;
  if (ini.xxl_timestamp_marker==0)//standard timestamp of 8 digits
    file_list = boost::str(boost::format("%08d") % static_cast<int>(Itime));
  else //xxl timestamp of 12 digits
    file_list = boost::str(boost::format("%012d") % static_cast<int>(Itime));
  //assemble filename (incl. path)
  const std::string file_name = "./outdata/prtl" + file_list + ".dat";
  
  ofstream out(file_name.c_str());
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
	       << ::setw(17) <<prtl->rho_output 
	       << ::setw(17)<<prtl->mtl->get_p(prtl->rho_output,prtl->e_output)
	       << ::setw(17)<<prtl->U_output[0]
	       << ::setw(17)<<prtl->e_output
	       <<"  "<<prtl->ID
	       <<"  "<<prtl->m
	       <<"\n";
	  else
	    out<<setprecision(9)
	       << ::setw(17)<<prtl->R[0] 
	       << ::setw(17)<<prtl->R[1] 
	       << ::setw(17)<<prtl->U_output[0]
	       << ::setw(17)<<prtl->U_output[1]
	       << ::setw(17) <<prtl->rho_output 
	       << ::setw(17)<<prtl->e_output
	       << ::setw(17)<<prtl->mtl->get_p(prtl->rho_output,prtl->e_output)
	       << ::setw(17)<<ini.supportlength/2
	       <<"  "<<prtl->m
	       <<"  "<<prtl->V// up-to-date as prtl position up-to-date and V only f(R,m)
	       <<"  "<<prtl->ID
	       <<"\n";
	}
      }
    }
    //  if(ini.simu_mode==2&&ini.splash_optimized_output==1) {
    // out<<endl;
    //   out<<"Boudnary Particles"<<endl;
    
    /// <li>iterate the boundary partilce list
    if(ini.output_boundary_prtl==1) {
      BOOST_FOREACH(spParticle prtl, boundary.boundary_particle_list) {
	g++;		
	if(hydro.materials[i]->material_name == prtl->mtl->material_name) { 
	  j ++;
	  b++;
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
		 << ::setw(17) <<prtl->rho_output 
		 << ::setw(17)<<prtl->mtl->get_p(prtl->rho_output,prtl->e_output)
		 << ::setw(17)<<prtl->U[0]
		 << ::setw(17)<<prtl->e_output
	       <<"  "<<prtl->ID
		 <<"  "<<prtl->m
	       <<"\n";
	    else
	      out<<setprecision(9)
		 << ::setw(17)<<prtl->R[0] 
		 << ::setw(17)<<prtl->R[1] 
		 << ::setw(17)<<prtl->U[0]//outputvariable for U useless, unless a specil boundary condition setting method is written for this variable as well...
		 << ::setw(17)<<prtl->U[1]
		 << ::setw(17) <<prtl->rho_output 
		 << ::setw(17)<<prtl->e_output
		 << ::setw(17)<<prtl->mtl->get_p(prtl->rho_output,prtl->e_output)
		 << ::setw(17)<<ini.supportlength/2
		 <<"  "<<prtl->m
		 <<"  "<<prtl->V// up-to-date as prtl position up-to-date and V only f(R,m)
		 <<"  "<<prtl->ID
		 <<"\n";
	  }
	}
      }
    }
  }
  if (ini.simu_mode == 2&&ini.output_SolObs_Ghost_prtl==1) {
    //   out<<" --------------------------ghost particles------------"<<endl;
    BOOST_FOREACH(spParticle prtl, obstacles->ghost_prtl_SolObs_list) {
      ///\todo{be aware that values for energy, and veloctiy are not fixed for a ghst aprticle but depend on the interaction partner! therefore the output only represents the last value that has been assigned to the ghost particle}
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
	   <<"  "<<prtl->ID<<"  "<<prtl->solidObstacle_ghostParticle
	   <<"\n";
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
void Output::OutRestart(const Hydrodynamics &hydro, const double Time, const Initiation& ini, const spSolidObstacles &obstacles) {
  ///- output non-dimensional data
  std::string outputfile = ini.Project_name + ".rst";
  ofstream out(outputfile.c_str());
  
  //calculate the real particle number
  int n = 0;
  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    if(prtl->bd == 0) n ++;
  }
  BOOST_FOREACH(spParticle prtl, obstacles->ghost_prtl_SolObs_list) {
    n ++;
  }
  
  ///- out reinitiation Time
  out<<Time<<"\n";
  out<<n<<"\n";
  ///- output real particles (by iterating the particle list)
  //iterate the partilce list
  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    if(prtl->bd == 0)  {
      //if liquid mode: use liquid particle costructor, therefore output without mass
      if(ini.simu_mode==1)
	out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
	   <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
      else //if simumode==2gasdynamics mode: output including mass
	out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]<<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  "<<prtl->m<<"  \n";
    }
  }
  //also output ghost particles for solid obstacles
 BOOST_FOREACH(spParticle prtl, obstacles->ghost_prtl_SolObs_list) {
   {
     //if liquid mode: use liquid particle costructor, therefore output without mass
     if(ini.simu_mode==1)
       out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
	  <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
     else //if simumode==2gasdynamics mode: output including mass
       out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]<<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  "<<prtl->m<<"  \n";
   }
 }
 out.close();
}
