#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>
#include "err.h"
#include "particle.h"
#include "list.h"
#include "ini.h"
#include "material.h"
#include "boundary.h"
#include "macro.h"
enum { X, Y };

#define A prtl = particle_mirror(prtl_old, mtl)
#define B prtl = particle_image(prtl_old)
#define C(t) do {                               \
	if (prtl->rl_prtl == NULL)		\
	    abort();				\
	particle_copy(prtl, prtl->rl_prtl, t);	\
    } while (0)
#define LIST struct ListNode
struct Boundary {
    double box_size[2];
    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    int xBl;
    int xBr;
    int x_clls;
    int yBd;
    int yBu;
    int y_clls;
    struct List *b;
};

static int boundary_w(struct Boundary *, struct Particle *);
static int boundary_e(struct Boundary *, struct Particle *);
static int boundary_s(struct Boundary *, struct Particle *);
static int boundary_n(struct Boundary *, struct Particle *);
static int boundary_sw(struct Boundary *, struct Particle *);
static int boundary_se(struct Boundary *, struct Particle *);
static int boundary_nw(struct Boundary *, struct Particle *);
static int boundary_ne(struct Boundary *, struct Particle *);

struct Boundary *
boundary_ini(struct Ini *ini)
{
    int n;
    char Key_word[FILENAME_MAX];
    FILE *f;
    struct Boundary *q;

    q = malloc(sizeof(*q));
    if (q == NULL)
	return q;

    q->b = list_ini();
    q->box_size[X] = ini->box_size[X];
    q->box_size[Y] = ini->box_size[Y];
    q->x_clls = ini->x_cells + 2;
    q->y_clls = ini->y_cells + 2;
    f = fopen(ini->inputfile, "r");
    if (!f)
	ABORT(("can't open '%s'\n", ini->inputfile));
    while (fscanf(f, "%s", Key_word) == 1)
	if (!strcmp(Key_word, "BOUNDARY")) {
	    n = fscanf(f, "%d %lf %lf %d %lf %lf %d %lf %lf %d %lf %lf",
		       &q->xBl, &q->UxBl[X], &q->UxBl[Y],
		       &q->xBr, &q->UxBr[X], &q->UxBr[Y],
		       &q->yBd, &q->UyBd[X], &q->UyBd[Y],
		       &q->yBu, &q->UyBu[X], &q->UyBu[Y]);
	    if (n != 3 * 4)
		ABORT(("can't read BOUNDARY keyword (n = %d)", n));
	}
    fclose(f);
    printf("The left, right, lower and upper boundary %d %d %d %d\n",
	   q->xBl, q->xBr, q->yBd, q->yBu);
    puts("0: wall boundary condition");
    puts("1: perodic boundary condition");
    puts("2: free slip wall boundary condition");
    puts("3: symmetry boundary condition");
    return q;
}

int
boundary_build(struct Boundary *q, struct List ***c, struct Material *mtl)
{
    int i, j;
    struct Particle *prtl, *prtl_old;
    int kb, ku, mb, mu;
    LIST *p;
    int x_clls;
    int y_clls;
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    struct List *b;

    x_clls = q->x_clls;
    y_clls = q->y_clls;
    xBl = q->xBl;
    xBr = q->xBr;
    yBd = q->yBd;
    yBu = q->yBu;
    b = q->b;

    LOOP_P(prtl, b) {
	particle_fin(prtl);
    }
    list_clear(b);

    kb = 0;
    mb = x_clls;
    ku = 0;
    mu = x_clls;
    if (xBl == yBd)
	kb = 1;
    if (xBr == yBd)
	mb = x_clls - 1;
    if (xBl == yBu)
	ku = 1;
    if (xBr == yBu)
	mu = x_clls - 1;
    for (j = 1; j < y_clls - 1; j++) {
	list_clear(c[X][j]);
	if (xBl == 0 || xBl == 2) {
	    LOOP_P(prtl_old, c[Y][j]) {
		A;
		boundary_w(q, prtl);
		prtl->cell_i = 0;
		prtl->cell_j = j;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[X][j]);
	    }
	}
	if (xBl == 3) {
	    LOOP_P(prtl_old, c[Y][j]) {
		B;
		boundary_w(q, prtl);
		prtl->cell_i = 0;
		prtl->cell_j = j;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[X][j]);
	    }
	}
	if (xBl == 1) {
	    LOOP_P(prtl_old, c[x_clls - 2][j]) {
		B;
		boundary_w(q, prtl);
		prtl->cell_i = 0;
		prtl->cell_j = j;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[X][j]);
	    }
	}
	list_clear(c[x_clls - 1][j]);
	if (xBr == 0 || xBr == 2) {
	    LOOP_P(prtl_old, c[x_clls - 2][j]) {
		A;
		boundary_e(q, prtl);
		prtl->cell_i = x_clls - 1;
		prtl->cell_j = j;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[x_clls - 1][j]);
	    }
	}
	if (xBr == 3) {
	    LOOP_P(prtl_old, c[x_clls - 2][j]) {
		B;
		boundary_e(q, prtl);
		prtl->cell_i = x_clls - 1;
		prtl->cell_j = j;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[x_clls - 1][j]);
	    }
	}
	if (xBr == 1) {
	    LOOP_P(prtl_old, c[Y][j]) {
		B;
		boundary_e(q, prtl);
		prtl->cell_i = x_clls - 1;
		prtl->cell_j = j;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[x_clls - 1][j]);
	    }
	}
    }
    for (i = kb; i < mb; i++) {
	list_clear(c[i][0]);
	if (yBd == 0 || yBd == 2) {
	    LOOP_P(prtl_old, c[i][1]) {
		A;
		boundary_s(q, prtl);
		prtl->cell_i = i;
		prtl->cell_j = 0;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[i][0]);
	    }
	}
	if (yBd == 3) {
	    LOOP_P(prtl_old, c[i][1]) {
		B;
		boundary_s(q, prtl);
		prtl->cell_i = i;
		prtl->cell_j = 0;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[i][0]);
	    }
	}
	if (yBd == 1) {
	    LOOP_P(prtl_old, c[i][y_clls - 2]) {
		B;
		boundary_s(q, prtl);
		prtl->cell_i = i;
		prtl->cell_j = 0;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[i][0]);
	    }
	}
    }
    for (i = ku; i < mu; i++) {
	list_clear(c[i][y_clls - 1]);
	if (yBu == 0 || yBu == 2) {
	    LOOP_P(prtl_old, c[i][y_clls - 2]) {
		A;
		boundary_n(q, prtl);
		prtl->cell_i = i;
		prtl->cell_j = y_clls - 1;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[i][y_clls - 1]);
	    }
	}
	if (yBu == 3) {
	    LOOP_P(prtl_old, c[i][y_clls - 2]) {
		B;
		boundary_n(q, prtl);
		prtl->cell_i = i;
		prtl->cell_j = y_clls - 1;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[i][y_clls - 1]);
	    }
	}
	if (yBu == 1) {
	    LOOP_P(prtl_old, c[i][1]) {
		B;
		boundary_n(q, prtl);
		prtl->cell_i = i;
		prtl->cell_j = y_clls - 1;
		INSERT_P(prtl, b);
		INSERT_P(prtl, c[i][y_clls - 1]);
	    }
	}
    }
    if ((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	list_clear(c[X][0]);
	LOOP_P(prtl_old, c[Y][1]) {
	    A;
	    boundary_sw(q, prtl);
	    prtl->cell_i = 0;
	    prtl->cell_j = 0;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[X][0]);
	}
    }
    if (xBl == 3 && yBd == 3) {
	list_clear(c[X][0]);
	LOOP_P(prtl_old, c[Y][1]) {
	    B;
	    boundary_sw(q, prtl);
	    prtl->cell_i = 0;
	    prtl->cell_j = 0;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[X][0]);
	}
    }
    if (xBl == 1 && yBd == 1) {
	list_clear(c[X][0]);
	LOOP_P(prtl_old, c[x_clls - 2][y_clls - 2]) {
	    B;
	    boundary_sw(q, prtl);
	    prtl->cell_i = 0;
	    prtl->cell_j = 0;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[X][0]);
	}
    }
    if ((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	list_clear(c[X][y_clls - 1]);
	LOOP_P(prtl_old, c[Y][y_clls - 2]) {
	    A;
	    boundary_nw(q, prtl);
	    prtl->cell_i = 0;
	    prtl->cell_j = y_clls - 1;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[X][y_clls - 1]);
	}
    }
    if (xBl == 3 && yBu == 3) {
	list_clear(c[X][y_clls - 1]);
	LOOP_P(prtl_old, c[Y][y_clls - 2]) {
	    B;
	    boundary_nw(q, prtl);
	    prtl->cell_i = 0;
	    prtl->cell_j = y_clls - 1;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[X][y_clls - 1]);
	}
    }
    if (xBl == 1 && yBu == 1) {
	list_clear(c[X][y_clls - 1]);
	LOOP_P(prtl_old, c[x_clls - 2][1]) {
	    B;
	    boundary_nw(q, prtl);
	    prtl->cell_i = 0;
	    prtl->cell_j = y_clls - 1;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[X][y_clls - 1]);
	}
    }
    if ((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	list_clear(c[x_clls - 1][y_clls - 1]);
	LOOP_P(prtl_old, c[x_clls - 2][y_clls - 2]) {
	    A;
	    boundary_ne(q, prtl);
	    prtl->cell_i = x_clls - 1;
	    prtl->cell_j = y_clls - 1;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[x_clls - 1][y_clls - 1]);
	}
    }
    if (xBr == 3 && yBu == 3) {
	list_clear(c[x_clls - 1][y_clls - 1]);
	LOOP_P(prtl_old, c[x_clls - 2][y_clls - 2]) {
	    B;
	    boundary_ne(q, prtl);
	    prtl->cell_i = x_clls - 1;
	    prtl->cell_j = y_clls - 1;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[x_clls - 1][y_clls - 1]);
	}
    }
    if (xBr == 1 && yBu == 1) {
	list_clear(c[x_clls - 1][y_clls - 1]);
	LOOP_P(prtl_old, c[Y][1]) {
	    B;
	    boundary_ne(q, prtl);
	    prtl->cell_i = x_clls - 1;
	    prtl->cell_j = y_clls - 1;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[x_clls - 1][y_clls - 1]);
	}
    }
    if ((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	list_clear(c[x_clls - 1][0]);
	LOOP_P(prtl_old, c[x_clls - 2][1]) {
	    A;
	    boundary_se(q, prtl);
	    prtl->cell_i = x_clls - 1;
	    prtl->cell_j = 0;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[x_clls - 1][0]);
	}
    }
    if (xBr == 3 && yBd == 3) {
	list_clear(c[x_clls - 1][0]);
	LOOP_P(prtl_old, c[x_clls - 2][1]) {
	    B;
	    boundary_se(q, prtl);
	    prtl->cell_i = x_clls - 1;
	    prtl->cell_j = 0;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[x_clls - 1][0]);
	}
    }
    if (xBr == 1 && yBd == 1) {
	list_clear(c[x_clls - 1][0]);
	LOOP_P(prtl_old, c[Y][y_clls - 2]) {
	    B;
	    boundary_se(q, prtl);
	    prtl->cell_i = x_clls - 1;
	    prtl->cell_j = 0;
	    INSERT_P(prtl, b);
	    INSERT_P(prtl, c[x_clls - 1][0]);
	}
    }
    return 0;
}

int
boundary_condition(struct Boundary *q, struct List ***c)
{
    int i, j;
    int kb, ku, mb, mu;
    struct Particle *prtl;
    LIST *p;
    int x_clls;
    int y_clls;
    int xBl;
    int xBr;
    int yBd;
    int yBu;

    x_clls = q->x_clls;
    y_clls = q->y_clls;
    xBl = q->xBl;
    xBr = q->xBr;
    yBd = q->yBd;
    yBu = q->yBu;

    kb = 0;
    mb = x_clls;
    ku = 0;
    mu = x_clls;
    if (xBl == yBd)
	kb = 1;
    if (xBr == yBd)
	mb = x_clls - 1;
    if (xBl == yBu)
	ku = 1;
    if (xBr == yBu)
	mu = x_clls - 1;
    for (j = 1; j < y_clls - 1; j++) {
	if (xBl == 0 || xBl == 2) {
	    LOOP_P(prtl, c[X][j]) {
		C(0);
		boundary_w(q, prtl);
	    }
	}
	if (xBl == 1 || xBl == 3) {
	    LOOP_P(prtl, c[X][j]) {
		C(1);
		boundary_w(q, prtl);
	    }
	}
	if (xBr == 0 || xBr == 2) {
	    LOOP_P(prtl, c[x_clls - 1][j]) {
		C(0);
		boundary_e(q, prtl);
	    }
	}
	if (xBr == 1 || xBr == 3) {
	    LOOP_P(prtl, c[x_clls - 1][j]) {
		C(1);
		boundary_e(q, prtl);
	    }
	}
    }
    for (i = kb; i < mb; i++) {
	if (yBd == 0 || yBd == 2) {
	    LOOP_P(prtl, c[i][0]) {
		C(0);
		boundary_s(q, prtl);
	    }
	}
	if (yBd == 1 || yBd == 3) {
	    LOOP_P(prtl, c[i][0]) {
		C(1);
		boundary_s(q, prtl);
	    }
	}
    }
    for (i = ku; i < mu; i++) {
	if (yBu == 0 || yBu == 2) {
	    LOOP_P(prtl, c[i][y_clls - 1]) {
		C(0);
		boundary_n(q, prtl);
	    }
	}
	if (yBu == 1 || yBu == 3) {
	    LOOP_P(prtl, c[i][y_clls - 1]) {
		C(1);
		boundary_n(q, prtl);
	    }
	}
    }
    if ((xBl == 0 && yBd == 0) || (xBl == 2 && yBd == 2)) {
	LOOP_P(prtl, c[X][0]) {
	    C(0);
	    boundary_sw(q, prtl);
	}
    }
    if ((xBl == 1 && yBd == 1) || (xBl == 3 && yBd == 3)) {
	LOOP_P(prtl, c[X][0]) {
	    C(1);
	    boundary_sw(q, prtl);
	}
    }
    if ((xBl == 0 && yBu == 0) || (xBl == 2 && yBu == 2)) {
	LOOP_P(prtl, c[X][y_clls - 1]) {
	    C(0);
	    boundary_nw(q, prtl);
	}
    }
    if ((xBl == 1 && yBu == 1) || (xBl == 3 && yBu == 3)) {
	LOOP_P(prtl, c[X][y_clls - 1]) {
	    C(1);
	    boundary_nw(q, prtl);
	}
    }
    if ((xBr == 0 && yBu == 0) || (xBr == 2 && yBu == 2)) {
	LOOP_P(prtl, c[x_clls - 1][y_clls - 1]) {
	    C(0);
	    boundary_ne(q, prtl);
	}
    }
    if ((xBr == 1 && yBu == 1) || (xBr == 3 && yBu == 3)) {
	LOOP_P(prtl, c[x_clls - 1][y_clls - 1]) {
	    C(1);
	    boundary_ne(q, prtl);
	}
    }
    if ((xBr == 0 && yBd == 0) || (xBr == 2 && yBd == 2)) {
	LOOP_P(prtl, c[x_clls - 1][0]) {
	    C(0);
	    boundary_se(q, prtl);
	}
    }
    if ((xBr == 1 && yBd == 1) || (xBr == 3 && yBd == 3)) {
	LOOP_P(prtl, c[x_clls - 1][0]) {
	    C(1);
	    boundary_se(q, prtl);
	}
    }
    return 0;
}

static int
boundary_w(struct Boundary *q, struct Particle *prtl)
{
    switch (q->xBl) {
    case 0:
	prtl->R[X] = -prtl->R[X];
	prtl->U[X] = q->UxBl[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] - q->box_size[X];
	break;
    case 2:
	prtl->R[X] = -prtl->R[X];
	prtl->U[X] = q->UxBl[X] * 2.0 - prtl->U[X];
	break;
    case 3:
	prtl->R[X] = -prtl->R[X];
	prtl->U[X] = q->UxBl[X] * 2.0 - prtl->U[X];
	prtl->del_phi[X] = -prtl->del_phi[X];
	break;
    }
    return 0;
}

static int
boundary_e(struct Boundary *q, struct Particle *prtl)
{
    switch (q->xBr) {
    case 0:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->U[X] = q->UxBr[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] + q->box_size[X];
	break;
    case 2:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->U[X] = q->UxBr[X] * 2.0 - prtl->U[X];
	break;
    case 3:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->U[X] = q->UxBr[X] * 2.0 - prtl->U[X];
	prtl->del_phi[X] = -prtl->del_phi[X];
	break;
    }
    return 0;
}

static int
boundary_s(struct Boundary *q, struct Particle *prtl)
{
    switch (q->yBd) {
    case 0:
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UyBd[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[Y] = prtl->R[Y] - q->box_size[Y];
	break;
    case 2:
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[Y] = q->UyBd[Y] * 2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[Y] = q->UyBd[Y] * 2.0 - prtl->U[Y];
	prtl->del_phi[Y] = -prtl->del_phi[Y];
	break;
    }
    return 0;
}

static int
boundary_n(struct Boundary *q, struct Particle *prtl)
{
    switch (q->yBu) {
    case 0:
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UyBu[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[Y] = prtl->R[Y] + q->box_size[Y];
	break;
    case 2:
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[Y] = q->UyBu[Y] * 2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[Y] = q->UyBu[Y] * 2.0 - prtl->U[Y];
	prtl->del_phi[Y] = -prtl->del_phi[Y];
	break;
    }
    return 0;
}

static int
boundary_sw(struct Boundary *q, struct Particle *prtl)
{
    switch (q->xBl) {
    case 0:
	prtl->R[X] = -prtl->R[X];
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] - q->box_size[X];
	prtl->R[Y] = prtl->R[Y] - q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = -prtl->R[X];
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = -prtl->R[X];
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	prtl->del_phi[X] = -prtl->del_phi[X];
	prtl->del_phi[Y] = -prtl->del_phi[Y];
	break;
    }
    return 0;
}

static int
boundary_nw(struct Boundary *q, struct Particle *prtl)
{
    switch (q->xBl) {
    case 0:
	prtl->R[X] = -prtl->R[X];
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] - q->box_size[X];
	prtl->R[Y] = prtl->R[Y] + q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = -prtl->R[X];
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = -prtl->R[X];
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBl[Y] * 2.0 - prtl->U[Y];
	prtl->del_phi[X] = -prtl->del_phi[X];
	prtl->del_phi[Y] = -prtl->del_phi[Y];
	break;
    }
    return 0;
}

static int
boundary_ne(struct Boundary *q, struct Particle *prtl)
{
    switch (q->xBr) {
    case 0:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] + q->box_size[X];
	prtl->R[Y] = prtl->R[Y] + q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->R[Y] = q->box_size[Y] * 2.0 - prtl->R[Y];
	prtl->U[X] = q->UyBu[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	prtl->del_phi[X] = -prtl->del_phi[X];
	prtl->del_phi[Y] = -prtl->del_phi[Y];
	break;
    }
    return 0;
}

static int
boundary_se(struct Boundary *q, struct Particle *prtl)
{
    switch (q->xBr) {
    case 0:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	break;
    case 1:
	prtl->R[X] = prtl->R[X] + q->box_size[X];
	prtl->R[Y] = prtl->R[Y] - q->box_size[Y];
	break;
    case 2:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	break;
    case 3:
	prtl->R[X] = q->box_size[X] * 2.0 - prtl->R[X];
	prtl->R[Y] = -prtl->R[Y];
	prtl->U[X] = q->UyBd[X] * 2.0 - prtl->U[X];
	prtl->U[Y] = q->UxBr[Y] * 2.0 - prtl->U[Y];
	prtl->del_phi[X] = -prtl->del_phi[X];
	prtl->del_phi[Y] = -prtl->del_phi[Y];
	break;
    }
    return 0;
}

int
boundary_check(struct Boundary *q, struct List *list)
{
    LIST *p;
    struct Particle *prtl;
    double *box_size;

    box_size = q->box_size;
    LOOP_P(prtl, list) {
	if (fabs(prtl->R[X]) >= 2.0 * box_size[X]
	    || fabs(prtl->R[Y]) >= 2.0 * box_size[Y])
	    ABORT(("run away particle"));
	if (prtl->bd == 0) {
	    if (prtl->R[X] < 0.0) {
		switch (q->xBl) {
		case 0:
		    prtl->R[X] = -prtl->R[X];
		    break;
		case 1:
		    prtl->R[X] = box_size[X] + prtl->R[X];
		    break;
		case 2:
		    prtl->R[X] = -prtl->R[X];
		    break;
		case 3:
		    prtl->R[X] = -prtl->R[X];
		    break;
		}
	    }
	    if (prtl->R[X] > box_size[X]) {
		switch (q->xBr) {
		case 0:
		    prtl->R[X] = 2.0 * box_size[X] - prtl->R[X];
		    break;
		case 1:
		    prtl->R[X] = prtl->R[X] - box_size[X];
		    break;
		case 2:
		    prtl->R[X] = 2.0 * box_size[X] - prtl->R[X];
		    break;
		case 3:
		    prtl->R[X] = 2.0 * box_size[X] - prtl->R[X];
		    break;
		}
	    }
	    if (prtl->R[Y] < 0.0) {
		switch (q->yBd) {
		case 0:
		    prtl->R[Y] = -prtl->R[Y];
		    break;
		case 1:
		    prtl->R[Y] = box_size[Y] + prtl->R[Y];
		    break;
		case 2:
		    prtl->R[Y] = -prtl->R[Y];
		    break;
		case 3:
		    prtl->R[Y] = -prtl->R[Y];
		    break;
		}
	    }
	    if (prtl->R[Y] > box_size[Y]) {
		switch (q->yBu) {
		case 0:
		    prtl->R[Y] = 2.0 * box_size[Y] - prtl->R[Y];
		    break;
		case 1:
		    prtl->R[Y] = prtl->R[Y] - box_size[Y];
		    break;
		case 2:
		    prtl->R[Y] = 2.0 * box_size[Y] - prtl->R[Y];
		    break;
		case 3:
		    prtl->R[Y] = 2.0 * box_size[Y] - prtl->R[Y];
		    break;
		}
	    }
	}
    }
    return 0;
}

int
boundary_fin(struct Boundary *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->b) {
	particle_fin(prtl);
    }
    list_clear(q->b);
    list_fin(q->b);
    free(q);
    return 0;
}

struct List *
boundary_list(struct Boundary *q)
{
    return q->b;
}
