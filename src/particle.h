class Material;
class Initiation;

class Particle {
public:
    Particle(double position[2], double velocity[2], double density, double pressure, double temperature, Material &material);
    Particle(double x, double y, double u, double v, Material &material);
    Particle(Particle &RealParticle);
    Particle(Particle &RealParticle, Material &material);
    ~Particle();
    void StatesCopier(Particle &RealParticle, int type);
    int cell_i;
    int cell_j;
    Material *mtl;
    Particle *rl_prtl;
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
    x	double P_I[2];
    double U_I[2];
    double P_n[2];
    double U_n[2];
    double ShearRate_x[2], ShearRate_y[2];
    double eta, zeta;
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
    static long ID_max;
};

