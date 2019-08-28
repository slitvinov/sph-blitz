struct Initiation;
struct Manager;
struct MLS;
struct QuinticSpline;
struct Boundary;
struct List;
struct Diagnose {
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

int Average(struct Diagnose *, struct Manager *, struct MLS *,
	    struct QuinticSpline *);
int BuildDistribution(struct List *, double dstrb[2][101]);
int KineticInformation(struct Diagnose *, double Time, struct List *,
		       struct Material *);
int OutputAverage(struct Diagnose *, double Time);
int OutputProfile(struct Diagnose *, double Time);
int SaveStates(struct Diagnose *, struct List *);

struct Diagnose *diag_ini(struct Initiation *, struct List *,
			  struct Material *);
int diag_fin(struct Diagnose *);
