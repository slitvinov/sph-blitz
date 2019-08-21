#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "vec2d.h"
#include "glbfunc.h"

#include "initiation.h"
#include "dllist.h"
#include "particle.h"
#include "interaction.h"
#include "hydrodynamics.h"
#include "material.h"
#include "boundary.h"
#include "particlemanager.h"

using namespace std;
enum {X, Y};

//----------------------------------------------------------------------------------------
//									constructor
//----------------------------------------------------------------------------------------
ParticleManager::ParticleManager(Initiation &ini)
{

  int i;

  ///- copy properties from class Initiation
  strcpy(Project_name, ini.Project_name);
  number_of_materials = ini.number_of_materials;
  smoothinglength = ini.smoothinglength;
  smoothinglengthsquare = smoothinglength*smoothinglength;
  box_size[X] = ini.box_size[X];
  box_size[Y] = ini.box_size[Y];
  cll_sz = ini.cell_size;
  x_clls = ini.x_cells + 2; y_clls = ini.y_cells + 2;
  initial_condition = ini.initial_condition;
  hdelta = ini.hdelta; delta = ini.delta;

  if(initial_condition == 0) {
    U0[X] = ini.U0[X];
    U0[Y] = ini.U0[Y];
    rho0 = ini.rho0;
    p0 = ini.p0;
    T0 = ini.T0;
  }

  ///- strore the cell linked lists in a 2-d array
  cell_lists = new Llist<Particle>*[x_clls];
  for(i = 0; i < x_clls; i++) cell_lists[i] = new Llist<Particle>[y_clls];

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
      LlistNode<Particle> *p = cell_lists[i][j].first();
      ///<li>if the list is empty or the node position is at the end <b>!!!Question!!! is this comment right? would it not rather be...if list NOT empty and NOT at the end </b>
      while(!cell_lists[i][j].isEnd(p)) {
	///<ul><li>check the position of the real particle
	Particle *prtl = cell_lists[i][j].retrieve(p);
	if(prtl->bd == 0) {
	  //where is the particle
	  k = int ((prtl->R[0] + cll_sz)/ cll_sz);
	  m = int ((prtl->R[1] + cll_sz)/ cll_sz);

	  ///<ul><li>if the partilce runs out of the current cell
	  if(k != i || m !=j) {
	    ///<ul><li>delete the current node
	    cell_lists[i][j].remove(p);
	    ///<li>insert it to the new cell linked list</ul></ul></ul></ul>
	    cell_lists[k][m].insert(cell_lists[k][m].first(), prtl);
	  } else p = cell_lists[i][j].next(p);
	} else p = cell_lists[i][j].next(p);
      }

    }
  }
}
//----------------------------------------------------------------------------------------
//						do NNP search and build the NNP list
//----------------------------------------------------------------------------------------
void ParticleManager::BuildNNP(Vec2d &point)
{
  int i, j; //current cell postions
  int k, m; //possible new cell postions
  double dstc; //distance

  ///<ul><li>clear the list first
  NNP_list.clear_data();

  //where is the point
  k = int ((point[0] + cll_sz)/ cll_sz);
  m = int ((point[1] + cll_sz)/ cll_sz);

  ///<li>loop on this and all surrounding cells
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) {
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	///<ul><li>iterate this cell list
	for (LlistNode<Particle> *p = cell_lists[i][j].first();
	     !cell_lists[i][j].isEnd(p);
	     p = cell_lists[i][j].next(p)) {

	  ///<ul><li>check the position of the particle
	  ///and (if particle is NNP) insert the nearest particle to the list
	  Particle *prtl = cell_lists[i][j].retrieve(p);
	  dstc = v_distance(point, prtl->R);
	  if(dstc < smoothinglength) {///<li>(line 137)<b>Question: WHY SMOOTHINGLENGTH AND NOT SUPPORT LENGT???</b>
	    NNP_list.insert(NNP_list.first(), prtl);
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

  ///<ul><li>loop on this and all surrounding cells
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) {
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	///<ul><li>iterate this cell list
	for (LlistNode<Particle> *p = cell_lists[i][j].first();
	     !cell_lists[i][j].isEnd(p);
	     p = cell_lists[i][j].next(p)) {

	  ///<ul><li>check the position of the real particle
	  ///and (if particle is NNP) insert it to the list
	  Particle *prtl = cell_lists[i][j].retrieve(p);
	  dstc = v_distance(point, prtl->R);
	  //only real particles included
	  if(dstc < smoothinglength && prtl->bd == 0) {
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
				       Force **forces, QuinticSpline &weight_function)
{
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

    ///<ul><li>iterate particles on the particle list
    for (LlistNode<Particle> *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {

      /// <ul><li> choose origin particle
      Particle *prtl_org = particle_list.retrieve(p);

      if(prtl_org->bd == 0) {

	///<li>find out where(in which cell) the particle is
	i = int ((prtl_org->R[0] + cll_sz)/ cll_sz);
	j = int ((prtl_org->R[1] + cll_sz)/ cll_sz);

	///<li>loop on this and all surrounding cells
	for(k = i - 1; k <= i + 1; k++)
	  for(m = j - 1; m <= j + 1; m++) {
	    ///<ul><li>iterate this cell list
	    for (LlistNode<Particle> *p1 = cell_lists[k][m].first();
		 !cell_lists[k][m].isEnd(p1);
		 p1 = cell_lists[k][m].next(p1)) {

	      // destination particle
	      Particle *prtl_dest = cell_lists[k][m].retrieve(p1);

	      ///<ul><li>calculate distance between particle in question and destination particle (which is iterated)and if interaction takes place: add pair to inetraction list (<b>question: why is dst compared to h^2 and not support length to determine if there is interaction or not??</b>
	      dstc = v_sq(prtl_org->R - prtl_dest->R);
	      if(dstc <= smoothinglengthsquare && prtl_org->ID >= prtl_dest->ID) {
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
}
//----------------------------------------------------------------------------------------
//					build the initial particles and the linked lists
//----------------------------------------------------------------------------------------
void ParticleManager::BuildRealParticles(Hydrodynamics &hydro, Initiation &ini)
{

  int i, j, k, m;
  Vec2d position;
  double velocity[2];
  double density, pressure, Temperature;
  int material_no;

  ///initial particles either from .cfg file or from .rst file

  //initialize particles from the file .cfg
  if(initial_condition==0) {
    //initialize the real particles inside the boundary
    for(i = 1; i < x_clls - 1; i++) {
      for(j = 1; j < y_clls - 1; j++) {

	//creat a new real particle
	for(k = 0; k < hdelta; k++) {
	  for(m = 0; m < hdelta; m++) {

	    position[0] = (i - 1)*cll_sz + (k + 0.5)*delta;
	    position[1] = (j - 1)*cll_sz + (m + 0.5)*delta;

	    material_no = 1;
	    
	    velocity[X] = U0[X];
	    velocity[Y] = U0[Y];
	    
	    Temperature = T0;
	    density = hydro.materials[material_no].rho0;
	    pressure = hydro.materials[material_no].get_p(density);

	    //creat a new real particle
	    Particle *prtl = new Particle( position, velocity, density, pressure, Temperature,
					   hydro.materials[material_no]);

	    prtl->cell_i = i; prtl->cell_j = j;

	    //insert its poistion on the particle list
	    hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	    //insert the position into corresponding cell list
	    cell_lists[i][j].insert(cell_lists[i][j].first(), prtl);

	  }
	}
      }
    }
  }

  //initialize real particles from the non-dimensional restart file .rst
  if(initial_condition==1) {

    int n, N;
    char inputfile[FILENAME_MAX];
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
      for(k = 0;  k <= number_of_materials; k++)
	if(strcmp(material_name, hydro.materials[k].material_name) == 0) material_no = k;
      if(material_no != -1) {

	pressure = hydro.materials[material_no].get_p(density);
	Particle *prtl = new Particle( position, velocity, density, pressure, Temperature,
				       hydro.materials[material_no]);
	//insert its poistion on the particle list
	hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	//where is the particle
	i = int (prtl->R[0] / cll_sz) + 1;
	j = int (prtl->R[1] / cll_sz) + 1;

	prtl->cell_i = i; prtl->cell_j = j;
	//insert the position into corresponding cell list
	cell_lists[i][j].insert(cell_lists[i][j].first(), prtl);

      } else {
	cout<<"The material in the restart file is not used by the program! \n";
	std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	exit(1);
      }
    }
    fin.close();
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
					 0.0, 0.0, cll_sz - (k + 0.5)*delta, hydro.materials[0]);

	  prtl->cell_i = 0; prtl->cell_j = j;
	  ///<li>insert its position on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists[0][j].insert(cell_lists[0][j].first(), prtl);

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
					 0.0, 0.0, (k + 0.5)*delta, hydro.materials[0]);

	  prtl->cell_i = x_clls - 1; prtl->cell_j = j;
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists[x_clls - 1][j].insert(cell_lists[x_clls - 1][j].first(), prtl);

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
					 0.0, 0.0, cll_sz - (m + 0.5)*delta, hydro.materials[0]);

	  prtl->cell_i = i; prtl->cell_j = 0;
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists[i][0].insert(cell_lists[i][0].first(), prtl);

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
					 0.0, 0.0, (m + 0.5)*delta, hydro.materials[0]);

	  prtl->cell_i = i; prtl->cell_j = y_clls - 1;
	  ///<li>insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);

	  ///<li>insert the position into corresponding cell list</ul></ul>
	  cell_lists[i][y_clls - 1].insert(cell_lists[i][y_clls - 1].first(), prtl);

	}
    }
  }
}
