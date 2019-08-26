struct Initiation;
struct Hydrodynamics;
struct Manager;
struct MLS;
struct QuinticSpline;
struct Boundary;
struct List;
class Diagnose {
	double delta;
	int x_cells, y_cells;
	int number_of_materials;
	double vx_dstrb[2][101];
	double vy_dstrb[2][101];
	double rho_dstrb[2][101];
	List *vx_list;
	List *vy_list;
	List *rho_list;
	int gridx;
	int gridy;
	double ***U;
	int n_average;
	void BuildDistribution(List*, double dstrb[2][101]);
	double ttl_m;
	double *mtl_m;
	double glb_ave_Ek;
	double *wght_cntr ;
	double *wght_v;
public:
	Diagnose(struct Initiation*, struct List*, struct Material*);
	void SaveStates(Hydrodynamics*);
	void OutputProfile(double Time);
	void Average(Manager*, MLS*, QuinticSpline*);
	void OutputAverage(double Time);
	void KineticInformation(double Time, Hydrodynamics*);
};
