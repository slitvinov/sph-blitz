#ifndef NODE_H
#define NODE_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
//#include "dllist.h"


class Interaction;
class Initiation;
class Material;
class ParticleManager;
class Force;
class QuinticSpline;
class InteractionState;
class Particle;
class DataCollector;

class Node {
 public:
  ///the number of Nodes
  static long nNode;
  static int number_of_materials;
  explicit Node(Particle* state_);

  ///particle class destructor
  virtual ~Node();
	
  void ChangeState(Particle* newState);
  
  ///output operation
  //  virtual ostream& operator<< (ostream& ostr, const Particle& pa);
  //  virtual Particle& operator= (const Particle&);
  virtual ostream& put(ostream& ostr) const;


  ///particle states copier for boundary particles
  ///\param &RealParticle a reference to the realparticle
  void StatesCopier(int type);

  ///accept data collector
  void acceptDataCollector(DataCollector* dc);
			
  /// Returns the position of the particles
  virtual const Vec2d& R() const;
  /// Returns the position of the particles
  virtual Vec2d&       R();

  /// Returns the velocity of the particles
  virtual const Vec2d& U() const;

  /// Returns the velocity the particles
  virtual Vec2d&       U();

  /// Returns the density of the particles
  virtual const double& rho() const;
  /// Returns the density of the particles
  virtual double&       rho();

  /// \bref first as phase field gradient matrix 
  virtual const Vec2d& del_phi() const;
  virtual Vec2d&       del_phi();
    
  virtual double getMass() const;
  virtual void setMass(double newM);
  virtual double getEta() const;
  virtual double getZeta() const;
  virtual double getP() const;
  virtual double getCs() const;
  virtual double getT() const;
  virtual void setVolume(double newV);
  virtual Interaction* createInteractionWith(Node *prtl_dest,
					    Force **force,
					    QuinticSpline &weight_function,
					    double dstc);
//   virtual Interaction* _createInteractionWith(Node *prtl_org,
// 					     Force** force,
// 					     QuinticSpline& weight_function,
// 					     double dstc);
  virtual long getParticleID() const;
  virtual int getParticleType() const;
  //  virtual int 
  virtual int getbd() const;
  virtual int getBDtype() const;

  ///save values at step n
  virtual void saveRRU();

  ///calculate the middle values at step n+1/2
  virtual void setMiddleRRU();
  
  /// one step for predictor summation
  virtual void predictorSummationStep(const double& dt);

  ///correction base on values on n step and change rate at n+1/2
  virtual void correctorSummationStep(const double& dt);

  ///correct U
  virtual void correctU();

  ///correction base on values on n step and change rate at n+1/2
  virtual void correctRRU(const double& dt);

//   ///set cell position
//   virtual void setCellPosition(int ncell_i, int ncell_j);

  ///increase shear rate
  virtual void increaseShearRate(Vec2d dSRx, Vec2d dSRy);

  ///set all shear rates to 0
  virtual void setShearRatetoZero();

  ///get shear rate in x direction
  virtual Vec2d getShearRateX() const;

  ///get shear rate in y direction
  virtual Vec2d getShearRateY() const;

  ///get the material number
  virtual int getMaterialNumber() const;

  ///get the material name
  virtual char* getMaterialName() const;

  ///returns a pointer to material
  virtual Material* getMaterial() const;

  ///update pressure according to the equation
  ///of state
  virtual void updatePressure();
  virtual void increaseRandomU(const Vec2d& deltaU);
  virtual void increaseRandomUReal(const Vec2d& deltaU);
  virtual void increasePhi(double deltaPhi, int noi, int noj);
  virtual void increaseLapPhi(double deltaLapPhi, int noi, int noj);
  
  virtual void setPhiToZero(int noi, int noj);
  virtual void setLapPhiToZero(int noi, int noj);
  virtual double getPhiElement(int noi, int noj) const;
  virtual void increaseRandomdU(const Vec2d& deltadU);
  virtual void increasedrhodt(const double& deltadrhodt);
  virtual void increasedUdt(const Vec2d& deltadUdt);
  virtual void setAlldToZero(double dt);
  virtual void setRandomUtoZero();
  virtual double getKinEnergy() const;
  virtual void setUtoZero();
  virtual Particle* getState() const;
  //  virtual Particle* Node::getState();

  ///create ghost particle based on this node
  virtual Particle* createGhost();

  ///return ID of the particle or ID of the real particle for ghost
  virtual long getRealID() const;

  ///return a pointer real particle 
  ///(for real particle return this)
  Particle* getReal();


protected: 
  Particle* state_;
};        

extern ostream& operator<< (ostream& ostr, const Node& prtl);
#endif
