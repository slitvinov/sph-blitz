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
#include "src/Output/output.h"
#include "src/initiation.h"
#include "src/boundary.h"
#include "src/ParticleContext/particlecontext.h"

using namespace std;

Output::Output() {
  LOG(INFO) << "Create Output object\n";
}


//--------------------------------------------------------------------------------------------
//		Output real particle data for restart the computation
//--------------------------------------------------------------------------------------------
void Output::OutputRestart(const Hydrodynamics &hydro, const double Time, const Initiation& ini) {
  ///- output non-dimensional data
  std::string outputfile = ini.Project_Name + ".rst";
  ofstream out(outputfile.c_str());

  //calculate the real particle number
  int n = 0;
  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    if (prtl->bd == 0) n++;
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

Output::~Output() {
  
}
