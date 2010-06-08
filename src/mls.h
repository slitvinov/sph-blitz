#ifndef MLS_H
#define MLS_H
/// \file mls.h
/// contains MLS class

/// \brief Moving Least Squares (MLS) class 
///
///  Using  Moving Least Squares Approximation
///  2D and linear aproximation
///  based on (Liu GR, Mesh Free Methods->Moving beyond the finite element method, CRC press, London, 2003, p79-87)
class MLS {
	
        int N;///< numbers of points
        int MLS_MAX; ///< maximum number of reference points
	double A[3][3], **B; ///<weighted moment matrix (pointer to pointer)
	double p[3], **pi; ///<ploynomial basis matrix (pointer to pointer)
	double *Wi; ///<weights (pointer to)

        ///calculate the shape function and its derivative
	void MLS_Solver(int order);
	
public:

	double *phi; ///<shape function (pointer to)
	Vec2d *dphi; ///<derivatives (pointer to): have not been implemented!

	///constructor
	MLS(Initiation &ini);

	///\brief MLS Mapping to grid points
	///
	///set up the enviroment for MLS calculation and run MLS solver
	void MLSMapping(Vec2d &point, Llist<Particle> &NNP_list, QuinticSpline &weight_function, int order);

};

#endif //MLS_H
