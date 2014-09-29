#ifndef NETCDFOUTPUTSTREAM_H
#define NETCDFOUTPUTSTREAM_H
#include <string>
#include "outputstream.h"
#include "netcdfcpp.h"


class Particle;
class PolymerParticle;

class NetCDFOutputStream: public OutputStream {
public:
  virtual ~NetCDFOutputStream();
  virtual void WriteFileDescription();
  virtual void VisitParticle(Particle*);
  virtual void VisitPolymerParticle(PolymerParticle*);

//   virtual void AddTimeStepAttribute(const string, 
// 				    Command*);
  virtual void WriteTimeStepAttribute(string, double);
  virtual void WriteParticleAttribute(string, double);
  virtual void NewTimeStep();
  virtual void Update(Subject*);
  virtual void Initialize();

  ///constructor
  NetCDFOutputStream();  
private:
  ///particle data output file name
  string timeparticlefilename_;

  NcFile* nc;
  NcDim* timestep;
  NcDim* space;
  NcDim* variparticle;
  NcVar* R;
  NcVar* U;

  long iparticle_;
  long itime_;
};
#endif 
