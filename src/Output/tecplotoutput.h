#ifndef SRC_OUTPUT_TECPLOTOUTPUT_H
#define SRC_OUTPUT_TECPLOTOUTPUT_H
#include "src/Output/output.h"

/// \file tecplotoutput.h
/// \brief Output the computational results
/// Output class 
class TecplotOutput : public Output {
public:
  ///constructor
  TecplotOutput();
  virtual ~TecplotOutput();
  ///output particle positions respected different materials
  virtual void OutputParticle(const Hydrodynamics &hydro,
		      const Boundary &boundary, 
		      const double Time, const Initiation &ini) ;

};
#endif // SRC_OUTPUT_TECPLOTOUTPUT_H
