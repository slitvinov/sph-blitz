struct Hydro;
struct Manager;
struct Boundary;
struct Kernel;
void step(int *ite, struct Hydro *, struct Manager *,
          struct Boundary *, double *, double D_time,
          struct Kernel *);
