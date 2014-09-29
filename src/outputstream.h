#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H
#include <map>
#include <string>
#include "command.h"
#include "observer.h"
#include "subject.h"
#include "datacollector.h"


class Particle;
class PolymerParticle;
class Interaction;
class PolymerInteraction;
class OutputStream;
class Subject;

using namespace std;

///an abstract class for output SPH data 
class OutputStream: public Observer, public Subject, public DataCollector {
 public:
  ///this class is a Singleton (only one instance exist)
  /// OutputStream::Instance() returns the pointer to the existing instance of 
  /// the class (or creates one if there was no instance)
  static OutputStream* Instance();
  

  ///write timestep attributes (attributes which are bound to the 
  ///current timestep (examples are average kinetic energy, average 
  ///density ...))
  virtual void WriteAllTimeStepAttributes();

  virtual void WriteAllParticleAttributes(Particle*);
  virtual void WriteAllParticleAttributes(PolymerParticle*);

  ///add information about where the data came from and what has been done to it
  virtual void WriteFileDescription();

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
  virtual ~OutputStream();

  ///write an attribute value 
  /// \param AttrName a name of the attribute in the output
  /// \param AttrValue a value of the attribute
  virtual void WriteTimeStepAttribute(string AttrName, 
				      double AttrValue) = 0;

  ///write an attribute value 
  /// \param AttrName a name of the attribute in the output
  /// \param AttrValue a value of the attribute
  virtual void WriteParticleAttribute(string AttrName, 
				      double AttrValue) = 0;

  
  ///update function (derived from Observer)
  virtual void Update(Subject*);

  ///initialize the output stream
  virtual void Initialize();
  
 protected:  
  OutputStream();  
  static OutputStream* instance_;

  ///an atrributes map (to keep name of attribute --- command pairs)
  map<const string, Command*> registry_;
  
  ///an particle attribute map (to keep naem of attribute --- command pairs)
  map<const string, Command*> pAttrRegistry_;
};
#endif
