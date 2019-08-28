struct Ini;
struct Manager;
struct MLS;
struct Kernel;
struct Boundary;
struct List;
struct Material;
struct Diag;

int Average(struct Diag *, struct Manager *, struct MLS *,
	    struct Kernel *);
int BuildDistribution(struct List *, double dstrb[2][101]);
int KineticInformation(struct Diag *, double Time, struct List *,
		       struct Material *);
int OutputAverage(struct Diag *, double Time);
int OutputProfile(struct Diag *, double Time);
int SaveStates(struct Diag *, struct List *);

struct Diag *diag_ini(struct Ini *, struct List *, struct Material *);
int diag_fin(struct Diag *);
