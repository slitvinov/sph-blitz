struct Ini;
struct Boundary;
int output_particles(struct Ini *, struct List *, struct Material *,
                     double Time);
int output_restart(struct Ini *, struct List *, double Time);
