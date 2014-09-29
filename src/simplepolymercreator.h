#ifndef SIMPLEPOLYMERCREATOR_H
#define SIMPLEPOLYMERCREATOR_H
#include "abspolymercreator.h"
#include <math.h>
#include <vector>
#include "vec2d.h"
#include <string.h>

class Node;
///very simple class concrete to create polymer
class SimplePolymerCreator : public AbsPolymerCreator {
public:
  ///constructor
  SimplePolymerCreator(const string& configfilename = "polymer.cfg");
  virtual ~SimplePolymerCreator();
  ///create polymer usin polymer manager object
  virtual void CreatePolymer(const ParticleManager& particles ) ;

  ///returns polymer force (FINE) <BR>
  ///\f$$ \mathbf{F} = \frac{H \mathbf{r}}{1-\frac{r^2}{R_0^2}}\f$
  virtual Vec2d getForce(const Vec2d& eij, const double& rij) const ;

  ///returns the energy of monomers interaction (FINE) <BR>
  ///\f$$ U(r) = -\frac{1}{2} H R_0^2 \log \left(1-\frac{r^2}{R_0^2}\right)\f$
  virtual double getEnergy(const Vec2d& eij,
			   const double& rij) const;
  virtual void showName() const;  
  virtual void push_back(PolymerInteraction* newinteraction);
private:
  ///FENE force parameters
  double R0_;
  double H_;
  ///the vector of angels
  std::vector<double> alphaVector_;
  ///polymer head position in the box 
  ///normolaized coordinates
  Vec2d polyHead_;
  ///polymer geometry file name
  string polyFileName_;
  ///a vector of polymer particles
  vector<Node*> polyVector_;
  ///a vector of polymer interactions
  vector<PolymerInteraction*> interactVector_;  

};

#endif
