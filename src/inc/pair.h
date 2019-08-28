struct Particle;
struct Force;
struct Ini;
struct QuinticSpline;
struct Pair {
    struct Particle *Org;
    struct Particle *Dest;
    struct Force **frc_ij;
    int noi;
    int noj;
    double mi;
    double rmi;
    double etai;
    double zetai;
    double mj;
    double rmj;
    double etaj;
    double zetaj;
    double rij;
    double rrij;
    double Wij;
    double Fij;
    double eij[2];
    double shear_rij;
    double bulk_rij;
};

struct Pair *interacion_ini(struct Particle *,
				   struct Particle *, struct Force **,
				   struct QuinticSpline *, double dstc);
struct Pair *pair_ini(struct Particle *,
				    struct Particle *, struct Force **,
				    struct QuinticSpline *q, double);
int pair_fin(struct Pair *);
void RenewPair(struct Pair *, struct QuinticSpline *);
void SummationDensity(struct Pair *);
void SummationPhaseGradient(struct Pair *);
void UpdateForces(struct Pair *);
void RandomForces(struct Pair *, double sqrtdt);
