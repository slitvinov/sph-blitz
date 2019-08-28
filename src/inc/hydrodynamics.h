struct Material;
struct Pair;
struct Force;
struct Particle;
struct Ini;
struct Boundary;
struct Material;
struct QuinticSpline;
struct Hydrodynamics {
    int number_of_materials;
    double gravity[2];
    double smoothinglength;
    double delta;
    double delta2;
    double delta3;
    double dt_g_vis;
    double dt_surf;
    struct List *pair_list;
    double viscosity_max;
    double surface_max;
    struct Material *materials;
    struct Force **forces;
    struct List *particle_list;
};

struct Hydrodynamics *hydrodynamics_ini(struct Ini *);
void hydrodynamics_fin(struct Hydrodynamics *);


void Zero_PhaseGradient(struct Hydrodynamics *, struct Boundary *);
void Zero_Random(struct Hydrodynamics *);
double GetTimestep(struct Hydrodynamics *);
void AddGravity(struct Hydrodynamics *);
void Corrector_summation(struct Hydrodynamics *, double dt);
void Predictor_summation(struct Hydrodynamics *, double dt);
void RandomEffects(struct Hydrodynamics *);
void UpdateChangeRate(struct Hydrodynamics *);
void UpdateDensity(struct Hydrodynamics *);
void UpdatePahseMatrix(struct Hydrodynamics *, struct Boundary *);
void UpdatePair(struct Hydrodynamics *, struct QuinticSpline *);
void UpdatePhaseGradient(struct Hydrodynamics *, struct Boundary *);
void UpdateRandom(struct Hydrodynamics *, double sqrtdt);
void UpdateState(struct Hydrodynamics *);
void UpdateSurfaceStress(struct Hydrodynamics *, struct Boundary *);
void ZeroChangeRate(struct Hydrodynamics *);
void Zero_density(struct Hydrodynamics *);
