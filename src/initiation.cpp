// initiation.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      initialize the progam
//              initiation.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbcls.h"
#include "glbfunc.h"
#include "initiation.h"
#include "particle.h"
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "quinticspline.h"

#include "cpptcl.h"


using namespace std;

//----------------------------------------------------------------------------------------
//                                                      constructor
//----------------------------------------------------------------------------------------
Initiation::Initiation(const char *project_name) {
        
    char Key_word[125];

    //the project name
    strcpy(Project_name, project_name);

    //the input file name
    strcpy(inputfile, Project_name);
    strcat(inputfile, ".tcl");
        
    Tcl::interpreter interp; 
    std::ifstream myfile;
    myfile.open (inputfile);
    
    interp.eval(myfile);
    initial_condition = interp.eval("[return $INITIAL_CONDITION]");
    diagnose = interp.eval("[return $DIAGNOSE]");
    x_cells = interp.eval ("[return $CELLS(1)]");
    y_cells = interp.eval ("[return $CELLS(2)]");
    cell_size = interp.eval("[return $CELL_SIZE]");
    smoothinglength = interp.eval("[return $SMOOTHING_LENGTH]");
    hdelta = interp.eval("[return $CELL_RATIO]");

    g_force[0] = interp.eval ("[return $G_FORCE(1)]");
    g_force[1] = interp.eval ("[return $G_FORCE(2)]");
    
    //     if(!strcmp(Key_word, "ARTIFICIAL_VISCOSITY")) fin>>;
    art_vis = interp.eval("[return $ARTIFICIAL_VISCOSITY]");
    _length = interp.eval("[return $_lenth]");
    _v = interp.eval("[return $_v]");
    _rho = interp.eval("[return $_rho]");
    _T = interp.eval("[return $_T]");
    number_of_materials = interp.eval("[return $NUMBER_OF_MATERIALS]");

    //     //comparing the key words for timing
    //     if(!strcmp(Key_word, "TIMING")) fin>>Start_time>>End_time>>D_time;

    Start_time = interp.eval("[return $Start_time]");
    End_time = interp.eval("[return $End_time]");
    D_time = interp.eval("[return $D_time]");

    MLS_MAX = interp.eval("[return $MLS_MAX]");
    rho0 = interp.eval("[return $rho0]");
    p0 = interp.eval("[return $p0]");
    T0 = interp.eval("[return $T0]");

    U0[0] = interp.eval ("[return $U0(1)]");
    U0[1] = interp.eval ("[return $U0(2)]");

    //     //Initialize the initial conditions from .cfg file
    //     if (initial_condition==0) {
    //         //comparing the key words for the initial state
    //         if(!strcmp(Key_word, "INITIAL_STATES")) fin>>U0[0]>>U0[1]>>rho0>>p0>>T0;
    //     }

    // }
    // fin.close();

    //create outdata directory
    const int ok = system("mkdir -p outdata");
    if (ok != 0) {
      std::cerr << "Cannot create outdata directory" << std::endl;
      std::cerr << __FILE__ << ':' << __LINE__ << std::endl;
      exit(EXIT_FAILURE);
    }
        
    //process the data
    box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
    delta = cell_size/hdelta;
        
    //output information to screen
    show_information();

    //non-dimensionalize
    non_dimensionalize();

}
//----------------------------------------------------------------------------------------
//                                      show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information()
{
    //output information to screen
    cout<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
    cout<<"The computational domain size is  "<<box_size[0]<<" micrometers x "<<box_size[1]<<" micrometers\n";
    cout<<"The cell size is "<<cell_size<<" micrometers \n";
    cout<<"The smoothing length is "<<smoothinglength<<" micrometers \n";
    cout<<"The cell matrix size is "<<x_cells<<" x "<<y_cells<<"\n";
    cout<<"The ratio between cell size and initial particle width is "<<hdelta<<"\n";
    cout<<"The initial particle width is "<<delta<<" micrometers\n";
    cout<<"The g force is "<<g_force[0]<<" m/s^2 x "<<g_force[1]<<" m/s^2 \n";
    cout<<"The dimensionless reference length, speed, density and temperature are \n"
        <<_length<<" micrometer, "<<_v<<" m/s, "<<_rho<<" kg/m^3, "<<_T<<" K\n";

    //output the timing on screen
    cout<<"\nInitialtion: Time controlling:\nStarting time is "<<Start_time<<" \n";
    cout<<"Ending time is "<<End_time<<" \n";
    cout<<"Output time interval is "<<D_time<<" \n";

        
    //Initialize the initial conditions from .cfg file
    if (initial_condition==0) {
        cout<<"\nInitialize the initial conditions from "<<inputfile<<" \n";
        cout<<"The initial flow speed is "<<U0[0]<<" m/s x "<<U0[1]<<" m/s\n";
        cout<<"The initial density is "<<rho0<<" kg/m^3\n";
        cout<<"The initial pressure is "<<p0<<" Pa\n";
        cout<<"The initial temperature is "<<T0<<" K\n";

    }
        
    //Initialize the initial conditions from .rst file
    if (initial_condition == 1)
        cout<<"Read the initial conditions from separated restat file "<<Project_name<<".rst \n";
}
//----------------------------------------------------------------------------------------
//                                      predict the particle volume and mass
//----------------------------------------------------------------------------------------
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, QuinticSpline &weight_function)
{

    double reciprocV; //the inverse of volume or volume
    double dstc;
    Vec2d eij, sumdw;

    //iterate particles on the particle list
    for (LlistNode<Particle> *p = hydro.particle_list.first(); 
         !hydro.particle_list.isEnd(p); 
         p = hydro.particle_list.next(p)) {
                                        
        //origin particle
        Particle *prtl_org = hydro.particle_list.retrieve(p);
        //build the nearest particle list
        particles.BuildNNP(prtl_org->R);

        reciprocV = 0.0; sumdw = 0.0;
        //iterate this Nearest Neighbor Particle list
        for (LlistNode<Particle> *p1 = particles.NNP_list.first(); 
             !particles.NNP_list.isEnd(p1); 
             p1 = particles.NNP_list.next(p1)) {
                        
            //get a particle
            Particle *prtl_dest = particles.NNP_list.retrieve(p1);
                                
            //summation the weights
            dstc = v_distance(prtl_org->R, prtl_dest->R);
            eij = (prtl_org->R - prtl_dest->R)/(dstc + 1.e-30);
                                
            reciprocV += weight_function.w(dstc);
            sumdw = sumdw + eij*weight_function.F(dstc);
        }
        //calculate volume
        reciprocV = 1.0/reciprocV;

        //predict particle volume and mass
        prtl_org->V = reciprocV;
        prtl_org->m = prtl_org->rho*reciprocV;
                        
        //clear the NNP_list
        particles.NNP_list.clear();
    }
}
//----------------------------------------------------------------------------------------
//                              Non-dimensionalize the initial condition and parameters
//----------------------------------------------------------------------------------------
void Initiation::non_dimensionalize()
{
    box_size = non_dms_box_size(box_size);
    cell_size = non_dms_length(cell_size);
    smoothinglength = non_dms_length(smoothinglength);
    delta = non_dms_length(delta); 
    g_force = non_dms_acceleration(g_force);
    Start_time = non_dms_time(Start_time);
    End_time = non_dms_time(End_time);
    D_time = non_dms_time(D_time);

    //Bltzmann constant
    extern double k_bltz;
    k_bltz = non_dms_Boltzmann(k_bltz);
        
    //non-dimensionalize initial states
    if(initial_condition==0) {

        U0 = non_dms_velocity(U0);
        rho0 = non_dms_rho(rho0);
        p0 = non_dms_p(p0);
        T0 = non_dms_T(T0);
    }
}
//-------------------------------------------------------
//                      Non_dimensionalize pressure
//-------------------------------------------------------
double Initiation::non_dms_p(double p) const
{
    return p/_v/_v/_rho;
}
//-------------------------------------------------------
//                      Non_dimensionalize temperature
//-------------------------------------------------------
double Initiation::non_dms_T(double T) const
{
    return T/_T;
}
//-------------------------------------------------------
//                      Non_dimensionalize density
//-------------------------------------------------------
double Initiation::non_dms_rho(double rho) const
{
    return rho/_rho;
}
//-------------------------------------------------------
//                      Non_dimensionalize mass
//                      in 2-dimension 
//-------------------------------------------------------
double Initiation::non_dms_mass(double mass) const
{
    return mass/_rho/_length/_length/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize time
//-------------------------------------------------------
double Initiation::non_dms_time(double time) const
{
    return time*_v/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize length
//-------------------------------------------------------
double Initiation::non_dms_length(double length) const
{
    return length/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize boxsize in 2-d
//-------------------------------------------------------
Vec2d Initiation::non_dms_box_size(Vec2d box_size) const
{
    return box_size/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize velocity
//-------------------------------------------------------
double Initiation::non_dms_velocity(double velocity) const
{
    return velocity/_v;
}
//-------------------------------------------------------
//                      Non_dimensionalize vector velocity
//-------------------------------------------------------
Vec2d Initiation::non_dms_velocity(Vec2d velocity) const
{
    return velocity/_v;
}
//-------------------------------------------------------
//                      Non_dimensionalize acceleration vector
//-------------------------------------------------------
Vec2d Initiation::non_dms_acceleration(Vec2d acceleration) const
{
    return acceleration*_length/_v/_v;
}
//-------------------------------------------------------
//                      Non_dimensionalize surface tension coefficient
//-------------------------------------------------------
double Initiation::non_dms_surface(double sigma) const
{
    return sigma/_rho/_v/_v/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize viscosity
//-------------------------------------------------------
double Initiation::non_dms_viscosity(double mu) const
{
    return mu/_v/_rho/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize kinetic viscosity
//-------------------------------------------------------
double Initiation::non_dms_kinetic_viscosity(double nu) const
{
    return nu/_v/_length;
}
//-------------------------------------------------------
//                      Non_dimensionalize heat ratio
//-------------------------------------------------------
double Initiation::non_dms_heat_ratio(double cv) const
{
    return cv*_T/_v/_v;

}
//-------------------------------------------------------
//                      Non_dimensionalize heat conduction rate
//-------------------------------------------------------
double Initiation::non_dms_heat_conduction(double kappa) const
{
    return kappa*_T/_v/_v/_v/_rho;
}
//-------------------------------------------------------
//                      Non_dimensionalize Boltzmann constant
//-------------------------------------------------------
double Initiation::non_dms_Boltzmann(double k_bltz) const
{
    return k_bltz*_T/_v/_v/_rho/_length/_length/_length;
}
//-------------------------------------------------------
//                      Dimensionalize functions
//-------------------------------------------------------
double Initiation::dms_p(double p_non) const
{
    return p_non*_v*_v*_rho;
}
//-------------------------------------------------------
double Initiation::dms_T(double T_non) const
{
    return T_non*_T;
}
//-------------------------------------------------------
double Initiation::dms_rho(double rho_non) const
{
    return rho_non*_rho;
}
//-------------------------------------------------------
double Initiation::dms_mass(double mass_non) const
{
    return mass_non*_rho*_length*_length;
}
//-------------------------------------------------------
double Initiation::dms_time(double time_non) const
{
    return time_non/_v*_length;
}
//-------------------------------------------------------
double Initiation::dms_length(double length_non) const
{
    return length_non*_length;
}
//-------------------------------------------------------
Vec2d Initiation::dms_box_size(Vec2d box_size_non) const
{
    return box_size_non*_length;
}
//-------------------------------------------------------
double Initiation::dms_velocity(double velocity_non) const
{
    return velocity_non*_v;
}
//-------------------------------------------------------
Vec2d Initiation::dms_velocity(Vec2d velocity_non) const
{
    return velocity_non*_v;
}
//-------------------------------------------------------
double Initiation::dms_energy(double energy_non) const
{
    return energy_non*_rho*_length*_length*_length*_v*_v;
}
//-------------------------------------------------------
Vec2d Initiation::dms_acceleration(Vec2d acceleration_non) const
{
    return acceleration_non*_v*_v/_length;
}
//-------------------------------------------------------
double Initiation::dms_viscosity(double mu_non) const
{
    return mu_non*_v*_rho*_length;
}
//-------------------------------------------------------
