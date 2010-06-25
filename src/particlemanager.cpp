// particlemanager.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Define 2-d vectors and associated operations
//		particlemanager.cpp
//----------------------------------------------------------------------------------------
// ***** system includes *****
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

// ***** local includes *****
#include "glbcls.h"
#include "glbfunc.h"
#include "material.h"
#include "particlemanager.h"
#include "hydrodynamics.h"

using namespace std;

//----------------------------------------------------------------------------------------
//									constructor
//----------------------------------------------------------------------------------------
ParticleManager::ParticleManager(Initiation &ini)
{
  

  ///- copy properties from class Initiation
  strcpy(Project_name, ini.Project_name);
  number_of_materials = ini.number_of_materials;
  supportlength = ini.supportlength;
  supportlengthsquare = supportlength*supportlength;
  box_size = ini.box_size;
  cll_sz = ini.cell_size;
  x_clls = ini.x_cells + 2; y_clls = ini.y_cells + 2;
  initial_condition = ini.initial_condition;
  hdelta = ini.hdelta; delta = ini.delta;
  simu_mode=ini.simu_mode;
	
  if(initial_condition == 0) {
    U0 = ini.U0;
    rho0 = ini.rho0;
    p0 = ini.p0;
    T0 = ini.T0;
  }

  ParticleManager::Init();

}

ParticleManager::ParticleManager(const char Project_name_in[25], const int number_of_materials, 
				 const double supportlength, const Vec2d box_size, 
				 const double cell_size, 
				 const int x_cells, const int y_cells,
				 const int initial_condition, const int hdelta,
				 const double delta, const int simu_mode, 
				 const Vec2d U0_in, const double rho0_in, const double p0_in, 
				 const double T0_in
				 ):
  number_of_materials(number_of_materials),
  supportlength(supportlength), 
  supportlengthsquare(supportlength*supportlength),
  box_size(box_size),
  cll_sz(cell_size),
  x_clls(x_cells+2),
  y_clls(y_cells+2), 
  initial_condition(initial_condition),
  hdelta(hdelta), 
  delta(delta),
  simu_mode(simu_mode)
{
  strcpy(Project_name, Project_name_in);
  if(initial_condition == 0) {
    U0 = U0_in;
    rho0 = rho0_in;
    p0 = p0_in;
    T0 = T0_in;
  }
  ParticleManager::Init();

}



void ParticleManager::Init() {
  ///- strore the cell linked lists in a 2-d array
  cell_lists.resize(x_clls, y_clls);
  for (int i=0; i < x_clls; i++) {
    for(int j = 0; j < y_clls; j++) {
      Llist<Particle>* prtl_list = new Llist<Particle>;
      cell_lists(i, j) = *prtl_list;
    }
  }
}



//----------------------------------------------------------------------------------------
//				update the cell linked lists for real particles
//----------------------------------------------------------------------------------------
void ParticleManager::UpdateCellLinkedLists() 
{
	
  int i, j; //current cell postions
  int k, m; //possible new cell postions

  ///<ul><li>(double) loop (as indices i, j) on all cells
  for(i = 0; i < x_clls; i++) {
    for(j = 0; j < y_clls; j++) { 

      ///<ul><li>iterate this cell list
      LlistNode<Particle> *p = cell_lists(i,j).first(); 
      ///<li>if the list is empty or the node position is at the end <b>!!!Question!!! is this comment right? would it not rather be...if list NOT empty and NOT at the end </b>
      while(!cell_lists(i,j).isEnd(p)) {
	///<ul><li>check the position of the real particle
	Particle *prtl = cell_lists(i,j).retrieve(p);
	if(prtl->bd == 0) {
	  //where is the particle
	  k = int ((prtl->R[0] + cll_sz)/ cll_sz);
	  m = int ((prtl->R[1] + cll_sz)/ cll_sz);
				
	  ///<ul><li>if the partilce runs out of the current cell
	  if(k != i || m !=j) {
	    ///<ul><li>delete the current node
	    cell_lists(i,j).remove(p);
	   
	    ///<li>insert it to the new cell linked list</ul></ul></ul></ul>
	    if(prtl->R[0]>=0.0 &&prtl->R[0]<=2.0)
	      cell_lists(k,m).insert(cell_lists(k,m).first(), prtl);
	  } else p = cell_lists(i,j).next(p);
	} else p = cell_lists(i,j).next(p);
      }

    }
  }
}
//----------------------------------------------------------------------------------------
//						do NNP search and build the NNP list
//----------------------------------------------------------------------------------------
void ParticleManager::BuildNNP(Vec2d &point)
{

  ///<ul><li>clear the list first
  NNP_list.clear_data();

  //where is the point
  const int k = int ((point[0] + cll_sz)/ cll_sz);
  const int m = int ((point[1] + cll_sz)/ cll_sz);


  // if ( point[0]>=0.0 && point[0]<=2.0)//this if- condition has been added for the 1D shock case (as there are no boundary conditions and particles who left the domains should not be considered any more) 

  {
    ///<li>loop on this and all surrounding cells
    for(int i = k - 1; i <= k + 1; i++) {
      for(int j = m - 1; j <= m + 1; j++) { 
	if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	  ///<ul><li>iterate this cell list
	  for (LlistNode<Particle> *p = cell_lists(i,j).first(); 
	       !cell_lists(i,j).isEnd(p); 
	       p = cell_lists(i,j).next(p)) {

	    ///<ul><li>check the position of the particle
	    ///and (if particle is NNP) insert the nearest particle to the list
	    Particle *prtl = cell_lists(i,j).retrieve(p);
	    const double dstc = v_distance(point, prtl->R);
	    if(dstc < supportlength) {///<li>(line 137)<b>Question: WHY SMOOTHINGLENGTH AND NOT SUPPORT LENGT???</b>
	      NNP_list.insert(NNP_list.first(), prtl);
	    }
	  }
	}
      }
    }
  }
}
//----------------------------------------------------------------------------------------
//				do NNP search and biuld the NNP list for MLS Mapping
//----------------------------------------------------------------------------------------
void ParticleManager::BuildNNP_MLSMapping(Vec2d &point)
{
  int i, j; //current cell postions
  int k, m; //possible new cell postions
  double dstc; //distance


  //where is the point
  k = int ((point[0] + cll_sz)/ cll_sz);
  m = int ((point[1] + cll_sz)/ cll_sz);
  // if ( point[0]>=0 && point[0]<=2)
  ///<ul><li>loop on this and all surrounding cells
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) { 
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	///<ul><li>iterate this cell list
	for (LlistNode<Particle> *p = cell_lists(i,j).first(); 
	     !cell_lists(i,j).isEnd(p); 
	     p = cell_lists(i,j).next(p)) {

	  ///<ul><li>check the position of the real particle
	  ///and (if particle is NNP) insert it to the list
	  Particle *prtl = cell_lists(i,j).retrieve(p);
	  dstc = v_distance(point, prtl->R);
	  //only real particles included
	  if(dstc < supportlength && prtl->bd == 0) {
	    NNP_list.insert(NNP_list.first(), prtl);
	  }
	}
      }
    }
  }
}
//----------------------------------------------------------------------------------------
//					build the interaction (particle pair) list
//----------------------------------------------------------------------------------------
void ParticleManager::BuildInteraction(Llist<Interaction> &interactions, Llist<Particle> &particle_list, 
				       Force **forces, Kernel &weight_function)
{
  cout<<"\n Am in build interaction \n";
  LlistNode<Interaction> *current = interactions.first();
  bool used_up_old = interactions.isEnd(current);
  LlistNode<Interaction> *first_unused;
  int old_length = interactions.length();

  {
    int i, j, k, m;
    double dstc; //distance
	
    //clear the list first
    //interactions.clear_data();

    int current_used = 0;


    cout<<"\n Am in build interaction control point 2 \n";
    ///<ul><li>iterate particles on the particle list
    for (LlistNode<Particle> *p = particle_list.first(); 
	 !particle_list.isEnd(p); 
	 p = particle_list.next(p)) {
					
      /// <ul><li> choose origin particle 
      Particle *prtl_org = particle_list.retrieve(p);

      if(prtl_org->bd == 0 && prtl_org->R[0]>=0 && prtl_org->R[0]<=2)//the second and the third condition have been added for the 1D shock case (as there are no boundary conditions and particles who left the domains should not be considered any more) 
	{
		
	  ///<li>find out where(in which cell) the particle is
	  i = int ((prtl_org->R[0] + cll_sz)/ cll_sz);
	  j = int ((prtl_org->R[1] + cll_sz)/ cll_sz);

	  ///<li>loop on this and all surrounding cells
	  for(k = i - 1; k <= i + 1; k++) 
	    for(m = j - 1; m <= j + 1; m++) { 
	      ///<ul><li>iterate this cell list
	      for (LlistNode<Particle> *p1 = cell_lists(k,m).first(); 
		   !cell_lists(k,m).isEnd(p1); 
		   p1 = cell_lists(k,m).next(p1)) {

		// destination particle
		Particle *prtl_dest = cell_lists(k,m).retrieve(p1);
		
		///<ul><li>calculate distance between particle in question and destination particle (which is iterated)and if interaction takes place: add pair to inetraction list (<b>question: why is dst compared to h^2 and not support length to determine if there is interaction or not??</b>
		dstc = v_sq(prtl_org->R - prtl_dest->R);
		if(dstc <= supportlengthsquare && prtl_org->ID >= prtl_dest->ID) {
		  //	cout<<"\n distances for BuildInteractions positif:"<<dstc<<"\n";
		  if(current_used == old_length) {
		    Interaction *pair = new Interaction(prtl_org, prtl_dest, forces, weight_function, sqrt(dstc));
		    {interactions.insert(current, pair);}
		  }
		  else {
		    interactions.retrieve(current)->NewInteraction(prtl_org, prtl_dest, forces, weight_function, sqrt(dstc));
		    current = interactions.next(current);
		    current_used++;
		  }
		}
	      }
	    }
	}
    }
    if (current_used == old_length)
      used_up_old = true;
    else
      first_unused = current;
  }
  if (!used_up_old) {
    while (!interactions.isEnd(first_unused)) { delete interactions.retrieve(first_unused); interactions.remove(first_unused); }
  }
  //control output
  cout<<"\n   build interaction (within build pair) done \n";
  ofstream txtFile("BuddiesDataN1");
  if (txtFile.is_open())
    {

      for (LlistNode<Interaction> *p = interactions.first(); 
	   !interactions.isEnd(p); 
	   p = interactions.next(p))
	{
	  Interaction *inte=interactions.retrieve (p);

	  txtFile <<setprecision (3)<< ::setw( 7 )<<inte->getOrigin()->ID<<::setw( 7 )<<inte->getDest()->ID<<::setw(17 )<<inte->getWij()<<"  "<<inte->getGradWij()[0]<<endl;
	}

      txtFile.close();
    }

}
//----------------------------------------------------------------------------------------
//					build the initial particles and the linked lists
//----------------------------------------------------------------------------------------
void ParticleManager::BuildRealParticles(
					 blast::vector<Material> materials, 
					 Llist<Particle>& particle_list, 
					 Initiation &ini)
{
	
  Vec2d position, velocity;
  double density, pressure, Temperature;
  int material_no;

  ///initial particles either from .cfg file or from .rst file or from .ivs (Initial Values Shock tube)file
  if(ini.simu_mode==1)//for liquids
    {
      //initialize particles from the file .cfg
      if(initial_condition==0) {	
	//initialize the real particles inside the boundary
	for(int i = 1; i < x_clls - 1; i++) {
	  for(int j = 1; j < y_clls - 1; j++) {
	    cout<<"Build initial particles within domain with .cfg data";
	    //creat a new real particle
	    for(int k = 0; k < hdelta; k++) {
	      for(int m = 0; m < hdelta; m++) {

		position[0] = (i - 1)*cll_sz + (k + 0.5)*delta;
		position[1] = (j - 1)*cll_sz + (m + 0.5)*delta;

		material_no = 1;
		velocity = U0;
		Temperature = T0;
		density = materials[material_no].rho0;
		pressure = materials[material_no].get_p(density);
						
		Vec2d c_cntr;
		c_cntr[0] = 4.0; c_cntr[1] = 4.0;
		if(v_abs(position - c_cntr) <= 1.0) {
		  //						if(position[1] < 0.2 && position[0] < 0.2) {
		  material_no = 2;
		  pressure += p0;
		  density = materials[material_no].get_rho(pressure);
		}

		//creat a new real particle
		Particle *prtl = new Particle( position, velocity, density, pressure, Temperature, 
					       materials[material_no]);
	    
		prtl->cell_i = i; prtl->cell_j = j; 
						
		//insert its poistion on the particle list
		particle_list.insert(particle_list.first(), prtl);

		//insert the position into corresponding cell list
		std::cerr << "i = " << i << '\n';
		std::cerr << "j = " << j << '\n';
		cell_lists(i,j).insert(cell_lists(i,j).first(), prtl);

	      }
	    }
	  }
	}
      }
	
      //initialize real particles from the non-dimensional restart file .rst
      if(initial_condition==1) {	

	int n, N;
	char inputfile[25];
	char material_name[25];
		
	//the restart file name
	strcpy(inputfile, Project_name);
	strcat(inputfile, ".rst");
	
	//check if the restart exist
	ifstream fin(inputfile, ios::in);
	if (!fin) {
	  cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
	  std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	  exit(1);
	}
	else cout<<"Initialtion: Read real particle data from "<< inputfile <<" \n"; 

	//reading the new starting time
	fin>>ini.Start_time;
	//change the starting and ending time
	ini.End_time += ini.Start_time;
	//read the real particle number
	fin>>N;

	//read the particle data
	for(n = 0; n < N; n++) { 
			
	  fin>>material_name>>position[0]>>position[1]>>velocity[0]>>velocity[1]
	     >>density>>pressure>>Temperature;
			
	  //find the right material number
	  material_no = -1;
	  for(int k = 0;  k <= number_of_materials; k++) 
	    if(strcmp(material_name, materials[k].material_name) == 0) material_no = k;
	  if(material_no != -1) {	
					
	    pressure = materials[material_no].get_p(density);
	    Particle *prtl = new Particle( position, velocity, density, pressure, Temperature, 
					   materials[material_no]);
	    //insert its poistion on the particle list
	    particle_list.insert(particle_list.first(), prtl);
					
	    //where is the particle
	    const int  i = int (prtl->R[0] / cll_sz) + 1;
	    const int j = int (prtl->R[1] / cll_sz) + 1;
					
	    prtl->cell_i = i; prtl->cell_j = j; 
	    //insert the position into corresponding cell list
	    cell_lists(i,j).insert(cell_lists(i,j).first(), prtl);

	  } else {
	    cout<<"The material in the restart file is not used by the program! \n";
	    std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	    exit(1);
	  }
	}
	fin.close();
	cout<<"Initialtion of Read real particle data from "<< inputfile <<"done! \n"; 
      }
    }
  if(ini.simu_mode==2)//gas dynamics
    {
      char inputfile[]="../cases/1Dshock.ivs";
      int material_no = 1; //number for Air (second line in cfg file (->index 1)
      //check if the .ivs file exists
      ifstream fin(inputfile, ios::in);
      if (!fin) {
	cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
	std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	exit(1);
      }
      else cout<<"Initialtion: Read real particle data from "<< inputfile <<" \n"; 
      //read the real particle number
      int N;
      fin>>N;
      //read the particle data
      for(int n = 0; n < N; n++)
	{ 
			
	  fin>>position[0]>>position[1]>>velocity[0]>>velocity[1]
	     >>density>>pressure;
	  Temperature=materials[material_no].get_T(pressure,density);
	  Particle *prtl = new Particle( position, velocity, density, pressure, Temperature, 
					 materials[material_no]);
	  //insert its poistion on the particle list
	  particle_list.insert(particle_list.first(), prtl);
					
	  //where is the particle
	  const int i = int (prtl->R[0] / cll_sz)+1;//I had to remove the "+1" because there is no boundary particle cells
	  const int j = int (prtl->R[1] / cll_sz)+1;//but works better with it!!!???!!!
					
	  prtl->cell_i = i; prtl->cell_j = j; 
	  //insert the position into corresponding cell list
	  std::cerr << "i = " << i << '\n';
	  std::cerr << "i = " << i << '\n';
	  cell_lists(i,j).insert(cell_lists(i,j).first(), prtl);
	  std::cerr << "after insert\n";
	};
      fin.close();
      std::cerr << "after fin.close()\n";
    }

}
//----------------------------------------------------------------------------------------
//				buid the initial wall particles and the linked lists
//----------------------------------------------------------------------------------------
void ParticleManager::BuildWallParticles(Hydrodynamics &hydro, Boundary &boundary)
{
  int i, j, k, m;

  ///left hand border (corresponds to the first column)
  if(boundary.xBl == 0) {

    ///<ul><li>iterate over the first colums of all cells that constitute this boundary
    for(j = 1; j < y_clls - 1; j++) {
      ///<ul><li>create a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Particle *prtl = new Particle( -1*cll_sz + (k + 0.5)*delta, (j - 1)*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, cll_sz - (k + 0.5)*delta, 1.0, 0.0, hydro.materials[0]);

	  prtl->cell_i = 0; prtl->cell_j = j; 
	  ///<li>insert its position on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(0,j).insert(cell_lists(0,j).first(), prtl);

	}
    }
  }
	
  /// right hand border(corresponds to the last column)
  if(boundary.xBr == 0) {

    ///<ul><li>iterate over the last colums of all cells that constitute this boundary
    for(j = 1; j < y_clls - 1; j++) {
      ///<ul><li>create a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Particle *prtl = new Particle( (x_clls - 2)*cll_sz + (k + 0.5)*delta, (j - 1)*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, (k + 0.5)*delta, 1.0, 0.0, hydro.materials[0]);

	  prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(x_clls - 1,j).insert(cell_lists(x_clls - 1,j).first(), prtl);

	}
    }
  }

  ///lower border(corresponds to the lowest row)
  if(boundary.yBd == 0) {

    ///<ul><li>iterate over the lowest row of all cells that constitute this boundary
    for(i = 1; i < x_clls - 1; i++) {
      ///<ul><li>creat a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Particle *prtl = new Particle( (i - 1)*cll_sz + (k + 0.5)*delta, -1*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, cll_sz - (m + 0.5)*delta, 0.0, 1.0, hydro.materials[0]);

	  prtl->cell_i = i; prtl->cell_j = 0; 
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(i,0).insert(cell_lists(i,0).first(), prtl);

	}
    }
  }

  ///upper border (corresponds to the last row)
  if(boundary.yBu == 0) {

    ///<ul><li>iterate over the last rows of all cells that constitute this boundary
    for(i = 1; i < x_clls - 1; i++) {
      ///<ul><li>create a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Particle *prtl = new Particle( (i - 1)*cll_sz + (k + 0.5)*delta, (y_clls - 2)*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, (m + 0.5)*delta, 0.0, 1.0, hydro.materials[0]);

	  prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists(i,y_clls - 1).insert(cell_lists(i,y_clls - 1).first(), prtl);

	}
    }
  }
}

