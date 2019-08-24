#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "err.h"
#include "particle.h"
#include "list.h"
#include "initiation.h"
#include "material.h"
#include "boundary.h"
#include "macro.h"
enum {X, Y};
#define A prtl = particle_mirror(prtl_old, mtl)
#define B prtl = particle_image(prtl_old)
#define C(t) do {                               \
	if (prtl->rl_prtl == NULL)		\
	    abort();				\
	particle_copy(prtl, prtl->rl_prtl, t);	\
    } while (0)
#define LIST ListNode

Boundary::Boundary(Initiation *ini, Material *mtl, List ***c)
{
    int n;
    char Key_word[FILENAME_MAX];
    FILE *f;
    b = list_ini();
    box_size[X] = ini->box_size[X];
    box_size[Y] = ini->box_size[Y];
    x_clls = ini->x_cells + 2;
    y_clls = ini->y_cells + 2;
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
    BuildBoundaryParticles(c, mtl);
}
void Boundary::BuildBoundaryParticles(List ***c, Material *mtl)
{
    int i, j;
    Particle *prtl, *prtl_old;
    int kb, ku, mb, mu;
    LIST *p;

    CLEAR_DATA(*b);
    kb = 0; mb = x_clls;
    ku = 0; mu = x_clls;
    if(xBl == yBd) kb = 1;
    if(xBr == yBd) mb = x_clls - 1;
    if(xBl == yBu) ku = 1;
    if(xBr == yBu) mu = x_clls - 1;
    for(j = 1; j < y_clls - 1; j++) {
	CLEAR(*c[X][j]);
	if(xBl == 0 || xBl == 2) {
	    LOOP(prtl_old, *c[Y][j]) {
		A;
		boundary_w(this, prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		INSERT(prtl, *b);
		INSERT(prtl, *c[X][j]);
	    }
	}
	if(xBl == 3) {
	    LOOP(prtl_old, *c[Y][j]) {
		B;
		boundary_w(this, prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		INSERT(prtl, *b);
		INSERT(prtl, *c[X][j]);
	    }
	}
	if(xBl == 1) {
	    LOOP(prtl_old, *c[x_clls - 2][j]) {
		B;
		boundary_w(this, prtl);
		prtl->cell_i = 0; prtl->cell_j = j;
		INSERT(prtl, *b);
		INSERT(prtl, *c[X][j]);
	    }
	}
	CLEAR(*c[x_clls - 1][j]);
	if(xBr == 0 || xBr == 2) {
	    LOOP(prtl_old, *c[x_clls - 2][j]) {
		A;
		boundary_e(this, prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		INSERT(prtl, *b);
		INSERT(prtl, *c[x_clls - 1][j]);
	    }
	}
	if(xBr == 3) {
	    LOOP(prtl_old, *c[x_clls - 2][j]) {
		B;
		boundary_e(this, prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		INSERT(prtl, *b);
		INSERT(prtl, *c[x_clls - 1][j]);
	    }
	}
	if(xBr == 1) {
	    LOOP(prtl_old, *c[Y][j]) {
		B;
		boundary_e(this, prtl);
		prtl->cell_i = x_clls - 1; prtl->cell_j = j;
		INSERT(prtl, *b);
		INSERT(prtl, *c[x_clls - 1][j]);
	    }
	}
    }
    for(i = kb; i < mb; i++) {
	CLEAR(*c[i][0]);
	if(yBd == 0 || yBd == 2) {
	    LOOP(prtl_old, *c[i][1]) {
		A;
		boundary_s(this, prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		INSERT(prtl, *b);
		INSERT(prtl, *c[i][0]);
	    }
	}
	if(yBd == 3) {
	    LOOP(prtl_old, *c[i][1]) {
		B;
		boundary_s(this, prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		INSERT(prtl, *b);
		INSERT(prtl, *c[i][0]);
	    }
	}
	if(yBd == 1) {
	    LOOP(prtl_old, *c[i][y_clls - 2]) {
		B;
		boundary_s(this, prtl);
		prtl->cell_i = i; prtl->cell_j = 0;
		INSERT(prtl, *b);
		INSERT(prtl, *c[i][0]);
	    }
	}
    }
    for(i = ku; i < mu; i++) {
	CLEAR(*c[i][y_clls - 1]);
	if(yBu == 0 || yBu == 2) {
	    LOOP(prtl_old, *c[i][y_clls - 2]) {
		A;
		boundary_n(this, prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		INSERT(prtl, *b);
		INSERT(prtl, *c[i][y_clls - 1]);
	    }
	}
	if(yBu == 3) {
	    LOOP(prtl_old, *c[i][y_clls - 2]) {
		B;
		boundary_n(this, prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		INSERT(prtl, *b);
		INSERT(prtl, *c[i][y_clls - 1]);
	    }
	}
	if(yBu == 1) {
	    LOOP(prtl_old, *c[i][1]) {
		B;
		boundary_n(this, prtl);
		prtl->cell_i = i; prtl->cell_j = y_clls - 1;
		INSERT(prtl, *b);
		INSERT(prtl, *c[i][y_clls - 1]);
	    }
	}
    }
    if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	CLEAR(*c[X][0]);
	LOOP(prtl_old, *c[Y][1]) {
	    A;
	    boundary_sw(this, prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[X][0]);
	}
    }
    if(xBl == 3 && yBd == 3) {
	CLEAR(*c[X][0]);
	LOOP(prtl_old, *c[Y][1]) {
	    B;
	    boundary_sw(this, prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[X][0]);
	}
    }
    if(xBl == 1 && yBd == 1) {
	CLEAR(*c[X][0]);
	LOOP(prtl_old, *c[x_clls - 2][y_clls - 2]) {
	    B;
	    boundary_sw(this, prtl);
	    prtl->cell_i = 0; prtl->cell_j = 0;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[X][0]);
	}
    }
    if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	CLEAR(*c[X][y_clls - 1]);
	LOOP(prtl_old, *c[Y][y_clls - 2]) {
	    A;
	    boundary_nw(this, prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[X][y_clls - 1]);
	}
    }
    if(xBl == 3 && yBu == 3) {
	CLEAR(*c[X][y_clls - 1]);
	LOOP(prtl_old, *c[Y][y_clls - 2]) {
	    B;
	    boundary_nw(this, prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[X][y_clls - 1]);
	}
    }
    if(xBl == 1 && yBu == 1) {
	CLEAR(*c[X][y_clls - 1]);
	LOOP(prtl_old, *c[x_clls - 2][1]) {
	    B;
	    boundary_nw(this, prtl);
	    prtl->cell_i = 0; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[X][y_clls - 1]);
	}
    }
    if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	CLEAR(*c[x_clls - 1][y_clls - 1]);
	LOOP(prtl_old, *c[x_clls - 2][y_clls - 2]) {
	    A;
	    boundary_ne(this, prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[x_clls - 1][y_clls - 1]);
	}
    }
    if(xBr == 3 && yBu == 3) {
	CLEAR(*c[x_clls - 1][y_clls - 1]);
	LOOP(prtl_old, *c[x_clls - 2][y_clls - 2]) {
	    B;
	    boundary_ne(this, prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[x_clls - 1][y_clls - 1]);
	}
    }
    if(xBr == 1 && yBu == 1) {
	CLEAR(*c[x_clls - 1][y_clls - 1]);
	LOOP(prtl_old, *c[Y][1]) {
	    B;
	    boundary_ne(this, prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = y_clls - 1;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[x_clls - 1][y_clls - 1]);
	}
    }
    if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	CLEAR(*c[x_clls - 1][0]);
	LOOP(prtl_old, *c[x_clls - 2][1]) {
	    A;
	    boundary_se(this, prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[x_clls - 1][0]);
	}
    }
    if(xBr == 3 && yBd == 3) {
	CLEAR(*c[x_clls - 1][0]);
	LOOP(prtl_old, *c[x_clls - 2][1]) {
	    B;
	    boundary_se(this, prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[x_clls - 1][0]);
	}
    }
    if(xBr == 1 && yBd == 1) {
	CLEAR(*c[x_clls - 1][0]);
	LOOP(prtl_old, *c[Y][y_clls - 2]) {
	    B;
	    boundary_se(this, prtl);
	    prtl->cell_i = x_clls - 1; prtl->cell_j = 0;
	    INSERT(prtl, *b);
	    INSERT(prtl, *c[x_clls - 1][0]);
	}
    }
}
void Boundary::BoundaryCondition(List ***c)
{
    int i, j;
    int kb, ku, mb, mu;
    Particle *prtl;
    LIST *p;

    kb = 0; mb = x_clls;
    ku = 0; mu = x_clls;
    if(xBl == yBd) kb = 1;
    if(xBr == yBd) mb = x_clls - 1;
    if(xBl == yBu) ku = 1;
    if(xBr == yBu) mu = x_clls - 1;
    for(j = 1; j < y_clls - 1; j++) {
	if(xBl == 0 || xBl == 2) {
	    LOOP(prtl, *c[X][j]) {
		C(0);
		boundary_w(this, prtl);
	    }
	}
	if(xBl == 1 || xBl == 3) {
	    LOOP(prtl, *c[X][j]) {
		C(1);
		boundary_w(this, prtl);
	    }
	}
	if(xBr == 0 || xBr == 2) {
	    LOOP(prtl, *c[x_clls - 1][j]) {
		C(0);
		boundary_e(this, prtl);
	    }
	}
	if(xBr == 1 || xBr == 3) {
	    LOOP(prtl, *c[x_clls - 1][j]) {
		C(1);
		boundary_e(this, prtl);
	    }
	}
    }
    for(i = kb; i < mb; i++) {
	if(yBd == 0 || yBd == 2) {
	    LOOP(prtl, *c[i][0]) {
		C(0);
		boundary_s(this, prtl);
	    }
	}
	if(yBd == 1 || yBd == 3) {
	    LOOP(prtl, *c[i][0]) {
		C(1);
		boundary_s(this, prtl);
	    }
	}
    }
    for(i = ku; i < mu; i++) {
	if(yBu == 0 || yBu == 2) {
	    LOOP(prtl, *c[i][y_clls - 1]) {
		C(0);
		boundary_n(this, prtl);
	    }
	}
	if(yBu == 1 || yBu == 3) {
	    LOOP(prtl, *c[i][y_clls - 1]) {
		C(1);
		boundary_n(this, prtl);
	    }
	}
    }
    if((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	LOOP(prtl, *c[X][0]) {
	    C(0);
	    boundary_sw(this, prtl);
	}
    }
    if((xBl == 1 && yBd == 1) || (xBl == 3 && yBd == 3)) {
	LOOP(prtl, *c[X][0]) {
	    C(1);
	    boundary_sw(this, prtl);
	}
    }
    if((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	LOOP(prtl, *c[X][y_clls - 1]) {
	    C(0);
	    boundary_nw(this, prtl);
	}
    }
    if((xBl == 1 && yBu == 1) || (xBl == 3 && yBu == 3)) {
	LOOP(prtl, *c[X][y_clls - 1]) {
	    C(1);
	    boundary_nw(this, prtl);
	}
    }
    if((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	LOOP(prtl, *c[x_clls - 1][y_clls - 1]) {
	    C(0);
	    boundary_ne(this, prtl);
	}
    }
    if((xBr == 1 && yBu == 1) || (xBr == 3 && yBu == 3)) {
	LOOP(prtl, *c[x_clls - 1][y_clls - 1]) {
	    C(1);
	    boundary_ne(this, prtl);
	}
    }
    if((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	LOOP(prtl, *c[x_clls - 1][0]) {
	    C(0);
	    boundary_se(this, prtl);
	}
    }
    if((xBr == 1 && yBd == 1) || (xBr == 3 && yBd == 3)) {
	LOOP(prtl, *c[x_clls - 1][0]) {
	    C(1);
	    boundary_se(this, prtl);
	}
    }
}
int boundary_w(Boundary *q, Particle *prtl)
{
    switch(q->xBl) {
    case 0:
	prtl->R[X] = - prtl->R[X];
	prtl->U[X] = q->UxBl[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] - q->box_size[X];
	break;
    case 2:
	prtl->R[X] = - prtl->R[X];
	prtl->U[X] = q->UxBl[X]*2.0 - prtl->U[X];
	break;
    case 3:
	prtl->R[X] = - prtl->R[X];
	prtl->U[X] = q->UxBl[X]*2.0 - prtl->U[X];
	prtl->del_phi[X] = - prtl->del_phi[X];
	break;
    }
    return 0;
}
int boundary_e(Boundary *q, Particle *prtl)
{
    switch(q->xBr) {
    case 0:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->U[X] = q->UxBr[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] + q->box_size[X];
	break;
    case 2:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->U[X] = q->UxBr[X]*2.0 - prtl->U[X];
	break;
    case 3:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->U[X] = q->UxBr[X]*2.0 - prtl->U[X];
	prtl->del_phi[X] = - prtl->del_phi[X];
	break;
    }
    return 0;
}
int boundary_s(Boundary *q, Particle *prtl)
{
    switch(q->yBd) {
    case 0:
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UyBd[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[Y] = prtl->R[Y] - q->box_size[Y];
	break;
    case 2:
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[Y] = q->UyBd[Y]*2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[Y] = q->UyBd[Y]*2.0 - prtl->U[Y];
	prtl->del_phi[Y] = - prtl->del_phi[Y];
	break;
    }
    return 0;
}
int boundary_n(Boundary *q, Particle *prtl)
{
    switch(q->yBu) {
    case 0:
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UyBu[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[Y] = prtl->R[Y] + q->box_size[Y];
	break;
    case 2:
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[Y] = q->UyBu[Y]*2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[Y] = q->UyBu[Y]*2.0 - prtl->U[Y];
	prtl->del_phi[Y] = - prtl->del_phi[Y];
	break;
    }
    return 0;
}
int boundary_sw(Boundary *q, Particle *prtl)
{
    switch(q->xBl) {
    case 0:
	prtl->R[X] = - prtl->R[X];
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] - q->box_size[X];
	prtl->R[Y] = prtl->R[Y] - q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = - prtl->R[X];
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = - prtl->R[X];
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	prtl->del_phi[X] = - prtl->del_phi[X];
	prtl->del_phi[Y] = - prtl->del_phi[Y];
	break;
    }
    return 0;
}
int boundary_nw(Boundary *q, Particle *prtl)
{
    switch(q->xBl) {
    case 0:
	prtl->R[X] = - prtl->R[X];
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] - q->box_size[X];
	prtl->R[Y] = prtl->R[Y] + q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = - prtl->R[X];
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = - prtl->R[X];
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y]*2.0 - prtl->U[Y];
	prtl->del_phi[X] = - prtl->del_phi[X];
	prtl->del_phi[Y] = - prtl->del_phi[Y];
	break;
    }
    return 0;
}
int boundary_ne(Boundary *q, Particle *prtl)
{
    switch(q->xBr) {
    case 0:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] + q->box_size[X];
	prtl->R[Y] = prtl->R[Y] + q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->R[Y] = q->box_size[Y]*2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	prtl->del_phi[X] = - prtl->del_phi[X];
	prtl->del_phi[Y] = - prtl->del_phi[Y];
	break;
    }
    return 0;
}
int boundary_se(Boundary *q, Particle *prtl)
{
    switch(q->xBr) {
    case 0:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] + q->box_size[X];
	prtl->R[Y] = prtl->R[Y] - q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = q->box_size[X]*2.0 - prtl->R[X];
	prtl->R[Y] = - prtl->R[Y];
	prtl->U[X] = q->UyBd[X]*2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y]*2.0 - prtl->U[Y];
	prtl->del_phi[X] = - prtl->del_phi[X];
	prtl->del_phi[Y] = - prtl->del_phi[Y];
	break;
    }
    return 0;
}
int boundary_check(Boundary *q, List *list)
{
    LIST *p;
    Particle *prtl;
    double *box_size;

    box_size = q->box_size;
    LOOP(prtl, *list) {
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

Boundary::~Boundary()
{
    list_fin(b);
}
