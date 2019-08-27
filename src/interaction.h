struct Particle;
struct Force;
struct Initiation;
struct QuinticSpline;
struct Interaction {
    Particle *Org;
    Particle *Dest;
    Force **frc_ij;
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
    Interaction(Particle *, Particle *, Force **, QuinticSpline *,
		double dstc);
};

void RenewInteraction(struct Interaction*, QuinticSpline *);
void SummationDensity(struct Interaction*);
void SummationPhaseGradient(struct Interaction*);
void UpdateForces(struct Interaction*);
void RandomForces(struct Interaction*, double sqrtdt);
