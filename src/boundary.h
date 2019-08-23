struct Boundary
{
    double box_size[2];
    int x_clls, y_clls;
    void show_information();
    void Boundary_W(Particle *prtl);
    void Boundary_E(Particle *prtl);
    void Boundary_S(Particle *prtl);
    void Boundary_N(Particle *prtl);
    void Boundary_SW(Particle *prtl);
    void Boundary_SE(Particle *prtl);
    void Boundary_NW(Particle *prtl);
    void Boundary_NE(Particle *prtl);
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    List b; 
    Boundary(Initiation *ini, Hydrodynamics *hydro, ParticleManager *particles);
    void BuildBoundaryParticles(ParticleManager *particles, Hydrodynamics *hydro);
    void BoundaryCondition(ParticleManager *particles);
    void RunAwayCheck(Hydrodynamics *hydro);
};
