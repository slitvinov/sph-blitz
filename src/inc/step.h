struct Ini;
struct Hydrodynamics;
struct Manager;
struct Boundary;
struct QuinticSpline;
struct Diagnose;
struct MLS;
void step(int *ite, struct Hydrodynamics *, struct Manager *,
	  struct Boundary *, double *, double D_time, struct Diagnose *,
	  struct Ini *, struct QuinticSpline *, struct MLS *);
