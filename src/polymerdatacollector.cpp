#include "polymerparticle.h"
#include "polymerdatacollector.h"
#include <iostream>
#include <fstream>
#include "timesolver.h"
#include "initiation.h"

PolymerDataCollector::PolymerDataCollector(Subject* ts):
  subject_(ts),
  R_(0.0),
  dist_file_name("outdata/dist.dat"),
  head(NULL),
  tail(NULL)
{
  //  timesolver_ = ts;
  subject_->Attach(this);
  //  avrho_ = 0.0;  
  ///erise file content
  std::ofstream fout( dist_file_name.c_str(), ios::trunc);
  fout.close();    
}

void PolymerDataCollector::VisitPolymerParticle(PolymerParticle* pa) {
  //  cout << "VisitPolymerParticle" << '\n';
  NParticle_++;
  if (pa->isHead()) {
    //    cout << "Found the head" << '\n';
    head=pa;
  }
  if (pa->isTail()) {
    //    cout << "Found the tail" << '\n';
    tail=pa;
  }  
  cout << "Polymer density: " << pa->rho() << '\n';
}


void PolymerDataCollector::Update(Subject* s) {
  //  cout << "PolymerDataCollectorupdated" << '\n';
  ofstream fout( dist_file_name.c_str(), ios::app);
  Initiation* ini = Initiation::Instance();
  Vec2d dR = tail->R() - head->R();
  R_ = sqrt(dot(dR, dR));
  fout << ini->dms_length(R_) << ' ' << 
    head->R()[0] << ' ' << head->R()[1] << ' ' <<
    tail->R()[0] << ' ' << tail->R()[1] << '\n';
  fout.close();    
  NParticle_ = 0;
}


PolymerDataCollector::~PolymerDataCollector() {
  subject_->Detach(this);
}
