// output.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Output the computational results
//              output.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>

// ***** localincludes *****
#include "glbcls.h"
#include "glbfunc.h"
#include "output.h"
#include "hydrodynamics.h"
#include "boundary.h"
#include "particlemanager.h"
#include "mls.h"
#include "initiation.h"
#include "quinticspline.h"
#include "material.h"
#include "particle.h"

using namespace std;

//--------------------------------------------------------------------------------------------
//                                                                      constructor
//--------------------------------------------------------------------------------------------
Output::Output(Initiation &ini)
{
    //copy boundary properties from initiation class
    strcpy(Project_name, ini.Project_name);
    number_of_materials = ini.number_of_materials;
    x_cells = ini.x_cells; y_cells = ini.y_cells;
    hdelta = ini.hdelta; 
    delta = ini.delta;
}
//--------------------------------------------------------------------------------------------
//                              output particle positions respected different materials
//--------------------------------------------------------------------------------------------
void Output::OutputParticles(Hydrodynamics &hydro, Boundary &boundary, 
                             double Time, Initiation &ini)
{
    int i, j;
    double Itime;
    char file_name[50], file_list[20];

    //produce output file name
    Itime = ini.dms_time(Time)*1.0e6;
    strcpy(file_name,"./outdata/prtl");
    sprintf(file_list, "%.10d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");

    ofstream out(file_name);
    //defining header for tecplot(plot software)
    out<<"title='particle position' \n";
    out<<"variables=x, y, Ux, Uy \n";
        
    //output real and soild particles
    for(i = 0; i < number_of_materials; i++) {
                
        j = 0; //if there is such material or not
        //iterate the real partilce list
        for (LlistNode<Particle> *p = hydro.particle_list.first(); 
             !hydro.particle_list.isEnd(p); 
             p = hydro.particle_list.next(p)) {
                                
            Particle *prtl = hydro.particle_list.retrieve(p);
            if(strcmp(hydro.materials[i].material_name, prtl->mtl->material_name) == 0) {
                j ++;
                if(j == 1)      out<<"zone t='"<<hydro.materials[i].material_name<<"' \n";
                out<<ini.dms_length(prtl->R[0])<<"  "<<ini.dms_length(prtl->R[1])
                   <<"  "<<ini.dms_velocity(prtl->U[0])<<"  "<<ini.dms_velocity(prtl->U[1])<<"\n";
            }
        }

        //iterate the boundary partilce list
        for (LlistNode<Particle> *p1 = boundary.boundary_particle_list.first(); 
             !boundary.boundary_particle_list.isEnd(p1); 
             p1 = boundary.boundary_particle_list.next(p1)) {
                                
            Particle *prtl = boundary.boundary_particle_list.retrieve(p1);
            if(strcmp(hydro.materials[i].material_name, prtl->mtl->material_name) == 0) { 
                j ++;
                if(j == 1)      out<<"zone t='"<<hydro.materials[i].material_name<<"' \n";
                out<<ini.dms_length(prtl->R[0])<<"  "<<ini.dms_length(prtl->R[1])
                   <<"  "<<ini.dms_velocity(prtl->U[0])<<"  "<<ini.dms_velocity(prtl->U[1])<<"\n";
            }
        }
    }

}
//--------------------------------------------------------------------------------------------
//                                                      output material states on uniform grid
//--------------------------------------------------------------------------------------------
void Output::OutputStates(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
                          double Time, Initiation &ini)
{
    int i, j, n;
    int gridx, gridy;
    Vec2d pstn;
    double rho, phi, pressure, Temperature, x_velocity, y_velocity;
    double Itime;
    char file_name[50], file_list[10];

        
    //grid box size
    gridx = x_cells*hdelta; gridy = y_cells*hdelta;
        
    //produce output file name
    Itime = ini.dms_time(Time)*1.0e6;
    strcpy(file_name,"./outdata/states");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");

    ofstream out(file_name);
    //defining header for tecplot(plot software)
    out<<"title='mapped states' \n";
    out<<"variables=x, y, p, rho, phi, Ux, Uy, T \n";
    out<<"zone t='filed', i="<<gridx + 1<<", j="<<gridy + 1<<"\n";
        
    //loop the grid points
    //NOTE: loop the x direction first and then the y direction!
    for(j = 0; j <= gridy; j++) { 
        for(i = 0; i <= gridx; i++) {
            pstn[0] = i*delta; pstn[1] = j*delta;
            //biuld the NNP_list
            particles.BuildNNP(pstn);
            //if the NNP list is not empty run MLS approximation
            if(!particles.NNP_list.empty()) 
                mls.MLSMapping(pstn, particles.NNP_list, weight_function, 1);
            n = 0;
            rho = 0.0; phi = 0.0; pressure = 0.0; Temperature = 0.0;
            x_velocity = 0.0; y_velocity = 0.0;
            //iterate this Nearest Neighbor Particle list
            for (LlistNode<Particle> *p = particles.NNP_list.first(); 
                 !particles.NNP_list.isEnd(p); 
                 p = particles.NNP_list.next(p)) {
                        
                //get particle data
                Particle *prtl = particles.NNP_list.retrieve(p);

                rho += prtl->rho*mls.phi[n];
                phi += prtl->phi[2][2]*mls.phi[n];
                pressure += prtl->p*mls.phi[n];
                Temperature += prtl->T*mls.phi[n];
                x_velocity += prtl->U[0]*mls.phi[n];
                y_velocity += prtl->U[1]*mls.phi[n];
                                
                n ++;
            }
            //clear the NNP_list
            particles.NNP_list.clear();

            out<<ini.dms_length(pstn[0])<<"  "<<ini.dms_length(pstn[1])
               <<"  "<<ini.dms_p(pressure)<<"  "<<ini.dms_rho(rho)
               <<"  "<<phi
               <<"  "<<ini.dms_velocity(x_velocity)<<"  "<<ini.dms_velocity(y_velocity)
               <<"  "<<ini.dms_T(Temperature)<<"\n";
        }
    }
    out.close();

}
//--------------------------------------------------------------------------------------------
//              Output real particle data for restart the computation
//--------------------------------------------------------------------------------------------
void Output::OutRestart(Hydrodynamics &hydro, double Time, Initiation &ini)
{
    int n;
    char outputfile[25];

    //non-dimensional data
    strcpy(outputfile, Project_name);
    strcat(outputfile,".rst");
    ofstream out(outputfile);

    //calculate the real particle number
    n = 0;
    for (LlistNode<Particle> *pp = hydro.particle_list.first(); 
         !hydro.particle_list.isEnd(pp); 
         pp = hydro.particle_list.next(pp)) {
                        
        Particle *prtl = hydro.particle_list.retrieve(pp);
        if(prtl->bd == 0) n ++;
                                                
    }
    //out reinitiation Time
    out<<Time<<"\n";
    out<<n<<"\n";
    //output real particles
    //iterate the partilce list
    for (LlistNode<Particle> *p = hydro.particle_list.first(); 
         !hydro.particle_list.isEnd(p); 
         p = hydro.particle_list.next(p)) {
                                
        Particle *prtl = hydro.particle_list.retrieve(p);
        if(prtl->bd == 0) 
            out<<prtl->mtl->material_name<<"  "<<prtl->R[0]<<"  "<<prtl->R[1]<<"  "<<prtl->U[0]<<"  "<<prtl->U[1]
               <<"  "<<prtl->rho<<"  "<<prtl->p<<"  "<<prtl->T<<"  \n";
    }
    out.close();
}
//--------------------------------------------------------------------------------------------
//                                      creat a head file for a movie of particle motion
//--------------------------------------------------------------------------------------------
void Output::CreatParticleMovie()
{
    char file_name[50];
    //produce output file name
    strcpy(file_name,"./outdata/prtl_movie.dat");

    ofstream out(file_name);
    out<<"title='particle movie' \n";
    out<<"variables=x, y, material, size \n";

    out.close();

}
//--------------------------------------------------------------------------------------------
//                                              write the data for a movie of particle motion
//                                              output the real and wall particles
//--------------------------------------------------------------------------------------------
void Output::WriteParticleMovie(Hydrodynamics &hydro, double Time, Initiation &ini)
{
    int k, m;
    char file_name[50];

    //produce output file name
    strcpy(file_name,"./outdata/prtl_movie.dat");

    ofstream out(file_name, ios::out | ios::ate);
    //zone names
    out<<"zone t='"<<ini.dms_time(Time)<<"' \n";
    //iterate the partilce list
    for (LlistNode<Particle> *p = hydro.particle_list.first(); 
         !hydro.particle_list.isEnd(p); 
         p = hydro.particle_list.next(p)) {
                        
        Particle *prtl = hydro.particle_list.retrieve(p);
        m = -1;
        //find the number of the material
        for(k = 0;  k < number_of_materials; k++) 
            if(strcmp(prtl->mtl->material_name, hydro.materials[k].material_name) == 0) m = k;
        out<<ini.dms_length(prtl->R[0])<<"  "<<ini.dms_length(prtl->R[1])
           <<"  "<<m<<"  "<<ini.dms_rho(prtl->rho)<<"\n";
    }
    out.close();

}
//--------------------------------------------------------------------------------------------
//                                      avergaed values for Poiseuille and Couette flows
//                                      the average is taken in horizontal diraction
//--------------------------------------------------------------------------------------------
void Output::OutAverage(ParticleManager &particles, MLS &mls, QuinticSpline &weight_function, 
                        double Time, Initiation &ini)
{
    int i, j, l, n;
    int gridx, gridy;
    Vec2d pstn;
    double rho, pressure, Temperature, x_velocity, y_velocity;
    double Itime;
    char file_name[50], file_list[10];

        
    //grid box size
    gridx = x_cells*hdelta; gridy = y_cells*hdelta;
        
    //produce output file name
    Itime = ini.dms_time(Time)*1.0e6;
    strcpy(file_name,"./outdata/averages");
    sprintf(file_list, "%d", (int)Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");

    ofstream out(file_name);
    //defining header for tecplot(plot software)
    out<<"title='averaged states' \n";
    out<<"variables=y, p, rho, Ux, Uy, T \n";
        
    //loop the grid points
    //NOTE: loop the x direction first and then the y direction!
    for(j = 0; j <= gridy; j++) { 
                
        l = 0;
        rho = 0.0; pressure = 0.0; Temperature = 0.0;
        x_velocity = 0.0; y_velocity = 0.0;
        for(i = 0; i <= gridx; i++) {
            pstn[0] = i*delta; pstn[1] = j*delta;
            //biuld the NNP_list
            particles.BuildNNP(pstn);
            //if the NNP list is not empty run MLS approximation
            if(!particles.NNP_list.empty()) 
                mls.MLSMapping(pstn, particles.NNP_list, weight_function, 0);
            n = 0;
            //iterate this Nearest Neighbor Particle list
            for (LlistNode<Particle> *p = particles.NNP_list.first(); 
                 !particles.NNP_list.isEnd(p); 
                 p = particles.NNP_list.next(p)) {
                        
                //get particle data
                Particle *prtl = particles.NNP_list.retrieve(p);

                rho += prtl->rho*mls.phi[n];
                pressure += prtl->p*mls.phi[n];
                Temperature += prtl->T*mls.phi[n];
                x_velocity += prtl->U[0]*mls.phi[n];
                y_velocity += prtl->U[1]*mls.phi[n];
                                
                n ++;
            }
            //clear the NNP_list
            particles.NNP_list.clear();
            l ++;
        }
                
        out<<ini.dms_length(pstn[1])<<"  "<<ini.dms_p(pressure)/double(l)<<"  "
           <<ini.dms_rho(rho)/double(l)<<"  "<<ini.dms_velocity(x_velocity)/double(l)<<"  "
           <<ini.dms_velocity(y_velocity)/double(l)<<"  "<<ini.dms_T(Temperature)/double(l)<<"\n";
    }
    out.close();
}
