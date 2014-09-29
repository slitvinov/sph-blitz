#ifndef TORRGDATACOLLECTOR_H
#define TORRGDATACOLLECTOR_H
#include "vec2d.h"
#include "datacollector.h"
#include "observer.h"
#include "command.h"
#include <vector>


///get gyration radius
class TorRgDataCollector: public DataCollector, 
		       public Observer, 
		       public Command {
public:
  virtual ~TorRgDataCollector();
  ///get data from the polymer particle
  virtual void VisitPolymerParticle(PolymerParticle*);

  ///get data frim the polymer interaction
  virtual void VisitPolymerInteraction(PolymerInteraction*);

  ///finish Rg calculations
  virtual void Update(Subject* theChangeSubject);
  
  ///return Rg
  virtual double Execute();
  
  ///constructor
  TorRgDataCollector(Subject*);
private:
  ///the number of polymer particle
  long N_;

  ///polymer particles vector
  vector<PolymerParticle*> vecPP;

  ///particles coordinates
  vector<Vec2d> vecR;

  ///the number of polymer interactions
  unsigned int nPInteraction_;

  ///the number of particle-ghost interactions
  unsigned int nGhostInteractions_;
};
#endif
