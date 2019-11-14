struct Ini;
struct Boundary;
struct Manager;
struct Output;
int output_particles(struct Output *, struct List *, struct Material *,
                     struct Boundary *, double Time);
int output_restart(struct Output *, struct List *, double Time);
struct Output *output_ini(struct Ini *);
int output_fin(struct Output *);
