struct Particle;
struct Boundary;
struct Ini;
struct Force;
struct Kernel;

struct Manager {
    double smoothinglength;
    double cell_size;
    int cell_ratio;
    int x_clls;
    int y_clls;
    struct List ***cell_lists;
    struct List *NNP_list;
};

int manager_update_list(struct Manager *);
void manager_build_particles(struct Manager *, struct Material *,
                             struct List *, struct Ini *);
int manager_build_nnp(struct Manager *, double[2]);
int manager_build_pair(struct Manager *,
                       struct List *, struct List *,
                       struct Force **, struct Kernel *);
struct Manager *manager_ini(struct Ini *);
int manager_fin(struct Manager *);
