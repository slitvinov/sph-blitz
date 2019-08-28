struct Particle;
struct Force;
struct Ini;
struct QuinticSpline;
struct Interaction {
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

struct Interaction *interacion_ini(struct Particle *,
				   struct Particle *, struct Force **,
				   struct QuinticSpline *, double dstc);
struct Interaction *interaction_ini(struct Particle *,
				    struct Particle *, struct Force **,
				    struct QuinticSpline *q, double);
int interaction_fin(struct Interaction *);
void RenewInteraction(struct Interaction *, struct QuinticSpline *);
void SummationDensity(struct Interaction *);
void SummationPhaseGradient(struct Interaction *);
void UpdateForces(struct Interaction *);
void RandomForces(struct Interaction *, double sqrtdt);
