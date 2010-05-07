/// \file boundary.h
/// \brief Bondary conditions
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
