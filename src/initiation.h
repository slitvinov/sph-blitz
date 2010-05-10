/// \file initiation.h 
/// \brief Initiation

#ifndef INITIATION_H
#define INITIATION_H

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
    ///non-dimensionalize
    void non_dimensionalize();
    ///show information on screen
    void show_information();

    ///predict the particle volume and mass
    void VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function);

    ///non-dimesionlize
    double non_dms_p(double p);
    double non_dms_T(double T);
    double non_dms_rho(double rho);
    double non_dms_mass(double mass);
    double non_dms_time(double time);
    double non_dms_length(double length);
    Vec2d non_dms_box_size(Vec2d box_size);
    double non_dms_velocity(double velocity);
    double non_dms_kinetic_viscosity(double nu);
    Vec2d non_dms_velocity(Vec2d velocity);
    double non_dms_acceleration(double acceleration);
    Vec2d non_dms_acceleration(Vec2d acceleration);
    double non_dms_viscosity(double mu);
    double non_dms_heat_ratio(double cv);
    double non_dms_heat_conduction(double kappa);
    double non_dms_Boltzmann(double k_bltz);
    double non_dms_surface(double sigma);

    ///dimesionlize
    double dms_p(double p_non);
    double dms_T(double T_non);
    double dms_rho(double rho_non);
    double dms_mass(double mass_non);
    double dms_time(double time_non);
    double dms_length(double length_non);
    Vec2d dms_box_size(Vec2d box_size_non);
    double dms_velocity(double velocity_non);
    Vec2d dms_velocity(Vec2d velocity_non);
    double dms_energy(double energy_non);
    double dms_acceleration(double acceleration_non);
    Vec2d dms_acceleration(Vec2d acceleration_non);
    double dms_viscosity(double mu_non);
    double dms_surface(double sigma_non);

};

#endif
