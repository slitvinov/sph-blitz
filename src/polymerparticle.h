#ifndef POLYMERPARTICLE_H
#define POLYMERPARTICLE_H
#include <iostream>
#include "vec2d.h"
//#include "wiener.h"
//#include "dllist.h"
#include "particle.h"
#include <vector>

//#include "interaction.h"
#include "polymerinteraction.h"

class Force;
class QuinticSpline;
class PolymerParticle;
//class PolymerInteraction;
class Material;

///Polymer particle class
class PolymerParticle : public Particle
{
  //the number of polymer particles
  long polyID_; 
  
  ///the list of polymer interactions the polymer particles involved in
  PolymerInteraction* polyInt_;

  ///previous polymer in the chain
  PolymerParticle* prevPoly_;
public:
  static long nPolyParticle_; 
  PolymerParticle(const Vec2d& position, 
		  const Vec2d& velocity, 
		  double density, double pressure, 
		  double temperature, 
		  Material &material);

  ///create polymer particle from plane particle  
  explicit PolymerParticle(Node*);
protected:
  ///creat a ghost particle 
  ///used by createGhost method
  explicit PolymerParticle(Node&);
public:
  virtual ~PolymerParticle();
  virtual Interaction* createInteractionWith(Particle *prtl_dest,
					    Force **force,
					    QuinticSpline &weight_function,
					    double dstc);

  virtual Interaction* _createInteractionWith(Particle *prtl_org,
					     Force** force,
					     QuinticSpline& weight_function,
					     double dstc);
  ///accept data collector
  virtual void acceptDataCollector(DataCollector*);


  ///output particle data
  virtual ostream& put(ostream& ostr) const;

  ///return the header for the output file
  ///  virtual vector<string> getHeader() const;
  virtual Vec2d& U();
  virtual const Vec2d& U() const;

  ///create ghost particle
  virtual Particle* createGhost(Node&);
  
  ///get connected interaction
  virtual PolymerInteraction* getInt();

  ///set a pointer  to a previous particles in the chain
  virtual void setPrev(PolymerParticle*);

  ///get previous Polymer particle in the chain
  virtual PolymerParticle* getPrev();
  

  virtual int getParticleType() const;    
  ///returns the number of polymer particles
//   virtual void increaseRandomdU(const Vec2d& deltadU);
  virtual long nPolyParticle() const;
  virtual long getPolyID() const;
  virtual bool isHead() const;
  virtual bool isTail() const;

  bool operator<(const PolymerParticle& pp) const;
};
#endif
