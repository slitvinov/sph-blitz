/* err */
#define WARN(x) do {                                    \
	wprint("%s:%d: ", __FILE__, __LINE__);		\
	wprint x;					\
	wprint("\n");					\
    } while (0)

#define ABORT(x) do {				\
	WARN(x);				\
	exit(2);				\
    } while (0)

int wprint(const char *, ...);

/* list */
struct List;
struct ListNode;
int list_endp(struct List *, struct ListNode *);
struct ListNode *list_first(struct List *);
struct ListNode *list_next(struct List *, struct ListNode *);
void *list_retrieve(struct List *, struct ListNode *);
void list_insert(struct List *, struct ListNode *, void *);
void list_remove(struct List *, struct ListNode *);
void list_clear(struct List *);
struct List *list_ini(void);
void list_fin(struct List *);

/* kernel */
struct Kernel;
struct Kernel *kernel_ini(double smoothingLength);
int kernel_fin(struct Kernel *);
double w(struct Kernel *, double);
double F(struct Kernel *, double);

/* material */
struct Material {
    char material_name[FILENAME_MAX];
    int number;
    int material_type;
    double eta;
    double zeta;
    double gamma;
    double nu;
    double b0;
    double rho0;
    double a0;
};

double get_p(struct Material *, double rho);
double get_Cs(struct Material *, double p, double rho);

/* particle */
struct Particle {
    int cell_i;
    int cell_j;
    struct Material *mtl;
    struct Particle *rl_prtl;
    double R[2];
    double U[2];
    double rho;
    double p;
    double T;
    double Cs;
    double rho_I;
    double rho_n;
    double m;
    double V;
    double R_I[2];
    double U_I[2];
    double U_n[2];
    double eta;
    double zeta;
    double **phi;
    double del_phi[2];
    double drhodt;
    double dUdt[2];
    double _dU[2];

    /// \brief boundary particle or not
    ///
    ///- 0: inside the boundary
    ///- 1: on the boundary
    int bd;

    ///boundary type if bd = 1
    ///- 0 wall particle with zero or constant velocity but never move its position
    ///- 1 ghost particle for perodic boundary
    int bd_type;

    ///\brief ID number
    ///
    ///- a real particle has a unique positive ID
    ///- a wall particle has zero ID
    ///- an ghost particle (for perodic boundary condition)
    ///has a negtive ID of its corresponding real particle
    long ID;
};

struct Particle *particle_real(double[2], double[2], double, double,
                               double, struct Material *);
struct Particle *particle_image(struct Particle *);
struct Particle *particle_mirror(struct Particle *, struct Material *);
int particle_fin(struct Particle *);
int particle_copy(struct Particle *, struct Particle *, int type);

/* ini */
struct Force;
struct Ini {
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
int initiation_fin(struct Ini *);
void manager_build_particles(struct Ini *, struct Material *,
                             struct List *, struct Ini *);
int output_particles(struct Ini *, struct List *, struct Material *,
                     double);
int output_restart(struct Ini *, struct List *, double);

int boundary_condition(struct Ini *, struct List ***);
int boundary_build(struct Ini *, struct List ***, struct Material *);
int boundary_check(struct Ini *, struct List *);

void VolumeMass(struct List *, struct Ini *, struct Kernel *);
void step(int *, struct Ini *, double *, double, struct Kernel *);
