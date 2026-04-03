#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sph.h"

enum { X, Y };

/* err */

int wprint(const char *fmt, ...) {
	int r;
	va_list ap;

	va_start(ap, fmt);
	r = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return r;
}

/* list */

struct List;
struct ListNode {
	void *data;
	struct ListNode *next;
};

struct List {
	struct ListNode *node;
};

int listendp(struct List *q, struct ListNode *n) { return n->next == q->node; }

struct ListNode *listfirst(struct List *q) {
	return q->node;
}

struct ListNode *listnext(struct List *q, struct ListNode *n) {
	(void)q;
	return n->next;
}

void *listget(struct List *q, struct ListNode *n) {
	(void)q;
	return n->next->data;
}

void listins(struct List *q, struct ListNode *n, void *p) {
	struct ListNode *node;

	node = malloc(sizeof(struct ListNode));
	node->data = p;
	node->next = n->next;
	n->next = node;
}

void listrm(struct List *q, struct ListNode *p) {
	struct ListNode *t = p->next;

	p->next = t->next;
	free(t);
}

void listclr(struct List *q) {
	while (q->node != q->node->next)
		listrm(q, q->node);
}

struct List *listnew(void) {
	struct List *q;
	struct ListNode *node;

	q = malloc(sizeof(struct List));
	node = malloc(sizeof(struct ListNode));
	node->data = NULL;
	node->next = node;
	q->node = node;
	return q;
}

void listfree(struct List *q) {
	while (q->node != q->node->next)
		listrm(q, q->node);
	free(q->node);
	free(q);
}

/* kernel */

struct Kernel {
	double rh;
	double fw;
	double fg;
	double h;
};

static double pi = 3.141592653589793;
struct Kernel *kernelnew(double h) {
	double norm;
	struct Kernel *q;

	q = malloc(sizeof(*q));
	if (q == NULL) {
		ABORT(("fail to alloc"));
		return q;
	}

	norm = 63.0 / 478.0 / pi;
	q->h = h;
	q->rh = 1.0 / h;
	q->fw = norm * pow(q->rh, 2);
	q->fg = 15.0 * norm * pow(q->rh, 3);
	return q;
}

int kernelfree(struct Kernel *q) {
	free(q);
	return 0;
}

double w(struct Kernel *q, double r) {
	double d = 3.0 * r * q->rh;
	double a, b, c;

	a = (3.0 - d);
	b = (2.0 - d);
	c = (1.0 - d);
	if (d < 1.0) {
		return q->fw * (a * a * a * a * a - 6.0 * b * b * b * b * b +
												 15.0 * c * c * c * c * c);
	} else if (d < 2.0) {
		return q->fw * (a * a * a * a * a - 6.0 * b * b * b * b * b);
	} else if (d < 3.0) {
		return q->fw * a * a * a * a * a;
	} else {
		return 0.0;
	}
}

double F(struct Kernel *q, double r) {
	double a, b, c, d;

	d = 3.0 * r * q->rh;
	a = (3.0 - d);
	b = (2.0 - d);
	c = (1.0 - d);

	if (d < 1.0) {
		return q->fg *
					 (a * a * a * a - 6.0 * b * b * b * b + 15.0 * c * c * c * c);
	} else if (d < 2.0) {
		return q->fg * (a * a * a * a - 6.0 * b * b * b * b);
	} else if (d < 3.0) {
		return q->fg * a * a * a * a;
	} else {
		return 0.0;
	}
}

/* material */

double getp(struct Material *q, double rho) {
	return q->b0 * pow(rho / q->rho0, q->gamma);
}

double getcs(struct Material *q, double p, double rho) {
	return sqrt(q->gamma * p / rho);
}


/* particle */

long idmax;
int nmat;

static double **phinew(void) {
	int n, i, j;
	double **q;

	n = nmat;
	q = malloc(n * sizeof(*q));
	for (i = 0; i < n; i++)
		q[i] = malloc(n * sizeof(**q));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			q[i][j] = 0.0;
	return q;
}

int prtfree(struct Particle *q) {
	int i;

	for (i = 0; i < nmat; i++)
		free(q->phi[i]);
	free(q->phi);
	free(q);
	return 0;
}

struct Particle *prtreal(double position[2], double velocity[2],
															 double density, double pressure,
															 double temperature, struct Material *material) {
	struct Particle *q;

	q = malloc(sizeof(*q));
	if (q == NULL) abort();
	idmax++;
	q->bd = 0;
	q->btype = 0;
	q->ID = idmax;
	q->mtl = material;
	q->eta = material->eta;
	q->zeta = material->zeta;
	q->R[X] = position[X];
	q->R[Y] = position[Y];
	q->rho = density;
	q->p = pressure;
	q->T = temperature;
	q->Cs = getcs(material, pressure, density);
	q->U[X] = velocity[X];
	q->U[Y] = velocity[Y];
	q->U_I[X] = velocity[X];
	q->U_I[Y] = velocity[Y];
	q->m = 0.0;
	q->V = 0.0;
	q->R_I[X] = position[X];
	q->R_I[Y] = position[Y];
	q->rho_I = density;
	q->U_n[X] = velocity[X];
	q->U_n[Y] = velocity[Y];
	q->rho_n = density;
	q->phi = phinew();
	return q;
}

struct Particle *prtimage(struct Particle *s) {
	struct Particle *q;

	q = malloc(sizeof(*q));
	if (q == NULL) abort();
	q->bd = 1;
	q->btype = 1;
	q->ID = 0;
	q->real = s;
	q->mtl = s->mtl;
	q->eta = s->mtl->eta;
	q->zeta = s->mtl->zeta;
	q->R[X] = s->R[X];
	q->R[Y] = s->R[Y];
	q->rho = s->rho;
	q->p = s->p;
	q->T = s->T;
	q->Cs = s->Cs;
	q->U[X] = s->U[X];
	q->U[Y] = s->U[Y];
	q->U_I[X] = s->U_I[X];
	q->U_I[Y] = s->U_I[Y];
	q->m = s->m;
	q->V = s->V;
	q->R_I[X] = s->R_I[X];
	q->R_I[Y] = s->R_I[Y];
	q->rho_I = s->rho;
	q->U_n[X] = s->U_n[X];
	q->U_n[Y] = s->U_n[Y];
	q->rho_n = s->rho_n;
	q->phi = phinew();
	return q;
}

struct Particle *prtmirror(struct Particle *s,
																 struct Material *material) {
	struct Particle *q;

	q = malloc(sizeof(*q));
	if (q == NULL) abort();
	q->bd = 1;
	q->btype = 0;
	q->ID = 0;
	q->real = s;
	q->mtl = material;
	q->eta = s->eta;
	q->zeta = s->zeta;
	q->R[X] = s->R[X];
	q->R[Y] = s->R[Y];
	q->rho = s->rho;
	q->p = s->p;
	q->T = s->T;
	q->Cs = s->Cs;
	q->U[X] = s->U[X];
	q->U[Y] = s->U[Y];
	q->U_I[X] = s->U_I[X];
	q->U_I[Y] = s->U_I[Y];
	q->m = s->m;
	q->V = s->V;
	q->R_I[X] = s->R_I[X];
	q->R_I[Y] = s->R_I[Y];
	q->rho_I = s->rho;
	q->U_n[X] = s->U_n[X];
	q->U_n[Y] = s->U_n[Y];
	q->rho_n = s->rho_n;
	q->phi = phinew();
	return q;
}

int prtcopy(struct Particle *q, struct Particle *s, int type) {
	int i, j;

	q->R[X] = s->R[X];
	q->R[Y] = s->R[Y];
	q->m = s->m;
	q->rho = s->rho;
	q->V = s->V;
	q->p = s->p;
	q->T = s->T;
	q->rho_I = s->rho_I;
	q->Cs = s->Cs;
	q->U[X] = s->U[X];
	q->U[Y] = s->U[Y];
	q->U_I[X] = s->U_I[X];
	q->U_I[Y] = s->U_I[Y];
	if (type == 1) {
		q->dphi[X] = s->dphi[X];
		q->dphi[Y] = s->dphi[Y];
		for (i = 0; i < nmat; i++)
			for (j = 0; j < nmat; j++)
				q->phi[i][j] = s->phi[i][j];
	}
	if (type == 0) {
		q->phi[0][0] = 0;
		for (i = 1; i < nmat; i++)
			q->phi[0][0] += s->phi[i][i];
	}
	return 0;
}


/* ini */

enum { MAX_SIZE = 4096 };
static double k_bltz = 1.380662e-023 / 0.02 / 0.02 / 0.02;
struct Pair {
	struct Particle *Org;
	struct Particle *Dest;
	struct Force **frc_ij;
	double mi;
	double rmi;
	double etai;
	double zetai;
	double mj;
	double rmj;
	double etaj;
	double zetaj;
	double rij;
	double rrij;
	double Wij;
	double Fij;
	double eij[2];
	double sr;
	double br;
};
struct Force {
	double epsilon;
	double sigma;
	double shear_slip, bulk_slip;
};

static double dmax(double a, double b) { return a > b ? a : b; }

static double dmin(double a, double b) { return a < b ? a : b; }

static double dist(double a[2], double b[2]) {
	double x, y;

	x = a[X] - b[X];
	y = a[Y] - b[Y];
	return sqrt(x * x + y * y);
}

static double vnorm(double v[2]) { return sqrt(v[X] * v[X] + v[Y] * v[Y]); }

static double sqdiff(double v[2]) { return v[X] * v[X] - v[Y] * v[Y]; }

static void SummationDensity(struct Pair *q) {
	struct Particle *Org, *Dest;
	double Wij;
	double mi, mj;

	Org = q->Org;
	Dest = q->Dest;
	Wij = q->Wij;
	mi = q->mi;
	mj = q->mj;

	Org->rho += mi * Wij;
	if (Org->ID != Dest->ID)
		Dest->rho += mj * Wij;
}

static void SummationPhaseGradient(struct Pair *q) {
	struct Particle *Org, *Dest;
	double mi, mj;
	double c;
	double Vi, rVi, Vj, rVj;
	double dphi[2];
	double Fij;
	double rij;
	struct Force **frc_ij;
	int noi;
	int noj;
	double *eij;

	Org = q->Org;
	Dest = q->Dest;
	mi = q->mi;
	mj = q->mj;
	Fij = q->Fij;
	rij = q->rij;
	frc_ij = q->frc_ij;
	noi = Org->mtl->number;
	noj = Dest->mtl->number;
	eij = q->eij;

	Vi = mi / Org->rho;
	Vj = mj / Dest->rho;
	rVi = 1.0 / Vi;
	rVj = 1.0 / Vj;
	double Vi2 = Vi * Vi, Vj2 = Vj * Vj;

	c = Fij * rij * frc_ij[noi][noj].sigma;
	dphi[X] = eij[X] * c;
	dphi[Y] = eij[Y] * c;
	Org->dphi[X] += dphi[X] * rVi * Vj2;
	Org->dphi[Y] += dphi[Y] * rVi * Vj2;
	Dest->dphi[X] -= dphi[X] * rVj * Vi2;
	Dest->dphi[Y] -= dphi[Y] * rVj * Vi2;
}

static void UpdateForces(struct Pair *q, double art_vis, double delta) {
	struct Particle *Org, *Dest;
	double Wij;
	double mi, mj;
	double c;
	double Vi, rVi, Vj, rVj;
	double Fij;
	double rij;
	double *eij;
	double pi, rhoi, pj, rhoj, Uijdoteij, dx, dy;
	double Ui[2], Uj[2], Uij[2];
	double sr;
	double br;
	double rmi, rmj;

	Org = q->Org;
	Dest = q->Dest;
	Wij = q->Wij;
	mi = q->mi;
	mj = q->mj;
	Fij = q->Fij;
	rij = q->rij;
	eij = q->eij;
	sr = q->sr;
	br = q->br;
	rmi = q->rmi;
	rmj = q->rmj;

	rhoi = Org->rho;
	rhoj = Dest->rho;
	Vi = mi / rhoi;
	Vj = mj / rhoj;
	rVi = 1.0 / Vi;
	rVj = 1.0 / Vj;
	pi = Org->p;
	pj = Dest->p;
	Ui[X] = Org->U[X];
	Ui[Y] = Org->U[Y];
	Uj[X] = Dest->U[X];
	Uj[Y] = Dest->U[Y];
	Uij[X] = Ui[X] - Uj[X];
	Uij[Y] = Ui[Y] - Uj[Y];
	Uijdoteij = Uij[X] * eij[X] + Uij[Y] * eij[Y];
	double dPdti[2], dUi[2];
	double drhodti;
	double Vi2 = Vi * Vi, Vj2 = Vj * Vj;
	double theta, Csi, Csj, NR_vis;

	Csi = Org->Cs;
	Csj = Dest->Cs;
	theta = Uijdoteij * rij * delta / (rij * rij + 0.01 * delta * delta);
	NR_vis =
			Uijdoteij > 0.0
					? 0.0
					: art_vis * theta * (rhoi * Csi * mj + rhoj * Csj * mi) / (mi + mj);
	c = theta * Wij * art_vis / (rhoi + rhoj);
	dUi[X] = -eij[X] * c;
	dUi[Y] = -eij[Y] * c;
	dx = Ui[X] * Vi2 - Uj[X] * Vj2;
	dy = Ui[Y] * Vi2 - Uj[Y] * Vj2;
	drhodti = -Fij * rij * (dx * eij[X] + dy * eij[Y]);
	dPdti[X] = eij[X] * Fij * rij * (pi * Vi2 + pj * Vj2) -
						 ((Uij[X] - eij[X] * Uijdoteij) * sr +
							eij[X] * (Uijdoteij * 2.0 * br + NR_vis)) *
								 Fij * (Vi2 + Vj2);
	dPdti[Y] = eij[Y] * Fij * rij * (pi * Vi2 + pj * Vj2) -
						 ((Uij[Y] - eij[Y] * Uijdoteij) * sr +
							eij[Y] * (Uijdoteij * 2.0 * br + NR_vis)) *
								 Fij * (Vi2 + Vj2);
	double Surfi[2], Surfj[2], SurfaceForcei[2], SurfaceForcej[2];

	Surfi[X] = Org->dphi[X];
	Surfi[Y] = Org->dphi[Y];
	Surfj[X] = Dest->dphi[X];
	Surfj[Y] = Dest->dphi[Y];
	SurfaceForcei[X] = Surfi[X] * eij[X] + Surfi[Y] * eij[Y];
	SurfaceForcei[Y] = Surfi[Y] * eij[X] - Surfi[X] * eij[Y];
	SurfaceForcej[X] = Surfj[X] * eij[X] + Surfj[Y] * eij[Y];
	SurfaceForcej[Y] = Surfj[Y] * eij[X] - Surfj[X] * eij[Y];
	dPdti[X] += (SurfaceForcei[X] * Vi2 + SurfaceForcej[X] * Vj2) * rij * Fij;
	dPdti[Y] += (SurfaceForcei[Y] * Vi2 + SurfaceForcej[Y] * Vj2) * rij * Fij;
	Org->_dU[X] += dUi[X] * mi;
	Org->_dU[Y] += dUi[Y] * mi;
	Dest->_dU[X] -= dUi[X] * mj;
	Dest->_dU[Y] -= dUi[Y] * mj;
	Org->drhodt += drhodti * rhoi * rVi;
	Dest->drhodt += drhodti * rhoj * rVj;
	Org->dUdt[X] += dPdti[X] * rmi;
	Org->dUdt[Y] += dPdti[Y] * rmi;
	Dest->dUdt[X] -= dPdti[X] * rmj;
	Dest->dUdt[Y] -= dPdti[Y] * rmj;
}

int iniread(char *project_name, struct Ini *q) {
	char Key_word[FILENAME_MAX];
	char inputfile[FILENAME_MAX];
	char *mkdir = "mkdir -p outdata";
	double delta;
	double sound;
	FILE *f;
	int i;
	int j;
	int k;
	int l;
	int m;
	int n;
	int nmat;
	int rc;
	struct Force *force;
	struct Material *mtl;

	strcpy(q->project, project_name);
	strcpy(inputfile, q->project);
	strcat(inputfile, ".cfg");
	f = fopen(inputfile, "r");
	if (!f)
		ABORT(("can't open '%s'", inputfile));
	{
		struct { const char *name; const char *fmt; void *dst[5]; } keys[] = {
			{"INITIAL_CONDITION",  "%d",              {&q->initial_condition}},
			{"CELLS",              "%d %d",           {&q->nx, &q->ny}},
			{"CELL_SIZE",          "%lf",             {&q->cs}},
			{"SMOOTHING_LENGTH",   "%lf",             {&q->h}},
			{"CELL_RATIO",         "%d",              {&q->cr}},
			{"GRAVITY",            "%lf %lf",         {&q->gravity[0], &q->gravity[1]}},
			{"ARTIFICIAL_VISCOSITY","%lf",            {&q->art_vis}},
			{"NUMBER_OF_MATERIALS","%d",              {&q->nmat}},
			{"TIMING",             "%lf %lf %lf",    {&q->t0, &q->t1, &q->tout}},
			{"INITIAL_STATES",     "%lf %lf %lf %lf %lf", {&q->U0[0], &q->U0[1], &q->rho0, &q->p0, &q->T0}},
		};
		int nkeys = sizeof(keys) / sizeof(keys[0]);
		while (fscanf(f, "%s", Key_word) == 1)
			for (k = 0; k < nkeys; k++) {
				if (strcmp(Key_word, keys[k].name) != 0) continue;
				if (k == nkeys - 1 && q->initial_condition != 0) continue;
				rc = fscanf(f, keys[k].fmt,
										keys[k].dst[0], keys[k].dst[1], keys[k].dst[2],
										keys[k].dst[3], keys[k].dst[4]);
			}
	}
	if (fclose(f) != 0)
		ABORT(("fclose failed"));
	if (system(mkdir) != 0)
		ABORT(("command '%s' faild", mkdir));
	q->box_size[0] = q->nx * q->cs;
	q->box_size[1] = q->ny * q->cs;
	q->delta = q->cs / q->cr;

	q->mx = q->nx + 2;
	q->my = q->ny + 2;
	q->cells = malloc(q->mx * sizeof(struct List **));
	for (i = 0; i < q->mx; i++) {
		q->cells[i] = malloc(q->my * sizeof(struct List *));
		for (j = 0; j < q->my; j++)
			q->cells[i][j] = listnew();
	}
	q->nnpl = listnew();

	q->b = listnew();
	f = fopen(inputfile, "r");
	if (!f)
		ABORT(("can't open '%s'\n", inputfile));
	while (fscanf(f, "%s", Key_word) == 1)
		if (!strcmp(Key_word, "BOUNDARY")) {
			n = fscanf(f, "%d %lf %lf %d %lf %lf %d %lf %lf %d %lf %lf", &q->bxl,
								 &q->uxl[X], &q->uxl[Y], &q->bxr, &q->uxr[X], &q->uxr[Y],
								 &q->byd, &q->uyd[X], &q->uyd[Y], &q->byu, &q->uyu[X],
								 &q->uyu[Y]);
			if (n != 3 * 4)
				ABORT(("can't read BOUNDARY keyword (n = %d)", n));
		}
	fclose(f);
	printf("The left, right, lower and upper boundary %d %d %d %d\n", q->bxl,
				 q->bxr, q->byd, q->byu);
	puts("0: wall boundary condition");
	puts("1: perodic boundary condition");
	puts("2: free slip wall boundary condition");
	puts("3: symmetry boundary condition");

	q->pair_list = listnew();
	nmat = q->nmat;
	delta = q->delta;
	q->delta2 = delta * delta;
	q->delta3 = delta * delta * delta;
	q->materials = malloc(nmat * sizeof(*q->materials));
	q->forces = malloc(nmat * sizeof(*q->forces));
	for (k = 0; k < nmat; k++)
		q->forces[k] = malloc(nmat * sizeof(*q->forces[k]));

	f = fopen(inputfile, "r");
	if (!f)
		ABORT(("can't open '%s'", inputfile));
	else
		printf("read the propeties of materials and forces\n");
	while (fscanf(f, "%s", Key_word) == 1) {
		if (!strcmp(Key_word, "MATERIALS"))
			for (k = 0; k < nmat; k++) {
				mtl = &q->materials[k];
				mtl->number = k;
				if (fscanf(f, "%s %d", mtl->name, &mtl->material_type) != 2)
					ABORT(("can't read material from '%s'", inputfile));
				if (fscanf(f, "%lf %lf %lf %lf %lf", &mtl->eta, &mtl->zeta, &mtl->gamma,
									 &mtl->rho0, &mtl->a0) != 5)
					ABORT(("can't read materal parameters from '%s'", inputfile));
				mtl->nu = dmax(mtl->eta, mtl->zeta) / mtl->rho0;
			}
		if (!strcmp(Key_word, "FORCES"))
			for (l = 0; l < nmat; l++)
				for (n = 0; n < nmat; n++) {
					if (fscanf(f, "%d %d", &k, &m) != 2)
						ABORT(("can't read materal from '%s'", inputfile));
					force = &q->forces[k][m];
					if (fscanf(f, "%lf %lf %lf %lf", &force->epsilon, &force->sigma,
										 &force->shear_slip, &force->bulk_slip) != 4)
						ABORT(("can't read force from '%s'", inputfile));
				}
	}
	fclose(f);
	q->numax = 0.0;
	q->sigmax = 0.0;
	for (k = 0; k < nmat; k++) {
		q->numax = dmax(q->numax, q->materials[k].nu);
		for (l = 0; l < nmat; l++) {
			q->sigmax = dmax(q->sigmax, q->forces[k][l].sigma);
		}
	}
	q->dt_g_vis = dmin(sqrt(delta / vnorm(q->gravity)),
											0.5 * q->delta2 / q->numax);
	q->dt_surf = 0.4 * sqrt(q->delta3 / q->sigmax);
	sound = dmax(vnorm(q->gravity), q->numax);
	sound = dmax(q->sigmax, sound);
	for (k = 0; k < nmat; k++)
		q->materials[k].b0 = q->materials[k].a0 * sound / q->materials[k].gamma;
	q->parts = listnew();
	nmat = q->nmat;
	idmax = 0;

	return 0;
}

int updcells(struct Ini *q) {

	int i, j;
	int k, m;
	struct ListNode *p;
	struct Particle *prtl;

	int mx;
	int my;
	double cs;
	struct List ***cells;

	mx = q->mx;
	my = q->my;
	cs = q->cs;
	cells = q->cells;

	for (i = 0; i < mx; i++) {
		for (j = 0; j < my; j++) {
			p = listfirst(cells[i][j]);
			while (!listendp(cells[i][j], p)) {
				prtl = listget(cells[i][j], p);
				if (prtl->bd == 0) {
					k = (int)((prtl->R[0] + cs) / cs);
					m = (int)((prtl->R[1] + cs) / cs);
					if (k != i || m != j) {
						listrm(cells[i][j], p);
						listins(cells[k][m], listfirst(cells[k][m]), prtl);
					} else
						p = listnext(cells[i][j], p);
				} else
					p = listnext(cells[i][j], p);
			}
		}
	}
	return 0;
}

int mknnp(struct Ini *q, double point[2]) {
	int i, j;
	int k, m;
	double dstc;
	struct ListNode *p;
	struct Particle *prtl;

	struct List *nnpl;
	int mx;
	int my;
	double cs;
	double h;
	struct List ***cells;

	mx = q->mx;
	my = q->my;
	cs = q->cs;
	cells = q->cells;
	h = q->h;
	nnpl = q->nnpl;

	listclr(nnpl);
	k = (int)((point[0] + cs) / cs);
	m = (int)((point[1] + cs) / cs);
	for (i = k - 1; i <= k + 1; i++)
		for (j = m - 1; j <= m + 1; j++)
			if (i < mx && j < my && i >= 0 && j >= 0)
				for (p = listfirst(cells[i][j]); !listendp(cells[i][j], p); p = listnext(cells[i][j], p)) { prtl = (struct Particle *)listget(cells[i][j], p);
					dstc = dist(point, prtl->R);
					if (dstc < h)
						listins(nnpl, listfirst(nnpl), prtl);
				}
	return 0;
}

int mkpairs(struct Ini *q, struct List *pairs,
											 struct List *parts, struct Force **forces,
											 struct Kernel *kernel) {
	struct ListNode *p, *p1;
	int i, j, k, m;
	double dstc;
	double sm2;
	struct Particle *prtl_org, *prtl_dest;
	struct Pair *pair;

	double h;
	double cs;
	struct List ***cells;

	cs = q->cs;
	cells = q->cells;
	h = q->h;

	sm2 = h * h;

	for (p = listfirst(pairs); !listendp(pairs, p); p = listnext(pairs, p)) { pair = (struct Pair *)listget(pairs, p);
		free(pair);
	}
	listclr(pairs);
	for (p = listfirst(parts); !listendp(parts, p); p = listnext(parts, p)) { prtl_org = (struct Particle *)listget(parts, p);
		if (prtl_org->bd == 0) {
			i = (int)((prtl_org->R[0] + cs) / cs);
			j = (int)((prtl_org->R[1] + cs) / cs);
			for (k = i - 1; k <= i + 1; k++)
				for (m = j - 1; m <= j + 1; m++) {
					for (p1 = listfirst(cells[k][m]); !listendp(cells[k][m], p1); p1 = listnext(cells[k][m], p1)) { prtl_dest = (struct Particle *)listget(cells[k][m], p1);
						double dx = prtl_org->R[X] - prtl_dest->R[X];
						double dy = prtl_org->R[Y] - prtl_dest->R[Y];
						dstc = dx * dx + dy * dy;
						if (dstc <= sm2 && prtl_org->ID >= prtl_dest->ID) {
							double rij, etai, etaj, zetai, zetaj;
							int noi, noj;
							struct Force **frc_ij;
							struct Particle *Org, *Dest;

							pair = malloc(sizeof(*pair));
							if (pair == NULL)
								ABORT(("can't allocate"));
							pair->Org = Org = prtl_org;
							pair->Dest = Dest = prtl_dest;
							pair->frc_ij = frc_ij = forces;
							noi = Org->mtl->number;
							noj = Dest->mtl->number;
							pair->mi = Org->m;
							pair->mj = Dest->m;
							pair->rmi = 1.0 / pair->mi;
							pair->rmj = 1.0 / pair->mj;
							pair->etai = etai = Org->eta;
							pair->etaj = etaj = Dest->eta;
							pair->zetai = zetai = Org->zeta;
							pair->zetaj = zetaj = Dest->zeta;
							pair->rij = rij = sqrt(dstc);
							pair->rrij = 1.0 / (rij + 1.0e-30);
							pair->eij[X] = (Org->R[X] - Dest->R[X]) * pair->rrij;
							pair->eij[Y] = (Org->R[Y] - Dest->R[Y]) * pair->rrij;
							pair->Wij = w(kernel, rij);
							pair->Fij = F(kernel, rij) * pair->rrij;
							pair->sr = 2.0 * etai * etaj * rij /
								(etai * (rij + 2.0 * frc_ij[noj][noi].shear_slip) +
								 etaj * (rij + 2.0 * frc_ij[noi][noj].shear_slip) + 1.0e-30);
							pair->br = 2.0 * zetai * zetaj * rij /
								(zetai * (rij + 2.0 * frc_ij[noj][noi].bulk_slip) +
								 zetaj * (rij + 2.0 * frc_ij[noi][noj].bulk_slip) + 1.0e-30);
							listins(pairs, listfirst(pairs), pair);
						}
					}
				}
		}
	}
	return 0;
}

void mkparts(struct Ini *q, struct Material *materials,
														 struct List *parts, struct Ini *ini) {

	int i, j, k, m;
	double position[2];
	double velocity[2];
	double delta;
	double density, pressure, Temperature;
	int material_no;
	struct Particle *prtl;
	int n, N, cnt;
	char inputfile[FILENAME_MAX], line[MAX_SIZE];
	char name[MAX_SIZE];
	FILE *f;

	int mx;
	int my;
	int cr;
	double cs;
	struct List ***cells;

	mx = q->mx;
	my = q->my;
	cs = q->cs;
	cells = q->cells;
	cr = ini->cr;

	delta = cs / cr;
	if (ini->initial_condition == 0) {
		for (i = 1; i < mx - 1; i++) {
			for (j = 1; j < my - 1; j++) {
				for (k = 0; k < cr; k++) {
					for (m = 0; m < cr; m++) {
						position[0] = (i - 1) * cs + (k + 0.5) * delta;
						position[1] = (j - 1) * cs + (m + 0.5) * delta;
						material_no = 1;
						velocity[X] = ini->U0[X];
						velocity[Y] = ini->U0[Y];
						Temperature = ini->T0;
						density = materials[material_no].rho0;
						pressure = getp(&materials[material_no], density);
						prtl = prtreal(position, velocity, density, pressure,
																 Temperature, &materials[material_no]);
						prtl->cell_i = i;
						prtl->cell_j = j;
						listins(parts, listfirst(parts), prtl);
						listins(cells[i][j], listfirst(cells[i][j]), prtl);
					}
				}
			}
		}
	}

	if (ini->initial_condition == 1) {
		strcpy(inputfile, ini->project);
		strcat(inputfile, ".txt");
		f = fopen(inputfile, "r");
		if (!f)
			ABORT(("can't open file '%s'", inputfile));
		else
			WARN(("Read real particles from '%s'", inputfile));
		if (fgets(line, MAX_SIZE, f) == NULL)
			ABORT(("can't read a line from '%s'", inputfile));
		sscanf(line, "%lf", &ini->t0);
		ini->t1 += ini->t0;
		if (fgets(line, MAX_SIZE, f) == NULL)
			ABORT(("can't read a line from '%s'", inputfile));
		cnt = sscanf(line, "%d", &N);
		if (cnt != 1)
			ABORT(("can't read number of particles from '%s'", inputfile));
		else
			WARN(("N = %d", N));
		for (n = 0; n < N; n++) {
			if (fgets(line, MAX_SIZE, f) == NULL)
				ABORT(("can't read a line from '%s'", inputfile));
			cnt = sscanf(line, "%s %lf %lf %lf %lf %lf %lf %lf", name,
									 &position[0], &position[1], &velocity[0], &velocity[1],
									 &density, &pressure, &Temperature);
			if (cnt != 8) {
				WARN(("line: '%s'", line));
				WARN(("name: %s", name));
				ABORT(("can't read a particle from '%s' (cnt = %d, n = %d)", inputfile,
							 cnt, n));
			}
			material_no = -1;
			for (k = 0; k < ini->nmat; k++)
				if (strcmp(name, materials[k].name) == 0)
					material_no = k;
			if (material_no != -1) {
				pressure = getp(&materials[material_no], density);
				prtl = prtreal(position, velocity, density, pressure, Temperature,
														 &materials[material_no]);
				listins(parts, listfirst(parts), prtl);
				i = (int)(prtl->R[0] / cs) + 1;
				j = (int)(prtl->R[1] / cs) + 1;
				prtl->cell_i = i;
				prtl->cell_j = j;
				listins(cells[i][j], listfirst(cells[i][j]), prtl);
			} else {
				ABORT(("The material in the restart file is not used by the program!"));
			}
		}
		fclose(f);
	}
}

int inifin(struct Ini *q) {
	int i;
	int j;
	int mx;
	int my;
	struct List ***c;
	struct ListNode *p;
	struct Pair *pair;
	struct Particle *prtl;

	mx = q->mx;
	my = q->my;
	c = q->cells;
	for (i = 0; i < mx; i++) {
		for (j = 0; j < my; j++) {
			listfree(c[i][j]);
		}
		free(c[i]);
	}
	free(c);
	listfree(q->nnpl);

	for (i = 0; i < q->nmat; i++)
		free(q->forces[i]);
	free(q->forces);
	free(q->materials);

	for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p);
		free(pair);
	}
	listfree(q->pair_list);

	for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p); prtfree(prtl); }
	listfree(q->parts);

	return 0;
}

static void UpdateSurfaceStress(struct Ini *q) {
	double epsilon = 1.0e-30;
	double interm0, interm1, interm2;
	struct Particle *prtl;
	struct ListNode *p;

	for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
		interm0 = 1.0 / (vnorm(prtl->dphi) + epsilon);
		interm1 = 0.5 * sqdiff(prtl->dphi);
		interm2 = prtl->dphi[X] * prtl->dphi[Y];
		prtl->dphi[0] = interm1 * interm0;
		prtl->dphi[1] = interm2 * interm0;
	}
	for (p = listfirst(q->b); !listendp(q->b, p); p = listnext(q->b, p)) { prtl = (struct Particle *)listget(q->b, p);
		interm0 = vnorm(prtl->dphi) + epsilon;
		interm1 = 0.5 * sqdiff(prtl->dphi);
		interm2 = prtl->dphi[X] * prtl->dphi[Y];
		prtl->dphi[0] = interm1 / interm0;
		prtl->dphi[1] = interm2 / interm0;
	}
}

int prtout(struct Ini *q, struct List *parts,
										 struct Material *materials, double Time) {
	char file_name[FILENAME_MAX], file_list[FILENAME_MAX];
	double Itime;
	FILE *f;
	int i, j;
	int nmat;
	struct ListNode *p;
	struct Particle *prtl;

	nmat = q->nmat;

	Itime = Time * 1.0e6;
	strcpy(file_name, "./outdata/p.");
	sprintf(file_list, "%.10lld", (long long)Itime);
	strcat(file_name, file_list);
	strcat(file_name, ".dat");

	f = fopen(file_name, "w");
	if (!f)
		ABORT(("can't write '%s'", file_name));
	fprintf(f, "%s", "title='particle position' \n");
	fprintf(f, "%s", "variables=x, y, Ux, Uy \n");
	for (i = 0; i < nmat; i++) {
		j = 0;
		for (p = listfirst(parts); !listendp(parts, p); p = listnext(parts, p)) { prtl = (struct Particle *)listget(parts, p);
			if (strcmp(materials[i].name, prtl->mtl->name) == 0) {
				j++;
				if (j == 1)
					fprintf(f, "zone t='%s' \n", materials[i].name);
				fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0],
								prtl->U[1]);
			}
		}
		for (p = listfirst(q->b); !listendp(q->b, p); p = listnext(q->b, p)) { prtl = (struct Particle *)listget(q->b, p);
			if (strcmp(materials[i].name, prtl->mtl->name) == 0) {
				j++;
				if (j == 1)
					fprintf(f, "zone t='%s' \n", materials[i].name);
				fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0],
								prtl->U[1]);
			}
		}
	}
	fclose(f);
	return 0;
}

int rstout(struct Ini *q, struct List *parts, double Time) {
	int n;
	char file_name[FILENAME_MAX];
	struct Particle *prtl;
	struct ListNode *p;
	FILE *f;

	strcpy(file_name, q->project);
	strcat(file_name, ".txt");
	f = fopen(file_name, "w");
	if (!f)
		ABORT(("can't write '%s'", file_name));
	n = 0;
	for (p = listfirst(parts); !listendp(parts, p); p = listnext(parts, p)) { prtl = (struct Particle *)listget(parts, p);
		if (prtl->bd == 0)
			n++;
	}
	fprintf(f, "%.6g\n", Time);
	fprintf(f, "%d\n", n);
	for (p = listfirst(parts); !listendp(parts, p); p = listnext(parts, p)) { prtl = (struct Particle *)listget(parts, p);
		if (prtl->bd == 0)
			fprintf(f, "%s %.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
							prtl->mtl->name, prtl->R[0], prtl->R[1], prtl->U[0],
							prtl->U[1], prtl->rho, prtl->p, prtl->T);
	}
	fclose(f);
	return 0;
}

void volmass(struct List *parts, struct Ini *ini,
								struct Kernel *kernel) {
	double reciprocV;
	double dstc;
	struct ListNode *p, *p1;
	struct Particle *prtl_org, *prtl_dest;

	for (p = listfirst(parts); !listendp(parts, p); p = listnext(parts, p)) { prtl_org = (struct Particle *)listget(parts, p);
		mknnp(ini, prtl_org->R);
		reciprocV = 0.0;
		for (p1 = listfirst(ini->nnpl); !listendp(ini->nnpl, p1); p1 = listnext(ini->nnpl, p1)) { prtl_dest = (struct Particle *)listget(ini->nnpl, p1);
			dstc = dist(prtl_org->R, prtl_dest->R);
			reciprocV += w(kernel, dstc);
		}
		reciprocV = 1.0 / reciprocV;
		prtl_org->V = reciprocV;
		prtl_org->m = prtl_org->rho * reciprocV;
		listclr(ini->nnpl);
	}
}

void step(int *pite, struct Ini *q, double *Time, double tout,
					struct Kernel *kernel) {
	double dt;
	double integeral_time;
	double sqrtdt;
	int ite;
	struct ListNode *p;
	struct Pair *pair;
	struct Particle *prtl;

	ite = *pite;

	integeral_time = 0;
	while (integeral_time < tout) {
		{
			double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
			for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
				Cs_max = dmax(Cs_max, prtl->Cs);
				V_max = dmax(V_max, vnorm(prtl->U));
				rho_min = dmin(rho_min, prtl->rho);
				rho_max = dmax(rho_max, prtl->rho);
			}
			dt = dmin(sqrt(0.5 * (rho_min + rho_max)) * q->dt_surf, q->dt_g_vis);
			dt = 0.25 * dmin(dt, q->delta / (Cs_max + V_max));
		}
		sqrtdt = sqrt(dt);
		ite++;
		integeral_time += dt;
		*Time += dt;
		if (ite % 10 == 0)
			printf("N=%d Time: %g\tdt: %g\n", ite, *Time, dt);
		mkpairs(q, q->pair_list, q->parts, q->forces, kernel);
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p); prtl->rho = 0.0; }
		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p); SummationDensity(pair); }
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p); prtl->p = getp(prtl->mtl, prtl->rho); }

		bndcond(q, q->cells);
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->dphi[X] = prtl->dphi[Y] = 0.0;
		}
		for (p = listfirst(q->b); !listendp(q->b, p); p = listnext(q->b, p)) { prtl = (struct Particle *)listget(q->b, p); prtl->dphi[X] = prtl->dphi[Y] = 0.0; }

		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p); SummationPhaseGradient(pair); }

		bndcond(q, q->cells);
		UpdateSurfaceStress(q);
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->drhodt = 0.0;
			prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
			prtl->_dU[X] = prtl->_dU[Y] = 0.0;
		}
		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p); UpdateForces(pair, q->art_vis, q->delta); }
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->dUdt[X] += q->gravity[X];
			prtl->dUdt[Y] += q->gravity[Y];
		}

		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->R_I[X] = prtl->R[X];
			prtl->R_I[Y] = prtl->R[Y];
			prtl->U[X] += prtl->_dU[X];
			prtl->U[Y] += prtl->_dU[Y];
			prtl->U_I[X] = prtl->U[X];
			prtl->U_I[Y] = prtl->U[Y];
			prtl->R[X] = prtl->R[X] + prtl->U[X] * dt;
			prtl->R[Y] = prtl->R[Y] + prtl->U[Y] * dt;
			prtl->U[X] = prtl->U[X] + prtl->dUdt[X] * dt;
			prtl->U[Y] = prtl->U[Y] + prtl->dUdt[Y] * dt;
			prtl->R[X] = (prtl->R[X] + prtl->R_I[X]) * 0.5;
			prtl->R[Y] = (prtl->R[Y] + prtl->R_I[Y]) * 0.5;
			prtl->U[X] = (prtl->U[X] + prtl->U_I[X]) * 0.5;
			prtl->U[Y] = (prtl->U[Y] + prtl->U_I[Y]) * 0.5;
		}
		bndcond(q, q->cells);

		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p);
			struct Particle *Org = pair->Org, *Dest = pair->Dest;
			double *eij = pair->eij;
			double etai = pair->etai, etaj = pair->etaj;
			double zetai = pair->zetai, zetaj = pair->zetaj;
			struct Force **frc_ij = pair->frc_ij;
			int noi = Org->mtl->number, noj = Dest->mtl->number;
			double rij, rrij;

			rij = pair->rij = dist(pair->Org->R, pair->Dest->R);
			rrij = pair->rrij = 1.0 / (pair->rij + 1.0e-30);
			eij[X] = (Org->R[X] - Dest->R[X]) * rrij;
			eij[Y] = (Org->R[Y] - Dest->R[Y]) * rrij;
			pair->Wij = w(kernel, rij);
			pair->Fij = F(kernel, rij) * rrij;
			pair->sr = 2.0 * etai * etaj * pair->rij /
				(etai * (rij + 2.0 * frc_ij[noj][noi].shear_slip) +
				 etaj * (rij + 2.0 * frc_ij[noi][noj].shear_slip) + 1.0e-30);
			pair->br = 2.0 * zetai * zetaj * rij /
				(zetai * (rij + 2.0 * frc_ij[noj][noi].bulk_slip) +
				 zetaj * (rij + 2.0 * frc_ij[noi][noj].bulk_slip) + 1.0e-30);
		}

		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p); prtl->rho = 0.0; }
		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p); SummationDensity(pair); }
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p); prtl->p = getp(prtl->mtl, prtl->rho); }

		bndcond(q, q->cells);
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->dphi[X] = prtl->dphi[Y] = 0.0;
		}
		for (p = listfirst(q->b); !listendp(q->b, p); p = listnext(q->b, p)) { prtl = (struct Particle *)listget(q->b, p); prtl->dphi[X] = prtl->dphi[Y] = 0.0; }

		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p); SummationPhaseGradient(pair); }

		bndcond(q, q->cells);
		UpdateSurfaceStress(q);
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->drhodt = 0.0;
			prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
			prtl->_dU[X] = prtl->_dU[Y] = 0.0;
		}
		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p); UpdateForces(pair, q->art_vis, q->delta); }
		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->dUdt[X] += q->gravity[X];
			prtl->dUdt[Y] += q->gravity[Y];
		}

		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p); prtl->_dU[X] = prtl->_dU[Y] = 0.0; }
		for (p = listfirst(q->pair_list); !listendp(q->pair_list, p); p = listnext(q->pair_list, p)) { pair = (struct Pair *)listget(q->pair_list, p);
			double rmi = pair->rmi, rmj = pair->rmj;
			double br = pair->br;
			double *eij = pair->eij;
			double sr = pair->sr;
			double Fij = pair->Fij;
			double mi = pair->mi, mj = pair->mj;
			struct Particle *Org = pair->Org, *Dest = pair->Dest;
			double Ti = Org->T, Tj = Dest->T;
			if (Ti == 0 && Tj == 0)
				continue;
			double Vi = mi / Org->rho, Vj = mj / Dest->rho;
			double Random_p, Random_v;
			{
				double x1, x2, wg;
				do {
					x1 = (double)rand() / RAND_MAX;
					x2 = (double)rand() / RAND_MAX;
					x1 = 2.0 * x1 - 1.0;
					x2 = 2.0 * x2 - 1.0;
					wg = x1 * x1 + x2 * x2;
				} while (wg >= 1.0 || wg == 0.0);
				wg = sqrt((-2.0 * log(wg)) / wg);
				Random_p = x1 * wg;
				Random_v = x2 * wg;
			}
			Random_p *= sqrtdt;
			Random_v *= sqrtdt;
			double _dUi[2];
			double Vi2 = Vi * Vi, Vj2 = Vj * Vj;
			double v_eij[2];
			v_eij[X] = -eij[Y];
			v_eij[Y] = eij[X];
			_dUi[X] = v_eij[X] * Random_p *
										sqrt(16.0 * k_bltz * sr * Ti * Tj / (Ti + Tj) *
												 (Vi2 + Vj2) * Fij) +
								eij[X] * Random_v *
										sqrt(16.0 * k_bltz * br * Ti * Tj / (Ti + Tj) *
												 (Vi2 + Vj2) * Fij);
			_dUi[Y] = v_eij[Y] * Random_p *
										sqrt(16.0 * k_bltz * sr * Ti * Tj / (Ti + Tj) *
												 (Vi2 + Vj2) * Fij) +
								eij[Y] * Random_v *
										sqrt(16.0 * k_bltz * br * Ti * Tj / (Ti + Tj) *
												 (Vi2 + Vj2) * Fij);
			if (Dest->btype == 1) {
				Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi * 0.5;
				Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi * 0.5;
				Dest->real->_dU[X] = Dest->real->_dU[X] - _dUi[X] * rmj * 0.5;
				Dest->real->_dU[Y] = Dest->real->_dU[Y] - _dUi[Y] * rmj * 0.5;
			} else {
				Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi;
				Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi;
				Dest->_dU[X] = Dest->_dU[X] - _dUi[X] * rmj;
				Dest->_dU[Y] = Dest->_dU[Y] - _dUi[Y] * rmj;
			}
		}

		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->U[X] += prtl->_dU[X];
			prtl->U[Y] += prtl->_dU[Y];
			prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
			prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
			prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
			prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
		}

		for (p = listfirst(q->parts); !listendp(q->parts, p); p = listnext(q->parts, p)) { prtl = (struct Particle *)listget(q->parts, p);
			prtl->U[X] = prtl->U[X] + prtl->_dU[X];
			prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
		}

		bndcheck(q, q->parts);
		updcells(q);
		bndbuild(q, q->cells, q->materials);
	}
	*pite = ite;
}

/*                         flip_n  flip_t  flip_dphi  periodic */
static const int bnd[4][4] = {
	/* 0 wall     */        {  1,     1,      0,         0 },
	/* 1 periodic */        {  0,     0,      0,         1 },
	/* 2 free-slip */       {  1,     0,      0,         0 },
	/* 3 symmetry */        {  1,     0,      1,         0 },
};

static void applybnd(int type, int c, double refl, double shift,
											double *U_bnd, struct Particle *prtl) {
	int t = c ^ 1;
	if (bnd[type][3])
		prtl->R[c] += shift;
	else
		prtl->R[c] = 2.0 * refl - prtl->R[c];
	if (bnd[type][0]) prtl->U[c] = 2.0 * U_bnd[c] - prtl->U[c];
	if (bnd[type][1]) prtl->U[t] = 2.0 * U_bnd[t] - prtl->U[t];
	if (bnd[type][2]) prtl->dphi[c] = -prtl->dphi[c];
}

static void applycorner(int type,
													double refl_x, double shift_x, double *U_x,
													double refl_y, double shift_y, double *U_y,
													struct Particle *prtl) {
	if (bnd[type][3]) {
		prtl->R[X] += shift_x;
		prtl->R[Y] += shift_y;
	} else {
		prtl->R[X] = 2.0 * refl_x - prtl->R[X];
		prtl->R[Y] = 2.0 * refl_y - prtl->R[Y];
	}
	if (bnd[type][0]) {
		prtl->U[X] = 2.0 * U_y[X] - prtl->U[X];
		prtl->U[Y] = 2.0 * U_x[Y] - prtl->U[Y];
	}
	if (bnd[type][2]) {
		prtl->dphi[X] = -prtl->dphi[X];
		prtl->dphi[Y] = -prtl->dphi[Y];
	}
}

int bndbuild(struct Ini *q, struct List ***c, struct Material *mtl) {
	int i, v, e;
	struct Particle *prtl, *prtl_old;
	struct ListNode *p;
	int mx, my;
	struct List *b;

	mx = q->mx;
	my = q->my;
	b = q->b;

	for (p = listfirst(b); !listendp(b, p); p = listnext(b, p)) { prtl = (struct Particle *)listget(b, p); prtfree(prtl); }
	listclr(b);

	struct {
		int type, coord, ghost, adj, opp, perp_lo, perp_hi;
		double refl, shift, *U_bnd;
	} edges[4] = {
		{q->bxl, X, 0,         1,         mx-2, 1, my-1, 0,              -q->box_size[X], q->uxl},
		{q->bxr, X, mx-1,  mx-2,  1,        1, my-1, q->box_size[X],  q->box_size[X], q->uxr},
		{q->byd, Y, 0,         1,         my-2, 0, mx,   0,              -q->box_size[Y], q->uyd},
		{q->byu, Y, my-1,  my-2,  1,        0, mx,   q->box_size[Y],  q->box_size[Y], q->uyu},
	};
	/* adjust south/north perp ranges to avoid corner overlap */
	if (q->bxl == q->byd) edges[2].perp_lo = 1;
	if (q->bxr == q->byd) edges[2].perp_hi = mx - 1;
	if (q->bxl == q->byu) edges[3].perp_lo = 1;
	if (q->bxr == q->byu) edges[3].perp_hi = mx - 1;
	for (e = 0; e < 4; e++) {
		int type = edges[e].type;
		int coord = edges[e].coord;
		int is_mirror = (type == 0 || type == 2);
		int src = (type == 1) ? edges[e].opp : edges[e].adj;
		for (v = edges[e].perp_lo; v < edges[e].perp_hi; v++) {
			int gi, gj, si, sj;
			if (coord == X) { gi = edges[e].ghost; gj = v; si = src; sj = v; }
			else            { gi = v; gj = edges[e].ghost; si = v; sj = src; }
			listclr(c[gi][gj]);
			for (p = listfirst(c[si][sj]); !listendp(c[si][sj], p); p = listnext(c[si][sj], p)) { prtl_old = (struct Particle *)listget(c[si][sj], p);
				prtl = is_mirror ? prtmirror(prtl_old, mtl) : prtimage(prtl_old);
				applybnd(type, coord, edges[e].refl, edges[e].shift, edges[e].U_bnd, prtl);
				prtl->cell_i = gi;
				prtl->cell_j = gj;
				listins(b, listfirst(b), prtl);
				listins(c[gi][gj], listfirst(c[gi][gj]), prtl);
			}
		}
	}

	struct {
		int type_x, type_y;
		int ghost_i, ghost_j, adj_i, adj_j, opp_i, opp_j;
		double refl_x, shift_x, refl_y, shift_y;
		double *U_x, *U_y;
	} corners[4] = {
		{q->bxl, q->byd, 0,        0,        1,        1,        mx-2, my-2,
		 0,              -q->box_size[X], 0,              -q->box_size[Y], q->uxl, q->uyd},
		{q->bxl, q->byu, 0,        my-1, 1,        my-2, mx-2, 1,
		 0,              -q->box_size[X], q->box_size[Y],  q->box_size[Y], q->uxl, q->uyu},
		{q->bxr, q->byu, mx-1, my-1, mx-2, my-2, 1,       1,
		 q->box_size[X],  q->box_size[X], q->box_size[Y],  q->box_size[Y], q->uxr, q->uyu},
		{q->bxr, q->byd, mx-1, 0,        mx-2, 1,        1,       my-2,
		 q->box_size[X],  q->box_size[X], 0,              -q->box_size[Y], q->uxr, q->uyd},
	};
	for (e = 0; e < 4; e++) {
		if (corners[e].type_x != corners[e].type_y) continue;
		int type = corners[e].type_x;
		int is_mirror = (type == 0 || type == 2);
		int si = (type == 1) ? corners[e].opp_i : corners[e].adj_i;
		int sj = (type == 1) ? corners[e].opp_j : corners[e].adj_j;
		int gi = corners[e].ghost_i, gj = corners[e].ghost_j;
		listclr(c[gi][gj]);
		for (p = listfirst(c[si][sj]); !listendp(c[si][sj], p); p = listnext(c[si][sj], p)) { prtl_old = (struct Particle *)listget(c[si][sj], p);
			prtl = is_mirror ? prtmirror(prtl_old, mtl) : prtimage(prtl_old);
			applycorner(type, corners[e].refl_x, corners[e].shift_x, corners[e].U_x,
												 corners[e].refl_y, corners[e].shift_y, corners[e].U_y, prtl);
			prtl->cell_i = gi;
			prtl->cell_j = gj;
			listins(b, listfirst(b), prtl);
			listins(c[gi][gj], listfirst(c[gi][gj]), prtl);
		}
	}
	return 0;
}

int bndcond(struct Ini *q, struct List ***c) {
	int e, v;
	struct Particle *prtl;
	struct ListNode *p;
	int mx = q->mx, my = q->my;

	struct {
		int type, coord, ghost, perp_lo, perp_hi;
		double refl, shift, *U_bnd;
	} edges[4] = {
		{q->bxl, X, 0,        1, my-1, 0,              -q->box_size[X], q->uxl},
		{q->bxr, X, mx-1, 1, my-1, q->box_size[X],  q->box_size[X], q->uxr},
		{q->byd, Y, 0,        0, mx,   0,              -q->box_size[Y], q->uyd},
		{q->byu, Y, my-1, 0, mx,   q->box_size[Y],  q->box_size[Y], q->uyu},
	};
	if (q->bxl == q->byd) edges[2].perp_lo = 1;
	if (q->bxr == q->byd) edges[2].perp_hi = mx - 1;
	if (q->bxl == q->byu) edges[3].perp_lo = 1;
	if (q->bxr == q->byu) edges[3].perp_hi = mx - 1;

	for (e = 0; e < 4; e++) {
		int type = edges[e].type;
		int coord = edges[e].coord;
		int copy_type = (type == 0 || type == 2) ? 0 : 1;
		for (v = edges[e].perp_lo; v < edges[e].perp_hi; v++) {
			int gi, gj;
			if (coord == X) { gi = edges[e].ghost; gj = v; }
			else             { gi = v; gj = edges[e].ghost; }
			for (p = listfirst(c[gi][gj]); !listendp(c[gi][gj], p); p = listnext(c[gi][gj], p)) { prtl = (struct Particle *)listget(c[gi][gj], p);
				if (prtl->real == NULL) abort();
				prtcopy(prtl, prtl->real, copy_type);
				applybnd(type, coord, edges[e].refl, edges[e].shift, edges[e].U_bnd, prtl);
			}
		}
	}

	struct {
		int type_x, type_y, ghost_i, ghost_j;
		double refl_x, shift_x, refl_y, shift_y;
		double *U_x, *U_y;
	} corners[4] = {
		{q->bxl, q->byd, 0,        0,
		 0,              -q->box_size[X], 0,              -q->box_size[Y], q->uxl, q->uyd},
		{q->bxl, q->byu, 0,        my-1,
		 0,              -q->box_size[X], q->box_size[Y],  q->box_size[Y], q->uxl, q->uyu},
		{q->bxr, q->byu, mx-1, my-1,
		 q->box_size[X],  q->box_size[X], q->box_size[Y],  q->box_size[Y], q->uxr, q->uyu},
		{q->bxr, q->byd, mx-1, 0,
		 q->box_size[X],  q->box_size[X], 0,              -q->box_size[Y], q->uxr, q->uyd},
	};
	for (e = 0; e < 4; e++) {
		if (corners[e].type_x != corners[e].type_y) continue;
		int type = corners[e].type_x;
		int copy_type = (type == 0 || type == 2) ? 0 : 1;
		for (p = listfirst(c[corners[e].ghost_i][corners[e].ghost_j]); !listendp(c[corners[e].ghost_i][corners[e].ghost_j], p); p = listnext(c[corners[e].ghost_i][corners[e].ghost_j], p)) { prtl = (struct Particle *)listget(c[corners[e].ghost_i][corners[e].ghost_j], p);
			if (prtl->real == NULL) abort();
			prtcopy(prtl, prtl->real, copy_type);
			applycorner(type, corners[e].refl_x, corners[e].shift_x, corners[e].U_x,
												 corners[e].refl_y, corners[e].shift_y, corners[e].U_y, prtl);
		}
	}
	return 0;
}

int bndcheck(struct Ini *q, struct List *list) {
	struct ListNode *p;
	struct Particle *prtl;
	double *box_size = q->box_size;
	int types[2][2] = {{q->bxl, q->bxr}, {q->byd, q->byu}};
	int c;

	for (p = listfirst(list); !listendp(list, p); p = listnext(list, p)) { prtl = (struct Particle *)listget(list, p);
		if (fabs(prtl->R[X]) >= 2.0 * box_size[X] ||
				fabs(prtl->R[Y]) >= 2.0 * box_size[Y])
			ABORT(("run away particle"));
		if (prtl->bd == 0) {
			for (c = 0; c < 2; c++) {
				if (prtl->R[c] < 0.0) {
					if (types[c][0] == 1)
						prtl->R[c] += box_size[c];
					else
						prtl->R[c] = -prtl->R[c];
				}
				if (prtl->R[c] > box_size[c]) {
					if (types[c][1] == 1)
						prtl->R[c] -= box_size[c];
					else
						prtl->R[c] = 2.0 * box_size[c] - prtl->R[c];
				}
			}
		}
	}
	return 0;
}
