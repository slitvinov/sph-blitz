#ifndef INTERACTION_H
#define INTERACTION_H

#ifdef _OPENMP
#include <omp.h>
#endif

#include <iostream>

#include "wiener.h"
#include "dllist.h"
#include "vec2d.h"
#include "datacollector.h"
//#include "particle.h"
//#include "polymerparticle.h"
//#include "force.h"
//#include "quinticspline.h"

class Wiener;
class Node;
class Force;
class QuinticSpline;
class Initiation;
class Particle;

//-----------------------------------------------------------------------
//			defines interaction between particles
//-----------------------------------------------------------------------
/// particles interaction class 

class Interaction {
protected:

  ///the number of interactions
  static long nInteraction;
	///total number of materials
	static int number_of_materials;
	static double smoothinglength;
	static double delta;
	///artificial viscosity
	static double art_vis;

	//particle pair
	///particel with larger ID
	Particle*  Org;	
	///particel with smaller ID
	Particle*  Dest;
	///force from particle i to particle j

	
	Force **frc_ij;
	
	///pair values do not change in sub time steps
	int noi, noj; //material NO. of the two partilces
	double mi, rmi, etai, zetai, mj, rmj, etaj, zetaj;

	///distance between the two particles, weight and derivatives
	double rij, rrij, Wij, Fij, LapWij, Wij2;
	Vec2d eij; //pair direction from orginal particle to destination particle 
	double shear_rij, bulk_rij; //particle length to implement slip boundary

#ifdef _OPENMP
	//temporary storage of computation terms
	double drhodt1, drhodt2;
	Vec2d _dU1, _dU2, dUdt1, dUdt2;
#endif
		
public:
	
///constructor
explicit Interaction(const Initiation* const ini);
Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
	    QuinticSpline &weight_function, 
	    double dstc);

#ifdef DEBUG  
  /// condtructor of interaction object for two polymer particles
#endif
  virtual ~Interaction();
  ///use old interaction object for new interaction
  void NewInteraction(Particle *prtl_org,
		      Particle *prtl_dest, 
		      Force **forces,
		      QuinticSpline &weight_function, 
		      double dstc);
  
  ///renew pair parameters and changing pair values
  void RenewInteraction(const QuinticSpline &weight_function);

  ///accept data collector object
  virtual void acceptDataCollector(DataCollector*);
  
  ///get particle with larger ID
  virtual  Particle* getOrg() const;

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
  virtual void UpdateForces();
  void UpdateForces_vis();
#ifdef _OPENMP
  void SummationUpdateForces();
#endif
  
  ///update random forces
  void RandomForces(Wiener &wiener, 
		     double sqrtdt);
  void RandomForces_Espanol(Wiener &wiener, 
			    double sqrtdt);
  ///output function
  ///used by operator<<
  virtual ostream& put(ostream& ostr) const;  
};

extern ostream& operator<< (ostream& ostr, const Node& prtl);
#endif
