#include <iostream>
#include "safeoutputstream.h"
#include "polymerparticle.h"

#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif
#include "glbfunc.h"


SafeOutputStream::SafeOutputStream(OutputStream* comp) {
  stream_ = comp;
}


void SafeOutputStream::WriteAllTimeStepAttributes() {
  stream_->WriteAllTimeStepAttributes();
}

void SafeOutputStream::WriteAllParticleAttributes(Particle* pa) {
  stream_->WriteAllParticleAttributes(pa);
}

void SafeOutputStream::WriteAllParticleAttributes(PolymerParticle* pp) {
  stream_->WriteAllParticleAttributes(pp);
}


void SafeOutputStream::NewTimeStep() {
  stream_->NewTimeStep();
}



void SafeOutputStream::AddTimeStepAttribute(string AttrName, 
					    Command* co)
{
  stream_->AddTimeStepAttribute(AttrName, co);
}

void SafeOutputStream::AddParticleAttribute(const string AttrName,
					     Command* co) {
  stream_->AddParticleAttribute(AttrName, co);
}


void SafeOutputStream::RemoveTimeStepAttribute(const string AttrName) {
  stream_->RemoveTimeStepAttribute(AttrName);
}


SafeOutputStream::~SafeOutputStream() {
#ifndef NOLOG
   log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("safeoutputstream");
   LOG4CXX_DEBUG(Logger, "Destructor");
#endif
   delete stream_;
}


 void SafeOutputStream::WriteTimeStepAttribute(string AttrName, 
						      double AttrValue) {
  stream_->WriteTimeStepAttribute(AttrName, AttrValue);
}


 void SafeOutputStream::WriteParticleAttribute(string AttrName, 
						      double AttrValue) {
  stream_->WriteParticleAttribute(AttrName, AttrValue);
}

 void SafeOutputStream::Update(Subject* su) 
{
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("safeoutputstream");
  LOG4CXX_DEBUG(Logger, "Feed Polymer particles to the stream");
  log4cxx::LoggerPtr NumLogger = log4cxx::Logger::getLogger("safeoutputstream.numbers");
#endif

  ///previous PolyID
  long int pID = 0;
  ///current PolyID
  long int cID;
  while (!vecPP.empty()) {
    //    cout << "Get " <<  vecPP.top()->getPolyID() << '\n';
    stream_->VisitPolymerParticle(vecPP.top());
    cID = vecPP.top()->getPolyID();
#ifndef NOLOG
    LOG4CXX_DEBUG(NumLogger, "PolyID = " + stringify(cID));
#endif
    //should be in right order
    assert(pID < cID);
    pID = cID;
    vecPP.pop();    
  }
  stream_->Update(su);
}

void SafeOutputStream::Initialize() {
  stream_->Initialize();
}


void SafeOutputStream::Attach(Observer* ob) {
  stream_->Attach(ob);  
}

void SafeOutputStream::Detach(Observer* ob) {
  stream_->Detach(ob);
}

void SafeOutputStream::Notify(double time) {
  stream_->Notify(time);
}

double SafeOutputStream::GetTime() {
  return stream_->GetTime();
}
  

void SafeOutputStream::SetTime(double time) {
  stream_->SetTime(time);
}



void SafeOutputStream::VisitParticle(Particle* ps ) {
  stream_->VisitParticle(ps);
}

void SafeOutputStream::VisitPolymerParticle(PolymerParticle* pp)  {  
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = 
    log4cxx::Logger::getLogger("safeoutputstream");
  LOG4CXX_DEBUG(Logger, "VisitPolymerParticle");
#endif
  vecPP.push(pp);
}

void SafeOutputStream::VisitInteraction(Interaction* ir) {
  stream_->VisitInteraction(ir);
}

void SafeOutputStream::VisitPolymerInteraction(PolymerInteraction* pi) {
  stream_->VisitPolymerInteraction(pi);
}

void SafeOutputStream::Add(DataCollector* dc) {
  stream_->Add(dc);
}

void SafeOutputStream::Remove(DataCollector* dc) {
  stream_->Remove(dc);
}
