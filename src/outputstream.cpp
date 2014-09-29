#include <cstdlib>
#include <iostream>
// #include <algorithm>
// #include <functional>
#include <map>
#include "stdlib.h"
//#include <hash>

#include "initiation.h"
#include "outputstream.h"
#include "textoutputstream.h"
#include "netcdfoutputstream.h"
#include "safeoutputstream.h"
#include "command.h"
#include "polymerparticle.h"


class SafeOutputStream;
class OutputStream;
class TextOutputStream;

OutputStream* OutputStream::instance_ = NULL;

OutputStream* OutputStream::Instance() {
  const Initiation* const ini(Initiation::Instance());
  if (ini->outputstream == "TEXT") {
    instance_ = new TextOutputStream;
  }
  else {
    instance_ = new SafeOutputStream(new NetCDFOutputStream);
  }
  return instance_;
}


void OutputStream::WriteFileDescription() {
}

void OutputStream::NewTimeStep() {
}

void OutputStream::AddTimeStepAttribute(const string  AttrName, 
					Command* co) {
  registry_[AttrName]=co;
}

void OutputStream::AddParticleAttribute(const string AttrName,
					Command* co) {
  pAttrRegistry_[AttrName]=co;
}


void OutputStream::RemoveTimeStepAttribute(const string AttrName) {
  registry_.erase(AttrName);
}

void OutputStream::WriteTimeStepAttribute(string AttrName, 
 					  double AttrValue) {
#ifdef DEBUG
  cout << "Base class WriteTimeStepAttribute was called" << endl;
#endif
}

void OutputStream::WriteParticleAttribute(string AttrName, 
					  double AttrValue) {
}

void OutputStream::WriteAllTimeStepAttributes() {
  //  for_each(regestry_.begin(), regestry_.end(), mem_fun(&Command::Execute)); 
  map<const string, Command*>::iterator theIterator;
   for( theIterator = registry_.begin(); theIterator != registry_.end(); theIterator++ ) {
     string s = theIterator->first;
     WriteTimeStepAttribute(s, theIterator->second->Execute());
   }    
   
   ///Notify all Observers that the output finised for this timestep
   Notify(GetTime());
}

void OutputStream::WriteAllParticleAttributes(Particle* pa) {
   map<const string, Command*>::iterator theIterator;
   for( theIterator = pAttrRegistry_.begin(); theIterator != pAttrRegistry_.end(); theIterator++ ) {
     string s = theIterator->first;
     WriteParticleAttribute(s, theIterator->second->Execute(pa));
   }    
}

void OutputStream::WriteAllParticleAttributes(PolymerParticle* polyp) {
  Particle* pa = static_cast<Particle*>(polyp);
  WriteAllParticleAttributes(pa);
}

OutputStream::~OutputStream() {
}

OutputStream::OutputStream() {
}

void OutputStream::Update(Subject* s) {
  ///set new timer value
  SetTime(s->GetTime());
}

void OutputStream::Initialize() {
}

