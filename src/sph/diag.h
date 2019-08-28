struct Ini;
struct Manager;
struct MLS;
struct Kernel;
struct Boundary;
struct List;
struct Material;
struct Diag {
    double delta;
    double glb_ave_Ek;
    double *mtl_m;
    double rho_dstrb[2][101];
    double ttl_m;
    double **U[5];
    double vx_dstrb[2][101];
    double vy_dstrb[2][101];
    double *wght_cntr;
    double *wght_v;
    int gridx;
    int gridy;
    int n_average;
    int number_of_materials;
    int x_cells, y_cells;
    struct List *rho_list;
    struct List *vx_list;
    struct List *vy_list;
};

int Average(struct Diag *, struct Manager *, struct MLS *,
	    struct Kernel *);
int BuildDistribution(struct List *, double dstrb[2][101]);
int KineticInformation(struct Diag *, double Time, struct List *,
		       struct Material *);
int OutputAverage(struct Diag *, double Time);
int OutputProfile(struct Diag *, double Time);
int SaveStates(struct Diag *, struct List *);

struct Diag *diag_ini(struct Ini *, struct List *,
			  struct Material *);
int diag_fin(struct Diag *);
