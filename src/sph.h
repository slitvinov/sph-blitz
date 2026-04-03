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

/* particle */
struct Material {
	char name[FILENAME_MAX];
	int number;
	double eta;
	double zeta;
	double gamma;
	double b0;
	double rho0;
	double a0;
};

struct Particle {
	struct Material *mtl;
	struct Particle *real;
	double R[2];
	double U[2];
	double rho;
	double p;
	double T;
	double m;
	double R_I[2];
	double U_I[2];
	double **phi;
	double dphi[2];
	double dUdt[2];
	double _dU[2];
	int bd;	/* 0: real, 1: boundary */
	int btype;	/* 0: wall, 1: periodic ghost */
	int id;
};

struct Particle *prtreal(double[2], double[2], double, double,
							   double, struct Material *);
struct Particle *prtimage(struct Particle *);
struct Particle *prtmirror(struct Particle *, struct Material *);
int prtfree(struct Particle *);
int prtcopy(struct Particle *, struct Particle *, int type);

/* cell */
struct Cell {
	struct Particle **data;
	int n, cap;
};

/* boundary tables */
struct Edge {
	int type, coord, ghost, adj, opp, perp_lo, perp_hi;
	double refl, shift, *U_bnd;
};
struct Corner {
	int type_x, type_y;
	int ghost_i, ghost_j, adj_i, adj_j, opp_i, opp_j;
	double refl_x, shift_x, refl_y, shift_y;
	double *U_x, *U_y;
};

/* ini */
struct Force {
	double sigma;
	double shear_slip, bulk_slip;
};

struct Ini {
	char project[FILENAME_MAX];
	double art_vis;
	double box_size[2];
	double cs;
	double delta;
	double tout;
	double t1;
	double gravity[2];
	double p0;
	double rho0;
	double h;
	double t0;
	double T0;
	double U0[2];
	int cr;
	int initial_condition;
	int nmat;

	/* kernel */
	double rh, fw, fg;

	int mx;
	int my;
	struct Cell **cells;

	struct Particle **nnp;
	int nnnp, nnpcap;

	double uxl[2];
	double uxr[2];
	double uyd[2];
	double uyu[2];
	int bxl;
	int bxr;
	int byd;
	int byu;

	struct Particle **bnd;
	int nbnd, bndcap;

	struct Edge edges[4];
	struct Corner corners[4];

	double dt_g_vis;
	double dt_surf;

	struct Material *materials;
	struct Force **forces;

	struct Particle **parts;
	int nparts, partcap;
};

int iniread(char *, struct Ini *);
int inifin(struct Ini *);
void mkparts(struct Ini *, struct Material *, struct Ini *);
int prtout(struct Ini *, struct Material *, double);
int rstout(struct Ini *, double);
int bndcond(struct Ini *);
int bndbuild(struct Ini *, struct Material *);
int bndcheck(struct Ini *);
void volmass(struct Ini *);
void step(int *, struct Ini *, double *, double);
