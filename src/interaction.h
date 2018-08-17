#ifndef INTERACTION_H
#define INTERACTION_H
/// \file interaction.h 
/// \brief Defines interaction between particles

/// Defines interaction between particles
class Interaction {

	///total number of materials
	static int number_of_materials;
	static double smoothinglength;
	///particle distance
	static double delta;
	///artificial viscosity
	static double art_vis;

	//particle pair
	Particle *Org;	///<pointer to particle with larger ID (of particle pair)
	Particle *Dest;	///<pointer to particle with smaller ID (of particle pair)
	Force **frc_ij;	///<force from particle i to particle j
	
	//pair values do not change in sub time steps
	int noi; ///<material NO. of the partilce i
        int noj; ///<material NO. of the partilce j
	double mi;///<mass particle i
	double rmi;///<reciprocal value of mass particle i
	double etai;///<viscosity for particle i
	double zetai;///<<b>!!!question!!!<b>other viscosity for particle???
	double mj;///<mass particle j
	double rmj;///<reciprocal value of mass particle j
	double etaj;///<viscosity for particle j
	double zetaj;///<<b>!!!question!!!<b>other viscosity for particle???

	//distance between the two particles, weight and derivatives
	double rij;///<distance between 2 particles
        double rrij;///< reciprocal value of distance between 2 particles
        double Wij;///<<b>!!!question!!!<b>
        double Fij;///<<b>!!!question!!!<b>
        double LapWij;///<<b>!!!question!!!<b>
        double Wij2;///<<b>!!!question!!!<b>
	Vec2d eij; ///<pair direction from orginal particle to destination particle 
	double shear_rij ;///<particle length to implement slip boundary<<b>!!!question!!!<b>
	double bulk_rij; ///<particle length to implement slip boundary<<b>!!!question!!!<b>

#ifdef _OPENMP

	double drhodt1;///<for temporary storage of computation terms
	double drhodt2;///<for temporary storage of computation terms
	Vec2d _dU1;///<for temporary storage of computation terms
	Vec2d _dU2;///<for temporary storage of computation terms
	Vec2d dUdt1;///<for temporary storage of computation terms
	Vec2d dUdt2;///<for temporary storage of computation terms
#endif
		
public:
	
	///constructor
	explicit Interaction(Initiation &ini);
	///constructor
	Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				QuinticSpline &weight_function, double dstc);
	
	///use old interaction object for new interaction
	void NewInteraction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
				QuinticSpline &weight_function, double dstc);

	///\brief renew pair parameters and changing pair values
	///
        ///Changes: Interaction object\n
        ///Depends on: Interaction Object, Org, Dest
	void RenewInteraction(QuinticSpline &weight_function);

	//pair interaction

	///\brief summation of the density
	///
        ///Changes: Org(rho:summation), Dest(rho:summation)\n
        ///Depends on: Interaction Object, Org(rho), Dest(rho)
        ///Remark: the idea is different from the original sph method
	void SummationDensity();

	/// \brief summation of the shear rates
	///
	/// Changes: Org(ShearRate_x, ShearRate_y:summation), Dest(ShearRate_x, ShearRate_y:summation)\n
        /// Depends on: Interaction Object, Org(ShearRate_x, ShearRate_y, U, rho), Dest(ShearRate_x, ShearRate_y, U, rho)
	void SummationShearRate();

	//pahse field and phase gradient
	///\brief sum phase field contribution of interaction pair
	///
        /// Changes: Org(phi:summation), Dest(phi:summation)\n
        /// Depends on: Interaction Object, Org(phi, rho), Dest(phi, rho)
	void SummationPhaseField();
	void SummationCurvature();

	///\brief sum phase gradient contribution of interaction pair
	///
	/// Changes: Org(del_phi:summation), Dest(del_phi:summation)\n
	/// Depends on: Interaction Object, Org(del_phi,rho), Dest(del_phi,rho)
	void SummationPhaseGradient();
	void SummationPhaseGradient_old();
	void SummationPhaseLaplacian();

	///update forces
	void UpdateForces();
	///update forces with summation of viscosity
	void UpdateForces_vis();
#ifdef _OPENMP
	void SummationUpdateForces();
#endif

	///update random forces
	void RandomForces(Wiener &wiener, double sqrtdt);
	///update random forces with Espanol's method
	void RandomForces_Espanol(Wiener &wiener, double sqrtdt);
	
};

#endif //INTERACTION_H
