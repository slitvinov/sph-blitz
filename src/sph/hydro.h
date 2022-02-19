struct Material;
struct Force;
struct Particle;
struct Ini;
struct Boundary;
struct Material;
struct Kernel;
struct Hydro {
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

struct Hydro *hydro_ini(struct Ini *);
void hydro_fin(struct Hydro *);


void Zero_PhaseGradient(struct Hydro *, struct Ini *);
void Zero_Random(struct Hydro *);
double GetTimestep(struct Hydro *);
void AddGravity(struct Hydro *);
void Corrector_summation(struct Hydro *, double dt);
void Predictor_summation(struct Hydro *, double dt);
void RandomEffects(struct Hydro *);
void UpdateChangeRate(struct Hydro *);
void UpdateDensity(struct Hydro *);
void UpdatePahseMatrix(struct Hydro *, struct Ini *);
void UpdatePair(struct Hydro *, struct Kernel *);
void UpdatePhaseGradient(struct Hydro *, struct Ini *);
void UpdateRandom(struct Hydro *, double sqrtdt);
void UpdateState(struct Hydro *);
void UpdateSurfaceStress(struct Hydro *, struct Ini *);
void ZeroChangeRate(struct Hydro *);
void Zero_density(struct Hydro *);
