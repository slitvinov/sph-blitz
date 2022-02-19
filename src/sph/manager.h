struct Particle;
struct Boundary;
struct Ini;
struct Force;
struct Kernel;

int manager_update_list(struct Ini *);
void manager_build_particles(struct Ini *, struct Material *,
                             struct List *, struct Ini *);
int manager_build_nnp(struct Ini *, double[2]);
int manager_build_pair(struct Ini *,
                       struct List *, struct List *,
                       struct Force **, struct Kernel *);
int manager_fin(struct Ini *);
