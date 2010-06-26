// \file boundary.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

///-------------------------------------------------------------------
///			Define boundary and boundary conditions
///			boundary.cpp
///----------------------------------------------------------------
/// ***** system includes *****

#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "material.h"
#include "boundary.h"
#include "initiation.h"
#include "glbtype.h"
#include <boost/smart_ptr/make_shared.hpp>

using namespace std;

//construtor
Boundary::Boundary(Initiation &ini, Hydrodynamics &hydro, ParticleManager &particles)
{
  char Key_word[25];
  char inputfile[25];

  ///copy global properties from initiation class
  box_size = ini.box_size;
  x_clls = particles.x_clls; y_clls = particles.y_clls;
  number_of_materials = ini.number_of_materials;

  //check if inputfile exist
  strcpy(inputfile, ini.inputfile);
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Boundary: Cannot open "<< inputfile <<" \n";
    std::cout << __FILE__ << ':' << __LINE__ << std::endl;
    exit(1);
  }
  else cout<<"\nBoundary: read left, right, upper and lower boundary conditions from "<< inputfile <<" \n"; 

  ///- reading key words and configuration data from input file
  while(!fin.eof()) {
		
    //read a string block
    fin>>Key_word;
		
     ///- compare the key words for left, right, upper and lower boundary condition type and their velocities
    if(!strcmp(Key_word, "BOUNDARY")) fin>>wall_file>>xBl>>UxBl[0]>>UxBl[1]
					 >>xBr>>UxBr[0]>>UxBr[1]
					 >>yBd>>UyBd[0]>>UyBd[1]
					 >>yBu>>UyBu[0]>>UyBu[1];

  }
  fin.close();

  show_information(ini);

   if(ini.simu_mode==1)	
   {
   non_dimensionalize(ini);
  ///- build boundary particles
   BuildBoundaryParticle(particles, hydro);
   };
    cout<<"\n boundary condition constructor successfully executed \n";
}
//----------------------------------------------------------------------------------------
//								Non-dimensionalize
//----------------------------------------------------------------------------------------
void Boundary::non_dimensionalize(Initiation &ini)
{
  UxBl = ini.non_dms_velocity(UxBl); 
  UxBr = ini.non_dms_velocity(UxBr); 
  UyBd = ini.non_dms_velocity(UyBd); 
  UyBu = ini.non_dms_velocity(UyBu); 
}
//----------------------------------------------------------------------------------------
//								show information on screen
//----------------------------------------------------------------------------------------
void Boundary::show_information(Initiation &ini)
{
  ///- output the property parameters to the screen
  if(wall_file == 1) cout<<"We read wall particle data from " <<ini.Project_name<<".wll \n";
  cout<<"The left, right, lower and upper boundary conditions are "
      <<xBl<<", "<<xBr<<", "<<yBd<<", "<<yBu<<" \n";
  cout<<"0: wall boundary condition\n";
  cout<<"1: perodic boundary condition\n";
  cout<<"2: free slip wall boundary condition\n";
  cout<<"3: symmetry boundary condition\n";
}
//----------------------------------------------------------------------------------------
//			check particle if the real particles run out of the computational domain
//----------------------------------------------------------------------------------------
void Boundary::RunAwayCheck(Hydrodynamics &hydro)
{
  ///- iterate the partilce list
  for (LlistNode<spParticle >* p = hydro.particle_list.first(); 
       !hydro.particle_list.isEnd(p); 
       p = hydro.particle_list.next(p)) {
				
    spParticle prtl = *hydro.particle_list.retrieve(p);

    if(fabs(prtl->R[0]) >= 2.0*box_size[0] || fabs(prtl->R[1]) >= 2.0*box_size[1]) {
      cout<<"Boundary: the particles run out too far away from the domain! \n";
      std::cout << __FILE__ << ':' << __LINE__ << std::endl;
      exit(1);
    }
    ///- only checking real particles (for all boundaries)
    if(prtl->bd == 0) {
      //west boundary
      if(prtl->R[0] < 0.0) {
	switch(xBl) {
	  //wall
	case 0: 
	  prtl->R[0] = - prtl->R[0]; 
	  break;
	  //perodic
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
	  //perodic
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
	  //perodic
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
	  //perodic
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
//						build boundary particles
//----------------------------------------------------------------------------------------
void Boundary::BuildBoundaryParticle(ParticleManager &particles, Hydrodynamics &hydro)
{
  int i, j;

  /// <ul><li>clear boundary particles list
  boundary_particle_list.clear();
	
  int kb, ku, mb, mu;
  //default: no corner needs to be considered
  kb = 0; mb = x_clls;
  ku = 0; mu = x_clls;
	
  //corners to be considered	
  if(xBl == yBd) kb = 1; //south-west corner
  if(xBr == yBd) mb = x_clls - 1; // south-east corner
  if(xBl == yBu) ku = 1; //north-west corner
  if(xBr == yBu) mu = x_clls - 1; //north-east corner

  /// <li>boundary condition for each side
  //x direction
  for(j = 1; j < y_clls - 1; j++) {
    /// <ul><li>west side: test boundary parameter for one of the following cases and then build the appropriate boundary particles
    //clear cell linked list data (particles)
    particles.cell_lists(0,j).clear();
		
    /// <ul>
      /// <li>the rigid wall conditions 	
    if(xBl == 0 || xBl == 2) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p10 = particles.cell_lists(1,j).first(); 
	   !particles.cell_lists(1,j).isEnd(p10); 
	   p10 = particles.cell_lists(1,j).next(p10)) {
				
	//the original real particle
	spParticle prtl_old = * (particles.cell_lists(1,j).retrieve(p10) );
	spParticle prtl = boost::make_shared<Particle >(prtl_old, hydro.materials[0]);

	//boundary condition
	Boundary_W(prtl);

	//in which cell
	prtl->cell_i = 0; prtl->cell_j = j; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(0,j).insert(particles.cell_lists(0,j).first(), &prtl);
      }
    }
		
      /// <li>the symmetry conditions 	
    if(xBl == 3) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle>* p13 = particles.cell_lists(1,j).first(); 
	   !particles.cell_lists(1,j).isEnd(p13); 
	   p13 = particles.cell_lists(1,j).next(p13)) {
				
	//the original real particle
	spParticle prtl_old = *(particles.cell_lists(1,j).retrieve(p13));
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_W(prtl);

	//in which cell
	prtl->cell_i = 0; prtl->cell_j = j; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(0,j).insert(particles.cell_lists(0,j).first(), &prtl);
      }
    }

      /// <li>the perodic conditions </ul>	
    if(xBl == 1) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p11 = particles.cell_lists(x_clls - 2,j).first(); 
	   !particles.cell_lists(x_clls - 2,j).isEnd(p11); 
	   p11 = particles.cell_lists(x_clls - 2,j).next(p11)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(x_clls - 2,j).retrieve(p11) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_W(prtl);
				
	//in which cell
	prtl->cell_i = 0; prtl->cell_j = j; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(0,j).insert(particles.cell_lists(0,j).first(), &prtl);
      }
    }

    /// <li>east side
    //clear linked list data (particles)
    particles.cell_lists(x_clls - 1,j).clear();

    /// <ul><li>the rigid wall conditions 	
    if(xBr == 0 || xBr == 2) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p20 = particles.cell_lists(x_clls - 2,j).first(); 
	   !particles.cell_lists(x_clls - 2,j).isEnd(p20); 
	   p20 = particles.cell_lists(x_clls - 2,j).next(p20)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(x_clls - 2,j).retrieve(p20) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

	//boundary condition
	Boundary_E(prtl);

	//in which cell
	prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(x_clls- 1,j).insert(particles.cell_lists(x_clls - 1,j).first(), &prtl);
      }
    }
		
    /// <li>the symmetry conditions 	
    if(xBr == 3) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p23 = particles.cell_lists(x_clls - 2,j).first(); 
	   !particles.cell_lists(x_clls - 2,j).isEnd(p23); 
	   p23 = particles.cell_lists(x_clls - 2,j).next(p23)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(x_clls - 2,j).retrieve(p23) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_E(prtl);

	//in which cell
	prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(x_clls- 1,j).insert(particles.cell_lists(x_clls - 1,j).first(), &prtl);
      }
    }

      /// <li>the perodic conditions</ul>	
    if(xBr == 1) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p21 = particles.cell_lists(1,j).first(); 
	   !particles.cell_lists(1,j).isEnd(p21); 
	   p21 = particles.cell_lists(1,j).next(p21)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(1,j).retrieve(p21) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_E(prtl);

	//in which cell
	prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(x_clls- 1,j).insert(particles.cell_lists(x_clls - 1,j).first(), &prtl);
      }
    }
  }

  //y direction

  /// <li>south side
  for(i = kb; i < mb; i++) {
    //clear cell linked list data (particles)
    particles.cell_lists(i,0).clear();

    /// <ul><li>the rigid wall conditions 	
    if(yBd == 0 || yBd == 2) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p30 = particles.cell_lists(i,1).first(); 
	   !particles.cell_lists(i,1).isEnd(p30); 
	   p30 = particles.cell_lists(i,1).next(p30)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(i,1).retrieve(p30) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

	//boundary condition
	Boundary_S(prtl);

	//in which cell
	prtl->cell_i = i; prtl->cell_j = 0; 
	//insert its poistion on the image particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(i,0).insert(particles.cell_lists(i,0).first(), &prtl);
      }
    }

    /// <li>the symmetry conditions 	
    if(yBd == 3) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p33 = particles.cell_lists(i,1).first(); 
	   !particles.cell_lists(i,1).isEnd(p33); 
	   p33 = particles.cell_lists(i,1).next(p33)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(i,1).retrieve(p33) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_S(prtl);

	//in which cell
	prtl->cell_i = i; prtl->cell_j = 0; 
	//insert its poistion on the image particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(i,0).insert(particles.cell_lists(i,0).first(), &prtl);
      }
    }

    /// <li>the perodic conditions</ul>	
    if(yBd == 1) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p31 = particles.cell_lists(i,y_clls - 2).first(); 
	   !particles.cell_lists(i,y_clls - 2).isEnd(p31); 
	   p31 = particles.cell_lists(i,y_clls - 2).next(p31)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(i,y_clls - 2).retrieve(p31) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_S(prtl);

	//in which cell
	prtl->cell_i = i; prtl->cell_j = 0; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(i,0).insert(particles.cell_lists(i,0).first(), &prtl);
      }
    }
  }

  /// <li>north side
  for(i = ku; i < mu; i++) {
    //clear the linked list data (particles)
    particles.cell_lists(i,y_clls - 1).clear();

      /// <ul><li>the rigid wall conditions 	
    if(yBu == 0 || yBu == 2) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p40 = particles.cell_lists(i,y_clls - 2).first(); 
	   !particles.cell_lists(i,y_clls - 2).isEnd(p40); 
	   p40 = particles.cell_lists(i,y_clls - 2).next(p40)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(i,y_clls - 2).retrieve(p40) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

	//boundary condition
	Boundary_N(prtl);

	//in which cell
	prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(i,y_clls- 1).insert(particles.cell_lists(i,y_clls - 1).first(), &prtl);
      }
    }
	
    /// <li>the symmetry conditions 	
    if(yBu == 3) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p43 = particles.cell_lists(i,y_clls - 2).first(); 
	   !particles.cell_lists(i,y_clls - 2).isEnd(p43); 
	   p43 = particles.cell_lists(i,y_clls - 2).next(p43)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(i,y_clls - 2).retrieve(p43) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_N(prtl);

	//in which cell
	prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(i,y_clls- 1).insert(particles.cell_lists(i,y_clls - 1).first(), &prtl);
      }
    }

    /// <li>the perodic conditions</ul></ul>	
    if(yBu == 1) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p41 = particles.cell_lists(i,1).first(); 
	   !particles.cell_lists(i,1).isEnd(p41); 
	   p41 = particles.cell_lists(i,1).next(p41)) {
					
	//the original real particle
	spParticle prtl_old = *( particles.cell_lists(i,1).retrieve(p41) );
	spParticle prtl = boost::make_shared<Particle>(prtl_old);

	//boundary condition
	Boundary_N(prtl);

	//in which cell
	prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
	//insert its poistion on the particle list
	boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
	//insert the position into corresponding cell list
	particles.cell_lists(i,y_clls- 1).insert(particles.cell_lists(i,y_clls - 1).first(), &prtl);
      }
    }
  }

    /// <li>considering the coner cells

  /// <ul><li>south-west corner
  /// <ul><li>the rigid wall conditions 	
  if(xBl == 0 && yBd == 0 || xBl == 2 && yBd == 2) {
    //clear cell linked list data (particles)
    particles.cell_lists(0,0).clear();
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p130 = particles.cell_lists(1,1).first(); 
	 !particles.cell_lists(1,1).isEnd(p130); 
	 p130 = particles.cell_lists(1,1).next(p130)) {
					
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(1,1).retrieve(p130) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_SW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = 0; 
      //insert its poistion on the image particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,0).insert(particles.cell_lists(0,0).first(), &prtl);
    }
  }

  /// <li>the symmetry conditions 	
  if(xBl == 3 && yBd == 3) {
    //clear cell linked list data (particles)
    particles.cell_lists(0,0).clear();
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p130 = particles.cell_lists(1,1).first(); 
	 !particles.cell_lists(1,1).isEnd(p130); 
	 p130 = particles.cell_lists(1,1).next(p130)) {
					
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(1,1).retrieve(p130) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = 0; 
      //insert its poistion on the image particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,0).insert(particles.cell_lists(0,0).first(), &prtl);
    }
  }
	
    /// <li> the perodic conditions </ul>	
  if(xBl == 1 && yBd == 1) {
    //clear cell linked list data (particles)
    particles.cell_lists(0,0).clear();
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p131 = particles.cell_lists(x_clls - 2,y_clls - 2).first(); 
	 !particles.cell_lists(x_clls - 2,y_clls - 2).isEnd(p131); 
	 p131 = particles.cell_lists(x_clls - 2,y_clls - 2).next(p131)) {
					
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(x_clls - 2,y_clls - 2).retrieve(p131) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = 0; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,0).insert(particles.cell_lists(0,0).first(), &prtl);
    }
  }
		
  /// <li>north-west corner

  /// <ul><li>the rigid wall conditions 	
  if(xBl == 0 && yBu == 0 || xBl == 2 && yBu == 2) {
    //clear the linked list data (particles)
    particles.cell_lists(0,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p140 = particles.cell_lists(1,y_clls - 2).first(); 
	 !particles.cell_lists(1,y_clls - 2).isEnd(p140); 
	 p140 = particles.cell_lists(1,y_clls - 2).next(p140)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(1,y_clls - 2).retrieve(p140) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_NW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,y_clls- 1).insert(particles.cell_lists(0,y_clls - 1).first(), &prtl);
    }
  }
	
  /// <li>the symmetry conditions 	
  if(xBl == 3 && yBu == 3) {
    //clear the linked list data (particles)
    particles.cell_lists(0,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p140 = particles.cell_lists(1,y_clls - 2).first(); 
	 !particles.cell_lists(1,y_clls - 2).isEnd(p140); 
	 p140 = particles.cell_lists(1,y_clls - 2).next(p140)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(1,y_clls - 2).retrieve(p140) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,y_clls- 1).insert(particles.cell_lists(0,y_clls - 1).first(), &prtl);
    }
  }

  /// <li>the perodic conditions</ul>	
  if(xBl == 1 && yBu == 1) {
    //clear the linked list data (particles)
    particles.cell_lists(0,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p141 = particles.cell_lists(x_clls - 2,1).first(); 
	 !particles.cell_lists(x_clls - 2,1).isEnd(p141); 
	 p141 = particles.cell_lists(x_clls - 2,1).next(p141)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(x_clls - 2,1).retrieve(p141) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NW(prtl);

      //in which cell
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(0,y_clls- 1).insert(particles.cell_lists(0,y_clls - 1).first(), &prtl);
    }
  }

  /// <li>north-east corner
	
  /// <ul><li>the rigid wall conditions 	
  if(xBr == 0 && yBu == 0 || xBr == 2 && yBu == 2) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,y_clls - 1).clear();
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p240 = particles.cell_lists(x_clls - 2,y_clls - 2).first(); 
	 !particles.cell_lists(x_clls - 2,y_clls - 2).isEnd(p240); 
	 p240 = particles.cell_lists(x_clls - 2,y_clls - 2).next(p240)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(x_clls - 2,y_clls - 2).retrieve(p240) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_NE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls- 1,y_clls - 1).insert(particles.cell_lists(x_clls - 1,y_clls - 1).first(), &prtl);
    }
  }
		
  /// <li>the symmetry conditions 	
  if(xBr == 3 && yBu == 3) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,y_clls - 1).clear();
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p240 = particles.cell_lists(x_clls - 2,y_clls - 2).first(); 
	 !particles.cell_lists(x_clls - 2,y_clls - 2).isEnd(p240); 
	 p240 = particles.cell_lists(x_clls - 2,y_clls - 2).next(p240)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(x_clls - 2,y_clls - 2).retrieve(p240) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls- 1,y_clls - 1).insert(particles.cell_lists(x_clls - 1,y_clls - 1).first(), &prtl);
    }
  }

  /// <li>the perodic conditions</ul>	
  if(xBr == 1 && yBu == 1) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,y_clls - 1).clear();
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p241 = particles.cell_lists(1,1).first(); 
	 !particles.cell_lists(1,1).isEnd(p241); 
	 p241 = particles.cell_lists(1,1).next(p241)) {
					
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(1,1).retrieve(p241) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_NE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls- 1,y_clls - 1).insert(particles.cell_lists(x_clls - 1,y_clls - 1).first(), &prtl);
    }
  }

  /// <li>south-east corner
	
  /// <ul> <li>the rigid wall conditions 	
  if(xBr == 0 && yBd == 0 || xBr == 2 && yBd == 2) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,0).clear();
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p230 = particles.cell_lists(x_clls - 2,1).first(); 
	 !particles.cell_lists(x_clls - 2,1).isEnd(p230); 
	 p230 = particles.cell_lists(x_clls - 2,1).next(p230)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(x_clls - 2,1).retrieve(p230) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old, hydro.materials[0]);

      //boundary condition
      Boundary_SE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0; 
      //insert its poistion on the image particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls - 1,0).insert(particles.cell_lists(x_clls - 1,0).first(), &prtl);
    }
  }

  /// <li>the symmetry conditions 	
  if(xBr == 3 && yBd == 3) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,0).clear();
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p230 = particles.cell_lists(x_clls - 2,1).first(); 
	 !particles.cell_lists(x_clls - 2,1).isEnd(p230); 
	 p230 = particles.cell_lists(x_clls - 2,1).next(p230)) {
				
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(x_clls - 2,1).retrieve(p230) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0; 
      //insert its poistion on the image particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls - 1,0).insert(particles.cell_lists(x_clls - 1,0).first(), &prtl);
    }
  }

  /// <li>the perodic conditions</ul></ul>	
  if(xBr == 1 && yBd == 1) {
    //clear the linked list data (particles)
    particles.cell_lists(x_clls - 1,0).clear();
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p231 = particles.cell_lists(1,y_clls - 2).first(); 
	 !particles.cell_lists(1,y_clls - 2).isEnd(p231); 
	 p231 = particles.cell_lists(1,y_clls - 2).next(p231)) {
					
      //the original real particle
      spParticle prtl_old = *( particles.cell_lists(1,y_clls - 2).retrieve(p231) );
      spParticle prtl = boost::make_shared<Particle>(prtl_old);

      //boundary condition
      Boundary_SE(prtl);

      //in which cell
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0; 
      //insert its poistion on the particle list
      boundary_particle_list.insert(boundary_particle_list.first(), &prtl);
      //insert the position into corresponding cell list
      particles.cell_lists(x_clls - 1,0).insert(particles.cell_lists(x_clls - 1,0).first(), &prtl);
    }
  }
}
//----------------------------------------------------------------------------------------
//							boundary condition
//----------------------------------------------------------------------------------------
void Boundary::BoundaryCondition(ParticleManager &particles)
{
  int i, j;

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
  for(j = 1; j < y_clls - 1; j++) {
	
    /// <ul> <li>west side

    /// <ul> <li>the rigid wall conditions</ul>	
    if(xBl == 0 || xBl == 2) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p1 = particles.cell_lists(0,j).first(); 
	   !particles.cell_lists(0,j).isEnd(p1); 
	   p1 = particles.cell_lists(0,j).next(p1)) {
				
	spParticle prtl = *( particles.cell_lists(0,j).retrieve(p1) );
	//copy states from the original particle
	prtl->StatesCopier(prtl->rl_prtl, 0);

	//boundary condition
	Boundary_W(prtl);
      }
    }
    /// <ul> <li>the perodic or symmetry conditions </ul>
    if(xBl == 1 || xBl == 3) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p1 = particles.cell_lists(0,j).first(); 
	   !particles.cell_lists(0,j).isEnd(p1); 
	   p1 = particles.cell_lists(0,j).next(p1)) {
				
	spParticle prtl = *( particles.cell_lists(0,j).retrieve(p1) );
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
      for (LlistNode<spParticle >* p2 = particles.cell_lists(x_clls - 1,j).first(); 
	   !particles.cell_lists(x_clls - 1,j).isEnd(p2); 
	   p2 = particles.cell_lists(x_clls - 1,j).next(p2)) {
					
	spParticle prtl = *( particles.cell_lists(x_clls - 1,j).retrieve(p2) );
	//copy states from the original particle
	prtl->StatesCopier(prtl->rl_prtl, 0);

	//boundary condition
	Boundary_E(prtl);
      }
    }
    /// <li>the perodic or symmetry conditions</ul>	
    if(xBr == 1 || xBr == 3) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p2 = particles.cell_lists(x_clls - 1,j).first(); 
	   !particles.cell_lists(x_clls - 1,j).isEnd(p2); 
	   p2 = particles.cell_lists(x_clls - 1,j).next(p2)) {
					
	spParticle prtl = *( particles.cell_lists(x_clls - 1,j).retrieve(p2) );
	//copy states from the original particle
	prtl->StatesCopier(prtl->rl_prtl, 1);

	//boundary condition
	Boundary_E(prtl);
      }
    }
  }

  //y direction
	
  /// <li>south side
  for(i = kb; i < mb; i++) {
    /// <ul><li>the rigid wall conditions	
    if(yBd == 0 || yBd == 2) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p3 = particles.cell_lists(i,0).first(); 
	   !particles.cell_lists(i,0).isEnd(p3); 
	   p3 = particles.cell_lists(i,0).next(p3)) {
					
	spParticle prtl = *( particles.cell_lists(i,0).retrieve(p3) );
	//copy states from the original particle
	prtl->StatesCopier(prtl->rl_prtl, 0);

	//boundary condition
	Boundary_S(prtl);
      }
    }
    /// <li>the perodic or symmetry conditions</ul>	
    if(yBd == 1 || yBd == 3) {
      //iterate the correspeond cell linked list
      for (LlistNode<spParticle >* p3 = particles.cell_lists(i,0).first(); 
	   !particles.cell_lists(i,0).isEnd(p3); 
	   p3 = particles.cell_lists(i,0).next(p3)) {
					
	spParticle prtl = *( particles.cell_lists(i,0).retrieve(p3) );
	//copy states from the original particle
	prtl->StatesCopier(prtl->rl_prtl, 1);

	//boundary condition
	Boundary_S(prtl);
      }
    }
  }

  /// <li>north side
  for(i = ku; i < mu; i++) {
    /// <ul><li>the rigid wall conditions	
    if(yBu == 0 || yBu == 2) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p4 = particles.cell_lists(i,y_clls - 1).first(); 
	   !particles.cell_lists(i,y_clls - 1).isEnd(p4); 
	   p4 = particles.cell_lists(i,y_clls - 1).next(p4)) {
					
	//the original real particle
	spParticle prtl = *( particles.cell_lists(i,y_clls - 1).retrieve(p4) );
	//copy states from the original particle
	prtl->StatesCopier(prtl->rl_prtl, 0);
	
	//boundary condition
	Boundary_N(prtl);
      }
    }
    /// <li>the perodic or symmetry conditions</ul></ul>	
    if(yBu == 1 || yBu == 3) {
      //iterate the correspeond cell for real and wall partilces
      for (LlistNode<spParticle >* p4 = particles.cell_lists(i,y_clls - 1).first(); 
	   !particles.cell_lists(i,y_clls - 1).isEnd(p4); 
	   p4 = particles.cell_lists(i,y_clls - 1).next(p4)) {
					
	//the original real particle
	spParticle prtl = *( particles.cell_lists(i,y_clls - 1).retrieve(p4) );
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
  if(xBl == 0 && yBd == 0 || xBl == 2 && yBd == 2) {
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p13 = particles.cell_lists(0,0).first(); 
	 !particles.cell_lists(0,0).isEnd(p13); 
	 p13 = particles.cell_lists(0,0).next(p13)) {
					
      spParticle prtl = *( particles.cell_lists(0,0).retrieve(p13) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);

      //boundary condition
      Boundary_SW(prtl);
    }
  }
  /// <li>the perodic or symmetry conditions</ul>	
  if(xBl == 1 && yBd == 1 || xBl == 3 && yBd == 3) {
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p13 = particles.cell_lists(0,0).first(); 
	 !particles.cell_lists(0,0).isEnd(p13); 
	 p13 = particles.cell_lists(0,0).next(p13)) {
					
      spParticle prtl = *( particles.cell_lists(0,0).retrieve(p13) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_SW(prtl);
    }
  }
		
  /// <li>north-west corner
  /// <ul><li>the rigid wall conditions 	
  if(xBl == 0 && yBu == 0 || xBl == 2 && yBu == 2) {
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p14 = particles.cell_lists(0,y_clls - 1).first(); 
	 !particles.cell_lists(0,y_clls - 1).isEnd(p14); 
	 p14 = particles.cell_lists(0,y_clls - 1).next(p14)) {
					
      //the original real particle
      spParticle prtl = *( particles.cell_lists(0,y_clls - 1).retrieve(p14) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);

      //boundary condition
      Boundary_NW(prtl);
    }
  }
  /// <li>the perodic or symmetry conditions</ul>	
  if(xBl == 1 && yBu == 1 || xBl == 3 && yBu == 3) {
    //iterate the correspeond cell for real and wall partilces
    for (LlistNode<spParticle >* p14 = particles.cell_lists(0,y_clls - 1).first(); 
	 !particles.cell_lists(0,y_clls - 1).isEnd(p14); 
	 p14 = particles.cell_lists(0,y_clls - 1).next(p14)) {
					
      //the original real particle
      spParticle prtl = *( particles.cell_lists(0,y_clls - 1).retrieve(p14) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_NW(prtl);
    }
  }

  /// <li>north-east corner
  /// <ul><li>the rigid wall conditions 	
  if(xBr == 0 && yBu == 0 || xBr == 2 && yBu == 2) {
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p24 = particles.cell_lists(x_clls - 1,y_clls - 1).first(); 
	 !particles.cell_lists(x_clls - 1,y_clls - 1).isEnd(p24); 
	 p24 = particles.cell_lists(x_clls - 1,y_clls - 1).next(p24)) {
				
      //the original real particle
      spParticle prtl = *( particles.cell_lists(x_clls - 1,y_clls - 1).retrieve(p24) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);

      //boundary condition
      Boundary_NE(prtl);
    }
  }
  /// <li>the perodic or symmetry conditions</ul>	
  if(xBr == 1 && yBu == 1 || xBr == 3 && yBu == 3) {
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p24 = particles.cell_lists(x_clls - 1,y_clls - 1).first(); 
	 !particles.cell_lists(x_clls - 1,y_clls - 1).isEnd(p24); 
	 p24 = particles.cell_lists(x_clls - 1,y_clls - 1).next(p24)) {
				
      //the original real particle
      spParticle prtl = *( particles.cell_lists(x_clls - 1,y_clls - 1).retrieve(p24) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_NE(prtl);
    }
  }

  /// <li>south-east corner
  /// <ul><li>the rigid wall conditions 	
  if(xBr == 0 && yBd == 0 || xBr == 2 && yBd == 2) {	
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p23 = particles.cell_lists(x_clls - 1,0).first(); 
	 !particles.cell_lists(x_clls - 1,0).isEnd(p23); 
	 p23 = particles.cell_lists(x_clls - 1,0).next(p23)) {
					
      //the original real particle
      spParticle prtl = *( particles.cell_lists(x_clls - 1,0).retrieve(p23) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 0);
	
      //boundary condition
      Boundary_SE(prtl);
    }
  }

  /// <li>the perodic or symmetry conditions</ul></ul></ul>	
  if(xBr == 1 && yBd == 1 || xBr == 3 && yBd == 3) {	
    //iterate the correspeond cell linked list
    for (LlistNode<spParticle >* p23 = particles.cell_lists(x_clls - 1,0).first(); 
	 !particles.cell_lists(x_clls - 1,0).isEnd(p23); 
	 p23 = particles.cell_lists(x_clls - 1,0).next(p23)) {
					
      //the original real particle
      spParticle prtl = *( particles.cell_lists(x_clls - 1,0).retrieve(p23) );
      //copy states from the original particle
      prtl->StatesCopier(prtl->rl_prtl, 1);

      //boundary condition
      Boundary_SE(prtl);
    }
  }
}
//----------------------------------------------------------------------------------------
//			implement west side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_W(spParticle prtl)
{
  //the rigid wall conditions	
  switch(xBl) {
    //wall
  case 0: 
    prtl->R[0] = - prtl->R[0]; 
    prtl->U = UxBl*2.0 - prtl->U;
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
//			implement east side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_E(spParticle prtl)
{
  //the rigid wall conditions	
  switch(xBr) {
    //wall
  case 0: 
    prtl->R[0] = box_size[0]*2.0 - prtl->R[0]; 
    prtl->U = UxBr*2.0 - prtl->U;
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
//			implement south side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_S(spParticle prtl)
{
  //the rigid wall conditions	
  switch(yBd) {
    //wall
  case 0: 
    prtl->R[1] = - prtl->R[1]; 
    prtl->U = UyBd*2.0 - prtl->U;
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
//			implement north side boundary by modifying particle states
//----------------------------------------------------------------------------------------
void Boundary::Boundary_N(spParticle prtl)
{
  //the rigid wall conditions	
  switch(yBu) {
    //wall
  case 0: 
    prtl->R[1] = box_size[1]*2.0 - prtl->R[1]; 
    prtl->U = UyBu*2.0 - prtl->U;
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
//			implement south-west corner boundadry by modifying particle states
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
//			implement north-west corner boundary by modifying particle states
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
//			implement north-east corner boundary by modifying particle states
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
//			implement north-east corner boundary by modifying particle states
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

