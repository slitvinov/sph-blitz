#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
struct QuinticSpline;
#include "particle.h"
#include "dllist.h"
#include "list.h"
#include "hydrodynamics.h"
#include "initiation.h"
#include "particlemanager.h"
#include "material.h"
#include "boundary.h"
enum {X, Y};
using namespace std;

#define A prtl = particle_mirror(prtl_old, &hydro->materials[0])
#define B prtl = particle_image(prtl_old)
#define C(t) do {                               \
	if (prtl->rl_prtl == NULL)		\
	    abort();				\
	particle_copy(prtl, prtl->rl_prtl, t);	\
    } while (0)
#define LIST ListNode

Boundary::Boundary(Initiation *ini, Hydrodynamics *hydro, ParticleManager *q)
{
    char Key_word[FILENAME_MAX];
    char inputfile[FILENAME_MAX];
    box_size[X] = ini->box_size[X];
    box_size[Y] = ini->box_size[Y];
    x_clls = q->x_clls;
    y_clls = q->y_clls;
    strcpy(inputfile, ini->inputfile);
    ifstream fin(inputfile, ios::in);
    if (!fin) {
	fprintf(stderr, "%s:%d: can't open '%s'\n", __FILE__, __LINE__, inputfile);
	exit(1);
    }
    printf("Boundary: read left, right, upper and lower boundary conditions from %s\n", inputfile);
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
    printf("The left, right, lower and upper boundary %d %d %d %d\n", xBl, xBr, yBd, yBu);
    puts("0: wall boundary condition");
    puts("1: perodic boundary condition");
    puts("2: free slip wall boundary condition");
    puts("3: symmetry boundary condition");
}
void Boundary::RunAwayCheck(Hydrodynamics *hydro)
{
    LIST *p;
    Particle *prtl;
    for (p = hydro->particle_list.first();
	 !hydro->particle_list.isEnd(p);
	 p = hydro->particle_list.next(p)) {
	prtl = hydro->particle_list.retrieve(p);
	if(fabs(prtl->R[X]) >= 2.0*box_size[X] || fabs(prtl->R[Y]) >= 2.0*box_size[Y]) {
	    fprintf(stderr, "%s:%d: Boundary: the q run out too far away from the domain! \n", __FILE__, __LINE__);
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
void Boundary::BuildBoundaryParticles(ParticleManager *q, Hydrodynamics *hydro)
{
    int i, j;
    Particle *prtl, *prtl_old;
    int kb, ku, mb, mu;
    List **c;
    LIST *p;

    c = q->cell_lists;
    b.clear_data();
    kb = 0; mb = x_clls;
    ku = 0; mu = x_clls;
    if(xBl == yBd) kb = 1;
    if(xBr == yBd) mb = x_clls - 1;
    if(xBl == yBu) ku = 1;
    if(xBr == yBu) mu = x_clls - 1;
    for(j = 1; j < y_clls - 1; j++) {
	c[X][j].clear();
	if(xBl == 0 || xBl == 2) {
	    for (p = c[Y][j].first();
		 !c[Y][j].isEnd(p);
		 p = c[Y][j].next(p)) {
		prtl_old = c[Y][j].retrieve(p);
		A;
		Boundary_W(prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		b.insert(b.first(), prtl);
		c[X][j].insert(c[X][j].first(), prtl);
	    }
	}
	if(xBl == 3) {
	    for (p = c[Y][j].first();
		 !c[Y][j].isEnd(p);
		 p = c[Y][j].next(p)) {
		prtl_old = c[Y][j].retrieve(p);
		B;
		Boundary_W(prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		b.insert(b.first(), prtl);
		c[X][j].insert(c[X][j].first(), prtl);
	    }
	}
	if(xBl == 1) {
	    for (p = c[x_clls - 2][j].first();
		 !c[x_clls - 2][j].isEnd(p);
		 p = c[x_clls - 2][j].next(p)) {
		prtl_old = c[x_clls - 2][j].retrieve(p);
		B;
		Boundary_W(prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		b.insert(b.first(), prtl);
		c[X][j].insert(c[X][j].first(), prtl);
	    }
	}
	c[x_clls - 1][j].clear();
	if(xBr == 0 || xBr == 2) {
	    for (p = c[x_clls - 2][j].first();
		 !c[x_clls - 2][j].isEnd(p);
		 p = c[x_clls - 2][j].next(p)) {
		prtl_old = c[x_clls - 2][j].retrieve(p);
		A;
		Boundary_E(prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		b.insert(b.first(), prtl);
		c[x_clls- 1][j].insert(c[x_clls - 1][j].first(), prtl);
	    }
	}
	if(xBr == 3) {
	    for (p = c[x_clls - 2][j].first();
		 !c[x_clls - 2][j].isEnd(p);
		 p = c[x_clls - 2][j].next(p)) {
		prtl_old = c[x_clls - 2][j].retrieve(p);
		B;
		Boundary_E(prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		b.insert(b.first(), prtl);
		c[x_clls- 1][j].insert(c[x_clls - 1][j].first(), prtl);
	    }
	}
	if(xBr == 1) {
	    for (p = c[Y][j].first();
		 !c[Y][j].isEnd(p);
		 p = c[Y][j].next(p)) {
		prtl_old = c[Y][j].retrieve(p);
		B;
		Boundary_E(prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		b.insert(b.first(), prtl);
		c[x_clls- 1][j].insert(c[x_clls - 1][j].first(), prtl);
	    }
	}
    }
    for(i = kb; i < mb; i++) {
	c[i][0].clear();
	if(yBd == 0 || yBd == 2) {
	    for (p = c[i][1].first();
		 !c[i][1].isEnd(p);
		 p = c[i][1].next(p)) {
		prtl_old = c[i][1].retrieve(p);
		A;
		Boundary_S(prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		b.insert(b.first(), prtl);
		c[i][0].insert(c[i][0].first(), prtl);
	    }
	}
	if(yBd == 3) {
	    for (p = c[i][1].first();
		 !c[i][1].isEnd(p);
		 p = c[i][1].next(p)) {
		prtl_old = c[i][1].retrieve(p);
		B;
		Boundary_S(prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		b.insert(b.first(), prtl);
		c[i][0].insert(c[i][0].first(), prtl);
	    }
	}
	if(yBd == 1) {
	    for (p = c[i][y_clls - 2].first();
		 !c[i][y_clls - 2].isEnd(p);
		 p = c[i][y_clls - 2].next(p)) {
		prtl_old = c[i][y_clls - 2].retrieve(p);
		B;
		Boundary_S(prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		b.insert(b.first(), prtl);
		c[i][0].insert(c[i][0].first(), prtl);
	    }
	}
    }
    for(i = ku; i < mu; i++) {
	c[i][y_clls - 1].clear();
	if(yBu == 0 || yBu == 2) {
	    for (p = c[i][y_clls - 2].first();
		 !c[i][y_clls - 2].isEnd(p);
		 p = c[i][y_clls - 2].next(p)) {
		prtl_old = c[i][y_clls - 2].retrieve(p);
		A;
		Boundary_N(prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		b.insert(b.first(), prtl);
		c[i][y_clls- 1].insert(c[i][y_clls - 1].first(), prtl);
	    }
	}
	if(yBu == 3) {
	    for (p = c[i][y_clls - 2].first();
		 !c[i][y_clls - 2].isEnd(p);
		 p = c[i][y_clls - 2].next(p)) {
		prtl_old = c[i][y_clls - 2].retrieve(p);
		B;
		Boundary_N(prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		b.insert(b.first(), prtl);
		c[i][y_clls- 1].insert(c[i][y_clls - 1].first(), prtl);
	    }
	}
	if(yBu == 1) {
	    for (p = c[i][1].first();
		 !c[i][1].isEnd(p);
		 p = c[i][1].next(p)) {
		prtl_old = c[i][1].retrieve(p);
		B;
		Boundary_N(prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		b.insert(b.first(), prtl);
		c[i][y_clls- 1].insert(c[i][y_clls - 1].first(), prtl);
	    }
	}
    }
    if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	c[X][0].clear();
	for (p = c[Y][1].first();
	     !c[Y][1].isEnd(p);
	     p = c[Y][1].next(p)) {
	    prtl_old = c[Y][1].retrieve(p);
	    A;
	    Boundary_SW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    b.insert(b.first(), prtl);
	    c[X][0].insert(c[X][0].first(), prtl);
	}
    }
    if(xBl == 3 && yBd == 3) {
	c[X][0].clear();
	for (p = c[Y][1].first();
	     !c[Y][1].isEnd(p);
	     p = c[Y][1].next(p)) {
	    prtl_old = c[Y][1].retrieve(p);
	    B;
	    Boundary_SW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    b.insert(b.first(), prtl);
	    c[X][0].insert(c[X][0].first(), prtl);
	}
    }
    if(xBl == 1 && yBd == 1) {
	c[X][0].clear();
	for (p = c[x_clls - 2][y_clls - 2].first();
	     !c[x_clls - 2][y_clls - 2].isEnd(p);
	     p = c[x_clls - 2][y_clls - 2].next(p)) {
	    prtl_old = c[x_clls - 2][y_clls - 2].retrieve(p);
	    B;
	    Boundary_SW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    b.insert(b.first(), prtl);
	    c[X][0].insert(c[X][0].first(), prtl);
	}
    }
    if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	c[X][y_clls - 1].clear();
	for (p = c[Y][y_clls - 2].first();
	     !c[Y][y_clls - 2].isEnd(p);
	     p = c[Y][y_clls - 2].next(p)) {
	    prtl_old = c[Y][y_clls - 2].retrieve(p);
	    A;
	    Boundary_NW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    b.insert(b.first(), prtl);
	    c[X][y_clls- 1].insert(c[X][y_clls - 1].first(), prtl);
	}
    }
    if(xBl == 3 && yBu == 3) {
	c[X][y_clls - 1].clear();
	for (p = c[Y][y_clls - 2].first();
	     !c[Y][y_clls - 2].isEnd(p);
	     p = c[Y][y_clls - 2].next(p)) {
	    prtl_old = c[Y][y_clls - 2].retrieve(p);
	    B;
	    Boundary_NW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    b.insert(b.first(), prtl);
	    c[X][y_clls- 1].insert(c[X][y_clls - 1].first(), prtl);
	}
    }
    if(xBl == 1 && yBu == 1) {
	c[X][y_clls - 1].clear();
	for (p = c[x_clls - 2][1].first();
	     !c[x_clls - 2][1].isEnd(p);
	     p = c[x_clls - 2][1].next(p)) {
	    prtl_old = c[x_clls - 2][1].retrieve(p);
	    B;
	    Boundary_NW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    b.insert(b.first(), prtl);
	    c[X][y_clls- 1].insert(c[X][y_clls - 1].first(), prtl);
	}
    }
    if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	c[x_clls - 1][y_clls - 1].clear();
	for (p = c[x_clls - 2][y_clls - 2].first();
	     !c[x_clls - 2][y_clls - 2].isEnd(p);
	     p = c[x_clls - 2][y_clls - 2].next(p)) {
	    prtl_old = c[x_clls - 2][y_clls - 2].retrieve(p);
	    A;
	    Boundary_NE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    b.insert(b.first(), prtl);
	    c[x_clls- 1][y_clls - 1].insert(c[x_clls - 1][y_clls - 1].first(), prtl);
	}
    }
    if(xBr == 3 && yBu == 3) {
	c[x_clls - 1][y_clls - 1].clear();
	for (p = c[x_clls - 2][y_clls - 2].first();
	     !c[x_clls - 2][y_clls - 2].isEnd(p);
	     p = c[x_clls - 2][y_clls - 2].next(p)) {
	    prtl_old = c[x_clls - 2][y_clls - 2].retrieve(p);
	    B;
	    Boundary_NE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    b.insert(b.first(), prtl);
	    c[x_clls- 1][y_clls - 1].insert(c[x_clls - 1][y_clls - 1].first(), prtl);
	}
    }
    if(xBr == 1 && yBu == 1) {
	c[x_clls - 1][y_clls - 1].clear();
	for (p = c[Y][1].first();
	     !c[Y][1].isEnd(p);
	     p = c[Y][1].next(p)) {
	    prtl_old = c[Y][1].retrieve(p);
	    B;
	    Boundary_NE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    b.insert(b.first(), prtl);
	    c[x_clls- 1][y_clls - 1].insert(c[x_clls - 1][y_clls - 1].first(), prtl);
	}
    }
    if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	c[x_clls - 1][0].clear();
	for (p = c[x_clls - 2][1].first();
	     !c[x_clls - 2][1].isEnd(p);
	     p = c[x_clls - 2][1].next(p)) {
	    prtl_old = c[x_clls - 2][1].retrieve(p);
	    A;
	    Boundary_SE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    b.insert(b.first(), prtl);
	    c[x_clls - 1][0].insert(c[x_clls - 1][0].first(), prtl);
	}
    }
    if(xBr == 3 && yBd == 3) {
	c[x_clls - 1][0].clear();
	for (p = c[x_clls - 2][1].first();
	     !c[x_clls - 2][1].isEnd(p);
	     p = c[x_clls - 2][1].next(p)) {
	    prtl_old = c[x_clls - 2][1].retrieve(p);
	    B;
	    Boundary_SE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    b.insert(b.first(), prtl);
	    c[x_clls - 1][0].insert(c[x_clls - 1][0].first(), prtl);
	}
    }
    if(xBr == 1 && yBd == 1) {
	c[x_clls - 1][0].clear();
	for (p = c[Y][y_clls - 2].first();
	     !c[Y][y_clls - 2].isEnd(p);
	     p = c[Y][y_clls - 2].next(p)) {
	    prtl_old = c[Y][y_clls - 2].retrieve(p);
	    B;
	    Boundary_SE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    b.insert(b.first(), prtl);
	    c[x_clls - 1][0].insert(c[x_clls - 1][0].first(), prtl);
	}
    }
}
void Boundary::BoundaryCondition(ParticleManager *q)
{
    int i, j;
    int kb, ku, mb, mu;
    Particle *prtl;
    LIST *p;
    List **c;

    c = q->cell_lists;
    kb = 0; mb = x_clls;
    ku = 0; mu = x_clls;
    if(xBl == yBd) kb = 1;
    if(xBr == yBd) mb = x_clls - 1;
    if(xBl == yBu) ku = 1;
    if(xBr == yBu) mu = x_clls - 1;
    for(j = 1; j < y_clls - 1; j++) {
	if(xBl == 0 || xBl == 2) {
	    for (p = c[X][j].first();
		 !c[X][j].isEnd(p);
		 p = c[X][j].next(p)) {
		prtl = c[X][j].retrieve(p);
		C(0);
		Boundary_W(prtl);
	    }
	}
	if(xBl == 1 || xBl == 3) {
	    for (p = c[X][j].first();
		 !c[X][j].isEnd(p);
		 p = c[X][j].next(p)) {
		prtl = c[X][j].retrieve(p);
		C(1);
		Boundary_W(prtl);
	    }
	}
	if(xBr == 0 || xBr == 2) {
	    for (p = c[x_clls - 1][j].first();
		 !c[x_clls - 1][j].isEnd(p);
		 p = c[x_clls - 1][j].next(p)) {
		prtl = c[x_clls - 1][j].retrieve(p);
		C(0);
		Boundary_E(prtl);
	    }
	}
	if(xBr == 1 || xBr == 3) {
	    for (p = c[x_clls - 1][j].first();
		 !c[x_clls - 1][j].isEnd(p);
		 p = c[x_clls - 1][j].next(p)) {
		prtl = c[x_clls - 1][j].retrieve(p);
		C(1);
		Boundary_E(prtl);
	    }
	}
    }
    for(i = kb; i < mb; i++) {
	if(yBd == 0 || yBd == 2) {
	    for (p = c[i][0].first();
		 !c[i][0].isEnd(p);
		 p = c[i][0].next(p)) {
		prtl = c[i][0].retrieve(p);
		C(0);
		Boundary_S(prtl);
	    }
	}
	if(yBd == 1 || yBd == 3) {
	    for (p = c[i][0].first();
		 !c[i][0].isEnd(p);
		 p = c[i][0].next(p)) {
		prtl = c[i][0].retrieve(p);
		C(1);
		Boundary_S(prtl);
	    }
	}
    }
    for(i = ku; i < mu; i++) {
	if(yBu == 0 || yBu == 2) {
	    for (p = c[i][y_clls - 1].first();
		 !c[i][y_clls - 1].isEnd(p);
		 p = c[i][y_clls - 1].next(p)) {
		prtl = c[i][y_clls - 1].retrieve(p);
		C(0);
		Boundary_N(prtl);
	    }
	}
	if(yBu == 1 || yBu == 3) {
	    for (p = c[i][y_clls - 1].first();
		 !c[i][y_clls - 1].isEnd(p);
		 p = c[i][y_clls - 1].next(p)) {
		prtl = c[i][y_clls - 1].retrieve(p);
		C(1);
		Boundary_N(prtl);
	    }
	}
    }
    if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	for (p = c[X][0].first();
	     !c[X][0].isEnd(p);
	     p = c[X][0].next(p)) {
	    prtl = c[X][0].retrieve(p);
	    C(0);
	    Boundary_SW(prtl);
	}
    }
    if((xBl == 1 && yBd == 1) || (xBl == 3 && yBd == 3)) {
	for (p = c[X][0].first();
	     !c[X][0].isEnd(p);
	     p = c[X][0].next(p)) {
	    prtl = c[X][0].retrieve(p);
	    C(1);
	    Boundary_SW(prtl);
	}
    }
    if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	for (p = c[X][y_clls - 1].first();
	     !c[X][y_clls - 1].isEnd(p);
	     p = c[X][y_clls - 1].next(p)) {
	    prtl = c[X][y_clls - 1].retrieve(p);
	    C(0);
	    Boundary_NW(prtl);
	}
    }
    if((xBl == 1 && yBu == 1) || (xBl == 3 && yBu == 3)) {
	for (p = c[X][y_clls - 1].first();
	     !c[X][y_clls - 1].isEnd(p);
	     p = c[X][y_clls - 1].next(p)) {
	    prtl = c[X][y_clls - 1].retrieve(p);
	    C(1);
	    Boundary_NW(prtl);
	}
    }
    if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	for (p = c[x_clls - 1][y_clls - 1].first();
	     !c[x_clls - 1][y_clls - 1].isEnd(p);
	     p = c[x_clls - 1][y_clls - 1].next(p)) {
	    prtl = c[x_clls - 1][y_clls - 1].retrieve(p);
	    C(0);
	    Boundary_NE(prtl);
	}
    }
    if((xBr == 1 && yBu == 1) || (xBr == 3 && yBu == 3)) {
	for (p = c[x_clls - 1][y_clls - 1].first();
	     !c[x_clls - 1][y_clls - 1].isEnd(p);
	     p = c[x_clls - 1][y_clls - 1].next(p)) {
	    prtl = c[x_clls - 1][y_clls - 1].retrieve(p);
	    C(1);
	    Boundary_NE(prtl);
	}
    }
    if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	for (p = c[x_clls - 1][0].first();
	     !c[x_clls - 1][0].isEnd(p);
	     p = c[x_clls - 1][0].next(p)) {
	    prtl = c[x_clls - 1][0].retrieve(p);
	    C(0);
	    Boundary_SE(prtl);
	}
    }
    if((xBr == 1 && yBd == 1) || (xBr == 3 && yBd == 3)) {
	for (p = c[x_clls - 1][0].first();
	     !c[x_clls - 1][0].isEnd(p);
	     p = c[x_clls - 1][0].next(p)) {
	    prtl = c[x_clls - 1][0].retrieve(p);
	    C(1);
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
