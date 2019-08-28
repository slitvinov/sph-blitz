struct Ini;
struct Particle;
struct Kernel;
struct List;
struct MLS;

int mls_solve(struct MLS *, int order);

int mls_map(struct MLS *, double point[2], struct List *,
	    struct Kernel *, int order);
int mls_fin(struct MLS *);
struct MLS *mls_ini(int MLS_MAX);
int mls_phi(struct MLS *, double **);
