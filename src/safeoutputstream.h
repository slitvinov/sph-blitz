#ifndef SAFEOUTPUTSTREAM_H
#define SAFEOUTPUTSTREAM_H
#include <vector>
#include <queue> 
#include "outputstream.h"
#include "polymerparticle.h"


class Particle;
class PolymerParticle;
class Interaction;
class PolymerInteraction;
class OutputStream;
class Subject;

using namespace std;

///comparing pointers to PolymerParticle
struct Better {
  bool  operator() ( PolymerParticle* p1,
                     PolymerParticle* p2 ) const {
    return !((*p1) < (*p2));
  };
}; 


///a decorator for the outputstream 
///keeps the polymer particles in the right order for output
class SafeOutputStream: public OutputStream {
 public:

  ///write timestep attributes (attributes which are bound to the 
  ///current timestep (examples are average kinetic energy, average 
  ///density ...))
  virtual void WriteAllTimeStepAttributes();

  virtual void WriteAllParticleAttributes(Particle*);
  virtual void WriteAllParticleAttributes(PolymerParticle*);

  ///open a new time step
  virtual void NewTimeStep();

  ///attache timestep attribute 
  /// \param AttrName a name of the attribute in the output
  /// \param co a pointer to an  instance of command class 
  /// (co->Execute() returns the attribute value at the current time)
  virtual void AddTimeStepAttribute(string AttrName, 
				    Command* co);

  ///attache particle attribute 
  /// \param AttrName a name of the attribute in the output
  /// \param co a pointer to an  instance of command class 
  /// (co->Execute(Particle*) returns the attribute value at the current time)
  virtual void AddParticleAttribute(const string AttrName,
				    Command* co);

  ///remove attribute from the outputstream
  virtual void RemoveTimeStepAttribute(const string AttrName);

  ///virtual destructor 
  virtual ~SafeOutputStream();

  ///write an attribute value 
  /// \param AttrName a name of the attribute in the output
  /// \param AttrValue a value of the attribute
  virtual void WriteTimeStepAttribute(string AttrName, 
				      double AttrValue);

  ///write an attribute value 
  /// \param AttrName a name of the attribute in the output
  /// \param AttrValue a value of the attribute
  virtual void WriteParticleAttribute(string AttrName, 
				      double AttrValue);

  
  ///update function (derived from Observer)
  virtual void Update(Subject*);

  ///initialize the output stream
  virtual void Initialize();
  explicit SafeOutputStream(OutputStream*);  

  ///attach observer
  virtual void Attach(Observer*);
  ///detach observer
  virtual void Detach(Observer*);
  ///notify all observers that the subject changed
  virtual void Notify(double);
  /// get time
  virtual double GetTime() ;
  /// set time
  virtual void SetTime(double) ;

  ///visit hydrodynamic particle
  virtual void VisitParticle(Particle*);
  ///visit polymer particle
  virtual void VisitPolymerParticle(PolymerParticle*);
  ///visit hydrodynamic interaction
  virtual void VisitInteraction(Interaction*);
  ///visit polymer interaction
  virtual void VisitPolymerInteraction(PolymerInteraction*);
  ///support composite pattern
  //@{
  ///add DataCollector from Composite
  virtual void Add(DataCollector*);
  ///remove DataCollector from Composite
  virtual void Remove(DataCollector*);
private:
  OutputStream* stream_;
  ///vector to store PolymerParticle pointers
  //  vector<PolymerParticle*> vecPP;
  priority_queue<PolymerParticle*, vector<PolymerParticle*>, 
		 Better> vecPP;
};
#endif
