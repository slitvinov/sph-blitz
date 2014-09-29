#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
#include "dllist.h"
#include "node.h"
#include "particle.h"
#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif


class Interaction;
class Initiation;
class Material;
class ParticleManager;
class Force;
class QuinticSpline;
class InteractionState;
class Particle;


long Node::nNode = 0;
Node::Node(Particle* newstate) {
  nNode ++;
  //  cerr << "nNode = " << nNode << endl;
  state_ = newstate;  
}

void Node::ChangeState(Particle* newState)
{  
  long ID;
  ID = state_->getParticleID();
  delete state_;
  state_ = newState;
  state_->setParticleID(ID);
  //Particle::ID_max--;    
}

  
///output operation
//   ostream& operator<< (ostream& ostr, const Particle& pa);
//   Particle& operator= (const Particle&);
ostream& Node::put(ostream& ostr) const {
  return (state_->put(ostr));
};

///particle class destructor
Node::~Node() {
  nNode = nNode - 1;
  //  cerr << "nNode = " << nNode << endl;
  delete state_;
};

///particle states copier for boundary particles
///\param &RealParticle a reference to the realparticle
void Node::StatesCopier(int type) {
  state_->StatesCopier(type);
};

///accept data collector
void Node::acceptDataCollector(DataCollector* dc) {
  state_->acceptDataCollector(dc);
}
/// Returns the position of the particles
inline const Vec2d& Node::R() const {
  //  cerr << "R = " << R() << endl;
  return(state_->R());
};

/// Returns the position of the particles
inline Vec2d&       Node::R() {
  //  cerr << "R = " << R() << endl;
  return(state_->R());
};

/// Returns the velocity of the particles
inline const Vec2d& Node::U() const {
  return(state_->U());
};

///Returns the velocity the particles
inline Vec2d& Node::U() {
  return(state_->U());
};

/// Returns the density of the particles
inline const double& Node::rho() const {
  return(state_->rho());
  };
/// Returns the density of the particles
inline double&       Node::rho() {
  return(state_->rho());
};

/// \bref first as phase field gradient matrix 
inline const Vec2d& Node::del_phi() const {
  return(state_->del_phi());
};

Vec2d&       Node::del_phi() {
  return(state_->del_phi());
};


inline double Node::getMass() const {
  return(state_->getMass());
};

inline void Node::setMass(double newM) {
  state_->setMass(newM);
};
inline double Node::getEta() const {
  return(state_->getEta());
};
inline double Node::getZeta() const {
  return(state_->getZeta());
};
inline double Node::getP() const {
  return(state_->getP());
};
inline double Node::getCs() const {
  return(state_->getCs());
};

inline double Node::getT() const {
  return(state_->getT());
};

inline void Node::setVolume(double newV) {
  state_->setVolume(newV);
};

Interaction* Node::createInteractionWith(Node *prtl_dest,
					 Force **force,
					 QuinticSpline &weight_function,
					 double dstc) {
  return(state_->createInteractionWith(prtl_dest->getState(),
				       force,
				       weight_function,
				       dstc));
};

// Interaction* Node::_createInteractionWith(Particle *prtl_org,
// 					     Force** force,
// 					     QuinticSpline& weight_function,
// 					     double dstc) {
//     return(state_->_createInteractionWith(prtl_org,
// 					 force,
// 					 weight_function,
// 					 dstc));
//   };

inline long Node::getParticleID() const {
    return(state_->getParticleID());
  };
inline int Node::getParticleType() const {
  return(state_->getParticleType());
};
inline int Node::getBDtype() const {
  return(state_->getBDtype());
};
inline int Node::getbd() const {
  return(state_->getbd());
};

  ///save values at step n
inline void Node::saveRRU() {
  state_->saveRRU();
};

///calculate the middle values at step n+1/2
inline void Node::setMiddleRRU() {
  state_->setMiddleRRU();
};
  
/// one step for predictor summation
inline void Node::predictorSummationStep(const double& dt) {
  state_->predictorSummationStep(dt);
};

///correction base on values on n step and change rate at n+1/2
inline void Node::correctorSummationStep(const double& dt) {
  state_->correctorSummationStep(dt);
};

///correct U
inline void Node::correctU() {
  state_->correctU();
};

///correction base on values on n step and change rate at n+1/2
inline void Node::correctRRU(const double& dt) {
  state_->correctRRU(dt);
};

//   ///set cell position
//    void Node::setCellPosition(int ncell_i, int ncell_j) {
//     state_->setCellPosition(ncell_i, ncell_j);
//   };

///increase shear rate
inline void Node::increaseShearRate(Vec2d dSRx, Vec2d dSRy) {
  state_->increaseShearRate(dSRx, dSRy);
};

///set all shear rates to 0
inline void Node::setShearRatetoZero() {
  state_->setShearRatetoZero();
};

///get shear rate in x direction
inline Vec2d Node::getShearRateX() const {
  return(state_->getShearRateX());
};

///get shear rate in y direction
inline Vec2d Node::getShearRateY() const {
  return(state_->getShearRateY());
};

///get the material number
inline int Node::getMaterialNumber() const {
  return(state_->getMaterialNumber());
};

  ///get the material name
inline char* Node::getMaterialName() const {
  return(state_->getMaterialName());
};

inline  Material* Node::getMaterial() const {
  return(state_->getMaterial());
}

///update pressure according to the equation
///of state
inline void Node::updatePressure() {
  state_->updatePressure();
};

inline void Node::increaseRandomU(const Vec2d& deltaU) {
  state_->increaseRandomU(deltaU);
};

inline void Node::increaseRandomUReal(const Vec2d& deltaU) {
  state_->increaseRandomUReal(deltaU);
};

inline void Node::increasePhi(double deltaPhi, int noi, int noj) {
  state_->increasePhi(deltaPhi, noi, noj);
};

inline void Node::increaseLapPhi(double deltaLapPhi, int noi, int noj) {
  state_->increaseLapPhi(deltaLapPhi, noi, noj);
};

inline void Node::setPhiToZero(int noi, int noj) {
  state_->setPhiToZero(noi, noj);
};

inline void Node::setLapPhiToZero(int noi, int noj) {
  state_->setLapPhiToZero(noi, noj);
};

inline double Node::getPhiElement(int noi, int noj) const {
  return(state_->getPhiElement(noi, noj));
};

inline void Node::increaseRandomdU(const Vec2d& deltadU) {
  state_->increaseRandomdU(deltadU);
};

inline void Node::increasedrhodt(const double& deltadrhodt) {
  state_->increasedrhodt(deltadrhodt);
};

inline void Node::increasedUdt(const Vec2d& deltadUdt) {
  state_->increasedUdt(deltadUdt);
};

inline void Node::setAlldToZero(double dt) {
  state_->setAlldToZero(dt);
};

inline void Node::setRandomUtoZero() {
  state_->setRandomUtoZero();
};

double Node::getKinEnergy() const {
  return(state_->getKinEnergy());
}

void Node::setUtoZero() {
  state_->setUtoZero();
}


inline Particle* Node::getState() const {
  assert(state_ != NULL);
  return state_;
}

// inline Particle* Node::getState() {
//   assert(state_ != NULL);
//   return state_;
// } 

inline Particle* Node::createGhost() {
  return state_->createGhost(*this);
}

long Node::getRealID() const {
  return state_->getRealID();
}

  ///return a pointer real particle 
  ///(for real particle return this)

Particle* Node::getReal() {
  return state_->getReal();
};



///output operator for Particle
ostream& operator<< (ostream& ostr, const Node& prtl) 
{
//  cout << "<<" << '\n';   
  return prtl.put(ostr);

}
