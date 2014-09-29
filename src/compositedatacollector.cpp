#include "compositedatacollector.h"

CompositeDataCollector::~CompositeDataCollector() {
  
}

void CompositeDataCollector::VisitParticle(Particle* pa) {
  list<DataCollector*>::iterator i;  
  for (i = _datacollectors.begin(); i != _datacollectors.end(); i++) {  
    (*i)->VisitParticle(pa);
  }
}

void CompositeDataCollector::VisitPolymerParticle(PolymerParticle* pa) {
  list<DataCollector*>::iterator i;  
  for (i = _datacollectors.begin(); i != _datacollectors.end(); i++) {  
    (*i)->VisitPolymerParticle(pa);
  }
}

void CompositeDataCollector::VisitInteraction(Interaction* inter) {
  list<DataCollector*>::iterator i;  
  for (i = _datacollectors.begin(); i != _datacollectors.end(); i++) {  
    (*i)->VisitInteraction(inter);
  }
}

void CompositeDataCollector::VisitPolymerInteraction(PolymerInteraction* inter) {
  list<DataCollector*>::iterator i;  
  for (i = _datacollectors.begin(); i != _datacollectors.end(); i++) {  
    (*i)->VisitPolymerInteraction(inter);
  }
}

void CompositeDataCollector::Add(DataCollector* dc) {
  _datacollectors.push_back(dc);
}

void CompositeDataCollector::Remove(DataCollector* dc) {
  _datacollectors.remove(dc);
}

list<DataCollector*>::iterator CompositeDataCollector::CreateIterator() {
  return _datacollectors.begin();
}
