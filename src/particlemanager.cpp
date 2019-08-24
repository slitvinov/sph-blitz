#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "glbfunc.h"
#include "vv.h"
#include "initiation.h"
#include "particle.h"
#include "dllist.h"
#include "list.h"
#include "interaction.h"
#include "hydrodynamics.h"
#include "material.h"
#include "boundary.h"
#include "particlemanager.h"

using namespace std;
enum {X, Y};

#define NEW_BND(x, y, mtl) particle_wall(x, y, mtl)
#define NEW(pos, vel, den, pre, tem, mtl) particle_real(pos, vel, den, pre, tem, mtl)
#define LIST ListNode
#define INSERT(q, l) l.insert(l.first(), q)

ParticleManager::ParticleManager(Initiation *ini)
{

  int i;
  strcpy(Project_name, ini->Project_name);
  number_of_materials = ini->number_of_materials;
  smoothinglength = ini->smoothinglength;
  smoothinglengthsquare = smoothinglength*smoothinglength;
  box_size[X] = ini->box_size[X];
  box_size[Y] = ini->box_size[Y];
  cll_sz = ini->cell_size;
  x_clls = ini->x_cells + 2; y_clls = ini->y_cells + 2;
  initial_condition = ini->initial_condition;
  hdelta = ini->hdelta; delta = ini->delta;

  if(initial_condition == 0) {
    U0[X] = ini->U0[X];
    U0[Y] = ini->U0[Y];
    rho0 = ini->rho0;
    p0 = ini->p0;
    T0 = ini->T0;
  }
  cell_lists = new List*[x_clls];
  for(i = 0; i < x_clls; i++) cell_lists[i] = new List[y_clls];

}
void ParticleManager::UpdateCellLinkedLists()
{

  int i, j;
  int k, m;
  for(i = 0; i < x_clls; i++) {
    for(j = 0; j < y_clls; j++) {
      LIST *p = cell_lists[i][j].first();
      while(!cell_lists[i][j].isEnd(p)) {
	Particle *prtl = cell_lists[i][j].retrieve(p);
	if(prtl->bd == 0) {
	  k = int ((prtl->R[0] + cll_sz)/ cll_sz);
	  m = int ((prtl->R[1] + cll_sz)/ cll_sz);
	  if(k != i || m !=j) {
	    cell_lists[i][j].remove(p);
	    INSERT(prtl, cell_lists[k][m]);
	  } else p = cell_lists[i][j].next(p);
	} else p = cell_lists[i][j].next(p);
      }

    }
  }
}

void ParticleManager::BuildNNP(double point[2])
{
  int i, j;
  int k, m;
  double dstc;

  NNP_list.clear_data();
  k = int ((point[0] + cll_sz)/ cll_sz);
  m = int ((point[1] + cll_sz)/ cll_sz);
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) {
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	for (LIST *p = cell_lists[i][j].first();
	     !cell_lists[i][j].isEnd(p);
	     p = cell_lists[i][j].next(p)) {
	  Particle *prtl = cell_lists[i][j].retrieve(p);
	  dstc = vv_distance(point, prtl->R);
	  if(dstc < smoothinglength) {
	    INSERT(prtl, NNP_list);
	  }
	}
      }
    }
  }
}

void ParticleManager::BuildNNP_MLSMapping(double point[2])
{
  int i, j;
  int k, m;
  double dstc;

  k = int ((point[0] + cll_sz)/ cll_sz);
  m = int ((point[1] + cll_sz)/ cll_sz);
  for(i = k - 1; i <= k + 1; i++) {
    for(j = m - 1; j <= m + 1; j++) {
      if(i < x_clls && j < y_clls && i >= 0 && j >= 0) {
	for (LIST *p = cell_lists[i][j].first();
	     !cell_lists[i][j].isEnd(p);
	     p = cell_lists[i][j].next(p)) {
	  Particle *prtl = cell_lists[i][j].retrieve(p);
	  dstc = vv_distance(point, prtl->R);
	  if(dstc < smoothinglength && prtl->bd == 0) {
	    INSERT(prtl, NNP_list);
	  }
	}
      }
    }
  }
}

void ParticleManager::BuildInteraction(Llist<Interaction> &interactions, List &particle_list,
				       Force **forces, QuinticSpline &weight_function)
{
  LlistNode<Interaction> *current = interactions.first();
  bool used_up_old = interactions.isEnd(current);
  LlistNode<Interaction> *first_unused;
  int old_length = interactions.length();
  {
    int i, j, k, m;
    double dstc;
    int current_used = 0;
    for (LIST *p = particle_list.first();
	 !particle_list.isEnd(p);
	 p = particle_list.next(p)) {
      Particle *prtl_org = particle_list.retrieve(p);
      if(prtl_org->bd == 0) {
	i = int ((prtl_org->R[0] + cll_sz)/ cll_sz);
	j = int ((prtl_org->R[1] + cll_sz)/ cll_sz);
	for(k = i - 1; k <= i + 1; k++)
	  for(m = j - 1; m <= j + 1; m++) {
	    for (LIST *p1 = cell_lists[k][m].first();
		 !cell_lists[k][m].isEnd(p1);
		 p1 = cell_lists[k][m].next(p1)) {
	      Particle *prtl_dest = cell_lists[k][m].retrieve(p1);
	      dstc = vv_sq_distance(prtl_org->R, prtl_dest->R);
	      if(dstc <= smoothinglengthsquare && prtl_org->ID >= prtl_dest->ID) {
		if(current_used == old_length) {
		    Interaction *pair = new Interaction(prtl_org, prtl_dest, forces, &weight_function, sqrt(dstc));
		    INSERT(pair, interactions);
		}
		else {
		    interactions.retrieve(current)->NewInteraction(prtl_org, prtl_dest, forces, &weight_function, sqrt(dstc));
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

void ParticleManager::BuildRealParticles(Hydrodynamics &hydro, Initiation *ini)
{

  int i, j, k, m;
  double position[2];
  double velocity[2];
  double density, pressure, Temperature;
  int material_no;
  Particle *prtl;

  if(initial_condition==0) {
    for(i = 1; i < x_clls - 1; i++) {
      for(j = 1; j < y_clls - 1; j++) {
	for(k = 0; k < hdelta; k++) {
	  for(m = 0; m < hdelta; m++) {
	    position[0] = (i - 1)*cll_sz + (k + 0.5)*delta;
	    position[1] = (j - 1)*cll_sz + (m + 0.5)*delta;
	    material_no = 1;
	    velocity[X] = U0[X];
	    velocity[Y] = U0[Y];
	    Temperature = T0;
	    density = hydro.materials[material_no].rho0;
	    pressure = get_p(&hydro.materials[material_no], density);
	    prtl = NEW(position, velocity, density, pressure, Temperature, &hydro.materials[material_no]);
	    prtl->cell_i = i; prtl->cell_j = j;
	    INSERT(prtl, hydro.particle_list);
	    INSERT(prtl, cell_lists[i][j]);

	  }
	}
      }
    }
  }

  if(initial_condition==1) {
    int n, N;
    char inputfile[FILENAME_MAX];
    char material_name[25];
    strcpy(inputfile, Project_name);
    strcat(inputfile, ".rst");
    ifstream fin(inputfile, ios::in);
    if (!fin) {
      cout<<"Initialtion: Cannot open "<< inputfile <<" \n";
      std::cout << __FILE__ << ':' << __LINE__ << std::endl;
      exit(1);
    }
    else cout<<"Initialtion: Read real particle data from "<< inputfile <<" \n";
    fin>>ini->Start_time;
    ini->End_time += ini->Start_time;
    fin>>N;
    for(n = 0; n < N; n++) {
      fin>>material_name>>position[0]>>position[1]>>velocity[0]>>velocity[1]
	 >>density>>pressure>>Temperature;
      material_no = -1;
      for(k = 0;  k < number_of_materials; k++)
	if(strcmp(material_name, hydro.materials[k].material_name) == 0) material_no = k;
      if(material_no != -1) {
	pressure = get_p(&hydro.materials[material_no], density);
	prtl = NEW(position, velocity, density, pressure, Temperature, &hydro.materials[material_no]);
	INSERT(prtl, hydro.particle_list);
	i = int (prtl->R[0] / cll_sz) + 1;
	j = int (prtl->R[1] / cll_sz) + 1;
	prtl->cell_i = i; prtl->cell_j = j;
	INSERT(prtl, cell_lists[i][j]);
      } else {
	cout<<"The material in the restart file is not used by the program! \n";
	std::cout << __FILE__ << ':' << __LINE__ << std::endl;
	exit(1);
      }
    }
    fin.close();
  }
}

void ParticleManager::BuildWallParticles(Hydrodynamics &hydro, Boundary &boundary)
{
  int i, j, k, m;
  Particle *prtl;
  if(boundary.xBl == 0) {
    for(j = 1; j < y_clls - 1; j++) {
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  prtl = NEW_BND(-1*cll_sz + (k + 0.5)*delta, (j - 1)*cll_sz + (m + 0.5)*delta, &hydro.materials[0]);
	  prtl->cell_i = 0; prtl->cell_j = j;
	  INSERT(prtl, hydro.particle_list);
	  INSERT(prtl, cell_lists[0][j]);
	}
    }
  }
  if(boundary.xBr == 0) {
    for(j = 1; j < y_clls - 1; j++) {
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  prtl = NEW_BND((x_clls - 2)*cll_sz + (k + 0.5)*delta, (j - 1)*cll_sz + (m + 0.5)*delta, &hydro.materials[0]);
	  prtl->cell_i = x_clls - 1; prtl->cell_j = j;
	  INSERT(prtl, hydro.particle_list);
	  INSERT(prtl, cell_lists[x_clls - 1][j]);
	}
    }
  }

  if(boundary.yBd == 0) {
    for(i = 1; i < x_clls - 1; i++) {
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  prtl = NEW_BND((i - 1)*cll_sz + (k + 0.5)*delta, -1*cll_sz + (m + 0.5)*delta, &hydro.materials[0]);
	  prtl->cell_i = i; prtl->cell_j = 0;
	  INSERT(prtl, hydro.particle_list);
	  INSERT(prtl, cell_lists[i][0]);

	}
    }
  }

  if(boundary.yBu == 0) {
    for(i = 1; i < x_clls - 1; i++) {
      for(k = 0; k < hdelta; k++)
	for(m = 0; m < hdelta; m++) {
	  prtl = NEW_BND((i - 1)*cll_sz + (k + 0.5)*delta, (y_clls - 2)*cll_sz + (m + 0.5)*delta, &hydro.materials[0]);
	  prtl->cell_i = i; prtl->cell_j = y_clls - 1;
	  INSERT(prtl, hydro.particle_list);
	  INSERT(prtl, cell_lists[i][y_clls - 1]);
	}
    }
  }
}
