/// \file mls.h
/// \brief Moving Least Squares (MLS) class 
///                     Using  Moving Least Squares Approximation
///                     2D and linear aproximation
///                     based on (Liu GR, Mesh Free Methods->Moving beyond the finite element method, 
///                     CRC press, London, 2003, p79-87)

#ifndef MLS_H
#define MLS_H

class Initiation;
class Particle;
class QuinticSpline;

/// Moving Least Squares Approximation (MLS)
class MLS {
        
    int N, MLS_MAX; ///numbers and maximum number of reference points
    double A[3][3], **B; ///weighted moment matrix
    double p[3], **pi; ///ploynomial basis matrix
    double *Wi; ///weights

    void MLS_Solver(int order); ///calculate the shape function and its derivatives
        
public:

    double *phi; ///shape function
    Vec2d *dphi; ///derivatives: have not been implemented!

    ///constructor
    MLS(Initiation &ini);
    
    /// destructor
    ~MLS();

    ///MLS Mapping to grid points
    void MLSMapping(Vec2d &point, Llist<Particle> &NNP_list, QuinticSpline &weight_function, int order);

};

#endif
