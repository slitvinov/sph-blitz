// \file boundary.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
#include <glog/logging.h>
#include <boost/smart_ptr/make_shared.hpp>

// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "boundary.h"
#include "Timer/timer.h"
#include "initiation.h"
//#include "glbtype.h"


// constructor
Boundary::Boundary(Initiation &ini, const ParticleManager &particles) {
  /// copy global properties from initiation class
  box_size = ini.box_size;
  x_clls = particles.x_clls;
  y_clls = particles.y_clls;
  // check if input-file exist
  /// - reading key words and configuration data from input file
  ///\todo{perhaps also implement an open boundary condition. at the moment shock tube simulations are done with "artificial" open edge by defining the domain from 0 til 3.9 and only placing particles from 1-3, so whatever boundary condition is  for xbl and xbr in the initiation file (tcl) it practically has no effect.}
  xBr = ini.interp->eval("[return $xBr]");
  UxBr[0] = ini.interp->eval("[return $UxBr(0)]");
  UxBr[1] = ini.interp->eval("[return $UxBr(1)]");

  xBl = ini.interp->eval("[return $xBl]");
  UxBl[0] = ini.interp->eval("[return $UxBl(0)]");
  UxBl[1] = ini.interp->eval("[return $UxBl(1)]");

  yBd = ini.interp->eval("[return $yBd]");
  UyBd[0] = ini.interp->eval("[return $UyBd(0)]");
  UyBd[1] = ini.interp->eval("[return $UyBd(1)]");

  yBu = ini.interp->eval("[return $yBu]");
  UyBu[0] = ini.interp->eval("[return $UyBu(0)]");
  UyBu[1] = ini.interp->eval("[return $UyBu(1)]");

  if (ini.simu_mode == 3) {
    /// read temperature of the wall from configuration file
    if (xBr == 0) xTr = ini.interp->getval("xTr");
    if (xBl == 0) xTl = ini.interp->getval("xTl");
    if (yBd == 0) yTd = ini.interp->getval("yTd");
    if (yBu == 0) yTu = ini.interp->getval("yTu");
    LOG(INFO) << "Temperature of the walls (xr, xl, yd, yu) is " << xTr << ' ' << xTl << ' ' << 
      yTd << ' ' << yTu;
  }

  show_information();

  //BuildBoundaryParticles is removed from the constructor and moved to the sph.cpp as an individual method call. In this way it can be switched of for 1D simulation
  //BuildBoundaryParticle(particles, hydro);
   
  LOG(INFO) << "boundary condition constructor successfully executed";
}

// show information on screen
void Boundary::show_information() const {
  std::cerr << "The left, right, lower and upper boundary conditions are "
      << xBl << ", "<< xBr << ", " << yBd << ", " << yBu << " \n";
  std::cerr << "0: wall boundary condition\n";
  std::cerr << "1: periodic boundary condition\n";
  std::cerr << "2: free slip wall boundary condition\n";
  std::cerr << "3: symmetry boundary condition\n";
}

// check particle if the real particles run out of the computational domain
void Boundary::RunAwayCheck(Hydrodynamics &hydro) {
  /// - iterate the particle list
  for (std::list<spParticle>::const_iterator  p = hydro.particle_list.begin(); 
       p != hydro.particle_list.end();
       p++) {
    spParticle prtl = *p;
    if (fabs(prtl->R[0]) >= 2.0*box_size[0] || fabs(prtl->R[1]) >= 2.0*box_size[1]) {
      std::cerr << "Boundary: the particles run out too far away from the domain! \n";
      std::cerr << __FILE__ << ':' << __LINE__ << std::endl;
      exit(EXIT_FAILURE);
    }
    ///- only checking real particles (for all boundaries)
    if (prtl->bd == 0) {
      //west boundary
      if (prtl->R[0] < 0.0) {
        switch(xBl) {
          //wall
          case 0: 
            prtl->R[0] = - prtl->R[0]; 
            break;
            //periodic
          case 1:
            prtl->R[0] = box_size[0] + prtl->R[0];
            break;
            //free slip
          case 2:
            prtl->R[0] = - prtl->R[0]; 
            break;
            //symmetry
          case 3:
            prtl->R[0] = - prtl->R[0]; 
            break;
        }
      }
      //east boundary
      if(prtl->R[0] > box_size[0]) {
        switch(xBr) {
          //wall
          case 0: 
            prtl->R[0] = 2.0*box_size[0] - prtl->R[0]; 
            break;
            //periodic
          case 1:
            prtl->R[0] = prtl->R[0] - box_size[0];
            break;
            //free slip
          case 2: 
            prtl->R[0] = 2.0*box_size[0] - prtl->R[0]; 
            break;
            //symmetry
          case 3:
            prtl->R[0] = 2.0*box_size[0] - prtl->R[0]; 
            break;
        }
      }
      //south boundary
      if(prtl->R[1] < 0.0) {
        switch(yBd) {
          //wall
          case 0: 
            prtl->R[1] = - prtl->R[1]; 
            break;
            //periodic
          case 1:
            prtl->R[1] = box_size[1] + prtl->R[1];
            break;
            //free slip
          case 2: 
            prtl->R[1] = - prtl->R[1]; 
            break;
            //symmetry
          case 3:
            prtl->R[1] = - prtl->R[1]; 
            break;
        }
      }
      //north boundary
      if(prtl->R[1] > box_size[1]) {
        switch(yBu) {
          //wall
          case 0: 
            prtl->R[1] = 2.0*box_size[1] - prtl->R[1]; 
            break;
            //periodic
          case 1:
            prtl->R[1] = prtl->R[1] - box_size[1];
            break;
            //free slip
          case 2: 
            prtl->R[1] = 2.0*box_size[1] - prtl->R[1]; 
            break;
            //symmetry
          case 3:
            prtl->R[1] = 2.0*box_size[1] - prtl->R[1]; 
            break;
        }
      }
    }
  }
}
//----------------------------------------------------------------------------------------
//                        build boundary particles
//----------------------------------------------------------------------------------------
void Boundary::BuildBoundaryParticle(ParticleManager &particles, Hydrodynamics &hydro)
{
  /// <ul><li>clear boundary particles list
  boundary_particle_list.clear();
    
  int kb = 0;
  int ku = 0;
  //default: no corner needs to be considered
  int mb = x_clls;
  int mu = x_clls;
    
  //corners to be considered    
  if(xBl == yBd) kb = 1; //south-west corner
  if(xBr == yBd) mb = x_clls - 1; // south-east corner
  if(xBl == yBu) ku = 1; //north-west corner
  if(xBr == yBu) mu = x_clls - 1; //north-east corner

  /// <li>boundary condition for each side
  //x direction
  for(int j = 1; j < y_clls - 1; j++) {
    /// <ul><li>west side: test boundary parameter for one of the following cases and then build the appropriate boundary particles
    //clear cell linked list data (particles)
    particles.cell_lists(0,j).clear();
        
    /// <ul>
    /// <li>the rigid wall conditions     
    if(xBl == 0 || xBl == 2) {
      //iterate the corresponded cell linked list
      for (std::list<spParticle>::const_iterator  p10 = particles.cell_lists(1,j).begin(); 
           p10!=particles.cell_lists(1,j).end(); 
           p10++) {
                
        //the original real particle
        spParticle prtl_old = *p10;
        spParticle prtl = boost::make_shared<Particle >(prtl_old, hydro.materials[0]);

        //boundary condition
        Boundary_W(prtl);

        //in which cell
        prtl->cell_i = 0; prtl->cell_j = j; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(0,j).insert(particles.cell_lists(0,j).begin(), prtl);
      }
    }
        
    /// <li>the symmetry conditions     
    if(xBl == 3) {
      //iterate the corresponded cell linked list
      for (std::list<spParticle>::const_iterator  p13 = particles.cell_lists(1,j).begin(); 
           p13 != particles.cell_lists(1,j).end(); 
           p13++) {
                
        //the original real particle
        spParticle prtl_old = *p13;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_W(prtl);

        //in which cell
        prtl->cell_i = 0; prtl->cell_j = j; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(0,j).insert(particles.cell_lists(0,j).begin(), prtl);
      }
    }

    /// <li>the periodic conditions </ul>    
    if(xBl == 1) {
      //iterate the corresponded cell linked list
      for (std::list<spParticle>::const_iterator  p11 = particles.cell_lists(x_clls - 2,j).begin(); 
           p11 != particles.cell_lists(x_clls - 2,j).end(); 
           p11++) {
                    
        //the original real particle
        spParticle prtl_old = *p11;
	///create a new particle identical to old particle ("copy")(boost creates smart pointer and the corresponding object)
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        ///boundary condition (modify properties of copied particle according to boundary condition)
        Boundary_W(prtl);
                
        //in which cell
        prtl->cell_i = 0; prtl->cell_j = j; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(0,j).insert(particles.cell_lists(0,j).begin(), prtl);
      }
    }

    /// <li>east side
    //clear linked list data (particles)
    particles.cell_lists(x_clls - 1,j).clear();

    /// <ul><li>the rigid wall conditions     
    if(xBr == 0 || xBr == 2) {
      //iterate the corresponded cell linked list
      for (std::list<spParticle>::const_iterator  p20 = particles.cell_lists(x_clls - 2,j).begin(); 
           p20 != particles.cell_lists(x_clls - 2,j).end(); 
           p20++) {
                    
        //the original real particle
        spParticle prtl_old = *p20;
        spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

        //boundary condition
        Boundary_E(prtl);

        //in which cell
        prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(x_clls- 1,j).insert(particles.cell_lists(x_clls - 1,j).begin(), prtl);
      }
    }
        
    /// <li>the symmetry conditions     
    if(xBr == 3) {
      //iterate the corresponded cell linked list
      for (std::list<spParticle>::const_iterator  p23 = particles.cell_lists(x_clls - 2,j).begin(); 
           p23 != particles.cell_lists(x_clls - 2,j).end(); 
           p23++) {
                    
        //the original real particle
        spParticle prtl_old = *p23;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_E(prtl);

        //in which cell
        prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(x_clls- 1,j).insert(particles.cell_lists(x_clls - 1,j).begin(), prtl);
      }
    }

    /// <li>the perodic conditions</ul>    
    if(xBr == 1) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p21 = particles.cell_lists(1,j).begin(); 
           p21 != particles.cell_lists(1,j).end(); 
           p21++) {
                    
        //the original real particle
        spParticle prtl_old = *p21;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_E(prtl);

        //in which cell
        prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(x_clls- 1,j).insert(particles.cell_lists(x_clls - 1,j).begin(), prtl);
      }
    }
  }

  //y direction

  /// <li>south side
  for (int i = kb; i < mb; i++) {
    //clear cell linked list data (particles)
    particles.cell_lists(i,0).clear();

    /// <ul><li>the rigid wall conditions     
    if(yBd == 0 || yBd == 2) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p30 = particles.cell_lists(i,1).begin(); 
           p30 != particles.cell_lists(i,1).end(); 
           p30++) {
                    
        //the original real particle
        spParticle prtl_old = *p30;
        spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

        //boundary condition
        Boundary_S(prtl);

        //in which cell
        prtl->cell_i = i; prtl->cell_j = 0; 
        //insert its position on the image particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(i,0).insert(particles.cell_lists(i,0).begin(), prtl);
      }
    }

    /// <li>the symmetry conditions     
    if(yBd == 3) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p33 = particles.cell_lists(i,1).begin(); 
           p33 != particles.cell_lists(i,1).end(); 
           p33++) {
                    
        //the original real particle
        spParticle prtl_old = *p33;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_S(prtl);

        //in which cell
        prtl->cell_i = i; prtl->cell_j = 0; 
        //insert its position on the image particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(i,0).insert(particles.cell_lists(i,0).begin(), prtl);
      }
    }

    /// <li>the perodic conditions</ul>    
    if(yBd == 1) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p31 = particles.cell_lists(i,y_clls - 2).begin(); 
           p31 != particles.cell_lists(i,y_clls - 2).end(); 
           p31++) {
                    
        //the original real particle
        spParticle prtl_old = *p31;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_S(prtl);

        //in which cell
        prtl->cell_i = i; prtl->cell_j = 0; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(i,0).insert(particles.cell_lists(i,0).begin(), prtl);
      }
    }
  }

  /// <li>north side
  for (int i = ku; i < mu; i++) {
    //clear the linked list data (particles)
    particles.cell_lists(i,y_clls - 1).clear();

    /// <ul><li>the rigid wall conditions     
    if(yBu == 0 || yBu == 2) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p40 = particles.cell_lists(i,y_clls - 2).begin(); 
           p40 != particles.cell_lists(i,y_clls - 2).end(); 
           p40++) {
                    
        //the original real particle
        spParticle prtl_old = *p40;
        spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

        //boundary condition
        Boundary_N(prtl);

        //in which cell
        prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(i,y_clls- 1).insert(particles.cell_lists(i,y_clls - 1).begin(), prtl);
      }
    }
    
    /// <li>the symmetry conditions     
    if(yBu == 3) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p43 = particles.cell_lists(i,y_clls - 2).begin(); 
           p43 != particles.cell_lists(i,y_clls - 2).end(); 
           p43++) {
                    
        //the original real particle
        spParticle prtl_old = *p43;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_N(prtl);

        //in which cell
        prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(i,y_clls- 1).insert(particles.cell_lists(i,y_clls - 1).begin(), prtl);
      }
    }

    /// <li>the perodic conditions</ul></ul>    
    if(yBu == 1) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p41 = particles.cell_lists(i,1).begin(); 
           p41 != particles.cell_lists(i,1).end(); 
           p41++) {
                    
        //the original real particle
        spParticle prtl_old = *p41;
        spParticle prtl = boost::make_shared<Particle>(prtl_old);

        //boundary condition
        Boundary_N(prtl);

        //in which cell
        prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
        //insert its position on the particle list
        boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
        //insert the position into corresponding cell list
        particles.cell_lists(i,y_clls- 1).insert(particles.cell_lists(i,y_clls - 1).begin(), prtl);
      }
    }
  }

  /// <li>considering the coner cells

  /// <ul><li>south-west corner
  /// <ul><li>the rigid wall conditions     
  if( (xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2) ) {
    //clear cell linked list data (particles)
    particles.cell_lists(0,0).clear();
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p130 = particles.cell_lists(1,1).begin(); 
         p130 != particles.cell_lists(1,1).end(); 
         p130++) {
                    
      //the original real particle
      spParticle prtl_old = *p130;
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_SW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = 0; 
      //insert its position on the image particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,0).insert(particles.cell_lists(0,0).begin(), prtl);
    }
  }

  /// <li>the symmetry conditions     
  if(xBl == 3 && yBd == 3) {
    //clear cell linked list data (particles)
    particles.cell_lists(0,0).clear();
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p130 = particles.cell_lists(1,1).begin(); 
         p130 != particles.cell_lists(1,1).end(); 
         p130++) {
                    
      //the original real particle
      spParticle prtl_old = *p130;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = 0; 
      //insert its position on the image particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,0).insert(particles.cell_lists(0,0).begin(), prtl);
    }
  }
    
  /// <li> the perodic conditions </ul>    
  if(xBl == 1 && yBd == 1) {
    //clear cell linked list data (particles)
    particles.cell_lists(0,0).clear();
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p131 = particles.cell_lists(x_clls - 2,y_clls - 2).begin(); 
         p131 != particles.cell_lists(x_clls - 2,y_clls - 2).end(); 
         p131++) {
                    
      //the original real particle
      spParticle prtl_old = *p131;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = 0; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,0).insert(particles.cell_lists(0,0).begin(), prtl);
    }
  }
        
  /// <li>north-west corner

  /// <ul><li>the rigid wall conditions     
  if( (xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2) ) {
    //clear the linked list data (particles)
    particles.cell_lists(0,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p140 = particles.cell_lists(1,y_clls - 2).begin(); 
         p140 != particles.cell_lists(1,y_clls - 2).end(); 
         p140++) {
                
      //the original real particle
      spParticle prtl_old = *p140;
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_NW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,y_clls- 1).insert(particles.cell_lists(0,y_clls - 1).begin(), prtl);
    }
  }
    
  /// <li>the symmetry conditions     
  if(xBl == 3 && yBu == 3) {
    //clear the linked list data (particles)
    particles.cell_lists(0,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p140 = particles.cell_lists(1,y_clls - 2).begin(); 
         p140 != particles.cell_lists(1,y_clls - 2).end(); 
         p140++) {
                
      //the original real particle
      spParticle prtl_old = *p140;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,y_clls- 1).insert(particles.cell_lists(0,y_clls - 1).begin(), prtl);
    }
  }

  /// <li>the perodic conditions</ul>    
  if(xBl == 1 && yBu == 1) {
    //clear the linked list data (particles)
    particles.cell_lists(0,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p141 = particles.cell_lists(x_clls - 2,1).begin(); 
         p141 != particles.cell_lists(x_clls - 2,1).end(); 
         p141++) {
                
      //the original real particle
      spParticle prtl_old = *p141;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,y_clls- 1).insert(particles.cell_lists(0,y_clls - 1).begin(), prtl);
    }
  }

  /// <li>north-east corner
    
  /// <ul><li>the rigid wall conditions     
  if( (xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2) ) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,y_clls - 1).clear();
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p240 = particles.cell_lists(x_clls - 2,y_clls - 2).begin(); 
         p240 != particles.cell_lists(x_clls - 2,y_clls - 2).end(); 
         p240++) {
                
      //the original real particle
      spParticle prtl_old = *p240;
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_NE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls- 1,y_clls - 1).insert(particles.cell_lists(x_clls - 1,y_clls - 1).begin(), prtl);
    }
  }
        
  /// <li>the symmetry conditions     
  if(xBr == 3 && yBu == 3) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,y_clls - 1).clear();
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p240 = particles.cell_lists(x_clls - 2,y_clls - 2).begin(); 
         p240 != particles.cell_lists(x_clls - 2,y_clls - 2).end(); 
         p240++) {
                
      //the original real particle
      spParticle prtl_old = *p240;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls- 1,y_clls - 1).insert(particles.cell_lists(x_clls - 1,y_clls - 1).begin(), prtl);
    }
  }

  /// <li>the perodic conditions</ul>    
  if(xBr == 1 && yBu == 1) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p241 = particles.cell_lists(1,1).begin(); 
         p241 != particles.cell_lists(1,1).end(); 
         p241++) {
                    
      //the original real particle
      spParticle prtl_old = *p241;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls- 1,y_clls - 1).insert(particles.cell_lists(x_clls - 1,y_clls - 1).begin(), prtl);
    }
  }

  /// <li>south-east corner
    
  /// <ul> <li>the rigid wall conditions     
  if( (xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2) ) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,0).clear();
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p230 = particles.cell_lists(x_clls - 2,1).begin(); 
         p230 != particles.cell_lists(x_clls - 2,1).end(); 
         p230++) {
                
      //the original real particle
      spParticle prtl_old = *p230;
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_SE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0; 
      //insert its position on the image particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls - 1,0).insert(particles.cell_lists(x_clls - 1,0).begin(), prtl);
    }
  }

  /// <li>the symmetry conditions     
  if(xBr == 3 && yBd == 3) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,0).clear();
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p230 = particles.cell_lists(x_clls - 2,1).begin(); 
         p230 != particles.cell_lists(x_clls - 2,1).end(); 
         p230++) {
                
      //the original real particle
      spParticle prtl_old = *p230;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0; 
      //insert its position on the image particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls - 1,0).insert(particles.cell_lists(x_clls - 1,0).begin(), prtl);
    }
  }

  /// <li>the perodic conditions</ul></ul>
  if(xBr == 1 && yBd == 1) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,0).clear();
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p231 = particles.cell_lists(1,y_clls - 2).begin(); 
         p231 != particles.cell_lists(1,y_clls - 2).end(); 
         p231++) {
                    
      //the original real particle
      spParticle prtl_old = *p231;
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0; 
      //insert its position on the particle list
      boundary_particle_list.insert(boundary_particle_list.begin(), prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls - 1,0).insert(particles.cell_lists(x_clls - 1,0).begin(), prtl);
    }
  }
}
//----------------------------------------------------------------------------------------
//                            boundary condition
//----------------------------------------------------------------------------------------
void Boundary::BoundaryCondition(ParticleManager &particles) {
  int kb, ku, mb, mu;
  //default: no coner need to be considered
  kb = 0; mb = x_clls;
  ku = 0; mu = x_clls;
    
  //coners to be considered    
  if(xBl == yBd) kb = 1; //south-west corner
  if(xBr == yBd) mb = x_clls - 1; // south-east corner
  if(xBl == yBu) ku = 1; //north-west corner
  if(xBr == yBu) mu = x_clls - 1; //north-east corner

  //x direction
  for(int j = 1; j < y_clls - 1; j++) {
    
    /// <ul> <li>west side

    /// <ul> <li>the rigid wall conditions</ul>    
    if(xBl == 0 || xBl == 2) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p1 = particles.cell_lists(0,j).begin(); 
           p1 != particles.cell_lists(0,j).end(); 
           p1++) {
        spParticle prtl = *p1;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 0);

        //boundary condition
        Boundary_W(prtl);
      }
    }
    /// <ul> <li>the perodic or symmetry conditions </ul>
    if(xBl == 1 || xBl == 3) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p1 = particles.cell_lists(0,j).begin(); 
           p1 != particles.cell_lists(0,j).end(); 
           p1++) {
                
        spParticle prtl = *p1;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 1);

        //boundary condition
        Boundary_W(prtl);
      }
    }

    /// <li> east side
    /// <ul> <li> the rigid wall conditions    
    if(xBr == 0 || xBr == 2) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p2 = particles.cell_lists(x_clls - 1,j).begin(); 
           p2 != particles.cell_lists(x_clls - 1,j).end(); 
           p2++) {
                    
        spParticle prtl = *p2;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 0);

        //boundary condition
        Boundary_E(prtl);
      }
    }
    /// <li>the perodic or symmetry conditions</ul>    
    if(xBr == 1 || xBr == 3) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p2 = particles.cell_lists(x_clls - 1,j).begin(); 
           p2 != particles.cell_lists(x_clls - 1,j).end(); 
           p2++) {
                    
        spParticle prtl = *p2;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 1);

        //boundary condition
        Boundary_E(prtl);
      }
    }
  }

  //y direction
    
  /// <li>south side
  for (int i = kb; i < mb; i++) {
    /// <ul><li>the rigid wall conditions    
    if(yBd == 0 || yBd == 2) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p3 = particles.cell_lists(i,0).begin(); 
           p3 != particles.cell_lists(i,0).end(); 
           p3++) {
                    
        spParticle prtl = *p3;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 0);

        //boundary condition
        Boundary_S(prtl);
      }
    }
    /// <li>the perodic or symmetry conditions</ul>    
    if(yBd == 1 || yBd == 3) {
      //iterate the correspeond cell linked list
      for (std::list<spParticle>::const_iterator  p3 = particles.cell_lists(i,0).begin(); 
           p3 != particles.cell_lists(i,0).end(); 
           p3++) {
                    
        spParticle prtl = *p3;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 1);

        //boundary condition
        Boundary_S(prtl);
      }
    }
  }

  /// <li>north side
  for (int i = ku; i < mu; i++) {
    /// <ul><li>the rigid wall conditions    
    if(yBu == 0 || yBu == 2) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p4 = particles.cell_lists(i,y_clls - 1).begin(); 
           p4 != particles.cell_lists(i,y_clls - 1).end(); 
           p4++) {
                    
        //the original real particle
        spParticle prtl = *p4;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 0);
    
        //boundary condition
        Boundary_N(prtl);
      }
    }
    /// <li>the perodic or symmetry conditions</ul></ul>    
    if(yBu == 1 || yBu == 3) {
      //iterate the correspeond cell for real and wall partilces
      for (std::list<spParticle>::const_iterator  p4 = particles.cell_lists(i,y_clls - 1).begin(); 
           p4 != particles.cell_lists(i,y_clls - 1).end(); 
           p4++) {
                    
        //the original real particle
        spParticle prtl = *p4;
        //copy states from the original particle
        prtl->StatesCopier(prtl->rl_prtl, 1);
    
        //boundary condition
        Boundary_N(prtl);
      }
    }
  }

  /// considering the coner cells

  /// <ul><li>south-west corner
  /// <ul><li>the rigid wall conditions     
  if( (xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2) ) {
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p13 = particles.cell_lists(0,0).begin(); 
         p13 != particles.cell_lists(0,0).end(); 
         p13++) {
                    
      spParticle prtl = *p13;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);

      //boundary condition
      Boundary_SW(prtl);
    }
  }
  /// <li>the perodic or symmetry conditions</ul>    
  if( (xBl == 1 && yBd == 1) || (xBl == 3 && yBd == 3) ) {
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p13 = particles.cell_lists(0,0).begin(); 
         p13 != particles.cell_lists(0,0).end(); 
         p13++) {
                    
      spParticle prtl = *p13;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_SW(prtl);
    }
  }
        
  /// <li>north-west corner
  /// <ul><li>the rigid wall conditions     
  if( (xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2) ) {
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p14 = particles.cell_lists(0,y_clls - 1).begin(); 
         p14 != particles.cell_lists(0,y_clls - 1).end(); 
         p14++) {
                    
      //the original real particle
      spParticle prtl = *p14;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);

      //boundary condition
      Boundary_NW(prtl);
    }
  }
  /// <li>the perodic or symmetry conditions</ul>    
  if( (xBl == 1 && yBu == 1) || (xBl == 3 && yBu == 3) ) {
    //iterate the correspeond cell for real and wall partilces
    for (std::list<spParticle>::const_iterator  p14 = particles.cell_lists(0,y_clls - 1).begin(); 
         p14 != particles.cell_lists(0,y_clls - 1).end(); 
         p14++) {
                    
      //the original real particle
      spParticle prtl = *p14;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_NW(prtl);
    }
  }

  /// <li>north-east corner
  /// <ul><li>the rigid wall conditions     
  if( (xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2) ) {
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p24 = particles.cell_lists(x_clls - 1,y_clls - 1).begin(); 
         p24 != particles.cell_lists(x_clls - 1,y_clls - 1).end(); 
         p24++) {
                
      //the original real particle
      spParticle prtl = *p24;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);

      //boundary condition
      Boundary_NE(prtl);
    }
  }
  /// <li>the perodic or symmetry conditions</ul>    
  if( (xBr == 1 && yBu == 1) || (xBr == 3 && yBu == 3) ) {
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p24 = particles.cell_lists(x_clls - 1,y_clls - 1).begin(); 
         p24 != particles.cell_lists(x_clls - 1,y_clls - 1).end(); 
         p24++) {
                
      //the original real particle
      spParticle prtl = *p24;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_NE(prtl);
    }
  }

  /// <li>south-east corner
  /// <ul><li>the rigid wall conditions     
  if( (xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2) ) {    
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p23 = particles.cell_lists(x_clls - 1,0).begin(); 
         p23 != particles.cell_lists(x_clls - 1,0).end(); 
         p23++) {
                    
      //the original real particle
      spParticle prtl = *p23;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);
    
      //boundary condition
      Boundary_SE(prtl);
    }
  }

  /// <li>the perodic or symmetry conditions</ul></ul></ul>    
  if( (xBr == 1 && yBd == 1) || (xBr == 3 && yBd == 3) ) {    
    //iterate the correspeond cell linked list
    for (std::list<spParticle>::const_iterator  p23 = particles.cell_lists(x_clls - 1,0).begin(); 
         p23 != particles.cell_lists(x_clls - 1,0).end(); 
         p23++) {
      //the original real particle
      spParticle prtl = *p23;
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_SE(prtl);
    }
  }
}
//----------------------------------------------------------------------------------------
//            implement west side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_W(spParticle prtl)
{
  //the rigid wall conditions    
  switch(xBl) {
    //wall
    case 0: 
      prtl->R[0] = - prtl->R[0]; 
      prtl->U = UxBl*2.0 - prtl->U;
      prtl->T = xTl;
      break;
      //perodic
    case 1:
      prtl->R[0] = prtl->R[0] - box_size[0];
      break;
      //free slip wall
    case 2: 
      prtl->R[0] = - prtl->R[0]; 
      prtl->U[0] = UxBl[0]*2.0 - prtl->U[0];
      break;
      //symmetry
    case 3: 
      prtl->R[0] = - prtl->R[0]; 
      prtl->U[0] = UxBl[0]*2.0 - prtl->U[0];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement east side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_E(spParticle prtl)
{
  //the rigid wall conditions    
  switch(xBr) {
    //wall
    case 0: 
      prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
      prtl->U = UxBr*2.0 - prtl->U;
      prtl->U = xTr;
      break;
      //perodic
    case 1:
      prtl->R[0] = prtl->R[0] + box_size[0];
      break;
      //free slip wall
    case 2: 
      prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
      prtl->U[0] = UxBr[0]*2.0 - prtl->U[0];
      break;
      //symmetry
    case 3: 
      prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
      prtl->U[0] = UxBr[0]*2.0 - prtl->U[0];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement south side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_S(spParticle prtl)
{
  //the rigid wall conditions    
  switch(yBd) {
    //wall
    case 0: 
      prtl->R[1] = - prtl->R[1]; 
      prtl->U = UyBd*2.0 - prtl->U;
      prtl->T = yTd;
      break;
      //perodic
    case 1:
      prtl->R[1] = prtl->R[1] - box_size[1];
      break;
      //free slip wall
    case 2: 
      prtl->R[1] = - prtl->R[1]; 
      prtl->U[1] = UyBd[1]*2.0 - prtl->U[1];
      break;
      //symmetry
    case 3: 
      prtl->R[1] = - prtl->R[1]; 
      prtl->U[1] = UyBd[1]*2.0 - prtl->U[1];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement north side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_N(spParticle prtl)
{
  //the rigid wall conditions    
  switch(yBu) {
    //wall
    case 0: 
      prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
      prtl->U = UyBu*2.0 - prtl->U;
      prtl->T = yTu;
      break;
      //perodic
    case 1:
      prtl->R[1] = prtl->R[1] + box_size[1];
      break;
      //free slip wall
    case 2: 
      prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
      prtl->U[1] = UyBu[1]*2.0 - prtl->U[1];
      break;
      //symmetry
    case 3: 
      prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
      prtl->U[1] = UyBu[1]*2.0 - prtl->U[1];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement south-west corner boundadry by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_SW(spParticle prtl)
{
  //the rigid wall conditions    
  switch(xBl) {
    //wall
    case 0: 
      prtl->R = - prtl->R;
      prtl->U[0] = UyBd[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBl[1]*2.0 - prtl->U[1];
      prtl->T = xTl;
      break;
      //perodic
    case 1:
      prtl->R = prtl->R - box_size;
      break;
      //free slip wall
    case 2: 
      prtl->R = - prtl->R;
      prtl->U[0] = UyBd[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBl[1]*2.0 - prtl->U[1];
      break;
      //symmetry
    case 3: 
      prtl->R = - prtl->R;
      prtl->U[0] = UyBd[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBl[1]*2.0 - prtl->U[1];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement north-west corner boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_NW(spParticle prtl)
{
  //the rigid wall conditions    
  switch(xBl) {
    //wall
    case 0: 
      prtl->R[0] = - prtl->R[0]; 
      prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
      prtl->U[0] = UyBu[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBl[1]*2.0 - prtl->U[1];
      prtl->T = xTl;
      break;
      //perodic
    case 1:
      prtl->R[0] = prtl->R[0] - box_size[0];
      prtl->R[1] = prtl->R[1] + box_size[1];
      break;
      //free slip wall
    case 2: 
      prtl->R[0] = - prtl->R[0]; 
      prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
      prtl->U[0] = UyBu[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBl[1]*2.0 - prtl->U[1];
      break;
      //symmetry
    case 3: 
      prtl->R[0] = - prtl->R[0]; 
      prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
      prtl->U[0] = UyBu[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBl[1]*2.0 - prtl->U[1];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement north-east corner boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_NE(spParticle prtl)
{
  //the rigid wall conditions    
  switch(xBr) {
    //wall
    case 0: 
      prtl->R = box_size*2.0 - prtl->R; 
      prtl->U[0] = UyBu[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBr[1]*2.0 - prtl->U[1];
      prtl->T = xTr;
      break;
      //perodic
    case 1:
      prtl->R = prtl->R + box_size;
      break;
      //free slip wall
    case 2: 
      prtl->R = box_size*2.0 - prtl->R; 
      prtl->U[0] = UyBu[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBr[1]*2.0 - prtl->U[1];
      break;
      //symmetry
    case 3: 
      prtl->R = box_size*2.0 - prtl->R; 
      prtl->U[0] = UyBu[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBr[1]*2.0 - prtl->U[1];
      break;
  }
}
//----------------------------------------------------------------------------------------
//            implement north-east corner boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_SE(spParticle prtl)
{
  //the rigid wall conditions    
  switch(xBr) {
    //wall
    case 0: 
      prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
      prtl->R[1] = - prtl->R[1]; 
      prtl->U[0] = UyBd[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBr[1]*2.0 - prtl->U[1];
      prtl->T = xTr;
      break;
      //perodic
    case 1:
      prtl->R[0] = prtl->R[0] + box_size[0];
      prtl->R[1] = prtl->R[1] - box_size[1];
      break;
      //free slip wall
    case 2: 
      prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
      prtl->R[1] = - prtl->R[1]; 
      prtl->U[0] = UyBd[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBr[1]*2.0 - prtl->U[1];
      break;
      //symmetry
    case 3: 
      prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
      prtl->R[1] = - prtl->R[1]; 
      prtl->U[0] = UyBd[0]*2.0 - prtl->U[0];
      prtl->U[1] = UxBr[1]*2.0 - prtl->U[1];
      break;
  }
}

