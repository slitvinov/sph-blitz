#ifndef COMPOSITEDATACOLLECTOR_H
#define COMPOSITEDATACOLLECTOR_H
#include "datacollector.h"

///the base class for DataCollector that contains other DataCollectors
class CompositeDataCollector: public DataCollector {
public:
  ///virtual destructor
  virtual ~CompositeDataCollector();

    ///visit hydrodynamic particle
  virtual void VisitParticle(Particle*);
  ///visit polymer particle
  virtual void VisitPolymerParticle(PolymerParticle*);
  ///visit hydrodynamic interaction
  virtual void VisitInteraction(Interaction*);
  ///visit polymer interaction
  virtual void VisitPolymerInteraction(PolymerInteraction*);
  ///support composite pattern
  //@{
  ///add DataCollector from Composite
  virtual void Add(DataCollector*);
  ///remove DataCollector from Composite
  virtual void Remove(DataCollector*);
  ///return iterator
  virtual list<DataCollector*>::iterator CreateIterator();
  //@}
private:
  ///list of DataCollectors
  list<DataCollector*> _datacollectors;  
};
#endif
