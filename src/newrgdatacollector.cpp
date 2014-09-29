#include "newrgdatacollector.h"
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


NewRgDataCollector::NewRgDataCollector(Subject* ts)
{  
  nPInteraction_ = 0;
  nGhostInteractions_ = 0;
  N_ = 0;
  ts->Attach(this);
  OutputStream* datast = OutputStream::Instance();
  datast->AddTimeStepAttribute("Rg3", this);
}

void NewRgDataCollector::VisitPolymerParticle(PolymerParticle* pp) {
  unsigned int nPoly = PolymerParticle::nPolyParticle_;
  if (pp->getPolyID() == nPoly) {
    Initiation* ini = Initiation::Instance();
    Boundary* bo = ini->getBoundary();
    unsigned long iPart = nPoly;
#ifndef NOLOG
    log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("newrgdatacollector");
    LOG4CXX_DEBUG(Logger, "pp: " + stringify<int>(pp->getPolyID()));      
#endif
    ///put the vector number nPoly
    vecR.push_back(pp->R()); 
    while (iPart>1) {      
      PolymerParticle* tempPart = pp->getPrev();
#ifndef NOLOG
      PolymerInteraction* tempInt;
      tempInt = pp->getInt();
      log4cxx::LoggerPtr Logger = 
	log4cxx::Logger::getLogger("newrgdatacollector.interaction");
      LOG4CXX_DEBUG(Logger,  "===");
      LOG4CXX_DEBUG(Logger,  "Org ID: " + stringify<int>(static_cast<PolymerParticle*>(tempInt->getOrg())->getPolyID()));
      LOG4CXX_DEBUG(Logger,  "Dest ID: " + stringify<int>(static_cast<PolymerParticle*>(tempInt->getDest())->getPolyID()));
      LOG4CXX_DEBUG(Logger,  "===");
#endif
      unsigned int n = vecR.size();
      Vec2d local_R = vecR.at(n-1) + bo->getBDistance(vecR.at(n-1), tempPart->R());    
      vecR.push_back(local_R);
      pp = static_cast<PolymerParticle*>(tempPart->getReal());	
      //	cout << "iPart = " << local_R << endl;      
      if (iPart > 1) {
	pp = static_cast<PolymerParticle*>(tempPart->getReal());	
#ifndef NOLOG
	LOG4CXX_DEBUG(Logger, "pp: " + stringify<int>(pp->getPolyID()));      
#endif	
      }
      iPart = iPart - 1;
    }
#ifndef NOLOG
	LOG4CXX_DEBUG(Logger, "vecR.size() = " + stringify<int>(vecR.size()));      
#endif	
  }
  N_++;  
}

void NewRgDataCollector::VisitPolymerInteraction(PolymerInteraction* pi) {
  nPInteraction_++;
  assert(abs(static_cast<PolymerParticle*>(pi->getOrg())->getPolyID() -
	     static_cast<PolymerParticle*>(pi->getDest())->getPolyID()) == 1);
}

void NewRgDataCollector::Update(Subject* theChangeSubject) {
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

double NewRgDataCollector::Execute() {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("torrgdatacollector");
#endif

//   Initiation* ini = Initiation::Instance();
//   Boundary* bo = ini->getBoundary();
  double Rg_ = 0.0;
  //  cout << "vecR.size() = " << vecR.size() << endl;
  for (unsigned int i=0; i<vecR.size(); i++) {
    for (unsigned int j=0; j<vecR.size(); j++) {
      //      Vec2d dR = bo->getBDistance(pi->R(), pj->R());
      Vec2d dR = vecR.at(j) - vecR.at(i);
      Rg_  = Rg_ + dot(dR, dR);
    }
  }
  Rg_ = sqrt(0.5/double(vecR.size()*vecR.size()) * Rg_);

  //  double Rg_old = Rg_;
  //  Rg_ = 0.0;
  return Rg_;
}

NewRgDataCollector::~NewRgDataCollector() {
}
