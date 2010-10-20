#ifndef SRC_OUTPUT_OUTPUT_H
#define SRC_OUTPUT_OUTPUT_H
/// \file output.h 
/// \brief Output the computational results
/// Output class 
class Output {
  ///constructor
public:
  Output();
  virtual ~Output();
  ///output particle positions respected different materials
  virtual void OutputParticle(const Hydrodynamics &hydro,
		      const Boundary &boundary, 
		      const double Time, const Initiation &ini) = 0;
  ///Output real particle data for restart the computation
  virtual void OutputRestart(const Hydrodynamics &hydro, 
		  const double Time, const Initiation& ini);
};
#endif // SRC_OUTPUT_OUTPUT_H
