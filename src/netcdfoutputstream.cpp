#include <iostream>
#include <fstream>
#include "initiation.h"
#include "netcdfoutputstream.h"
#include "particle.h"
#include "polymerparticle.h"
#include "simpleparticlecommand.h"
#include "glbfunc.h"
#include "material.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif

NetCDFOutputStream::NetCDFOutputStream():
  iparticle_(0)
{
  ///open netCDF file
  Initiation* ini = Initiation::Instance();
  string timeparticlefilename_  = ini->output_dir + "/par.nc";
  if (ini->initial_condition == 0) {
    itime_ = 0;    
    nc = new NcFile(timeparticlefilename_.c_str(), 
		    NcFile::Replace); 
    assert(nc->is_valid());
    ///create dimenshions
    timestep = nc->add_dim("timestep");
    ///Fix:: add dimenshions
    Initiation* ini = Initiation::Instance();
    space = nc->add_dim("space", ini->getDim());
    const unsigned long nparticle = Particle::ID_max;
    variparticle = nc->add_dim("iparticle", nparticle);
    //  ovariparticle = timestep;
    
    ///add variables
    R = nc->add_var("R", ncDouble, timestep, 
		    variparticle, space);
    R->add_att("units", "m");
    
    U = nc->add_var("U", ncDouble, timestep, 
		    variparticle, space);
    U->add_att("units", "m/second");

    ///attache time
    NcVar* var_time = nc->add_var("t", ncDouble, timestep);    
    var_time->add_att("units", "second");

    //    nc->add_var("T", ncDouble, timestep);    
    WriteFileDescription();
  }
  else {
#ifdef DEBUG
    cout << "***Read restart file***" << '\n';
#endif
    nc = new NcFile(timeparticlefilename_.c_str(), 
		    NcFile::Write); 	
    assert(nc->is_valid());
    timestep = nc->get_dim("timestep");
    variparticle = nc->get_dim("iparticle");
    space = nc->get_dim("space");
    R = nc->get_var("R");
    U = nc->get_var("U");
    itime_ = timestep->size();
  }
  ///attache particle temperature to the output
  Command* co;
  co = new SimpleParticleCommand('T');
  AddParticleAttribute("T", co);

  ///attache a particle type to the output
  co = new SimpleParticleCommand('t');
  AddParticleAttribute("type", co);
}

NetCDFOutputStream::~NetCDFOutputStream() {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("netcdfoutputstream");
  LOG4CXX_DEBUG(Logger, "Sync file in the destructor");
#endif
  nc->sync();
}

void NetCDFOutputStream::WriteFileDescription() {
  nc->add_att("title", "SPH data file");
  nc->add_att("institution", "Institute of Aerodynamics\n"
	      "Department of Aeronautics and Aerospace\n"
	      "Technical University of Munich");
  nc->add_att("file_format_version", 2);
  nc->add_att("NParticle", PolymerParticle::nPolyParticle_);
}

void NetCDFOutputStream::VisitParticle(Particle* pa) {
  if (iparticle_ == 0) {
#ifndef NOLOG
    log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("netcdfoutputstream.particle");
    LOG4CXX_DEBUG(Logger, "VisitParticle, itime_ = " + stringify(itime_));
#endif
  }
  iparticle_++;
  Initiation* ini = Initiation::Instance();
  //Fix:: add dimensions
  const long idx[3] = {1, 1, ini->getDim()};
  Vec2d R_cur = ini->dms_R(pa->R());
  Vec2d U_cur = ini->dms_velocity(pa->U());
  //  cout << ini->dms_mass(pa->getMass()) << endl;
  //  cout << ini->dms_p(pa->getMaterial()->get_p(pa->rho())) << endl;

  R->set_cur(itime_, iparticle_-1, 0);
  U->set_cur(itime_, iparticle_-1, 0);
  if (ini->getDim() == 3) {
    double Rc[3] = {R_cur[0], R_cur[1], R_cur[2]}; 
    double Uc[3] = {U_cur[0], U_cur[1], U_cur[2]}; 
    R->put(&Rc[0], idx);
    U->put(&Uc[0], idx);
  }
  else {
    double Rc[2] = {R_cur[0], R_cur[1]};
    double Uc[2] = {U_cur[0], U_cur[1]};
    R->put(&Rc[0], idx);
    U->put(&Uc[0], idx);
  }
  WriteAllParticleAttributes(pa);
#ifndef NOLOG
  nc->sync();
#endif
  ///Fix:: 
}

void NetCDFOutputStream::VisitPolymerParticle(PolymerParticle* poly) {
  VisitParticle(poly);
#ifndef NOLOG
  nc->sync();
#endif
}



void NetCDFOutputStream::WriteTimeStepAttribute(string AttrName, 
						double AttrValue) {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("netcdfoutputstream");
  LOG4CXX_DEBUG(Logger, "WriteTimeStepAttribute, itime = " + stringify(itime_));
#endif
  NcVar* var = nc->get_var(AttrName.c_str());
  double* s = &AttrValue;
  const long idx[1] = {1};
  var->set_cur(itime_ - 1);
  var->put(s, idx);
}

void NetCDFOutputStream::WriteParticleAttribute(string AttrName, 
						double AttrValue) {
  const long idx[2] = {1, 1};
  double* val = &AttrValue;
  NcVar* var = nc->get_var(AttrName.c_str());
  var->set_cur(itime_, iparticle_-1);
  var->put(val, idx);
}

void NetCDFOutputStream::NewTimeStep() {
  ///synfronize output file 
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("netcdfoutputstream");
  LOG4CXX_DEBUG(Logger, "NewTimeStep");
#endif
  iparticle_ = 0;
  //  cout << "NewTimeStep: " << iparticle_ << endl;
  itime_++;
  // write time attributes
  WriteTimeStepAttribute("t", GetTime());
  WriteAllTimeStepAttributes();
}

void NetCDFOutputStream::Update(Subject* s) {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("netcdfoutputstream");
  LOG4CXX_DEBUG(Logger, "Update");
#endif
  OutputStream::Update(s);
  NewTimeStep();
  nc->sync();
}


void NetCDFOutputStream::Initialize() {
  ///header for time attributes file
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("netcdfoutputstream");
  LOG4CXX_DEBUG(Logger, "Initialize stream");
#endif
  Initiation* ini = Initiation::Instance();
  if (ini->initial_condition==0) {
    map<const string, Command*>::iterator theIterator;
    for( theIterator = registry_.begin(); 
	 theIterator != registry_.end(); 
	 theIterator++ ) {
      string s = theIterator->first;
      nc->add_var(s.c_str(), ncDouble, timestep);
    }    
    
    for( theIterator = pAttrRegistry_.begin(); 
	 theIterator != pAttrRegistry_.end(); 
	 theIterator++ ) {
      string s = theIterator->first;
      nc->add_var(s.c_str(), ncDouble, timestep, variparticle);
    }  
  } 
}
