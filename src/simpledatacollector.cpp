#include "simpledatacollector.h"
#include "polymerparticle.h"
#include <iostream>
#include <fstream>
#include <gsl/gsl_const_mksa.h>
#include "timesolver.h"
#include "initiation.h"
#include "outputstream.h"
#include "simplecommand.h"
#include "particlecommand.h"

extern double k_bltz;
SimpleDataCollector::SimpleDataCollector (Subject* ts):
  subject_(ts),
  avrho_(0.0),
  avkin_(0.0),
  avp_(0.0),
  //  rho_file_name("outdata/rho.dat"),
  //  kin_file_name("outdata/kin.dat"),
  NParticle_(0)
{
  //  timesolver_ = ts;
  subject_->Attach(this);
  //  avrho_ = 0.0;  
  ///erise file content
  //  std::ofstream fout( rho_file_name.c_str(), ios::trunc);
  //  fout.close();    
  //  fout.open(kin_file_name.c_str(), ios::trunc);

  ///get data stream  
  OutputStream* datast = OutputStream::Instance();
  
  Command* co;

//   co = 
//     new ParticleCommand<SimpleDataCollector>(this,
// 					   &SimpleDataCollector::getParticlePressure);
//   datast->AddParticleAttribute("P", co);

  co = 
    new ParticleCommand<SimpleDataCollector>(this,
					   &SimpleDataCollector::getRho);
  datast->AddParticleAttribute("rho", co);

//   co = 
//     new ParticleCommand<SimpleDataCollector>(this,
// 					     &SimpleDataCollector::getMass);
//   datast->AddParticleAttribute("mass", co);

}


void SimpleDataCollector::VisitParticle(Particle* pa) {
  NParticle_++;
  avrho_ += pa->rho();
  avkin_ += pa->getKinEnergy();
  avp_ += pa->getP();
  //  cout << "Sum rho = " << avrho_ << '\n';
}

void SimpleDataCollector::VisitPolymerParticle(PolymerParticle* pp) {
  VisitParticle(pp);
}

void SimpleDataCollector::Update(Subject* s) {
  //  cout << "SimpleDataCollector updated" << '\n';
  //  ofstream fout( rho_file_name.c_str(), ios::app);
  //  Initiation* ini = Initiation::Instance();
  //  fout << ini->dms_rho(avrho_/NParticle_) << '\n';
  //  fout.close();    
  avrho_ = 0.0;
  //  cout << "kb = " << GSL_CONST_MKSA_BOLTZMANN << '\n';
  //  fout.open(kin_file_name.c_str(), ios::app);
  //  cout << "k_bltz = " << k_bltz << '\n';
  //  fout << avkin_/NParticle_/(k_bltz*ini->T0) << ' ';    
  //  fout << ini->dms_p(avp_/NParticle_) << '\n';
  //  cout << "kin = " << avkin_/NParticle_ << '\n';
  avp_ = 0.0;
  
  //  fout.close();
  avkin_ = 0.0;

  NParticle_ = 0;  
}


double SimpleDataCollector::getParticlePressure(Particle* pa) {
  Initiation* ini = Initiation::Instance();
  return ini->dms_p(pa->getP());
}

double SimpleDataCollector::getNPartice() {
  return double(NParticle_);
}

double SimpleDataCollector::getRho(Particle* pa) {
  return  pa->rho();
}

double SimpleDataCollector::getMass(Particle* pa) {
  return pa->getMass();
}

SimpleDataCollector::~SimpleDataCollector() {
  subject_->Detach(this);
}
