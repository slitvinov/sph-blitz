#ifndef RGDATACOLLECTOR_H
#define RGDATACOLLECTOR_H
#include "vec2d.h"
#include "datacollector.h"
#include "observer.h"
#include "command.h"


///get gyration radius
class RgDataCollector: public DataCollector, 
		       public Observer, 
		       public Command {
public:
  virtual ~RgDataCollector();
  ///get data from the polymer particle
  virtual void VisitPolymerParticle(PolymerParticle*);

  ///finish Rg calculations
  virtual void Update(Subject* theChangeSubject);
  
  ///return Rg
  virtual double Execute();
  
  ///constructor
  RgDataCollector(Subject*);
private:
  ///the sum of radius vectors
  Vec2d RmeanSum_;

  ///the sum of vector products (r_k, r_k)
  double R2sum_;

  ///the number of polymer particle
  long N_;

  ///gyration radius
  double Rg_;
};

#endif
