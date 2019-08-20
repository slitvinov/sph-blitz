/// \file betaspline.h
/// \brief Beta spline kernel function


/// \brief   A concrete kernel class
///
///    	see Monaghan & Lattanzio (1985) most often used kernel
///	implemented in	bskernel.cpp
class BetaSpline : public Kernel
{

public:
    ///constructor to initialize the data members and
    explicit BetaSpline(double smoothingLength);

    ///\brief Calculates the kernel value for the given distance of two particles.
    ///
    /// We take this from Monaghan & Lattenzio (1985)
    /// but used a doubled smoothing length for the definition of the interaction radius. 
    virtual double w(double distance) const;

    ///\brief Calculates the kernel derivation for the given distance of two particles. 
    ///
    /// We take this from Monaghan & Lattenzio (1985)
    /// but used a doubled smoothing length for the definition of the interaction radius.
    virtual Vec2d gradW(double distance, const Vec2d& distanceVector) const;
	
    ///Calculates the kernel derivation to distance. 
	double F(double distance) const;

private:
    ///Normalization factor
    double norm;

    ///Auxiliary factors for intermediate results: The inverse smoothing length */
    double reciprocH;

    ///Auxiliary factors for intermediate results: A pre-factor for w */
    double factorW;

    ///Auxiliary factors for intermediate results: A pre-factor for grad w */
    double factorGradW;

};

#endif //BETASPLINE_H
