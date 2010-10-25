/// \file plainouput.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
#include <fstream>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <glog/logging.h>
// ***** localincludes *****
#include "src/hydrodynamics.h"
#include "src/particlemanager.h"
#include "src/Output/plainoutput.h"
#include "src/initiation.h"
#include "src/boundary.h"
#include "src/ParticleContext/particlecontext.h"

PlainOutput::PlainOutput():
  isFirst(true) {
  LOG(INFO) << "Create PlainOutput object\n";
}

void PlainOutput::OutputParticle(const Hydrodynamics &hydro, const Boundary &boundary,
				 const double Time, const Initiation &ini) {

  ///<ul><li>produce output file name
  const double Itime = Time*ini.output_file_format_factor;

  /// generate file name with leading zeros
  const std::string file_list = boost::str(boost::format("%08d") % static_cast<int>(Itime));
  const std::string file_name = ini.outdir + "/prtl" + file_list + ".dat";
  std::cerr << "Write snapshot to " << file_name << '\n';

  std::ofstream out(file_name.c_str());
  if (!out.is_open()) {
    LOG(ERROR) << "Cannot open file: " << file_name;
    exit(EXIT_FAILURE);
  }

  const std::string timefilename = ini.outdir + "/time.dat";
  std::ofstream timef;
  if (isFirst) {
    timef.open(timefilename.c_str());
    isFirst = false;
  } else {
    timef.open(timefilename.c_str(), std::ios::app);
  }
  if (!timef.is_open()) {
    LOG(ERROR) << "Cannot open file: " << file_name;
    exit(EXIT_FAILURE);
  }
  timef << Time << ' ' << file_name << '\n';
  LOG(INFO) << "writing time and related file name to: " << timefilename;
  timef.close();

  BOOST_FOREACH(spParticle prtl, hydro.particle_list) {
    PrintOneParticle(prtl, ini, out);
  }

  BOOST_FOREACH(spParticle prtl, boundary.boundary_particle_list) {
    PrintOneParticle(prtl, ini, out);
  }
  out.close();
}

PlainOutput::~PlainOutput() {
}

void PlainOutput::PrintOneParticle(spParticle prtl, const Initiation& ini, std::ostream& o) {
  o << prtl->R[0] << "  " << prtl->R[1]
    << "  " << prtl->rho << " " << prtl->m 
    << "  " << prtl->U[0] << "  " << prtl->U[1] 
    << "  " << prtl->dUdt[0] << "  " << prtl->dUdt[1] 
    << "  " << ini.context->ContextID(prtl)
    << "  " << prtl->e << '\n';
}
