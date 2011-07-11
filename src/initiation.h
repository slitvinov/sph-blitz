/// \file initiation.h 
/// \brief Initiation

#ifndef INITIATION_H
#define INITIATION_H
#include "vec2d.h"

class QuinticSpline;
class Material; 
class Hydrodynamics;
class ParticleManager;

/// Initiation
class Initiation {
        
    friend class Material;
    friend class Hydrodynamics;
    ///reference length, speed, and density for dimensionless
    double _length, _v, _rho, _T; 

public:
        
    ///the project name
    char Project_name[125];

    ///number of materials
    ///the no. zero material is always the wall
    ///therefore at least 2 materials should be included
    int number_of_materials;
    ///the global inputfile name: a *.cfg file
    char inputfile[125];
    ///initial condition marker: 0 initialize from the .cfg file; 
    ///1 read from the .rst file particle by particle with non-dimensional data
    int initial_condition;
    ///diagnose information maker: 1 output diagnose information
    int diagnose;
    ///artificial viscosity
    double art_vis;

    ///smoothinglength
    double smoothinglength;
    ///the compuational domain size
    Vec2d box_size;
    ///cell size
    double cell_size;
    ///the inital particle distance
    double delta;
    ///the ration between smoothing length and inital particle distance
    int hdelta;
    ///cells matrix for real particles
    int x_cells, y_cells;
    ///g force on particles
    Vec2d g_force;

	/// FENE force paramters for the polymers F = H*r / (1 - (r/r0)^2)
	double polymer_H;
	double polymer_r0;

	/// IDs of moving particles
	///int moveID1, moveID2,moveID3,moveID4;

	/// velocity of the moving particles
	///Vec2d moveVel1,moveVel2;


    ///timing control, D_time is output time interval
    double Start_time, End_time, D_time;

    ///if initial condition is defined here
    ///inital flow speed
    Vec2d U0;
    ///initial particle density, pressure and temperature
    double rho0, p0, T0;

    ///MLS
    int MLS_MAX;

    ///constructors
    explicit Initiation(const char *project_name);
    ///show information on screen
    void show_information();

    ///predict the particle volume and mass
    void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function);
};

#endif
