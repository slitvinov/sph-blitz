#include "rgdatacollector.h"
#include "polymerparticle.h"
#include "subject.h"
#include "outputstream.h"
#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif


RgDataCollector::RgDataCollector(Subject* ts):
  N_(0),
  R2sum_(0.0),
  RmeanSum_(0.0),
  Rg_(0.0)
{  
  ts->Attach(this);
  OutputStream* datast = OutputStream::Instance();
  datast->AddTimeStepAttribute("Rg", this);
}

void RgDataCollector::VisitPolymerParticle(PolymerParticle* pp) {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("rgdatacollector");
  LOG4CXX_DEBUG(Logger, "VisitPolymerParticle");
#endif
  N_++;
  R2sum_ += dot(pp->R(), pp->R());
  RmeanSum_ += pp->R();
}

void RgDataCollector::Update(Subject* theChangeSubject) {
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("rgdatacollector");
  LOG4CXX_DEBUG(Logger, "Update");  
#endif
  assert(N_ == PolymerParticle::nPolyParticle_);
  N_ = 0;
  R2sum_ = 0.0;
  RmeanSum_ = 0.0;
}

double RgDataCollector::Execute() {
  assert(N_ == PolymerParticle::nPolyParticle_);
  Rg_ = sqrt(- dot(RmeanSum_/double(N_), RmeanSum_/double(N_)) + 
	     R2sum_/double(N_));
  return Rg_;
}

RgDataCollector::~RgDataCollector() {
}
