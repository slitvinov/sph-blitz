struct Hydro;
struct Boundary;
struct Kernel;
void step(int *ite, struct Hydro *, struct Ini *,
          struct Boundary *, double *, double D_time, struct Kernel *);
