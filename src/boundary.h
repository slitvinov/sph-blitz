struct QuinticSpline;
struct Initiation;
struct Hydrodynamics;
struct ParticleManager;
struct Boundary
{
    double box_size[2];
    int x_clls, y_clls;
    void Boundary_W(Particle*);
    void Boundary_E(Particle*);
    void Boundary_S(Particle*);
    void Boundary_N(Particle*);
    void Boundary_SW(Particle*);
    void Boundary_SE(Particle*);
    void Boundary_NW(Particle*);
    void Boundary_NE(Particle*);
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    List *b;
    Boundary(Initiation*, Hydrodynamics*, ParticleManager*);
    void BuildBoundaryParticles(ParticleManager*, Hydrodynamics*);
    void BoundaryCondition(ParticleManager*);
    ~Boundary();
};

int boundary_check(Boundary*, Hydrodynamics*);
