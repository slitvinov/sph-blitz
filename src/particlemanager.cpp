#define NOMULTIPHASE 
// particlemanager.cpp
// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//// particle.cpp
/// author: Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
//----------------------------------------------------------------------------------------
//      Define 2-d vectors and associated operations
//		particlemanager.cpp
//----------------------------------------------------------------------------------------
// ***** system includes *****
//#include <iostream>
#include <fstream>
//#include <string>

//#include <cstdio>
//#include <cstdlib>
//#include <cmath>

// ***** local includes *****
#include "particlemanager.h"
#include "initiation.h"
#include "particle.h"
#include "polymerparticle.h"
#include "glbfunc.h"
#include "interaction.h"
#include "polymerinteraction.h"
#include "hydrodynamics.h"
#include "material.h"
#include "interactionstate.h"
#include "boundary.h"
#include "abspolymercreator.h"
#include "input.h"

using namespace std;

//----------------------------------------------------------------------------------------
//									constructor
//----------------------------------------------------------------------------------------
ParticleManager::ParticleManager()
{
}
//----------------------------------------------------------------------------------------
//									constructor
//----------------------------------------------------------------------------------------
ParticleManager::ParticleManager(const Initiation* ini):
  x_clls(ini->x_cells+2),
  y_clls(ini->y_cells+2),
  box_size(ini->box_size),
  smoothinglength(ini->smoothinglength),
  hdelta(ini->hdelta),
  delta(ini->delta),
  cll_sz(ini->cell_size),
  cell_lists(blitz::Array <Llist<Node>, 2> (x_clls, y_clls))
  
{
  
  int i;  
  //copy properties from class Initiation
  strcpy(Project_name, ini->Project_name);
  number_of_materials = ini->number_of_materials;
  //  smoothinglength = ini->smoothinglength;
  smoothinglengthsquare = smoothinglength*smoothinglength;
  //  box_size = ini->box_size;
  cll_sz = ini->cell_size;
  //  x_clls = ini->x_cells + 2; y_clls = ini->y_cells + 2;
  initial_condition = ini->initial_condition;
  hdelta = ini->hdelta; delta = ini->delta;
  
  if(initial_condition == 0) {
    U0 = ini->U0;
    rho0 = ini->rho0;
    p0 = ini->p0;
    T0 = ini->T0;
  }
  
  //strore the cell linked lists in a 2-d array

  
  
  //  cell_lists = new Llist<Node>*[x_clls];
  //  for(i = 0; i < x_clls; i++) cell_lists(i, = new Llist<Node>[y_clls);
  
}
//----------------------------------------------------------------------------------------
//								constructor
//----------------------------------------------------------------------------------------
ParticleManager::ParticleManager(double cell_size, int x_cells, int y_cells)
{
  
  cll_sz = cell_size;
  x_clls = x_cells + 2; y_clls = y_cells + 2;
  
}

///destructor 
ParticleManager::~ParticleManager() {
}

//----------------------------------------------------------------------------------------
//				update the cell linked lists for real particles
//----------------------------------------------------------------------------------------
void ParticleManager::UpdateCellLinkedLists() 
{
  
  int i, j; //current cell postions
  int k, m; //possible new cell postions
  
  //loop on all cells
  for(i = 0; i < x_clls; i++) {
    for(j = 0; j < y_clls; j++) {       
      //iterate this cell list
      LlistNode<Node> *p = cell_lists(i, j).first(); 
      //if the list is empty or the node pisition is at the end
      while(!cell_lists(i, j).isEnd(p)) {
	//check the position of the real particle
	Node *prtl = cell_lists(i, j).retrieve(p);
	if(prtl->getbd() == 0) {
	  //where is the particle
	  k = int ((prtl->R()[0] + cll_sz)/ cll_sz);
	  m = int ((prtl->R()[1] + cll_sz)/ cll_sz);
	  
	  //if the partilce run out of the current cell
	  if(k != i || m !=j) {
	    //delete the current node
	    cell_lists(i, j).remove(p);
	    //insert it to the new cell linked list
	    cell_lists(k, m).insert(cell_lists(k, m).first(), prtl);
	  } else p = cell_lists(i, j).next(p);
	} else p = cell_lists(i, j).next(p);
      }
      
    }
  }
}
//----------------------------------------------------------------------------------------
//						do NNP search and biuld the NNP list
//----------------------------------------------------------------------------------------
void ParticleManager::BuildNNP(Vec2d &point)
{
  int i, j; //current cell postions
  int k, m; //possible new cell postions
  double dstc; //distance
  
  //clear the list first
  NNP_list.clear_data();
  
  //where is the point
  k = int ((point[0] + cll_sz)/ cll_sz);
  m = int ((point[1] + cll_sz)/ cll_sz);
  
  //loop on this and all surrounding cells
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) { 
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	//iterate this cell list
	for (LlistNode<Node> *p = cell_lists(i, j).first(); 
	     !cell_lists(i, j).isEnd(p); 
	     p = cell_lists(i, j).next(p)) {
	  
	  //check the position of the particle
	  //and insert the nearest particle to the list
	  Node *prtl = cell_lists(i, j).retrieve(p);
	  dstc = v_distance(point, prtl->R());
	  if(dstc < smoothinglength) {
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
  
  //loop on this and all surrounding cells
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) { 
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	//iterate this cell list
	for (LlistNode<Node> *p = cell_lists(i, j).first(); 
	     !cell_lists(i, j).isEnd(p); 
	     p = cell_lists(i, j).next(p)) {
	  
	  //check the position of the real particle
	  //and insert the nearest particle to the list
	  Node *prtl = cell_lists(i, j).retrieve(p);
	  dstc = v_distance(point, prtl->R());
	  //only real particles included
	  if(dstc < smoothinglength && prtl->getbd() == 0) {
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
void ParticleManager::BuildInteraction(Llist<InteractionState> &interactions, 
				       const Llist<Node> &particle_list, 
				       Force **forces, 
				       QuinticSpline &weight_function)
{
  LlistNode<InteractionState> *current = interactions.first();
  bool used_up_old = interactions.isEnd(current);
  LlistNode<InteractionState> *first_unused;
  int old_length = interactions.length();
  
  {
    int i, j, k, m;
    double dstc; //distance
#ifdef DEBUG
    Initiation* const ini = Initiation::Instance();
#endif
    
    //clear the list first
    //interactions.clear_data();
    
    int current_used = 0;
    
    //iterate particles on the particle list
    for (LlistNode<Node> *p = particle_list.first(); 
	 !particle_list.isEnd(p); 
	 p = particle_list.next(p)) {
      
      //origin particle
      Node *prtl_org = particle_list.retrieve(p);
      if(prtl_org->getbd() == 0) {
#ifdef DEBUG
	unsigned long nLocalInt(0);	
#endif
	//where is the particle
	i = int ((prtl_org->R()[0] + cll_sz)/ cll_sz);
	j = int ((prtl_org->R()[1] + cll_sz)/ cll_sz);
	
	//loop on this and all surrounding cells
	for(k = i - 1; k <= i + 1; k++) 
	  for(m = j - 1; m <= j + 1; m++) { 
	    //iterate this cell list
	    for (LlistNode<Node> *p1 = cell_lists(k, m).first(); 
		 !cell_lists(k, m).isEnd(p1); 
		 p1 = cell_lists(k, m).next(p1)) {	      
	      //destination particle
	      Node *prtl_dest = cell_lists(k, m).retrieve(p1);	      
	      //calculate distance
	      dstc = v_sq(prtl_org->R() - prtl_dest->R());
	      if(dstc <= smoothinglengthsquare && prtl_org->getParticleID() >= prtl_dest->getParticleID()) {
#ifdef DEBUG
		nLocalInt++;
#endif
		if(current_used == old_length) {
		  ///create interaction
		  InteractionState *pair = 
		    new InteractionState(prtl_org->createInteractionWith(prtl_dest,
									 forces,
									 weight_function,
									 sqrt(dstc))); 
		    interactions.insert(current, pair);
		}
		else {
		  interactions.retrieve(current)->ChangeState(prtl_org->createInteractionWith(prtl_dest,
											      forces,
											      weight_function,
											      sqrt(dstc))); 
		  current = interactions.next(current);
		  current_used++;
		}
	      }
	    }
	  }
#ifdef DEBUG
	if (ini->diagnose==3) {
	  cerr << "The number of interaction for particle = " << nLocalInt << endl;
	}	

#endif
      }
    }
    if (current_used == old_length)
      used_up_old = true;
    else
      first_unused = current;
  }
  if (!used_up_old) {
    while (!interactions.isEnd(first_unused)) {
      delete interactions.retrieve(first_unused); 
      interactions.remove(first_unused); 
    }
  }
}

//----------------------------------------------------------------------------------------
//					buid the initial particles and the linked lists
//----------------------------------------------------------------------------------------
void ParticleManager::BuildRealParticles(Hydrodynamics &hydro, 
					 Initiation* ini)
{
  
  int i, j, k, m;
  Vec2d position, velocity;
  double density, pressure, Temperature;
  int material_no;
  
  //initialize particles from the file .cfg
  if(initial_condition==0) {	
    //initialize the real particles inside the boundary
    int nparticle=0;
    for(i = 1; i < x_clls - 1; i++) {
      for(j = 1; j < y_clls - 1; j++) {	
	//creat a new real particle
	for(k = 0; k < hdelta; k++) {
	  for(m = 0; m < hdelta; m++) {	    
	    position[0] = (i - 1)*cll_sz + (k + 0.5)*delta;
	    position[1] = (j - 1)*cll_sz + (m + 0.5)*delta;	    
	    material_no = 1;
	    velocity = U0;
	    Temperature = T0;
	    density = hydro.materials[material_no].rho0;
	    pressure = hydro.materials[material_no].get_p(density);
	    Vec2d c_cntr;
	    c_cntr[0] = 4.0; c_cntr[1] = 4.0;
	    if(v_abs(position - c_cntr) <= 1.0) {
#ifdef NOMULTIPHASE
	      pressure += 0.0;
	      material_no = 1;
#else 
	      material_no = 2;
	      pressure += p0;
#endif
	      density = hydro.materials[material_no].get_rho(pressure);
	    }	    
	    //creat a new real particle
	    nparticle++;
	    //cout << nparticle << endl;
	    //	    Node* prtl;	    
	    //	    cout << "New Particle" << '\n';
	    Node* prtl(new Node(new Particle(position, velocity, 
					     density, pressure, 
					     Temperature, 
					     hydro.materials[material_no])));
	    //	    prtl->setCellPosition(i, j);	    
	    //insert its poistion on the particle list
	    hydro.particle_list.insert(hydro.particle_list.first(), prtl);	    
	    //insert the position into corresponding cell list
	    cell_lists(i, j).insert(cell_lists(i, j).first(), prtl); 
	  }
	}
      }
    }
        ini->getPolymerCreator()->CreatePolymer(*this);
  }
  ///call polymer creator
  //
  ///read particles data from restart file
  if(initial_condition==1) {	    
    
    string fname  = ini->output_dir +  "/par.nc";
    Input inp(fname, 
	      &hydro.materials[1]);
	      
    ini->Start_time = inp.getTime();
    ini->End_time += ini->Start_time;
    while (!inp.isEnd()) {
      Node *prtl = new Node(inp.Next());
      hydro.particle_list.insert(hydro.particle_list.first(), prtl);
      i = int (prtl->R()[0] / cll_sz) + 1;
      j = int (prtl->R()[1] / cll_sz) + 1;
      //      prtl->setCellPosition(i, j);
      cell_lists(i, j).insert(cell_lists(i, j).first(), prtl);    
    }
  }	
}

//----------------------------------------------------------------------------------------
//				buid the initial wall particles and the linked lists
//----------------------------------------------------------------------------------------
void ParticleManager::BuildWallParticles(Hydrodynamics &hydro, Initiation &ini, Boundary &boundary)
{
  int i, j, k, m;
  
  //left
  if(boundary.xBl == 0) {
    
    //the first column
    for(j = 1; j < y_clls - 1; j++) {
      //creat a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Node *prtl = 
	    new Node(new Particle( -1*cll_sz + (k + 0.5)*delta, 
				   (j - 1)*cll_sz + (m + 0.5)*delta, 
				   0.0, 0.0, cll_sz - (k + 0.5)*delta, 
				   1.0, 0.0, hydro.materials[0]));
	  
	  //prtl->cell_i = 0; prtl->cell_j = j; 
	  //	  prtl->setCellPosition(0, j);
	  //insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);
	  //insert the position into corresponding cell list
	  cell_lists(0, j).insert(cell_lists(0, j).first(), prtl);
	  
	}
    }
  }
  
  //right
  if(boundary.xBr == 0) {
    
    //the last column
    for(j = 1; j < y_clls - 1; j++) {
      //creat a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Node *prtl = new Node(new Particle( (x_clls - 2)*cll_sz + (k + 0.5)*delta, 
					 (j - 1)*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, 
					 (k + 0.5)*delta, 
					 1.0, 0.0, hydro.materials[0]));
	  
	  //prtl->cell_i = x_clls - 1; prtl->cell_j = j; 
	  //	  prtl->setCellPosition(x_clls - 1, j);
	  //insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);
	  
	  //insert the position into corresponding cell list
	  cell_lists(x_clls - 1, j).insert(cell_lists(x_clls - 1, j).first(), prtl);
	  
	}
    }
  }
  
  //bottom
  if(boundary.yBd == 0) {
    
    //the lowest row
    for(i = 1; i < x_clls - 1; i++) {
      //creat a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Node *prtl = new Node(new Particle( (i - 1)*cll_sz + (k + 0.5)*delta, -1*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, cll_sz - (m + 0.5)*delta, 0.0, 1.0, hydro.materials[0]));
	  
	  //prtl->cell_i = i; prtl->cell_j = 0; 
	  //	  prtl->setCellPosition(i, 0);
	  //insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);
	  
	  //insert the position into corresponding cell list
	  cell_lists(i, 0).insert(cell_lists(i, 0).first(), prtl);
	  
	}
    }
  }
  
  //upper
  if(boundary.yBu == 0) {
    
    //the last row
    for(i = 1; i < x_clls - 1; i++) {
      //creat a new wall particle
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  Node *prtl = new Node(new Particle( (i - 1)*cll_sz + (k + 0.5)*delta, (y_clls - 2)*cll_sz + (m + 0.5)*delta, 
					 0.0, 0.0, (m + 0.5)*delta, 0.0, 1.0, hydro.materials[0]));
	  
	  //prtl->cell_i = i; prtl->cell_j = y_clls - 1; 
	  //	  prtl->setCellPosition(i, y_clls - 1);
	  //insert its poistion on the particle list
	  hydro.particle_list.insert(hydro.particle_list.first(), prtl);
	  
	  //insert the position into corresponding cell list
	  cell_lists(i, y_clls - 1).insert(cell_lists(i, y_clls - 1).first(), prtl);	  
	}
    }
  }
}

///returns the pointer to the clossest particle to the given vector
///norm_vec should be normolized to box size <BR>
/// 0 <= norm_vec[0] <= 1 <BR>
/// 1 <= norm_vec[1] <= 1
Node* ParticleManager::getClosestParticle(const Vec2d& norm_vec) const throw()
{
  int i, j; //current cell postions
  int k, m; //possible new cell postions
  double dstc; //distance
    
  Vec2d vec = norm_vec*box_size;

  //where is the point
  k = int ((vec[0] + cll_sz)/ cll_sz);
  m = int ((vec[1] + cll_sz)/ cll_sz);
  //minimum distance
  double mindisnanse;
  bool isfirst = true;
  Node* minPointer;
  
  //loop on this and all surrounding cells
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) { 
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	//iterate this cell list
	for (LlistNode<Node> *p = cell_lists(i, j).first(); 
	     !cell_lists(i, j).isEnd(p); 
	     p = cell_lists(i, j).next(p)) {
	  
	  //check the position of the particle
	  Node *prtl = cell_lists(i, j).retrieve(p);
	  dstc = v_distance(vec, prtl->R());
	  if (isfirst) {
	    mindisnanse = dstc; 
	    minPointer = prtl;
	    isfirst = false;
	  }
	  else if (mindisnanse>dstc) {
	    mindisnanse = dstc;
	    minPointer = prtl;
	  }	  	    
	}
      }
    }
  }
  if (isfirst) {
    cout << "isfirst is not defined" << '\n';
    throw 1;
  }
  return minPointer;    
}

