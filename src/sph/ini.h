struct Force;
struct Kernel;
struct Material;
struct Ini {
    char inputfile[FILENAME_MAX];
    char Project_name[FILENAME_MAX];
    double art_vis;
    double box_size[2];
    double cell_size;
    double delta;
    double D_time;
    double End_time;
    double gravity[2];
    double p0;
    double rho0;
    double smoothinglength;
    double Start_time;
    double T0;
    double U0[2];
    int cell_ratio;
    int diag;
    int initial_condition;
    int number_of_materials;
    int x_cells;
    int y_cells;

    int x_clls;
    int y_clls;
    struct List ***cell_lists;
    struct List *NNP_list;

    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    struct List *b;

    double delta2;
    double delta3;
    double dt_g_vis;
    double dt_surf;
    struct List *pair_list;
    double viscosity_max;
    double surface_max;
    struct Material *materials;
    struct Force **forces;
    struct List *particle_list;
};

int initiation_ini(char *, struct Ini *);
void manager_build_particles(struct Ini *, struct Material *,
                             struct List *, struct Ini *);
int manager_build_nnp(struct Ini *, double[2]);
int manager_build_pair(struct Ini *,
                       struct List *, struct List *,
                       struct Force **, struct Kernel *);
int output_particles(struct Ini *, struct List *, struct Material *,
                     double);
int output_restart(struct Ini *, struct List *, double);

int boundary_fin(struct Ini *);
int boundary_condition(struct Ini *, struct List ***);
int boundary_build(struct Ini *, struct List ***, struct Material *);
int boundary_check(struct Ini *, struct List *);
struct List *boundary_list(struct Ini *);

void VolumeMass(struct List *, struct Ini *, struct Kernel *);
void step(int *, struct Ini *, double *, double, struct Kernel *);
