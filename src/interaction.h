/// \file interaction.h 
/// \brief Defines interaction between particles

#ifndef INTERACTION_H
#define INTERACTION_H

class Particle;
class QuinticSpline;
class Force;
class Initiation;

/// Defines interaction between particles
class Interaction {
	/// local reference to Initiation object
	 Initiation& ini;

    ///total number of materials
    static int number_of_materials;
    static double smoothinglength;
    static double delta;
    ///artificial viscosity
    static double art_vis;

    ///particle pair
    Particle *Org;      ///particel with larger ID
    Particle *Dest;     ///particel with smaller ID
    Force **frc_ij;     ///force from particle i to particle j
        
    ///pair values do not change in sub time steps
    int noi, noj; ///material NO. of the two partilces
    double mi, rmi, etai, zetai, mj, rmj, etaj, zetaj;

    ///distance between the two particles, weight and derivatives
    double rij, rrij, Wij, Fij, LapWij, Wij2;
    Vec2d eij; ///pair direction from orginal particle to destination particle 
    double shear_rij, bulk_rij; ///particle length to implement slip boundary

#ifdef _OPENMP
    ///temporary storage of computation terms
    double drhodt1, drhodt2;
    Vec2d _dU1, _dU2, dUdt1, dUdt2;
#endif
                
public:
    ///constructor
    Interaction(Initiation &ini);
    Interaction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
                QuinticSpline &weight_function, double dstc, Initiation& ini);
        
    ///use old interaction object for new interaction
    void NewInteraction(Particle *prtl_org, Particle *prtl_dest, Force **forces,
                        QuinticSpline &weight_function, double dstc);

    ///renew pair parameters and changing pair values
    void RenewInteraction(QuinticSpline &weight_function);

    ///pair interaction
    void SummationDensity();
    void SummationShearRate();

    ///pahse field and phase gradient
    void SummationPhaseField();
    void SummationCurvature();
    void SummationPhaseGradient();
    void SummationPhaseGradient_old();
    void SummationPhaseLaplacian();

    ///update forces
    void UpdateForces();
    void UpdateForces_vis();
#ifdef _OPENMP
    void SummationUpdateForces();
#endif

    ///update random forces
    void RandomForces(Wiener &wiener, double sqrtdt);
    void RandomForces_Espanol(Wiener &wiener, double sqrtdt);
        
};
#endif
