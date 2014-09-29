#ifndef TEXTOUTPUTSTREAM_H
#define TEXTOUTPUTSTREAM_H
#include <iostream>
#include <fstream>

#include "outputstream.h"
#include "observer.h"
#include "subject.h"

using namespace std;

class TextOutputStream: public OutputStream {
public:
  TextOutputStream();
  virtual ~TextOutputStream();
  
  virtual void VisitParticle(Particle*);
  virtual void VisitPolymerParticle(PolymerParticle*);
  virtual void VisitInteraction(Interaction*);
  virtual void VisitPolymerInteraction(PolymerInteraction*);
  
  virtual void NewTimeStep();
  virtual void Update(Subject*);
  virtual void  WriteTimeStepAttribute(string AttrName, 
				       double AttrName);
  virtual void WriteParticleAttribute(string, double);

  ///output headers to files
  virtual void Initialize();
private:
  ///names of output files
  string attrfilename_;
  string particlefilename_;
 
  ///output file
  ofstream foutTime_;
  ofstream foutPart_;
  
  ///the number of timestep
  long itime_;
  
  ///the number of particles
  long iparticle_;
};

#endif
