struct Ini;
struct Hydro;
struct Manager;
struct Boundary;
struct Kernel;
struct Diag;
struct MLS;
void step(int *ite, struct Hydro *, struct Manager *,
	  struct Boundary *, double *, double D_time, struct Diag *,
	  struct Ini *, struct Kernel *, struct MLS *);
