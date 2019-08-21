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
	double R[2];///<position
        double P[2];///<momentum
        double U[2]; ///<velocityy
        double rho;///<density
        double p;///<pressure
        double T;///<Temperature
        double Cs;///<do not know what this is <b>!!!Question!!!</b>
        double rho_I;///<intermediate value for density (needed for integration)
        double rho_n; ////<do not know what this is ("conservative value") <b>!!!Question!!!</b>
	double m;///<mass
	double V;///<volume
	double e; ///<internal energy
	double R_I[2];///<intermediate position
	double P_I[2];///<intermediate momentim
	double U_I[2];///<intermediate velocity
	double P_n[2];///<do not knwo what this is n=?conservative???<b>!!!Question!!!</b>
	double U_n[2]; ///<do not knwo what this is n=?conservative???<b>!!!Question!!!</b>
	double ShearRate_x[2], ShearRate_y[2];

	//for multimaterials
	double eta, zeta; ///particle.h(line 69-74) viscosity of each particle<b>!!!Question!!!</b>
	double **phi; ///phase field matrix<b>!!!Question!!!</b>
	///first as phase field gradient matrix <b>!!!Question!!!</b>
	///then the independent values ([0][0] and [0][1]) of suface stress matrix <b>!!!Question!!!</b>
	double del_phi[2];
	
	//change rate for real particles
	double drhodt; ///<density change rate for real particles
        double dedt; ///<internal energy change rate for real particles
	double dUdt[2];///<acceleration change for real particles <b>or is it the other wa round</b>
        double _dU[2]; ///< random velocity change for real particles <b>or is it the other wa round</b>

	//other data
	
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

