#include "datacollector.h"
DataCollector::~DataCollector() {
}

DataCollector::DataCollector() {
}

void DataCollector::VisitParticle(Particle* pa) {
}

void DataCollector::VisitPolymerParticle(PolymerParticle* pp) {
}

void DataCollector::VisitInteraction(Interaction* inter) {
}

void DataCollector::VisitPolymerInteraction(PolymerInteraction* pinter) {
}

void DataCollector::Add(DataCollector*) {
}

void DataCollector::Remove(DataCollector*) {
}

list<DataCollector*>::iterator DataCollector::CreateIterator() {
  return list<DataCollector*>::iterator();
}; 
