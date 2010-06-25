#ifndef DIAGNOSE_H
#define DIAGNOSE_H
/// \file diagnose.h
/// \brief Output the diagnosal results

/// Output diagnosal 
class Diagnose {
	
	///the inital particle distance
	double delta;

	///cells matrix for real particles
	int x_cells, y_cells;

	///the ration between smoothing length and inital particle distance
	int hdelta; 

	///the project name
	char Project_name[25];
	int number_of_materials;

	double vx_dstrb[2][101];///<x-velocity distribution
	double vy_dstrb[2][101];///<y-velocity distribution
        double rho_dstrb[2][101];///<density distribution

	Llist<double> vx_list;///<list for vx states of a given particle
	Llist<double> vy_list;///<list for vy states of a given particle
	Llist<double> rho_list; ///<list for rho states of a given particle

        int gridx;///<average profile mesh size in x-direction
        int gridy;///<average profile mesh size in y-direction
	double ***U;
	int n_average; ///<the times of average

	///build distribution
	void BuildDistribution(Llist<double> &list, double dstrb[2][101]);

	///total mass, global average kinetic energy,
        double ttl_m;///<total mass
        double *mtl_m;///<??????<b>(diagnose.h, line 36)</b>
        double glb_ave_Ek;///<global average kinetic energy
        Vec2d *wght_cntr ;///<material weight center position
        Vec2d *wght_v; ///<material weight center velocity

public:

	///constructor
	Diagnose(Initiation &ini, Hydrodynamics &hydro);

	///save the states of a particle in particle states vectors (vx_list, vy_list, rho_list)
	void SaveStates(Hydrodynamics &hydro);

	///output distribution up to the time
	void OutputProfile(double Time, Initiation &ini);

	///output the average values
	void OutputAverage(double Time, Initiation &ini);

};

#endif //DIAGNOSE_H
