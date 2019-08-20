/// \file wiener.h
/// \brief Wiener process

///-----------------------------------------------------------------------
///		The class defining Wiener process in two dimensions
///-----------------------------------------------------------------------

/// Wiener process
class Wiener {

	int dimension;
	double randoms[2][2];

	///for random number generator
	///variables
	long int idum, idum2, iy, ntab, iseed;
	long int iv[32];
	///get the random number uniform distributed in [0, 1]
	double Ranuls();
	///get two random numbers y1, y2 with guassian distribution with zero mean and variance one
	///from random numbers uniform distributed in [0, 1]
	void Gaussian(double *y1, double *y2);

public:
	double sym_trclss[2][2];

        /// trace of the matrix
	double trace_d;
	double Random_p, Random_v;

	///costructure
	Wiener();

	///produce wiener vlaue matrix with symmetric tracless part, and the trace
	void get_wiener_Espanol(const double sqrtdt);

	///wiener process with Flekkoy's form
	void get_wiener(const double sqrtdt);

	///set the random seed
	void Ranils();
};

