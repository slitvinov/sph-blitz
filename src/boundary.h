#ifndef BOUNDARY_H
#define BOUNDARY_H
/// \file boundary.h
/// \brief Bonudary conditions



/// Boundary conditions
class Boundary
{
	///computational domain size
	Vec2d box_size;
  ///cell matrix size in x direction
  int x_clls;

  ///cell matrix size in y direction
  int y_clls;

	///show information on screen
	void show_information() const;

	//implement a side boundary by modifying particle states

        ///implement west side boundary by modifying particle states
	void Boundary_W(spParticle prtl);
	///implement east side boundary by modifying particle states
	void Boundary_E(spParticle prtl);
	///implement south side boundary by modifying particle states
	void Boundary_S(spParticle prtl);
	///implement north side boundary by modifying particle states
	void Boundary_N(spParticle prtl);
	///implement south-west corner boundary by modifying particle states
	void Boundary_SW(spParticle prtl);
	///implement south-east corner boundary by modifying particle states
	void Boundary_SE(spParticle prtl);
	///implement north-west corner boundary by modifying particle states
	void Boundary_NW(spParticle prtl);
	///implement north-east corner boundary by modifying particle states
	void Boundary_NE(spParticle prtl);

public:
	///\brief boundary condition indicator left hand side
	///
	///- 0: wall boundary condition
	///- 1: perodic boundary condition
	///- 2: free slip wall boundary condition
	///- 3: symmetry boundary condition 
	int  xBl;

  /// temperature for the left hand side
  double xTl;

        ///\brief boundary condition indicator right hand side
	///
	///- 0: wall boundary condition
	///- 1: perodic boundary condition
	///- 2: free slip wall boundary condition
	///- 3: symmetry boundary condition 
	int xBr;
  /// temperature for the right hand side
  double xTr;


	///\brief boundary condition indicator bottom side
	///
	///- 0: wall boundary condition
	///- 1: perodic boundary condition
	///- 2: free slip wall boundary condition
	///- 3: symmetry boundary condition 
	int yBd;
  /// temperature for the bottom side
  double yTd;


	///\brief boundary condition indicator upper side
	///
	///- 0: wall boundary condition
	///- 1: perodic boundary condition
	///- 2: free slip wall boundary condition
	///- 3: symmetry boundary condition 
	int yBu;
  /// temperature for the upper side
  double yTu;



	//boundary velocities
	Vec2d UxBl;///<left hand side boundary velocity
	Vec2d UxBr;///<right hand side boundary velocity
	Vec2d UyBd;///<bottom side boundary velocity
	Vec2d UyBu;///<upper side boundary velocity

	///boundary particle lists
	std::list<spParticle > boundary_particle_list; ///boundary particle list for all boundray particles

	///constructor
	Boundary(Initiation &ini, const ParticleManager &particles);

	///build boundary particles
	void BuildBoundaryParticle(ParticleManager &particles, Hydrodynamics &hydro);
	///boundary conditions
	void BoundaryCondition(ParticleManager &particles);
	///check particle if particle run out of the computational domain
	void RunAwayCheck(Hydrodynamics &hydro);
};

#endif //BOUNDARY_H
