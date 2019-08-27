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
    void RenewInteraction(QuinticSpline *);
    void SummationDensity();
    void SummationPhaseGradient();
    void UpdateForces();
    void RandomForces(double sqrtdt);
};

struct Interaction interaction_ini(struct Interaction *, Particle *,
				   Particle *, Force **, QuinticSpline *,
				   double dstc);
int interaction_renew(struct Interaction *, QuinticSpline *);
int interaction_density(struct Interaction *);
int interaction_phase_gradient(struct Interaction *);
int interaction_force(struct Interaction *);
int interaction_random_forces(struct Interaction *, double sqrtdt);
