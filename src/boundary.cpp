#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
struct QuinticSpline;
#include "dllist.h"
#include "hydrodynamics.h"
#include "initiation.h"
#include "particlemanager.h"
#include "particle.h"
#include "material.h"
#include "boundary.h"
enum {X, Y};
using namespace std;
Boundary::Boundary(Initiation &ini, Hydrodynamics &hydro, ParticleManager &q)
{
  char Key_word[FILENAME_MAX];
  char inputfile[FILENAME_MAX];
  box_size[X] = ini.box_size[X];
  box_size[Y] = ini.box_size[Y];
  x_clls = q.x_clls; y_clls = q.y_clls;
  number_of_materials = ini.number_of_materials;
  strcpy(inputfile, ini.inputfile);
  ifstream fin(inputfile, ios::in);
  if (!fin) {
    cout<<"Boundary: Cannot open "<< inputfile <<" \n";
    std::cout << __FILE__ << ':' << __LINE__ << std::endl;
    exit(1);
  }
  else cout<<"\nBoundary: read left, right, upper and lower boundary conditions from "<< inputfile <<" \n";
  while(!fin.eof()) {
    fin>>Key_word;
    if(!strcmp(Key_word, "BOUNDARY")) fin>>xBl>>UxBl[X]>>UxBl[Y]
					 >>xBr>>UxBr[X]>>UxBr[Y]
					 >>yBd>>UyBd[X]>>UyBd[Y]
					 >>yBu>>UyBu[X]>>UyBu[Y];
  }
  fin.close();
  show_information();
  BuildBoundaryParticles(q, hydro);
}
void Boundary::show_information(void)
{
  cout<<"The left, right, lower and upper boundary conditions are "
      <<xBl<<", "<<xBr<<", "<<yBd<<", "<<yBu<<" \n";
  cout<<"0: wall boundary condition\n";
  cout<<"1: perodic boundary condition\n";
  cout<<"2: free slip wall boundary condition\n";
  cout<<"3: symmetry boundary condition\n";
}
void Boundary::RunAwayCheck(Hydrodynamics &hydro)
{
  for (LlistNode<Particle> *p = hydro.particle_list.first();
       !hydro.particle_list.isEnd(p);
       p = hydro.particle_list.next(p)) {
    Particle *prtl = hydro.particle_list.retrieve(p);
    if(fabs(prtl->R[X]) >= 2.0*box_size[X] || fabs(prtl->R[Y]) >= 2.0*box_size[Y]) {
      cout<<"Boundary: the q run out too far away from the domain! \n";
      std::cout << __FILE__ << ':' << __LINE__ << std::endl;
      exit(1);
    }
    if(prtl->bd == 0) {
      if(prtl->R[X] < 0.0) {
	switch(xBl) {
	case 0:
	  prtl->R[X] = - prtl->R[X];
	  break;
	case 1:
	  prtl->R[X] = box_size[X] + prtl->R[X];
	  break;
	case 2:
	  prtl->R[X] = - prtl->R[X];
	  break;
	case 3:
	  prtl->R[X] = - prtl->R[X];
	  break;
	}
      }
      if(prtl->R[X] > box_size[X]) {
	switch(xBr) {
	case 0:
	  prtl->R[X] = 2.0*box_size[X] - prtl->R[X];
	  break;
	case 1:
	  prtl->R[X] = prtl->R[X] - box_size[X];
	  break;
	case 2:
	  prtl->R[X] = 2.0*box_size[X] - prtl->R[X];
	  break;
	case 3:
	  prtl->R[X] = 2.0*box_size[X] - prtl->R[X];
	  break;
	}
      }
      if(prtl->R[Y] < 0.0) {
	switch(yBd) {
	case 0:
	  prtl->R[Y] = - prtl->R[Y];
	  break;
	case 1:
	  prtl->R[Y] = box_size[Y] + prtl->R[Y];
	  break;
	case 2:
	  prtl->R[Y] = - prtl->R[Y];
	  break;
	case 3:
	  prtl->R[Y] = - prtl->R[Y];
	  break;
	}
      }
      if(prtl->R[Y] > box_size[Y]) {
	switch(yBu) {
	case 0:
	  prtl->R[Y] = 2.0*box_size[Y] - prtl->R[Y];
	  break;
	case 1:
	  prtl->R[Y] = prtl->R[Y] - box_size[Y];
	  break;
	case 2:
	  prtl->R[Y] = 2.0*box_size[Y] - prtl->R[Y];
	  break;
	case 3:
	  prtl->R[Y] = 2.0*box_size[Y] - prtl->R[Y];
	  break;
	}
      }
    }
  }
}
void Boundary::BuildBoundaryParticles(ParticleManager &q, Hydrodynamics &hydro)
{
  int i, j;
  boundary_particle_list.clear();
  int kb, ku, mb, mu;
  kb = 0; mb = x_clls;
  ku = 0; mu = x_clls;
  if(xBl == yBd) kb = 1; 
  if(xBr == yBd) mb = x_clls - 1; 
  if(xBl == yBu) ku = 1; 
  if(xBr == yBu) mu = x_clls - 1; 
  for(j = 1; j < y_clls - 1; j++) {
    q.cell_lists[X][j].clear_data();
    if(xBl == 0 || xBl == 2) {
      for (LlistNode<Particle> *p10 = q.cell_lists[Y][j].first();
	   !q.cell_lists[Y][j].isEnd(p10);
	   p10 = q.cell_lists[Y][j].next(p10)) {
	Particle *prtl_old = q.cell_lists[Y][j].retrieve(p10);
	Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
	Boundary_W(prtl);
	prtl->cell_i = 0; prtl->cell_j = j;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[X][j].insert(q.cell_lists[X][j].first(), prtl);
      }
    }
    if(xBl == 3) {
      for (LlistNode<Particle> *p13 = q.cell_lists[Y][j].first();
	   !q.cell_lists[Y][j].isEnd(p13);
	   p13 = q.cell_lists[Y][j].next(p13)) {
	Particle *prtl_old = q.cell_lists[Y][j].retrieve(p13);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_W(prtl);
	prtl->cell_i = 0; prtl->cell_j = j;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[X][j].insert(q.cell_lists[X][j].first(), prtl);
      }
    }
    if(xBl == 1) {
      for (LlistNode<Particle> *p11 = q.cell_lists[x_clls - 2][j].first();
	   !q.cell_lists[x_clls - 2][j].isEnd(p11);
	   p11 = q.cell_lists[x_clls - 2][j].next(p11)) {
	Particle *prtl_old = q.cell_lists[x_clls - 2][j].retrieve(p11);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_W(prtl);
	prtl->cell_i = 0; prtl->cell_j = j;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[X][j].insert(q.cell_lists[X][j].first(), prtl);
      }
    }
    q.cell_lists[x_clls - 1][j].clear_data();
    if(xBr == 0 || xBr == 2) {
      for (LlistNode<Particle> *p20 = q.cell_lists[x_clls - 2][j].first();
	   !q.cell_lists[x_clls - 2][j].isEnd(p20);
	   p20 = q.cell_lists[x_clls - 2][j].next(p20)) {
	Particle *prtl_old = q.cell_lists[x_clls - 2][j].retrieve(p20);
	Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
	Boundary_E(prtl);
	prtl->cell_i = x_clls - 1; prtl->cell_j = j;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[x_clls- 1][j].insert(q.cell_lists[x_clls - 1][j].first(), prtl);
      }
    }
    if(xBr == 3) {
      for (LlistNode<Particle> *p23 = q.cell_lists[x_clls - 2][j].first();
	   !q.cell_lists[x_clls - 2][j].isEnd(p23);
	   p23 = q.cell_lists[x_clls - 2][j].next(p23)) {
	Particle *prtl_old = q.cell_lists[x_clls - 2][j].retrieve(p23);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_E(prtl);
	prtl->cell_i = x_clls - 1; prtl->cell_j = j;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[x_clls- 1][j].insert(q.cell_lists[x_clls - 1][j].first(), prtl);
      }
    }
    if(xBr == 1) {
      for (LlistNode<Particle> *p21 = q.cell_lists[Y][j].first();
	   !q.cell_lists[Y][j].isEnd(p21);
	   p21 = q.cell_lists[Y][j].next(p21)) {
	Particle *prtl_old = q.cell_lists[Y][j].retrieve(p21);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_E(prtl);
	prtl->cell_i = x_clls - 1; prtl->cell_j = j;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[x_clls- 1][j].insert(q.cell_lists[x_clls - 1][j].first(), prtl);
      }
    }
  }
  for(i = kb; i < mb; i++) {
    q.cell_lists[i][X].clear_data();
    if(yBd == 0 || yBd == 2) {
      for (LlistNode<Particle> *p30 = q.cell_lists[i][Y].first();
	   !q.cell_lists[i][Y].isEnd(p30);
	   p30 = q.cell_lists[i][Y].next(p30)) {
	Particle *prtl_old = q.cell_lists[i][Y].retrieve(p30);
	Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
	Boundary_S(prtl);
	prtl->cell_i = i; prtl->cell_j = 0;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[i][X].insert(q.cell_lists[i][X].first(), prtl);
      }
    }
    if(yBd == 3) {
      for (LlistNode<Particle> *p33 = q.cell_lists[i][Y].first();
	   !q.cell_lists[i][Y].isEnd(p33);
	   p33 = q.cell_lists[i][Y].next(p33)) {
	Particle *prtl_old = q.cell_lists[i][Y].retrieve(p33);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_S(prtl);
	prtl->cell_i = i; prtl->cell_j = 0;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[i][X].insert(q.cell_lists[i][X].first(), prtl);
      }
    }
    if(yBd == 1) {
      for (LlistNode<Particle> *p31 = q.cell_lists[i][y_clls - 2].first();
	   !q.cell_lists[i][y_clls - 2].isEnd(p31);
	   p31 = q.cell_lists[i][y_clls - 2].next(p31)) {
	Particle *prtl_old = q.cell_lists[i][y_clls - 2].retrieve(p31);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_S(prtl);
	prtl->cell_i = i; prtl->cell_j = 0;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[i][X].insert(q.cell_lists[i][X].first(), prtl);
      }
    }
  }
  for(i = ku; i < mu; i++) {
    q.cell_lists[i][y_clls - 1].clear_data();
    if(yBu == 0 || yBu == 2) {
      for (LlistNode<Particle> *p40 = q.cell_lists[i][y_clls - 2].first();
	   !q.cell_lists[i][y_clls - 2].isEnd(p40);
	   p40 = q.cell_lists[i][y_clls - 2].next(p40)) {
	Particle *prtl_old = q.cell_lists[i][y_clls - 2].retrieve(p40);
	Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
	Boundary_N(prtl);
	prtl->cell_i = i; prtl->cell_j = y_clls - 1;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[i][y_clls- 1].insert(q.cell_lists[i][y_clls - 1].first(), prtl);
      }
    }
    if(yBu == 3) {
      for (LlistNode<Particle> *p43 = q.cell_lists[i][y_clls - 2].first();
	   !q.cell_lists[i][y_clls - 2].isEnd(p43);
	   p43 = q.cell_lists[i][y_clls - 2].next(p43)) {
	Particle *prtl_old = q.cell_lists[i][y_clls - 2].retrieve(p43);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_N(prtl);
	prtl->cell_i = i; prtl->cell_j = y_clls - 1;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[i][y_clls- 1].insert(q.cell_lists[i][y_clls - 1].first(), prtl);
      }
    }
    if(yBu == 1) {
      for (LlistNode<Particle> *p41 = q.cell_lists[i][Y].first();
	   !q.cell_lists[i][Y].isEnd(p41);
	   p41 = q.cell_lists[i][Y].next(p41)) {
	Particle *prtl_old = q.cell_lists[i][Y].retrieve(p41);
	Particle *prtl = new Particle(*prtl_old);
	Boundary_N(prtl);
	prtl->cell_i = i; prtl->cell_j = y_clls - 1;
	boundary_particle_list.insert(boundary_particle_list.first(), prtl);
	q.cell_lists[i][y_clls- 1].insert(q.cell_lists[i][y_clls - 1].first(), prtl);
      }
    }
  }
  if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
    q.cell_lists[X][X].clear_data();
    for (LlistNode<Particle> *p130 = q.cell_lists[Y][Y].first();
	 !q.cell_lists[Y][Y].isEnd(p130);
	 p130 = q.cell_lists[Y][Y].next(p130)) {
      Particle *prtl_old = q.cell_lists[Y][Y].retrieve(p130);
      Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
      Boundary_SW(prtl);
      prtl->cell_i = 0; prtl->cell_j = 0;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[X][X].insert(q.cell_lists[X][X].first(), prtl);
    }
  }
  if(xBl == 3 && yBd == 3) {
    q.cell_lists[X][X].clear_data();
    for (LlistNode<Particle> *p130 = q.cell_lists[Y][Y].first();
	 !q.cell_lists[Y][Y].isEnd(p130);
	 p130 = q.cell_lists[Y][Y].next(p130)) {
      Particle *prtl_old = q.cell_lists[Y][Y].retrieve(p130);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_SW(prtl);
      prtl->cell_i = 0; prtl->cell_j = 0;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[X][X].insert(q.cell_lists[X][X].first(), prtl);
    }
  }
  if(xBl == 1 && yBd == 1) {
    q.cell_lists[X][X].clear_data();
    for (LlistNode<Particle> *p131 = q.cell_lists[x_clls - 2][y_clls - 2].first();
	 !q.cell_lists[x_clls - 2][y_clls - 2].isEnd(p131);
	 p131 = q.cell_lists[x_clls - 2][y_clls - 2].next(p131)) {
      Particle *prtl_old = q.cell_lists[x_clls - 2][y_clls - 2].retrieve(p131);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_SW(prtl);
      prtl->cell_i = 0; prtl->cell_j = 0;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[X][X].insert(q.cell_lists[X][X].first(), prtl);
    }
  }
  if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
    q.cell_lists[X][y_clls - 1].clear_data();
    for (LlistNode<Particle> *p140 = q.cell_lists[Y][y_clls - 2].first();
	 !q.cell_lists[Y][y_clls - 2].isEnd(p140);
	 p140 = q.cell_lists[Y][y_clls - 2].next(p140)) {
      Particle *prtl_old = q.cell_lists[Y][y_clls - 2].retrieve(p140);
      Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
      Boundary_NW(prtl);
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[X][y_clls- 1].insert(q.cell_lists[X][y_clls - 1].first(), prtl);
    }
  }
  if(xBl == 3 && yBu == 3) {
    q.cell_lists[X][y_clls - 1].clear_data();
    for (LlistNode<Particle> *p140 = q.cell_lists[Y][y_clls - 2].first();
	 !q.cell_lists[Y][y_clls - 2].isEnd(p140);
	 p140 = q.cell_lists[Y][y_clls - 2].next(p140)) {
      Particle *prtl_old = q.cell_lists[Y][y_clls - 2].retrieve(p140);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_NW(prtl);
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[X][y_clls- 1].insert(q.cell_lists[X][y_clls - 1].first(), prtl);
    }
  }
  if(xBl == 1 && yBu == 1) {
    q.cell_lists[X][y_clls - 1].clear_data();
    for (LlistNode<Particle> *p141 = q.cell_lists[x_clls - 2][Y].first();
	 !q.cell_lists[x_clls - 2][Y].isEnd(p141);
	 p141 = q.cell_lists[x_clls - 2][Y].next(p141)) {
      Particle *prtl_old = q.cell_lists[x_clls - 2][Y].retrieve(p141);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_NW(prtl);
      prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[X][y_clls- 1].insert(q.cell_lists[X][y_clls - 1].first(), prtl);
    }
  }
  if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
    q.cell_lists[x_clls - 1][y_clls - 1].clear_data();
    for (LlistNode<Particle> *p240 = q.cell_lists[x_clls - 2][y_clls - 2].first();
	 !q.cell_lists[x_clls - 2][y_clls - 2].isEnd(p240);
	 p240 = q.cell_lists[x_clls - 2][y_clls - 2].next(p240)) {
      Particle *prtl_old = q.cell_lists[x_clls - 2][y_clls - 2].retrieve(p240);
      Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
      Boundary_NE(prtl);
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[x_clls- 1][y_clls - 1].insert(q.cell_lists[x_clls - 1][y_clls - 1].first(), prtl);
    }
  }
  if(xBr == 3 && yBu == 3) {
    q.cell_lists[x_clls - 1][y_clls - 1].clear_data();
    for (LlistNode<Particle> *p240 = q.cell_lists[x_clls - 2][y_clls - 2].first();
	 !q.cell_lists[x_clls - 2][y_clls - 2].isEnd(p240);
	 p240 = q.cell_lists[x_clls - 2][y_clls - 2].next(p240)) {
      Particle *prtl_old = q.cell_lists[x_clls - 2][y_clls - 2].retrieve(p240);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_NE(prtl);
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[x_clls- 1][y_clls - 1].insert(q.cell_lists[x_clls - 1][y_clls - 1].first(), prtl);
    }
  }
  if(xBr == 1 && yBu == 1) {
    q.cell_lists[x_clls - 1][y_clls - 1].clear_data();
    for (LlistNode<Particle> *p241 = q.cell_lists[Y][Y].first();
	 !q.cell_lists[Y][Y].isEnd(p241);
	 p241 = q.cell_lists[Y][Y].next(p241)) {
      Particle *prtl_old = q.cell_lists[Y][Y].retrieve(p241);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_NE(prtl);
      prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[x_clls- 1][y_clls - 1].insert(q.cell_lists[x_clls - 1][y_clls - 1].first(), prtl);
    }
  }
  if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
    q.cell_lists[x_clls - 1][X].clear_data();
    for (LlistNode<Particle> *p230 = q.cell_lists[x_clls - 2][Y].first();
	 !q.cell_lists[x_clls - 2][Y].isEnd(p230);
	 p230 = q.cell_lists[x_clls - 2][Y].next(p230)) {
      Particle *prtl_old = q.cell_lists[x_clls - 2][Y].retrieve(p230);
      Particle *prtl = new Particle(*prtl_old, &hydro.materials[X]);
      Boundary_SE(prtl);
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[x_clls - 1][X].insert(q.cell_lists[x_clls - 1][X].first(), prtl);
    }
  }
  if(xBr == 3 && yBd == 3) {
    q.cell_lists[x_clls - 1][X].clear_data();
    for (LlistNode<Particle> *p230 = q.cell_lists[x_clls - 2][Y].first();
	 !q.cell_lists[x_clls - 2][Y].isEnd(p230);
	 p230 = q.cell_lists[x_clls - 2][Y].next(p230)) {
      Particle *prtl_old = q.cell_lists[x_clls - 2][Y].retrieve(p230);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_SE(prtl);
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[x_clls - 1][X].insert(q.cell_lists[x_clls - 1][X].first(), prtl);
    }
  }
  if(xBr == 1 && yBd == 1) {
    q.cell_lists[x_clls - 1][X].clear_data();
    for (LlistNode<Particle> *p231 = q.cell_lists[Y][y_clls - 2].first();
	 !q.cell_lists[Y][y_clls - 2].isEnd(p231);
	 p231 = q.cell_lists[Y][y_clls - 2].next(p231)) {
      Particle *prtl_old = q.cell_lists[Y][y_clls - 2].retrieve(p231);
      Particle *prtl = new Particle(*prtl_old);
      Boundary_SE(prtl);
      prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
      boundary_particle_list.insert(boundary_particle_list.first(), prtl);
      q.cell_lists[x_clls - 1][X].insert(q.cell_lists[x_clls - 1][X].first(), prtl);
    }
  }
}
void Boundary::BoundaryCondition(ParticleManager &q)
{
  int i, j;
  int kb, ku, mb, mu;
  kb = 0; mb = x_clls;
  ku = 0; mu = x_clls;
  if(xBl == yBd) kb = 1; 
  if(xBr == yBd) mb = x_clls - 1; 
  if(xBl == yBu) ku = 1; 
  if(xBr == yBu) mu = x_clls - 1; 
  for(j = 1; j < y_clls - 1; j++) {
    if(xBl == 0 || xBl == 2) {
      for (LlistNode<Particle> *p1 = q.cell_lists[X][j].first();
	   !q.cell_lists[X][j].isEnd(p1);
	   p1 = q.cell_lists[X][j].next(p1)) {
	Particle *prtl = q.cell_lists[X][j].retrieve(p1);
	prtl->StatesCopier(prtl->rl_prtl, 0);
	Boundary_W(prtl);
      }
    }
    if(xBl == 1 || xBl == 3) {
      for (LlistNode<Particle> *p1 = q.cell_lists[X][j].first();
	   !q.cell_lists[X][j].isEnd(p1);
	   p1 = q.cell_lists[X][j].next(p1)) {
	Particle *prtl = q.cell_lists[X][j].retrieve(p1);
	prtl->StatesCopier(prtl->rl_prtl, 1);
	Boundary_W(prtl);
      }
    }
    if(xBr == 0 || xBr == 2) {
      for (LlistNode<Particle> *p2 = q.cell_lists[x_clls - 1][j].first();
	   !q.cell_lists[x_clls - 1][j].isEnd(p2);
	   p2 = q.cell_lists[x_clls - 1][j].next(p2)) {
	Particle *prtl = q.cell_lists[x_clls - 1][j].retrieve(p2);
	prtl->StatesCopier(prtl->rl_prtl, 0);
	Boundary_E(prtl);
      }
    }
    if(xBr == 1 || xBr == 3) {
      for (LlistNode<Particle> *p2 = q.cell_lists[x_clls - 1][j].first();
	   !q.cell_lists[x_clls - 1][j].isEnd(p2);
	   p2 = q.cell_lists[x_clls - 1][j].next(p2)) {
	Particle *prtl = q.cell_lists[x_clls - 1][j].retrieve(p2);
	prtl->StatesCopier(prtl->rl_prtl, 1);
	Boundary_E(prtl);
      }
    }
  }
  for(i = kb; i < mb; i++) {
    if(yBd == 0 || yBd == 2) {
      for (LlistNode<Particle> *p3 = q.cell_lists[i][X].first();
	   !q.cell_lists[i][X].isEnd(p3);
	   p3 = q.cell_lists[i][X].next(p3)) {
	Particle *prtl = q.cell_lists[i][X].retrieve(p3);
	prtl->StatesCopier(prtl->rl_prtl, 0);
	Boundary_S(prtl);
      }
    }
    if(yBd == 1 || yBd == 3) {
      for (LlistNode<Particle> *p3 = q.cell_lists[i][X].first();
	   !q.cell_lists[i][X].isEnd(p3);
	   p3 = q.cell_lists[i][X].next(p3)) {
	Particle *prtl = q.cell_lists[i][X].retrieve(p3);
	prtl->StatesCopier(prtl->rl_prtl, 1);
	Boundary_S(prtl);
      }
    }
  }
  for(i = ku; i < mu; i++) {
    if(yBu == 0 || yBu == 2) {
      for (LlistNode<Particle> *p4 = q.cell_lists[i][y_clls - 1].first();
	   !q.cell_lists[i][y_clls - 1].isEnd(p4);
	   p4 = q.cell_lists[i][y_clls - 1].next(p4)) {
	Particle *prtl = q.cell_lists[i][y_clls - 1].retrieve(p4);
	prtl->StatesCopier(prtl->rl_prtl, 0);
	Boundary_N(prtl);
      }
    }
    if(yBu == 1 || yBu == 3) {
      for (LlistNode<Particle> *p4 = q.cell_lists[i][y_clls - 1].first();
	   !q.cell_lists[i][y_clls - 1].isEnd(p4);
	   p4 = q.cell_lists[i][y_clls - 1].next(p4)) {
	Particle *prtl = q.cell_lists[i][y_clls - 1].retrieve(p4);
	prtl->StatesCopier(prtl->rl_prtl, 1);
	Boundary_N(prtl);
      }
    }
  }
  if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
    for (LlistNode<Particle> *p13 = q.cell_lists[X][X].first();
	 !q.cell_lists[X][X].isEnd(p13);
	 p13 = q.cell_lists[X][X].next(p13)) {
      Particle *prtl = q.cell_lists[X][X].retrieve(p13);
      prtl->StatesCopier(prtl->rl_prtl, 0);
      Boundary_SW(prtl);
    }
  }
  if((xBl == 1 && yBd == 1) || (xBl == 3 && yBd == 3)) {
    for (LlistNode<Particle> *p13 = q.cell_lists[X][X].first();
	 !q.cell_lists[X][X].isEnd(p13);
	 p13 = q.cell_lists[X][X].next(p13)) {
      Particle *prtl = q.cell_lists[X][X].retrieve(p13);
      prtl->StatesCopier(prtl->rl_prtl, 1);
      Boundary_SW(prtl);
    }
  }
  if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
    for (LlistNode<Particle> *p14 = q.cell_lists[X][y_clls - 1].first();
	 !q.cell_lists[X][y_clls - 1].isEnd(p14);
	 p14 = q.cell_lists[X][y_clls - 1].next(p14)) {
      Particle *prtl = q.cell_lists[X][y_clls - 1].retrieve(p14);
      prtl->StatesCopier(prtl->rl_prtl, 0);
      Boundary_NW(prtl);
    }
  }
  if((xBl == 1 && yBu == 1) || (xBl == 3 && yBu == 3)) {
    for (LlistNode<Particle> *p14 = q.cell_lists[X][y_clls - 1].first();
	 !q.cell_lists[X][y_clls - 1].isEnd(p14);
	 p14 = q.cell_lists[X][y_clls - 1].next(p14)) {
      Particle *prtl = q.cell_lists[X][y_clls - 1].retrieve(p14);
      prtl->StatesCopier(prtl->rl_prtl, 1);
      Boundary_NW(prtl);
    }
  }
  if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
    for (LlistNode<Particle> *p24 = q.cell_lists[x_clls - 1][y_clls - 1].first();
	 !q.cell_lists[x_clls - 1][y_clls - 1].isEnd(p24);
	 p24 = q.cell_lists[x_clls - 1][y_clls - 1].next(p24)) {
      Particle *prtl = q.cell_lists[x_clls - 1][y_clls - 1].retrieve(p24);
      prtl->StatesCopier(prtl->rl_prtl, 0);
      Boundary_NE(prtl);
    }
  }
  if((xBr == 1 && yBu == 1) || (xBr == 3 && yBu == 3)) {
    for (LlistNode<Particle> *p24 = q.cell_lists[x_clls - 1][y_clls - 1].first();
	 !q.cell_lists[x_clls - 1][y_clls - 1].isEnd(p24);
	 p24 = q.cell_lists[x_clls - 1][y_clls - 1].next(p24)) {
      Particle *prtl = q.cell_lists[x_clls - 1][y_clls - 1].retrieve(p24);
      prtl->StatesCopier(prtl->rl_prtl, 1);
      Boundary_NE(prtl);
    }
  }
  if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
    for (LlistNode<Particle> *p23 = q.cell_lists[x_clls - 1][X].first();
	 !q.cell_lists[x_clls - 1][X].isEnd(p23);
	 p23 = q.cell_lists[x_clls - 1][X].next(p23)) {
      Particle *prtl = q.cell_lists[x_clls - 1][X].retrieve(p23);
      prtl->StatesCopier(prtl->rl_prtl, 0);
      Boundary_SE(prtl);
    }
  }
  if((xBr == 1 && yBd == 1) || (xBr == 3 && yBd == 3)) {
    for (LlistNode<Particle> *p23 = q.cell_lists[x_clls - 1][X].first();
	 !q.cell_lists[x_clls - 1][X].isEnd(p23);
	 p23 = q.cell_lists[x_clls - 1][X].next(p23)) {
      Particle *prtl = q.cell_lists[x_clls - 1][X].retrieve(p23);
      prtl->StatesCopier(prtl->rl_prtl, 1);
      Boundary_SE(prtl);
    }
  }
}
void Boundary::Boundary_W(Particle *prtl)
{
  switch(xBl) {
  case 0:
    prtl->R[X] = - prtl->R[X];
    prtl->U[X] = UxBl[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[X] = prtl->R[X] - box_size[X];
    break;
  case 2:
    prtl->R[X] = - prtl->R[X];
    prtl->U[X] = UxBl[X]*2.0 - prtl->U[X];
    break;
  case 3:
    prtl->R[X] = - prtl->R[X];
    prtl->U[X] = UxBl[X]*2.0 - prtl->U[X];
    prtl->del_phi[X] = - prtl->del_phi[X];
    break;
  }
}
void Boundary::Boundary_E(Particle *prtl)
{
  switch(xBr) {
  case 0:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->U[X] = UxBr[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[X] = prtl->R[X] + box_size[X];
    break;
  case 2:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->U[X] = UxBr[X]*2.0 - prtl->U[X];
    break;
  case 3:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->U[X] = UxBr[X]*2.0 - prtl->U[X];
    prtl->del_phi[X] = - prtl->del_phi[X];
    break;
  }
}
void Boundary::Boundary_S(Particle *prtl)
{
  switch(yBd) {
  case 0:
    prtl->R[Y] = - prtl->R[Y];
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UyBd[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[Y] = prtl->R[Y] - box_size[Y];
    break;
  case 2:
    prtl->R[Y] = - prtl->R[Y];
    prtl->U[Y] = UyBd[Y]*2.0 - prtl->U[Y];
    break;
  case 3:
    prtl->R[Y] = - prtl->R[Y];
    prtl->U[Y] = UyBd[Y]*2.0 - prtl->U[Y];
    prtl->del_phi[Y] = - prtl->del_phi[Y];
    break;
  }
}
void Boundary::Boundary_N(Particle *prtl)
{
  switch(yBu) {
  case 0:
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UyBu[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[Y] = prtl->R[Y] + box_size[Y];
    break;
  case 2:
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[Y] = UyBu[Y]*2.0 - prtl->U[Y];
    break;
  case 3:
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[Y] = UyBu[Y]*2.0 - prtl->U[Y];
    prtl->del_phi[Y] = - prtl->del_phi[Y];
    break;
  }
}
void Boundary::Boundary_SW(Particle *prtl)
{
  switch(xBl) {
  case 0:
    prtl->R[X] = - prtl->R[X];
    prtl->R[Y] = - prtl->R[Y];    
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[X] = prtl->R[X] - box_size[X];
    prtl->R[Y] = prtl->R[Y] - box_size[Y];
    break;
  case 2:
    prtl->R[X] = - prtl->R[X];
    prtl->R[Y] = - prtl->R[Y];    
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    break;
  case 3:
    prtl->R[X] = - prtl->R[X];
    prtl->R[Y] = - prtl->R[Y];    
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    prtl->del_phi[X] = - prtl->del_phi[X];
    prtl->del_phi[Y] = - prtl->del_phi[Y];    
    break;
  }
}
void Boundary::Boundary_NW(Particle *prtl)
{
  switch(xBl) {
  case 0:
    prtl->R[X] = - prtl->R[X];
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[X] = prtl->R[X] - box_size[X];
    prtl->R[Y] = prtl->R[Y] + box_size[Y];
    break;
  case 2:
    prtl->R[X] = - prtl->R[X];
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    break;
  case 3:
    prtl->R[X] = - prtl->R[X];
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBl[Y]*2.0 - prtl->U[Y];
    prtl->del_phi[X] = - prtl->del_phi[X];
    prtl->del_phi[Y] = - prtl->del_phi[Y];    
    break;
  }
}
void Boundary::Boundary_NE(Particle *prtl)
{
  switch(xBr) {
  case 0:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[X] = prtl->R[X] + box_size[X];
    prtl->R[Y] = prtl->R[Y] + box_size[Y];
    break;
  case 2:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];    
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    break;
  case 3:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->R[Y] = box_size[Y]*2.0 - prtl->R[Y];    
    prtl->U[X] = UyBu[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    prtl->del_phi[X] = - prtl->del_phi[X];
    prtl->del_phi[Y] = - prtl->del_phi[Y];    
    break;
  }
}
void Boundary::Boundary_SE(Particle *prtl)
{
  switch(xBr) {
  case 0:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->R[Y] = - prtl->R[Y];
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    break;
  case 1:
    prtl->R[X] = prtl->R[X] + box_size[X];
    prtl->R[Y] = prtl->R[Y] - box_size[Y];
    break;
  case 2:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->R[Y] = - prtl->R[Y];
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    break;
  case 3:
    prtl->R[X] = box_size[X]*2.0 - prtl->R[X];
    prtl->R[Y] = - prtl->R[Y];
    prtl->U[X] = UyBd[X]*2.0 - prtl->U[X];
    prtl->U[Y] = UxBr[Y]*2.0 - prtl->U[Y];
    prtl->del_phi[X] = - prtl->del_phi[X];
    prtl->del_phi[Y] = - prtl->del_phi[Y];    
    break;
  }
}
