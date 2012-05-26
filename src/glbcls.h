/// \file glbcls.h
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief Global class declarations

#ifndef GLBCLS_H
#define GLBCLS_H

#ifdef _OPENMP
#include <omp.h>
#endif

//#include <iostream>
#include "vec2d.h"
#include "wiener.h"
#include "dllist.h"
//-----------------------------------------------------------------------
//					Global constant
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//					Pre-claimer
//-----------------------------------------------------------------------
class Initiation; class Kernel; class MLS; class Interaction; class ParticleManager;
class Particle; class Initiation; class Boundary; class Force; class Output; class Diagnose;
class Hydrodynamics; class ListNode; class Material; class BetaSpline; class QuinticSpline;
//-----------------------------------------------------------------------
//					Initiation
//-----------------------------------------------------------------------
class Initiation {
	
	friend class Material;
	friend class Hydrodynamics;
	//reference length, speed, and density for dimensionless

public:
	
	//the project name
	char Project_name[125];

	/// if simulation is special
	/// 0 means generic
	int sim_special;

	// a fraction of the domain in y direction where 
	// force is not applyed
	double tube_no_force_region;

	//number of materials
	//the no. zero material is always the wall
	//therefore at least 2 materials should be included
	int number_of_materials;
	//the global inputfile name: a *.cfg file
	char inputfile[125];
	//initial condition marker: 0 initialize from the .cfg file; 
	//1 read from the .rst file particle by particle with non-dimensional data
	int initial_condition;
	//diagnose information maker: 1 output diagnose information
	int diagnose;
	//artificial viscosity
	double art_vis;

	//smoothinglength
	double smoothinglength;
	//the compuational domain size
	Vec2d box_size;
	//cell size
	double cell_size;
	//the inital particle distance
	double delta;
	//the ration between smoothing length and inital particle distance
	int hdelta;
	//cells matrix for real particles
	int x_cells, y_cells;
	//g force on particles
	Vec2d g_force;
        
        ///  apply gravity force only to this phase
        int  g_only;

        ///  time step
        double  tstep;

	//timing control, D_time is output time interval
	double Start_time, End_time, D_time;

	//if initial condition is defined here
	//inital flow speed
	Vec2d U0;
	//initial particle density, pressure and temperature
	double rho0, p0, energy0;

	//MLS
	int MLS_MAX;

	//constructors
	explicit Initiation(const char *project_name);
	//non-dimensionalize
	void non_dimensionalize();
	//show information on screen
	void show_information();

	//predict the particle volume and mass
	void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function);


};
//-----------------------------------------------------------------------
//					Kernel abstract base
//-----------------------------------------------------------------------
class Kernel
{

public:

    //Conctructor
	Kernel(double smoothingLength);
    
	//Base classes with virtual member functions should have a virtual destructor
    virtual ~Kernel();



    // Calculates the kernel value for the given distance of two particles
    virtual double w(double distance) const = 0;

    /** Calculates the kernel derivation for the given distance of two particles */
    virtual Vec2d gradW(double distance, const Vec2d& distanceVector) const = 0;

protected:

    //A local copy of the smoothing length
    const double smoothingLength;

};
//-----------------------------------------------------------------------
//					cubic beta-spline as kernel.
//-----------------------------------------------------------------------
class BetaSpline : public Kernel
{

public:

    //constructor to initialize the data members and
    BetaSpline(double smoothingLength);



    //Calculates the kernel value for the given distance of two particles. 
    virtual double w(double distance) const;

    //Calculates the kernel derivation for the given distance of two particles. 
    virtual Vec2d gradW(double distance, const Vec2d& distanceVector) const;
	
    //Calculates the kernel derivation to distance. 
	double F(double distance) const;

private:
    //Normalization factor
    double norm;

    //Auxiliary factors for intermediate results: The inverse smoothing length */
    double reciprocH;

    //Auxiliary factors for intermediate results: A pre-factor for w */
    double factorW;

    //Auxiliary factors for intermediate results: A pre-factor for grad w */
    double factorGradW;

};
//-----------------------------------------------------------------------
//					Quintic spline kernel.
//-----------------------------------------------------------------------
class QuinticSpline : public Kernel
{

public:

    //constructor to initialize the data members and
    QuinticSpline(double smoothingLength);

    //Calculates the kernel value for the given distance of two particles. 
    virtual double w(double distance) const;

    //Calculates the kernel derivation for the given distance of two particles. 
    virtual Vec2d gradW(double distance, const Vec2d& distanceVector) const;
	
    //Calculates the kernel derivation to distance. 
	double F(double distance) const;

    //Calculates the kernel Laplacian. 
	double LapW(double distance) const;

private:
    //Normalization factor
    double norm;

    //Auxiliary factors for intermediate results: The inverse smoothing length */
    double reciprocH;

    //Auxiliary factors for intermediate results: A pre-factor for w */
    double factorW;

    //Auxiliary factors for intermediate results: A pre-factor for grad w */
    double factorGradW;

    //Auxiliary factors for Laplacian/
    double factorLapW;

};
//particle
//a sph particle
//note: reference a particle by pointer or adress
//never reference a particle directly!
class Particle {
	static int number_of_materials;
public:
	
	//constructors-------------------------------------------------------------------
	
	//a particle
	Particle(Initiation &ini);
	//construct a real particle
	Particle(Vec2d position, Vec2d velocity, double density, double pressure, double temperature, 
			 Material &material);

	//construct a wall particle
	Particle(double x, double y, double u, double v, 
			 double distance, double normal_x, double normal_y, Material &material);
	
	//ghost particle creator
	Particle(Particle &RealParticle);
	//Mirror image particle creator
	Particle(Particle &RealParticle, Material &material);

	//deconstructor particle
	~Particle();
	
	//particle creator
	void StatesCopier(Particle &RealParticle, int type);
  /// change phase of the particle
  void ChangePhase(Material &mtl);

	//constructors-------------------------------------------------------------------

	int cell_i, cell_j; //position in cells
	
	//point to the material
	Material *mtl; 

	//point to a real particle
	Particle *rl_prtl;

	//Physical data
	Vec2d R, P, U; //position, momentum, velocity
	double rho, p, T, Cs, rho_I, rho_n; //mass, density, inverse of density, pressure, temperature
	double m, V, energy; //mass, volume, internal energy
	Vec2d  R_I, P_I, U_I, P_n, U_n; //intermediate momentum and velocity used in integrator
	double energy_I, energy_n; //intermediate volume, internal energy used in integrator
  double k_thermal; // thermal conductivity
	Vec2d ShearRate_x, ShearRate_y;

	//for multimaterials
	double eta, zeta; //viscosity of each particle
	double **phi; //phase field matrix
	//first as phase field gradient matrix 
	//then the independent values ([0][0] and [0][1]) of suface stress matrix 
	Vec2d del_phi;
	double **lap_phi;
	
	//change rate for real particles
	double drhodt, dedt; //density and internal energy
	Vec2d dUdt, _dU; //acceration and random velocity change

	//other data	
	//0: inside the boundary
	//1: on the boundary
	int bd; //boundary particle or not
	
	//boundary type when bd = 1
	//0 wall particle with zero or constant velocity but never move its position
	//1 ghost particle for perodic boundary
	int bd_type; 

	//ID number
	//a real particle has a unique positive ID
	//a wall particle has zero ID
	//an ghost particle (for perodic boundary condition)
	//has a negtive ID of its corresponding real particle
	long ID; 
	
	//maximum ID number for non-ghost particles (real or wall particles) in the simulation
	static long ID_max;

	//for wall boundary particles
	double bd_dst;
  //Vec2d  nrml;

};
//-----------------------------------------------------------------------
//					particle manager
//-----------------------------------------------------------------------
class ParticleManager
{
	//parameters copied from initiation
	char Project_name[125]; //the project name
	int number_of_materials;
	double smoothinglength; //smoothinglenth
	double smoothinglengthsquare; //smoothinglenth
	double cll_sz; //cell size
	Vec2d box_size; //computational domain size
	int initial_condition; //initial condition marker
	double delta; //the inital particle distance
	int hdelta; //the ration between smoothing length and inital particle distance
	Vec2d U0; //inital flow speed
	double rho0, p0, energy0; //initial particle mass and density, pressure and temperature

	//buid the initial wall particles and the linked lists
	void BiuldWallParticles(Hydrodynamics &hydro, Initiation &ini, Boundary &boundary);

public:

	//linked cell matrix size
	int x_clls, y_clls;

	//lists
	Llist<Particle> **cell_lists;	//cell linked list in 2-d array
	
	Llist<Particle> NNP_list; //list for the nearest neighbor particles

	//constructors
	ParticleManager();
	ParticleManager(Initiation &ini);
	ParticleManager(double cell_size, int x_cells, int y_cells);

	//buid the initial particles and the linked lists
	void BiuldRealParticles(Hydrodynamics &hydro, Initiation &ini);
	void BiuldRealParticles(Hydrodynamics &hydro);

	//update the cell linked lists
	void UpdateCellLinkedLists();
	//do NNP search around a point and biuld the NNP list
	void BuildNNP(Vec2d &point);
	//do NNP search around a point and biuld the NNP list for MLS approximation
	void BuildNNP_MLSMapping(Vec2d &point);
	//build the interaction (particle pair) list
	void BuildInteraction(Llist<Interaction> &interactions, Llist<Particle> &particle_list, 
						Force **forces, QuinticSpline &weight_function);
	
};
//-----------------------------------------------------------------------
//				boundary condition
//				wall particle used for wall boundary condition
//-----------------------------------------------------------------------
class Boundary
{
	//if read wall particle from file .wll
	int wall_file;
	//computational domain size
	Vec2d box_size;
	//cell matrix size
	int x_clls, y_clls;
	int number_of_materials;

	//non-dimensionalize
	void non_dimensionalize(Initiation &ini);
	//show information on screen
	void show_information(Initiation &ini);

	//implement a side boubadry by modeify particle states
	void Boundary_W(Particle *prtl);
	void Boundary_E(Particle *prtl);
	void Boundary_S(Particle *prtl);
	void Boundary_N(Particle *prtl);
	void Boundary_SW(Particle *prtl);
	void Boundary_SE(Particle *prtl);
	void Boundary_NW(Particle *prtl);
	void Boundary_NE(Particle *prtl);

public:
	//boundary condition indicator
	//left, right, upper and botton
	//0: wall boundary condition
	//1: perodic boundary condition
	//2: free slip wall boundary condition
	//3: symmetry boundary condition 
	int  xBl, xBr, yBd, yBu;
	Vec2d UxBl, UxBr, UyBd, UyBu; //boundary velocity

	//boundary particle lists
	Llist<Particle> boundary_particle_list; //boundary particle list for all boundray particles

	//constructor
	Boundary(Initiation &ini, Hydrodynamics &hydro, ParticleManager &particles);

	//build boundary particles
	void BuildBoundaryParticles(ParticleManager &particles, Hydrodynamics &hydro);
	//boundary conditions
	void BoundaryCondition(ParticleManager &particles);
	//check particle if particle run out of the computational domain
	void RunAwayCheck(Hydrodynamics &hydro);
};
//-----------------------------------------------------------------------
//					class material
//-----------------------------------------------------------------------
class Material {

	//total number of materials
	static int number_of_materials;
	static double smoothinglength, delta; //smoothinglenth

public:
	
	//material name string
	char material_name[125];
	int number; //the material NO.

	//material type
	//0: solid; 1: liquid; 2: gas
	int material_type;
  
  double k_thermal; // thermal conductivity
	double cv, eta, zeta, kappa, gamma; //heat capacity, viscosity, heat conduction rate, heat ratio
	double nu; //kinetice viscosity
	double b0, rho0, a0; //reference pressure, reference density

	//constructor
	Material();
	Material(Initiation &ini);
	Material(char *material_name, Initiation &ini);
	
	//non-dimensionalize
	void non_dimensionalize(Initiation &ini);
	//show properties
	void show_properties();

	//obtain parameter b0
	void Get_b0(double sound);
	
	//equation of states
	double get_p(double rho);
	double get_rho(double p);
	double get_e(double T);
	double get_T(double e);
	double get_Cs(double p, double rho);

};
//-----------------------------------------------------------------------
//		The class defining force on or between particles
//-----------------------------------------------------------------------
class Force {

	friend class Hydrodynamics;
	
	//total number of materials
	static int number_of_materials;
	//smoothinglenth
	static double smoothinglength;

	//interactive force parameters
	double epsilon;
	double heat_slip; //heat conduction slip length 

public:

	double sigma; //surface tension parameters, its dimension is rho*u^2*L
	double shear_slip, bulk_slip; //shear and bulk slip length

	//constructor
	Force();
	Force(Initiation &ini);

	//non-dimensionalize
	void non_dimensionalize(Initiation &ini);
	
};
//-----------------------------------------------------------------------
//			defines interaction between particles
//-----------------------------------------------------------------------
class Interaction {

	//total number of materials
	static int number_of_materials;
	static double smoothinglength;
	static double delta;
	//artificial viscosity
	static double art_vis;

	//particle pair
	Particle *Org;	//particel with larger ID
	Particle *Dest;	//particel with smaller ID
	Force **frc_ij;	//force from particle i to particle j
	
	//pair values do not change in sub time steps
	int noi, noj; //material NO. of the two partilces
	double mi, rmi, etai, zetai, mj, rmj, etaj, zetaj;

	//distance between the two particles, weight and derivatives
	double rij, rrij, Wij, Fij, LapWij, Wij2;
	Vec2d eij; //pair direction from orginal particle to destination particle 
	double shear_rij, bulk_rij; //particle length to implement slip boundary

#ifdef _OPENMP
	//temporary storage of computation terms
	double drhodt1, drhodt2;
	Vec2d _dU1, _dU2, dUdt1, dUdt2;
#endif
		
public:
	
	//constructor
	Interaction(Initiation &ini);
	Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				QuinticSpline &weight_function, double dstc);
	
	//use old interaction object for new interaction
	void NewInteraction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				QuinticSpline &weight_function, double dstc);

	//renew pair parameters and changing pair values
	void RenewInteraction(QuinticSpline &weight_function);

	//pair interaction
	void SummationDensity();
	void SummationShearRate();

	//pahse field and phase gradient
	void SummationPhaseField();
	void SummationCurvature();
	void SummationPhaseGradient();
	void SummationPhaseGradient_old();
	void SummationPhaseLaplacian();

	//update forces
	void UpdateForces();
	void UpdateForces_vis();
#ifdef _OPENMP
	void SummationUpdateForces();
#endif

	//update random forces
	void RandomForces(Wiener &wiener, double sqrtdt);
	void RandomForces_Espanol(Wiener &wiener, double sqrtdt);
	
};
//-----------------------------------------------------------------------
//					Hydrodynamical interactions
//-----------------------------------------------------------------------
class Hydrodynamics
{	
	int number_of_materials;
	Vec2d gravity;

	double smoothinglength;
	double delta, delta2, delta3;
	double dt_g_vis, dt_surf;

	//the interaction (particle pair) list
	Llist<Interaction> interaction_list;

	//for time step 
	double viscosity_max, surface_max;

  /// wall number
  int solid_number;
public:

	//the materials used
	Material *materials;
	//the interaction force used
	Force **forces;
	Llist<Particle> particle_list; //particle list for all particles

	//Wiener process
	Wiener wiener;

	//constructor
	Hydrodynamics(ParticleManager &particles, Initiation &ini);

	//get the time step
        double GetTimestep(Initiation &ini);
  // get the time step (thermo)
  double GetTimestepThermo(const Initiation& ini) const ;

	//update new parameters in pairs
	void BuildPair(ParticleManager &particles, QuinticSpline &weight_function);
	void UpdatePair(QuinticSpline &weight_function);

	//manupilate the particle physics
	//initiate particle change rate
	void ZeroChangeRate();
	//add the gravity effects
	void AddGravity(Initiation& ini);
	//calculate interaction with updating interaction list
	void UpdateChangeRate(ParticleManager &particles, QuinticSpline &weight_function, Initiation& ini);
	//calculate interaction without updating interaction list
	void UpdateChangeRate(Initiation& ini);
	//initiate particle density to zero
	void Zero_density();
	void Zero_ShearRate();
	//summation for particles density and shear rates
	void UpdateDensity(ParticleManager &particles, QuinticSpline &weight_function);
	void UpdateShearRate(ParticleManager &particles, QuinticSpline &weight_function);
	//currently no shear rate calculated  without updating interaction list
	void UpdateDensity();
	void UpdateShearRate();
	
	//update pahse field
	void UpdatePhaseGradient(Boundary &boundary);
	void Zero_PhaseGradient(Boundary &boundary);
	void UpdatePhaseField(Boundary &boundary);
	void Zero_PhaseField(Boundary &boundary);
	void UpdateSurfaceStress(Boundary &boundary);
	void UpdatePhaseLaplacian(Boundary &boundary);
	void Zero_PhaseLaplacian(Boundary &boundary);
	double SurfaceTensionCoefficient();
	void UpdatePahseMatrix(Boundary &boundary);

	//calculate states from conservatives
	void UpdateState();
	//calculate partilce volume
	void UpdateVolume(ParticleManager &particles, QuinticSpline &weight_function);

	//for predictor and corrector method, density evaluated directly
	void Predictor(double dt);
	void Corrector(double dt);

	//for predictor and corrector method, density evaluated with summation
	void Predictor_summation(double dt);
	void Corrector_summation(double dt);

	//DPD simultion
	//initiate random force
	void Zero_Random();
	//calculate random interaction without updating interaction list
	void UpdateRandom(double sqrtdt);
	//including random effects
	void RandomEffects();

	//tests for debug
	void MovingTest(Initiation &ini);
	double ConservationTest();

	//special uitilities
	void Zero_Velocity();

};
//-----------------------------------------------------------------------
//					Time solver class
//-----------------------------------------------------------------------
class TimeSolver{

	//parameters copied from initiation
	double cell_size;
	Vec2d box_size;
	double smoothinglength;

	int ite; //number of itenary
	double dt; //time step

public:
	
	//constructor
	TimeSolver(Initiation &ini);
	
	//advance time interval D_time
	void TimeIntegral(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
				   double &Time, double D_time, Diagnose &diagnose,
				   Initiation &ini, QuinticSpline &weight_function, MLS &mls);
	//advance time interval D_time with summation for density
	void TimeIntegral_summation(Hydrodynamics &hydro, ParticleManager &particles, Boundary &boundary,
				   double &Time, double D_time, Diagnose &diagnose,
				   Initiation &ini, QuinticSpline &weight_function, MLS &mls);

};
//-----------------------------------------------------------------------
//					Output the computational results
//-----------------------------------------------------------------------
class Output {
	
	//the project name
	char Project_name[125];

	int number_of_materials;
	//the inital particle distance
	double delta;
	//cells matrix for real particles
	int x_cells, y_cells;
	//the ration between smoothing length and inital particle distance
	int hdelta; 

public:

	//constructor
	Output(Initiation &ini);

	//output particle positions respected different materials
	void OutputParticles(Hydrodynamics &hydro, Boundary &boundary, 
						double Time, Initiation &ini);
	//output material states on uniform grid
	void OutputStates(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
					  double Time, Initiation &ini);
	//Output data for restart
	void OutRestart(Hydrodynamics &hydro, double Time, Initiation &ini);
	//a movie for particle motion
	void CreatParticleMovie();
	void WriteParticleMovie(Hydrodynamics &hydro, double Time, Initiation &ini);
	//avergaed values for Poiseuille and Couette flows
	void OutAverage(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
					double Time, Initiation &ini);
};
//-----------------------------------------------------------------------
//					Output the diagnosal results
//-----------------------------------------------------------------------
class Diagnose {
	
	//the inital particle distance
	double delta;
	//cells matrix for real particles
	int x_cells, y_cells;
	//the ration between smoothing length and inital particle distance
	int hdelta; 

	//the project name
	char Project_name[125];
	int number_of_materials;

	//velocity, density, distributions
	double vx_dstrb[2][101], vy_dstrb[2][101], rho_dstrb[2][101];
	//list for states of a given particle
	Llist<double> vx_list, vy_list, rho_list; 

	//average profile mesh size
	int gridx, gridy;
	double ***U;
	int n_average; //the times of average

	//biuld distribution
	void BuildDistribution(Llist<double> &list, double dstrb[2][101]);

	//total mass, global average kinetic energy, material weight center position and velocity
	double ttl_m, *mtl_m, glb_ave_Ek;
	Vec2d *wght_cntr, *wght_v;

public:

	//constructor
	Diagnose(Initiation &ini, Hydrodynamics &hydro);

	//save the states of a particle
	void SaveStates(Hydrodynamics &hydro);
	//output distribution up to the time
	void OutputProfile(double Time, Initiation &ini);

	//calculate the average values
	void Average(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, Initiation &ini);
	//output the average values
	void OutputAverage(double Time, Initiation &ini);

	//track the globle average kinetic energy, weight center position and velocity
	void KineticInformation(double Time, Initiation &ini, Hydrodynamics &hydro);
};
//-----------------------------------------------------------------------
//			Using Moving Least Squares Approximation
//			2D and linear aproximation
//			based on (Liu GR, Mesh Free Methods->Moving beyond the finite element method, 
//			CRC press, London, 2003, p79-87)
//-----------------------------------------------------------------------
class MLS {
	
	int N, MLS_MAX; //numbers and maximum number of reference points
	double A[3][3], **B; //weighted moment matrix
	double p[3], **pi; //ploynomial basis matrix
	double *Wi; //weights

	void MLS_Solver(int order); //calculate the shape function and its derivatives
	
public:

	double *phi; //shape function
	Vec2d *dphi; //derivatives: have not been implemented!

	//constructor
	MLS(Initiation &ini);
	//MLS Mapping to grid points
	void MLSMapping(Vec2d &point, Llist<Particle> &NNP_list, QuinticSpline &weight_function, int order);

};

#endif
