#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H
#include <list>
using namespace std;

class Particle;
class PolymerParticle;
class Interaction;
class PolymerInteraction;
class DataCollector;

///abstract data collector class
///all function do nothing by default
class DataCollector {  
public:
  ///virtual destructor
  virtual ~DataCollector();
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
protected:
  DataCollector();
};
#endif
