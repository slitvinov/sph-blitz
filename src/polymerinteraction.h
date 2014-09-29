#ifndef POLYMERINTERACTION_H
#define POLYMERINTERACTION_H
#include <iostream>
#include "interaction.h"

class PolymerParticle;
class Interaction;
///constructor for PolymerInteraction class
class PolymerInteraction : public Interaction
{
public:
  PolymerInteraction(PolymerParticle *prtl_org, 
		     PolymerParticle *prtl_dest, 
		     Force **forces,
		     QuinticSpline &weight_function, 
		     double dstc);
  virtual double getPolyEnegry() const;
  virtual ~PolymerInteraction();
  virtual void UpdateForces();  

  ///accept data collector object
  virtual void acceptDataCollector(DataCollector*);


  ///output function
  ///used by operator<<
  virtual ostream& put(ostream& ostr) const;
};



#endif
