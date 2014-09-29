#ifndef POLYMERDATACOLLECTOR_H
#define POLYMERDATACOLLECTOR_H
#include <string>
#include "datacollector.h"
#include "observer.h"


class TimeSolver;
///simple concrete data collecter
class PolymerDataCollector: public DataCollector, public Observer {
public:
  virtual ~PolymerDataCollector();
  ///get information from polymer particles
  virtual void VisitPolymerParticle(PolymerParticle*);
  
  ///update at the end of time iteration
  void Update(Subject*);
  explicit PolymerDataCollector(Subject*);
  
private:
    ///Subject object
  Subject* subject_;
  ///head-tail distance
  double R_;
  ///number of particles counted
  long NParticle_;
  ///distance file name
  string dist_file_name;
  ///the head of polymer
  PolymerParticle* head;
  ///the tail of polymer
  PolymerParticle* tail;  
};
#endif
