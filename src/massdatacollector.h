#ifndef MASSDATACOLLECTOR_H
#define MASSDATACOLLECTOR_H
#include <string>
#include "datacollector.h"
#include "observer.h"


class TimeSolver;
///simple concrete data collecter
class MassDataCollector: public DataCollector, public Observer {
public:
  virtual ~MassDataCollector();
  ///get information from polymer particles
  virtual void VisitParticle(Particle*);
  ///get information frim the polymer particle
  virtual void VisitPolymerParticle(PolymerParticle*);
  ///update at the end of time iteration  
  virtual void Update(Subject*);
  ///return average particle mass
  virtual double getAvMass();
  explicit MassDataCollector(Subject*);
  
private:
  ///Subject object
  Subject* subject_;
  ///total mass couter
  double summass_;
  ///number of particles counted
  long NParticle_;
};
#endif
