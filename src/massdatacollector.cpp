#include <iostream>
#include <fstream>

#include "polymerparticle.h"
#include "massdatacollector.h"
#include "timesolver.h"
#include "initiation.h"
#include "simplecommand.h"
#include "outputstream.h"

MassDataCollector::MassDataCollector(Subject* ts):
  subject_(ts),
  summass_(0.0)
{
  //  timesolver_ = ts;nnn
  subject_->Attach(this);
  ///get data stream  
  OutputStream* datast = OutputStream::Instance();
  
  ///create a command from getAvKin() function
  Command* co = 
    new SimpleCommand<MassDataCollector>(this,
					   &MassDataCollector::getAvMass);
  
  ///attache a command to the datastream
  datast->AddTimeStepAttribute("avMass", co);       

}

void MassDataCollector::VisitParticle(Particle* pa) {
  NParticle_++;
  summass_ = summass_ + pa->getMass();
}

void MassDataCollector::VisitPolymerParticle(PolymerParticle* po) {
  VisitParticle(po);
}

void MassDataCollector::Update(Subject* s) {
  //  cout << "PolymerDataCollectorupdated" << '\n';
  NParticle_ = 0;
  summass_ = 0.0;
}

MassDataCollector::~MassDataCollector() {
  subject_->Detach(this);
}

double MassDataCollector::getAvMass(){
  Initiation* ini = Initiation::Instance();
  return ini->dms_mass(summass_)/NParticle_;
}
