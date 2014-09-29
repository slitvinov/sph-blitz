#ifndef SIMPLEDATACOLLECTOR_H
#define SIMPLEDATACOLLECTOR_H
#include <string>
#include "datacollector.h"
#include "observer.h"

class TimeSolver;
///simple concrete data collecter
class SimpleDataCollector: public DataCollector, public Observer {
public:
  virtual ~SimpleDataCollector();
  ///get the average density of the particle
  virtual void VisitParticle(Particle*);
  ///get 
  virtual void VisitPolymerParticle(PolymerParticle*);
  ///update at the end of time iteration
  virtual void Update(Subject* theChangeSubject);
  
  ///return particle pressure
  virtual double getParticlePressure(Particle*);

  ///return particle density
  virtual double getRho(Particle*);


  ///return the number of counted particles (for testing)
  virtual  double getNPartice();

  ///return the particle mass
  virtual double getMass(Particle*);

  ///constructor 
  explicit SimpleDataCollector(Subject*);  
private:
  ///average particle density
  double avrho_;

  ///average kinetic energy
  double avkin_;

  ///average pressure
  double avp_;

  ///Subject object
  Subject* subject_;

//   ///output file name
//   std::string rho_file_name;
//   ///output file name
//   std::string kin_file_name;

  ///number of particles counted
  long NParticle_;
};
#endif
