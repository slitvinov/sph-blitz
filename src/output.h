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
	void OutputParticle(Hydrodynamics &hydro, 
			    Boundary &boundary, 
			    double Time, const Initiation &ini);

	///Output real particle data for restart the computation
	void OutRestart(Hydrodynamics &hydro, 
			double Time, const Initiation& ini);
};

#endif //OUTPUT_H
