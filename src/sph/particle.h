struct Material;
struct Particle {
    int cell_i;
    int cell_j;
    struct Material *mtl;
    struct Particle *rl_prtl;
    double R[2];
    double P[2];
    double U[2];
    double rho;
    double p;
    double T;
    double Cs;
    double rho_I;
    double rho_n;
    double m;
    double V;
    double e;
    double R_I[2];
    double P_I[2];
    double U_I[2];
    double P_n[2];
    double U_n[2];
    double ShearRate_x[2];
    double ShearRate_y[2];
    double eta;
    double zeta;
    double **phi;
    double del_phi[2];
    double drhodt;
    double dedt;
    double dUdt[2];
    double _dU[2];

    /// \brief boundary particle or not
    ///
    ///- 0: inside the boundary
    ///- 1: on the boundary
    int bd;

    ///boundary type if bd = 1
    ///- 0 wall particle with zero or constant velocity but never move its position
    ///- 1 ghost particle for perodic boundary
    int bd_type;

    ///\brief ID number
    ///
    ///- a real particle has a unique positive ID
    ///- a wall particle has zero ID
    ///- an ghost particle (for perodic boundary condition)
    ///has a negtive ID of its corresponding real particle
    long ID;
};

struct Particle *particle_real(double[2], double[2], double, double,
                               double, struct Material *);
struct Particle *particle_image(struct Particle *);
struct Particle *particle_wall(double, double, struct Material *);
struct Particle *particle_mirror(struct Particle *, struct Material *);
int particle_fin(struct Particle *);
int particle_copy(struct Particle *, struct Particle *, int type);
