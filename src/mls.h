class Initiation;
class Particle;
class QuinticSpline;
class MLS {
	int N;
	int MLS_MAX; 
	double A[3][3], **B; 
	double p[3], **pi; 
	double *Wi; 
	void MLS_Solver(int order);
public:
	double *phi; 
	explicit MLS(int MLS_MAX);
	void MLSMapping(double point[2], List &NNP_list, QuinticSpline &weight_function, int order);
};
