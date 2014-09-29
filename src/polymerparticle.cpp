#include "vec2d.h"
#include "polymerinteraction.h"
#include "node.h"
#include "particle.h"
#include "polymerparticle.h"
#include "initiation.h"
#include "interactionstate.h"
#include "datacollector.h"
#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif

long PolymerParticle::nPolyParticle_ = 0;

PolymerParticle::PolymerParticle(const Vec2d& position, 
				 const Vec2d& velocity, 
				 double density, 
				 double pressure, 
				 double temperature, 
				 Material &material):
Particle(position, 
	 velocity,
	 density, 
	 pressure,
	 temperature,
	 material) {
  //increase the polymer particle counter
  nPolyParticle_++;
  polyID_ = nPolyParticle_;
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("polymerparticle");
  LOG4CXX_DEBUG(Logger,  "Create PolymerParticle with number: " +
		stringify(getParticleID()));
  LOG4CXX_DEBUG(Logger, "The number of PolymerParticles is " + 
		stringify(nPolyParticle_));
#endif
}

PolymerParticle::PolymerParticle(Node* Pa):
  Particle(Pa->R(),
	   Pa->U(),
	   Pa->rho(),
	   Pa->getP(),
	   Pa->getT(),
	   *(Pa->getMaterial())) {
  //increase the polymer particle counter  
  nPolyParticle_++;
  polyID_ = nPolyParticle_;  
#ifndef NOLOG
  log4cxx::LoggerPtr Logger = log4cxx::Logger::getLogger("polymerparticle");
  LOG4CXX_DEBUG(Logger,  "Create PolymerParticle with number: " +
		stringify(getParticleID()));
  LOG4CXX_DEBUG(Logger, "The number of PolymerParticles is " + 
		stringify(nPolyParticle_));
#endif
  //  this.setCellPosition(
}

//----------------------------------------------------------------------------------------
//						creat a ghost particle 
//----------------------------------------------------------------------------------------
PolymerParticle::PolymerParticle(Node &RealNode):
  Particle::Particle(RealNode)
//   bd(1), 
//   bd_type(1),
//   //give a new ID number
//   ID(0),
//   polyID_(RealNode.getPolyID())
{
  polyID_ = 
    static_cast<PolymerParticle*>(RealNode.getState())->getPolyID();
}

//output
ostream& PolymerParticle::put(ostream& ostr) const{
  ///get a pointer to initiation Singelton
  Initiation* pini = Initiation::Instance();
  ///output

  ostr<<pini->dms_length(R()[0])<<' ' <<
    pini->dms_length(R()[1])<<' '<<
    pini->dms_velocity(U()[0])<<' ' <<
    pini->dms_velocity(U()[1]) << ' ' <<
    pini->dms_volume(getVolume()) << ' ' <<
    1;  
    ///0: plane particle
    ///1: polymer particle 
  return ostr;
}

// vector<string> PolymerParticle::getHeader() const {
//   vector<string> v;
//   v.push_back("Rx");
//   v.push_back("Ry");
//   v.push_back("Ux");
//   v.push_back("Uy");
//   v.push_back("V");
//   v.push_back("type");
//   return v;
// }


Interaction* PolymerParticle::createInteractionWith(Particle* prtl_dest,
					  Force **force, 
					  QuinticSpline &weight_function,
					  double dstc) {
  //  cout << prtl_dest->getParticleType() << endl;
  return (prtl_dest->_createInteractionWith(this,
					    force, 
					    weight_function,
					    dstc));
}

PolymerParticle::~PolymerParticle() {
}

Interaction* PolymerParticle::_createInteractionWith(Particle* prtl_org,
						     Force** force,
						     QuinticSpline& weight_function,
						     double dstc) {
  PolymerParticle* polyprtl_org = static_cast<PolymerParticle*>(prtl_org);
  long dPolyID = abs(polyprtl_org->polyID_ - polyID_);
  Interaction* pnewinter;
  if (dPolyID == 1) {
    PolymerInteraction* p_temp = new PolymerInteraction(polyprtl_org, this,
				force, weight_function,
				dstc);
    ///if org is a real particle and has a higher polyID 
    ///attach interaction to this particle
#ifdef QFIX
    if (polyprtl_org->getPolyID() > polyID_) {
      polyprtl_org->polyInt_ = p_temp;
      
      polyprtl_org->setPrev(this);
    }
    else {
      if (ID != 0) {
	polyInt_ = p_temp;	
	setPrev(polyprtl_org);
      }	
    }
#endif
    pnewinter = p_temp;


    ///attache interaction to the particle
#ifndef NOLOG
    log4cxx::LoggerPtr Logger = 
      log4cxx::Logger::getLogger("polymerparticle.create");
    LOG4CXX_DEBUG(Logger,  "===");
    LOG4CXX_DEBUG(Logger,  "Org ID " 
		  + stringify<int>(polyprtl_org->getPolyID()));
    LOG4CXX_DEBUG(Logger,  "Dest ID " 
		  + stringify<int>(polyID_));
    LOG4CXX_DEBUG(Logger,  "===");
#endif

    //no more then 2 interactions
    //    assert(listInt_.size() < 3);

  }
  else {
    pnewinter = new Interaction(polyprtl_org, this,
				force, weight_function,
				dstc); 
  }
  return pnewinter;    
}

void PolymerParticle::acceptDataCollector(DataCollector* dc) {
  if (dc==NULL) {
    cout << "NULL" << '\n';
  }
  dc->VisitPolymerParticle(this);
}

// void PolymerParticle::increaseRandomdU(const Vec2d& deltadU) {
//   // do nothing
// }

Vec2d&       PolymerParticle::U() {
  return U_;
}

const Vec2d& PolymerParticle::U() const {
   return U_;
}



int PolymerParticle::getParticleType() const {
  return 1;
}

long PolymerParticle::nPolyParticle() const {
  return nPolyParticle_;
}

long PolymerParticle::getPolyID() const {
  return polyID_;
}

bool PolymerParticle::isHead() const {
  return (polyID_==1);
}

bool PolymerParticle::isTail() const {
  return (polyID_==nPolyParticle_);
}

Particle* PolymerParticle::createGhost(Node& old_node) {
  return new PolymerParticle(old_node);
}

PolymerInteraction* PolymerParticle::getInt() {
  assert(polyInt_ != NULL);
  return polyInt_;
}

PolymerParticle* PolymerParticle::getPrev() {
  return prevPoly_;
}


///output operator for PolymerParticle
ostream& operator<< (ostream& ostr, const PolymerParticle& prtl) 
{
//  cout << "<<" << '\n';   
  return prtl.put(ostr);
}

void PolymerParticle::setPrev(PolymerParticle* pp) {
  assert(polyID_ - pp->getPolyID() == 1);
  prevPoly_ = pp;
}

///comparing two PolymerParticle
bool PolymerParticle::operator<(const PolymerParticle& pp) const
{
  return getPolyID() < pp.getPolyID();
} 
