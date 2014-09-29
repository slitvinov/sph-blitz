#include "torrgdatacollector.h"
#include "polymerparticle.h"
#include "polymerinteraction.h"
#include "subject.h"
#include "outputstream.h"
#include "initiation.h"
#include "boundary.h"
#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif


TorRgDataCollector::TorRgDataCollector(Subject* ts)
{  
  nPInteraction_ = 0;
  nGhostInteractions_ = 0;
  N_ = 0;
  ts->Attach(this);
  OutputStream* datast = OutputStream::Instance();
  datast->AddTimeStepAttribute("Rg2", this);
}

void TorRgDataCollector::VisitPolymerParticle(PolymerParticle* pp) {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("torrgdatacollector");
  LOG4CXX_DEBUG(Logger, "VisitPolymerParticle");
#endif
  vecPP.push_back(pp);
  if (N_ == 0) {
    vecR.push_back(pp->R());
  }
  else {
    Initiation* ini = Initiation::Instance();
    Boundary* bo = ini->getBoundary();
    Vec2d local_R = vecR.at(N_-1) + 
      bo->getBDistance(vecR.at(N_-1), pp->R());    
    vecR.push_back(local_R);
  }
  N_ ++;
}

void TorRgDataCollector::VisitPolymerInteraction(PolymerInteraction* pi) {
  //  pi-
  ///total number of interactions
  nPInteraction_++;
// #ifndef NOLOG
//   log4cxx::LoggerPtr Logger = 
//     log4cxx::Logger::getLogger("torrgdatacollector");
//   LOG4CXX_DEBUG(Logger, "VisitPolymerInteraction");
// #endif

//   ///check existence of particle in the 
//   ///interaction structure
//   Particle* Org = pi->getOrg();
//   assert(Org != NULL);

//   Particle* Dest = pi->getDest();
//   assert(Dest != NULL);

//   ///ghost - ghost interaction should not appear
//   assert((Org->getParticleID()>0) || (Dest->getParticleID()>0));
  
//   if ((Org->getParticleID()==0) || (Dest->getParticleID()==0)) {
//     cout << nGhostInteractions_ << '\n';
//     nGhostInteractions_ ++;
//   };
// #ifndef NOLOG
//   log4cxx::LoggerPtr Logger = 
//     log4cxx::Logger::getLogger("torrgdatacollector");
//   LOG4CXX_DEBUG(Logger,  "ID = " + stringify(Org->getParticleID()) + 
//  		" ID = " + stringify(Dest->getParticleID()));		
// #endif
}

void TorRgDataCollector::Update(Subject* theChangeSubject) {
  ///the number of interactions should be more the the number of polymer particles plus 
  ///two (periodic boundary conditions are taken into account)
  assert(nPInteraction_ - PolymerParticle::nPolyParticle_ + 2 > 0);
#ifndef NOLOG  
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("torrgdatacollector");
  LOG4CXX_DEBUG(Logger, "Update");
  LOG4CXX_DEBUG(Logger, "The number of polymer interactons: " + stringify<unsigned int>(nPInteraction_)); 
  LOG4CXX_DEBUG(Logger, "The number of ghost interactons: " + stringify<unsigned int>(nGhostInteractions_)); 
#endif
  ///check the number of polymer particles
  assert(N_ == PolymerParticle::nPolyParticle_);
  nPInteraction_ = 0;
  nGhostInteractions_ = 0;
  N_ = 0;
  vecPP.clear();
  vecR.clear();
}

double TorRgDataCollector::Execute() {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("torrgdatacollector");
#endif

//   Initiation* ini = Initiation::Instance();
//   Boundary* bo = ini->getBoundary();
  double Rg_ = 0.0;
  for (unsigned int i=0; i<vecPP.size(); i++) {
    for (unsigned int j=0; j<vecPP.size(); j++) {
      //      Vec2d dR = bo->getBDistance(pi->R(), pj->R());
      Vec2d dR = vecR.at(j) - vecR.at(i);
#ifndef NOLOG
      LOG4CXX_DEBUG(Logger, "i = " + stringify<unsigned int>(i) +
		    " j= " + stringify<unsigned int>(j));
#endif
      Rg_  = Rg_ + dot(dR, dR);
    }
  }
  Rg_ = sqrt(0.5/double(vecPP.size()*vecPP.size()) * Rg_);

  //  double Rg_old = Rg_;
  //  Rg_ = 0.0;
  return Rg_;
}

TorRgDataCollector::~TorRgDataCollector() {
}
