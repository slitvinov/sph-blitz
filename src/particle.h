/// \file partilce.h 
/// \brief a sph particle

#ifndef PARTICLE_H
#define PARTICLE_H

///note: reference a particle by pointer or adress
///never reference a particle directly!

class Material;
class Boundary;
class Initiation;
class Hydrodynamics;

/// Particle class 
class Particle {
    static int number_of_materials;
        
public:
        
    ///constructors-------------------------------------------------------------------
        
    ///a particle
    Particle(Initiation &ini);
    ///construct a real particle
    Particle(Vec2d position, Vec2d velocity, double density, double pressure, double temperature, 
             Material &material);

    ///construct a wall particle
    Particle(double x, double y, double u, double v, 
             double distance, double normal_x, double normal_y, Material &material);
        
    ///ghost particle creator
    Particle(Particle &RealParticle);
    ///Mirror image particle creator
    Particle(Particle &RealParticle, Material &material);

    ///deconstructor particle
    ~Particle();
        
    ///particle creator
    void StatesCopier(Particle &RealParticle, int type);

    ///constructors-------------------------------------------------------------------

    int cell_i, cell_j; ///position in cells
        
    ///point to the material
    Material *mtl; 

    ///point to a real particle
    Particle *rl_prtl;

    ///Physical data
    Vec2d R, P, U; ///position, momentum, velocity
    double rho, p, T, Cs, rho_I, rho_n; ///mass, density, inverse of density, pressure, temperature
    double m, V, e; ///mass, volume, internal energy
    Vec2d  R_I, P_I, U_I, P_n, U_n; ///intermediate momentum and velocity used in integrator
    double e_I, e_n; ///intermediate volume, internal energy used in integrator
    Vec2d ShearRate_x, ShearRate_y;

    ///for multimaterials
    double eta, zeta; ///viscosity of each particle
    double **phi; ///phase field matrix
    ///first as phase field gradient matrix 
    ///then the independent values ([0][0] and [0][1]) of suface stress matrix 
    Vec2d del_phi;
    double **lap_phi;
        
    ///change rate for real particles
    double drhodt, dedt; ///density and internal energy
    Vec2d dUdt, _dU; ///acceration and random velocity change

    ///other data       
    ///0: inside the boundary
    ///1: on the boundary
    int bd; ///boundary particle or not
        
    ///boundary type when bd = 1
    ///0 wall particle with zero or constant velocity but never move its position
    ///1 ghost particle for perodic boundary
    int bd_type; 

    ///ID number
    ///a real particle has a unique positive ID
    ///a wall particle has zero ID
    ///an ghost particle (for perodic boundary condition)
    ///has a negtive ID of its corresponding real particle
    long ID; 
        
    ///maximum ID number for non-ghost particles (real or wall particles) in the simulation
    static long ID_max;

    ///for wall boundary particles
    double bd_dst;
    Vec2d  nrml;

};

#endif
