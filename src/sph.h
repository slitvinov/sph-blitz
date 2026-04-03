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
int listendp(struct List *, struct ListNode *);
struct ListNode *listfirst(struct List *);
struct ListNode *listnext(struct List *, struct ListNode *);
void *listget(struct List *, struct ListNode *);
void listins(struct List *, struct ListNode *, void *);
void listrm(struct List *, struct ListNode *);
void listclr(struct List *);
struct List *listnew(void);
void listfree(struct List *);

/* kernel */
struct Kernel;
struct Kernel *kernelnew(double h);
int kernelfree(struct Kernel *);
double w(struct Kernel *, double);
double F(struct Kernel *, double);

/* material */
struct Material {
    char name[FILENAME_MAX];
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

double getp(struct Material *, double rho);
double getcs(struct Material *, double p, double rho);

/* particle */
struct Particle {
    int cell_i;
    int cell_j;
    struct Material *mtl;
    struct Particle *real;
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
    double dphi[2];
    double drhodt;
    double dUdt[2];
    double _dU[2];
    int bd;	/* 0: real, 1: boundary */
    int btype;	/* 0: wall, 1: periodic ghost */
    long ID;
};

struct Particle *prtreal(double[2], double[2], double, double,
                               double, struct Material *);
struct Particle *prtimage(struct Particle *);
struct Particle *prtmirror(struct Particle *, struct Material *);
int prtfree(struct Particle *);
int prtcopy(struct Particle *, struct Particle *, int type);

/* ini */
struct Force;
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
    int diag;
    int initial_condition;
    int nmat;
    int nx;
    int ny;

    int mx;
    int my;
    struct List ***cells;
    struct List *nnpl;

    double uxl[2];
    double uxr[2];
    double uyd[2];
    double uyu[2];
    int bxl;
    int bxr;
    int byd;
    int byu;
    struct List *b;

    double delta2;
    double delta3;
    double dt_g_vis;
    double dt_surf;
    struct List *pair_list;
    double numax;
    double sigmax;
    struct Material *materials;
    struct Force **forces;
    struct List *parts;
};

int iniread(char *, struct Ini *);
int inifin(struct Ini *);
void mkparts(struct Ini *, struct Material *, struct List *, struct Ini *);
int prtout(struct Ini *, struct List *, struct Material *, double);
int rstout(struct Ini *, struct List *, double);
int bndcond(struct Ini *, struct List ***);
int bndbuild(struct Ini *, struct List ***, struct Material *);
int bndcheck(struct Ini *, struct List *);
void volmass(struct List *, struct Ini *, struct Kernel *);
void step(int *, struct Ini *, double *, double, struct Kernel *);
