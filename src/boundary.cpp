#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "err.h"
#include "particle.h"
#include "dllist.h"
#include "list.h"
#include "ilist.h"
#include "hydrodynamics.h"
#include "initiation.h"
#include "particlemanager.h"
#include "material.h"
#include "boundary.h"
enum {X, Y};
#define A prtl = particle_mirror(prtl_old, &hydro->materials[0])
#define B prtl = particle_image(prtl_old)
#define C(t) do {                               \
	if (prtl->rl_prtl == NULL)		\
	    abort();				\
	particle_copy(prtl, prtl->rl_prtl, t);	\
    } while (0)
#define LIST ListNode

#define LOOP(q, l) for (p = l.first();			       \
    			!list_isEnd(&l, p) && (q = l.retrieve(p), 1);	\
			p = l.next(p))
#define INSERT(q, l) l.insert(l.first(), q)
#define CLEAR(l) l.clear()
#define CLEAR_DATA(l) l.clear_data()

Boundary::Boundary(Initiation *ini, Hydrodynamics *hydro, ParticleManager *q)
{
    int n;
    char Key_word[FILENAME_MAX];
    FILE *f;
    box_size[X] = ini->box_size[X];
    box_size[Y] = ini->box_size[Y];
    x_clls = q->x_clls;
    y_clls = q->y_clls;
    f = fopen(ini->inputfile, "r");
    if (!f)
	ABORT(("can't open '%s'\n", ini->inputfile));
    while (fscanf(f, "%s", Key_word) == 1)
	if(!strcmp(Key_word, "BOUNDARY")) {
	    n = fscanf(f, "%d %lf %lf %d %lf %lf %d %lf %lf %d %lf %lf",
		   &xBl, &UxBl[X], &UxBl[Y],
		   &xBr, &UxBr[X], &UxBr[Y],
		   &yBd, &UyBd[X], &UyBd[Y],
		   &yBu, &UyBu[X], &UyBu[Y]);
	    if (n != 3*4)
		ABORT(("can't read BOUNDARY keyword (n = %d)", n));
	}
    fclose(f);
    printf("The left, right, lower and upper boundary %d %d %d %d\n", xBl, xBr, yBd, yBu);
    puts("0: wall boundary condition");
    puts("1: perodic boundary condition");
    puts("2: free slip wall boundary condition");
    puts("3: symmetry boundary condition");
    BuildBoundaryParticles(q, hydro);
}
void Boundary::BuildBoundaryParticles(ParticleManager *q, Hydrodynamics *hydro)
{
    int i, j;
    Particle *prtl, *prtl_old;
    int kb, ku, mb, mu;
    List **c;
    LIST *p;

    c = q->cell_lists;
    CLEAR_DATA(b);
    kb = 0; mb = x_clls;
    ku = 0; mu = x_clls;
    if(xBl == yBd) kb = 1;
    if(xBr == yBd) mb = x_clls - 1;
    if(xBl == yBu) ku = 1;
    if(xBr == yBu) mu = x_clls - 1;
    for(j = 1; j < y_clls - 1; j++) {
	CLEAR(c[X][j]);
	if(xBl == 0 || xBl == 2) {
	    LOOP(prtl_old, c[Y][j]) {
		A;
		Boundary_W(prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		INSERT(prtl, b);
		INSERT(prtl, c[X][j]);
	    }
	}
	if(xBl == 3) {
	    LOOP(prtl_old, c[Y][j]) {
		B;
		Boundary_W(prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		INSERT(prtl, b);
		INSERT(prtl, c[X][j]);
	    }
	}
	if(xBl == 1) {
	    LOOP(prtl_old, c[x_clls - 2][j]) {
		B;
		Boundary_W(prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		INSERT(prtl, b);
		INSERT(prtl, c[X][j]);
	    }
	}
	CLEAR(c[x_clls - 1][j]);
	if(xBr == 0 || xBr == 2) {
	    LOOP(prtl_old, c[x_clls - 2][j]) {
		A;
		Boundary_E(prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		INSERT(prtl, b);
		INSERT(prtl, c[x_clls - 1][j]);
	    }
	}
	if(xBr == 3) {
	    LOOP(prtl_old, c[x_clls - 2][j]) {
		B;
		Boundary_E(prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		INSERT(prtl, b);
		INSERT(prtl, c[x_clls - 1][j]);
	    }
	}
	if(xBr == 1) {
	    LOOP(prtl_old, c[Y][j]) {
		B;
		Boundary_E(prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		INSERT(prtl, b);
		INSERT(prtl, c[x_clls - 1][j]);
	    }
	}
    }
    for(i = kb; i < mb; i++) {
	CLEAR(c[i][0]);
	if(yBd == 0 || yBd == 2) {
	    LOOP(prtl_old, c[i][1]) {
		A;
		Boundary_S(prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		INSERT(prtl, b);
		INSERT(prtl, c[i][0]);
	    }
	}
	if(yBd == 3) {
	    LOOP(prtl_old, c[i][1]) {
		B;
		Boundary_S(prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		INSERT(prtl, b);
		INSERT(prtl, c[i][0]);
	    }
	}
	if(yBd == 1) {
	    LOOP(prtl_old, c[i][y_clls - 2]) {
		B;
		Boundary_S(prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		INSERT(prtl, b);
		INSERT(prtl, c[i][0]);
	    }
	}
    }
    for(i = ku; i < mu; i++) {
	CLEAR(c[i][y_clls - 1]);
	if(yBu == 0 || yBu == 2) {
	    LOOP(prtl_old, c[i][y_clls - 2]) {
		A;
		Boundary_N(prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		INSERT(prtl, b);
		INSERT(prtl, c[i][y_clls - 1]);
	    }
	}
	if(yBu == 3) {
	    LOOP(prtl_old, c[i][y_clls - 2]) {
		B;
		Boundary_N(prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		INSERT(prtl, b);
		INSERT(prtl, c[i][y_clls - 1]);
	    }
	}
	if(yBu == 1) {
	    LOOP(prtl_old, c[i][1]) {
		B;
		Boundary_N(prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		INSERT(prtl, b);
		INSERT(prtl, c[i][y_clls - 1]);
	    }
	}
    }
    if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	CLEAR(c[X][0]);
	LOOP(prtl_old, c[Y][1]) {
	    A;
	    Boundary_SW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    INSERT(prtl, b);
	    INSERT(prtl, c[X][0]);
	}
    }
    if(xBl == 3 && yBd == 3) {
	CLEAR(c[X][0]);
	LOOP(prtl_old, c[Y][1]) {
	    B;
	    Boundary_SW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    INSERT(prtl, b);
	    INSERT(prtl, c[X][0]);
	}
    }
    if(xBl == 1 && yBd == 1) {
	CLEAR(c[X][0]);
	LOOP(prtl_old, c[x_clls - 2][y_clls - 2]) {
	    B;
	    Boundary_SW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    INSERT(prtl, b);
	    INSERT(prtl, c[X][0]);
	}
    }
    if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	CLEAR(c[X][y_clls - 1]);
	LOOP(prtl_old, c[Y][y_clls - 2]) {
	    A;
	    Boundary_NW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, b);
	    INSERT(prtl, c[X][y_clls - 1]);
	}
    }
    if(xBl == 3 && yBu == 3) {
	CLEAR(c[X][y_clls - 1]);
	LOOP(prtl_old, c[Y][y_clls - 2]) {
	    B;
	    Boundary_NW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, b);
	    INSERT(prtl, c[X][y_clls - 1]);
	}
    }
    if(xBl == 1 && yBu == 1) {
	CLEAR(c[X][y_clls - 1]);
	LOOP(prtl_old, c[x_clls - 2][1]) {
	    B;
	    Boundary_NW(prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, b);
	    INSERT(prtl, c[X][y_clls - 1]);
	}
    }
    if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	CLEAR(c[x_clls - 1][y_clls - 1]);
	LOOP(prtl_old, c[x_clls - 2][y_clls - 2]) {
	    A;
	    Boundary_NE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, b);
	    INSERT(prtl, c[x_clls - 1][y_clls - 1]);
	}
    }
    if(xBr == 3 && yBu == 3) {
	CLEAR(c[x_clls - 1][y_clls - 1]);
	LOOP(prtl_old, c[x_clls - 2][y_clls - 2]) {
	    B;
	    Boundary_NE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, b);
	    INSERT(prtl, c[x_clls - 1][y_clls - 1]);
	}
    }
    if(xBr == 1 && yBu == 1) {
	CLEAR(c[x_clls - 1][y_clls - 1]);
	LOOP(prtl_old, c[Y][1]) {
	    B;
	    Boundary_NE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, b);
	    INSERT(prtl, c[x_clls - 1][y_clls - 1]);
	}
    }
    if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	CLEAR(c[x_clls - 1][0]);
	LOOP(prtl_old, c[x_clls - 2][1]) {
	    A;
	    Boundary_SE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    INSERT(prtl, b);
	    INSERT(prtl, c[x_clls - 1][0]);
	}
    }
    if(xBr == 3 && yBd == 3) {
	CLEAR(c[x_clls - 1][0]);
	LOOP(prtl_old, c[x_clls - 2][1]) {
	    B;
	    Boundary_SE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    INSERT(prtl, b);
	    INSERT(prtl, c[x_clls - 1][0]);
	}
    }
    if(xBr == 1 && yBd == 1) {
	CLEAR(c[x_clls - 1][0]);
	LOOP(prtl_old, c[Y][y_clls - 2]) {
	    B;
	    Boundary_SE(prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    INSERT(prtl, b);
	    INSERT(prtl, c[x_clls - 1][0]);
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
	    LOOP(prtl, c[X][j]) {
		C(0);
		Boundary_W(prtl);
	    }
	}
	if(xBl == 1 || xBl == 3) {
	    LOOP(prtl, c[X][j]) {
		C(1);
		Boundary_W(prtl);
	    }
	}
	if(xBr == 0 || xBr == 2) {
	    LOOP(prtl, c[x_clls - 1][j]) {
		C(0);
		Boundary_E(prtl);
	    }
	}
	if(xBr == 1 || xBr == 3) {
	    LOOP(prtl, c[x_clls - 1][j]) {
		C(1);
		Boundary_E(prtl);
	    }
	}
    }
    for(i = kb; i < mb; i++) {
	if(yBd == 0 || yBd == 2) {
	    LOOP(prtl, c[i][0]) {
		C(0);
		Boundary_S(prtl);
	    }
	}
	if(yBd == 1 || yBd == 3) {
	    LOOP(prtl, c[i][0]) {
		C(1);
		Boundary_S(prtl);
	    }
	}
    }
    for(i = ku; i < mu; i++) {
	if(yBu == 0 || yBu == 2) {
	    LOOP(prtl, c[i][y_clls - 1]) {
		C(0);
		Boundary_N(prtl);
	    }
	}
	if(yBu == 1 || yBu == 3) {
	    LOOP(prtl, c[i][y_clls - 1]) {
		C(1);
		Boundary_N(prtl);
	    }
	}
    }
    if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	LOOP(prtl, c[X][0]) {
	    C(0);
	    Boundary_SW(prtl);
	}
    }
    if((xBl == 1 && yBd == 1) || (xBl == 3 && yBd == 3)) {
	LOOP(prtl, c[X][0]) {
	    C(1);
	    Boundary_SW(prtl);
	}
    }
    if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	LOOP(prtl, c[X][y_clls - 1]) {
	    C(0);
	    Boundary_NW(prtl);
	}
    }
    if((xBl == 1 && yBu == 1) || (xBl == 3 && yBu == 3)) {
	LOOP(prtl, c[X][y_clls - 1]) {
	    C(1);
	    Boundary_NW(prtl);
	}
    }
    if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	LOOP(prtl, c[x_clls - 1][y_clls - 1]) {
	    C(0);
	    Boundary_NE(prtl);
	}
    }
    if((xBr == 1 && yBu == 1) || (xBr == 3 && yBu == 3)) {
	LOOP(prtl, c[x_clls - 1][y_clls - 1]) {
	    C(1);
	    Boundary_NE(prtl);
	}
    }
    if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	LOOP(prtl, c[x_clls - 1][0]) {
	    C(0);
	    Boundary_SE(prtl);
	}
    }
    if((xBr == 1 && yBd == 1) || (xBr == 3 && yBd == 3)) {
	LOOP(prtl, c[x_clls - 1][0]) {
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
int boundary_check(Boundary *q, Hydrodynamics *hydro)
{
    LIST *p;
    Particle *prtl;
    double *box_size;

    box_size = q->box_size;
    LOOP(prtl, hydro->particle_list) {
	if(fabs(prtl->R[X]) >= 2.0*box_size[X] || fabs(prtl->R[Y]) >= 2.0*box_size[Y])
	    ABORT(("run away particle"));
	if(prtl->bd == 0) {
	    if(prtl->R[X] < 0.0) {
		switch(q->xBl) {
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
		switch(q->xBr) {
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
		switch(q->yBd) {
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
		switch(q->yBu) {
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
    return 0;
}
