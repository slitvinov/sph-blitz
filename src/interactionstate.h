#ifndef INTERACTIONSTATE_H
#define INTERACTIONSTATE_H

#ifdef _OPENMP
#include <omp.h>
#endif

#include <iostream>
#include "datacollector.h"
//#include <iostream>
//#include "vec2d.h"
//#include "wiener.h"
//#include "dllist.h"
//#include "particle.h"
//#include "polymerparticle.h"
//#include "force.h"
//#include "quinticspline.h"

class Interaction;
class Particle;
class Force;
class QuinticSpline;
class Initiation;
class Wiener;

using namespace std;
///the state of interaction between particles
class InteractionState {
public:	
  ///constructor
  InteractionState(Interaction*);
  virtual ~InteractionState();
  
  ///use old interaction object for new interaction
  void ChangeState(Interaction* newState);
  // void NewInteraction(Particle *prtl_org,
  // 		      Particle *prtl_dest, 
  // 		      Force **forces,
  // 		      const QuinticSpline &weight_function, 
  // 		      double dstc);
  
  ///renew pair parameters and changing pair values
  void RenewInteraction(QuinticSpline &weight_function);

  ///accept data collector object
  virtual void acceptDataCollector(DataCollector*);

  ///get particle with larger ID
  virtual Particle* getOrg() const;

  ///get particle with larger ID
  virtual Particle* getDest() const;

  
  ///pair interaction
  void SummationDensity();
  void SummationShearRate();
  
  ///pahse field and phase gradient
  void SummationPhaseField();
  void SummationCurvature();
  void SummationPhaseGradient();
  void SummationPhaseGradient_old();
  void SummationPhaseLaplacian();
  
  ////update forces
  void UpdateForces();
  void UpdateForces_vis();

  
  ///update random forces
  void RandomForces(Wiener &wiener, 
		    double sqrtdt);
  void RandomForces_Espanol(Wiener &wiener,
			    double sqrtdt);
  virtual ostream& put(ostream& ostr) const;
private:
  Interaction* state_;
};
#endif
