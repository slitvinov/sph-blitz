#ifndef OUTPUT_H
#define OUTPUT_H
/// \file output.h 
/// \brief Output the computational results
/// Output class 
class Output {
public:
  ///constructor
  Output();
  ///output particle positions respected different materials
  void OutputParticle(const Hydrodynamics &hydro,
		      const Boundary &boundary, 
		      const double Time, const Initiation &ini, 
		      const spSolidObstacles &obstacles);
  ///Output real particle data for restart the computation
  void OutRestart(const Hydrodynamics &hydro, 
		  const double Time, const Initiation& ini);
};
#endif //OUTPUT_H
