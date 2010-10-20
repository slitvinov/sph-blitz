#ifndef SRC_OUTPUT_PLAINOUTPUT_H
#define SRC_OUTPUT_PLAINOUTPUT_H
#include "src/Output/output.h"

/// \file plainoutput.h
/// \brief Output the computational results
/// Output class 
class PlainOutput : public Output {
public:
  ///constructor
  PlainOutput();
  virtual ~PlainOutput();
  ///output particle positions respected different materials
  virtual void OutputParticle(const Hydrodynamics &hydro,
		      const Boundary &boundary, 
		      const double Time, const Initiation &ini) ;

};
#endif // SRC_OUTPUT_PLAINOUTPUT_H
