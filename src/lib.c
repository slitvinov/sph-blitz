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

/* array helpers */

static void *agrow(void *p, int *cap, int sz) {
	*cap = *cap ? *cap * 2 : 16;
	return realloc(p, *cap * sz);
}

static void cellpush(struct Cell *c, struct Particle *p) {
	if (c->n >= c->cap)
		c->data = agrow(c->data, &c->cap, sizeof(*c->data));
	c->data[c->n++] = p;
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

static struct Particle *prtghost(struct Particle *s, int btype, struct Material *mtl) {
	struct Particle *q;

	q = malloc(sizeof(*q));
	if (q == NULL) abort();
	*q = *s;
	q->bd = 1;
	q->btype = btype;
	q->ID = 0;
	q->real = s;
	q->mtl = mtl;
	q->rho_I = s->rho;
	q->phi = phinew();
	return q;
}

struct Particle *prtimage(struct Particle *s) {
	return prtghost(s, 1, s->mtl);
}

struct Particle *prtmirror(struct Particle *s, struct Material *material) {
	return prtghost(s, 0, material);
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
	rewind(f);
	while (fscanf(f, "%s", Key_word) == 1) {
		if (!strcmp(Key_word, "BOUNDARY")) {
			n = fscanf(f, "%d %lf %lf %d %lf %lf %d %lf %lf %d %lf %lf", &q->bxl,
								 &q->uxl[X], &q->uxl[Y], &q->bxr, &q->uxr[X], &q->uxr[Y],
								 &q->byd, &q->uyd[X], &q->uyd[Y], &q->byu, &q->uyu[X],
								 &q->uyu[Y]);
			if (n != 3 * 4)
				ABORT(("can't read BOUNDARY keyword (n = %d)", n));
		}
		if (!strcmp(Key_word, "MATERIALS")) {
			nmat = q->nmat;
			q->materials = malloc(nmat * sizeof(*q->materials));
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
		}
		if (!strcmp(Key_word, "FORCES")) {
			nmat = q->nmat;
			q->forces = malloc(nmat * sizeof(*q->forces));
			for (k = 0; k < nmat; k++)
				q->forces[k] = malloc(nmat * sizeof(*q->forces[k]));
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
	}
	fclose(f);
	if (system(mkdir) != 0)
		ABORT(("command '%s' faild", mkdir));
	q->box_size[0] = q->nx * q->cs;
	q->box_size[1] = q->ny * q->cs;
	q->delta = q->cs / q->cr;
	delta = q->delta;

	q->mx = q->nx + 2;
	q->my = q->ny + 2;
	q->cells = malloc(q->mx * sizeof(*q->cells));
	for (i = 0; i < q->mx; i++)
		q->cells[i] = calloc(q->my, sizeof(struct Cell));

	q->nnp = NULL; q->nnnp = 0; q->nnpcap = 0;
	q->bnd = NULL; q->nbnd = 0; q->bndcap = 0;
	q->pairs = NULL; q->npairs = 0; q->pcap = 0;

	q->delta2 = delta * delta;
	q->delta3 = delta * delta * delta;
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

	q->parts = NULL;
	q->nparts = 0;
	q->partcap = 0;

	nmat = q->nmat;
	idmax = 0;

	{
		int mx = q->mx, my = q->my;
		struct Edge e[4] = {
			{q->bxl, X, 0,    1,    mx-2, 1, my-1, 0,             -q->box_size[X], q->uxl},
			{q->bxr, X, mx-1, mx-2, 1,    1, my-1, q->box_size[X], q->box_size[X], q->uxr},
			{q->byd, Y, 0,    1,    my-2, 0, mx,   0,             -q->box_size[Y], q->uyd},
			{q->byu, Y, my-1, my-2, 1,    0, mx,   q->box_size[Y], q->box_size[Y], q->uyu},
		};
		if (q->bxl == q->byd) e[2].perp_lo = 1;
		if (q->bxr == q->byd) e[2].perp_hi = mx - 1;
		if (q->bxl == q->byu) e[3].perp_lo = 1;
		if (q->bxr == q->byu) e[3].perp_hi = mx - 1;
		memcpy(q->edges, e, sizeof(e));

		struct Corner c[4] = {
			{q->bxl, q->byd, 0,    0,    1,    1,    mx-2, my-2,
			 0,             -q->box_size[X], 0,             -q->box_size[Y], q->uxl, q->uyd},
			{q->bxl, q->byu, 0,    my-1, 1,    my-2, mx-2, 1,
			 0,             -q->box_size[X], q->box_size[Y], q->box_size[Y], q->uxl, q->uyu},
			{q->bxr, q->byu, mx-1, my-1, mx-2, my-2, 1,    1,
			 q->box_size[X], q->box_size[X], q->box_size[Y], q->box_size[Y], q->uxr, q->uyu},
			{q->bxr, q->byd, mx-1, 0,    mx-2, 1,    1,    my-2,
			 q->box_size[X], q->box_size[X], 0,             -q->box_size[Y], q->uxr, q->uyd},
		};
		memcpy(q->corners, c, sizeof(c));
	}

	return 0;
}

int updcells(struct Ini *q) {
	int i, j, n;
	int k, m;
	double cs = q->cs;

	for (i = 0; i < q->mx; i++)
		for (j = 0; j < q->my; j++)
			q->cells[i][j].n = 0;
	for (n = 0; n < q->nparts; n++) {
		struct Particle *prtl = q->parts[n];
		k = (int)((prtl->R[0] + cs) / cs);
		m = (int)((prtl->R[1] + cs) / cs);
		prtl->cell_i = k;
		prtl->cell_j = m;
		cellpush(&q->cells[k][m], prtl);
	}
	return 0;
}

int mknnp(struct Ini *q, double point[2]) {
	int i, j;
	int k, m, n;
	double dstc;
	struct Particle *prtl;

	int mx;
	int my;
	double cs;
	double h;

	mx = q->mx;
	my = q->my;
	cs = q->cs;
	h = q->h;

	q->nnnp = 0;
	k = (int)((point[0] + cs) / cs);
	m = (int)((point[1] + cs) / cs);
	for (i = k - 1; i <= k + 1; i++)
		for (j = m - 1; j <= m + 1; j++)
			if (i < mx && j < my && i >= 0 && j >= 0)
				for (n = 0; n < q->cells[i][j].n; n++) {
					prtl = q->cells[i][j].data[n];
					dstc = dist(point, prtl->R);
					if (dstc < h) {
						if (q->nnnp >= q->nnpcap)
							q->nnp = agrow(q->nnp, &q->nnpcap, sizeof(*q->nnp));
						q->nnp[q->nnnp++] = prtl;
					}
				}
	return 0;
}

int mkpairs(struct Ini *q, struct Force **forces,
											 struct Kernel *kernel) {
	int i, j, k, m, n, n1;
	double dstc;
	double sm2;
	struct Particle *prtl_org, *prtl_dest;
	struct Pair *pair;

	double h;
	double cs;

	cs = q->cs;
	h = q->h;

	sm2 = h * h;

	q->npairs = 0;
	for (n = 0; n < q->nparts; n++) {
		prtl_org = q->parts[n];
		if (prtl_org->bd == 0) {
			i = (int)((prtl_org->R[0] + cs) / cs);
			j = (int)((prtl_org->R[1] + cs) / cs);
			for (k = i - 1; k <= i + 1; k++)
				for (m = j - 1; m <= j + 1; m++) {
					for (n1 = 0; n1 < q->cells[k][m].n; n1++) {
						prtl_dest = q->cells[k][m].data[n1];
						double dx = prtl_org->R[X] - prtl_dest->R[X];
						double dy = prtl_org->R[Y] - prtl_dest->R[Y];
						dstc = dx * dx + dy * dy;
						if (dstc <= sm2 && prtl_org->ID >= prtl_dest->ID) {
							double rij, etai, etaj, zetai, zetaj;
							int noi, noj;
							struct Force **frc_ij;
							struct Particle *Org, *Dest;

							if (q->npairs >= q->pcap)
								q->pairs = agrow(q->pairs, &q->pcap, sizeof(*q->pairs));
							pair = &q->pairs[q->npairs++];
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
						}
					}
				}
		}
	}
	return 0;
}

void mkparts(struct Ini *q, struct Material *materials,
														 struct Ini *ini) {

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

	mx = q->mx;
	my = q->my;
	cs = q->cs;
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
						if (q->nparts >= q->partcap)
							q->parts = agrow(q->parts, &q->partcap, sizeof(*q->parts));
						q->parts[q->nparts++] = prtl;
						cellpush(&q->cells[i][j], prtl);
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
				if (q->nparts >= q->partcap)
					q->parts = agrow(q->parts, &q->partcap, sizeof(*q->parts));
				q->parts[q->nparts++] = prtl;
				i = (int)(prtl->R[0] / cs) + 1;
				j = (int)(prtl->R[1] / cs) + 1;
				prtl->cell_i = i;
				prtl->cell_j = j;
				cellpush(&q->cells[i][j], prtl);
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

	mx = q->mx;
	my = q->my;
	for (i = 0; i < mx; i++) {
		for (j = 0; j < my; j++)
			free(q->cells[i][j].data);
		free(q->cells[i]);
	}
	free(q->cells);
	free(q->nnp);

	for (i = 0; i < q->nmat; i++)
		free(q->forces[i]);
	free(q->forces);
	free(q->materials);

	free(q->pairs);

	for (i = 0; i < q->nparts; i++)
		prtfree(q->parts[i]);
	free(q->parts);

	for (i = 0; i < q->nbnd; i++)
		prtfree(q->bnd[i]);
	free(q->bnd);

	return 0;
}

static void UpdateSurfaceStress(struct Ini *q) {
	double epsilon = 1.0e-30;
	double interm0, interm1, interm2;
	struct Particle *prtl;
	int i;

	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
		interm0 = 1.0 / (vnorm(prtl->dphi) + epsilon);
		interm1 = 0.5 * sqdiff(prtl->dphi);
		interm2 = prtl->dphi[X] * prtl->dphi[Y];
		prtl->dphi[0] = interm1 * interm0;
		prtl->dphi[1] = interm2 * interm0;
	}
	for (i = 0; i < q->nbnd; i++) {
		prtl = q->bnd[i];
		interm0 = vnorm(prtl->dphi) + epsilon;
		interm1 = 0.5 * sqdiff(prtl->dphi);
		interm2 = prtl->dphi[X] * prtl->dphi[Y];
		prtl->dphi[0] = interm1 / interm0;
		prtl->dphi[1] = interm2 / interm0;
	}
}

int prtout(struct Ini *q, struct Material *materials, double Time) {
	char file_name[FILENAME_MAX], file_list[FILENAME_MAX];
	double Itime;
	FILE *f;
	int i, j, n;
	int nmat;
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
		for (n = 0; n < q->nparts; n++) {
			prtl = q->parts[n];
			if (strcmp(materials[i].name, prtl->mtl->name) == 0) {
				j++;
				if (j == 1)
					fprintf(f, "zone t='%s' \n", materials[i].name);
				fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0],
								prtl->U[1]);
			}
		}
		for (n = 0; n < q->nbnd; n++) {
			prtl = q->bnd[n];
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

int rstout(struct Ini *q, double Time) {
	int n;
	char file_name[FILENAME_MAX];
	struct Particle *prtl;
	FILE *f;

	strcpy(file_name, q->project);
	strcat(file_name, ".txt");
	f = fopen(file_name, "w");
	if (!f)
		ABORT(("can't write '%s'", file_name));
	fprintf(f, "%.6g\n", Time);
	fprintf(f, "%d\n", q->nparts);
	for (n = 0; n < q->nparts; n++) {
		prtl = q->parts[n];
		fprintf(f, "%s %.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
						prtl->mtl->name, prtl->R[0], prtl->R[1], prtl->U[0],
						prtl->U[1], prtl->rho, prtl->p, prtl->T);
	}
	fclose(f);
	return 0;
}

void volmass(struct Ini *q, struct Kernel *kernel) {
	double reciprocV;
	double dstc;
	int i, n;
	struct Particle *prtl_org, *prtl_dest;

	for (n = 0; n < q->nparts; n++) {
		prtl_org = q->parts[n];
		mknnp(q, prtl_org->R);
		reciprocV = 0.0;
		for (i = 0; i < q->nnnp; i++) {
			prtl_dest = q->nnp[i];
			dstc = dist(prtl_org->R, prtl_dest->R);
			reciprocV += w(kernel, dstc);
		}
		reciprocV = 1.0 / reciprocV;
		prtl_org->V = reciprocV;
		prtl_org->m = prtl_org->rho * reciprocV;
	}
}

static void halfstep(struct Ini *q) {
	int i;
	struct Pair *pair;
	struct Particle *prtl;

	for (i = 0; i < q->nparts; i++) { prtl = q->parts[i]; prtl->rho = 0.0; }
	for (i = 0; i < q->npairs; i++) SummationDensity(&q->pairs[i]);
	for (i = 0; i < q->nparts; i++) { prtl = q->parts[i]; prtl->p = getp(prtl->mtl, prtl->rho); }

	bndcond(q);
	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
		prtl->dphi[X] = prtl->dphi[Y] = 0.0;
	}
	for (i = 0; i < q->nbnd; i++) { prtl = q->bnd[i]; prtl->dphi[X] = prtl->dphi[Y] = 0.0; }

	for (i = 0; i < q->npairs; i++) SummationPhaseGradient(&q->pairs[i]);

	bndcond(q);
	UpdateSurfaceStress(q);
	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
		prtl->drhodt = 0.0;
		prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
		prtl->_dU[X] = prtl->_dU[Y] = 0.0;
	}
	for (i = 0; i < q->npairs; i++) UpdateForces(&q->pairs[i], q->art_vis, q->delta);
	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
		prtl->dUdt[X] += q->gravity[X];
		prtl->dUdt[Y] += q->gravity[Y];
	}
}

void step(int *pite, struct Ini *q, double *Time, double tout,
					struct Kernel *kernel) {
	double dt;
	double integeral_time;
	double sqrtdt;
	int i;
	int ite;
	struct Pair *pair;
	struct Particle *prtl;

	ite = *pite;

	integeral_time = 0;
	while (integeral_time < tout) {
		{
			double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
			for (i = 0; i < q->nparts; i++) {
				prtl = q->parts[i];
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
		mkpairs(q, q->forces, kernel);
		halfstep(q);

		for (i = 0; i < q->nparts; i++) {
			prtl = q->parts[i];
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
		bndcond(q);

		for (i = 0; i < q->npairs; i++) {
			pair = &q->pairs[i];
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

		halfstep(q);

		for (i = 0; i < q->nparts; i++) { prtl = q->parts[i]; prtl->_dU[X] = prtl->_dU[Y] = 0.0; }
		for (i = 0; i < q->npairs; i++) {
			pair = &q->pairs[i];
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

		for (i = 0; i < q->nparts; i++) {
			prtl = q->parts[i];
			prtl->U[X] += prtl->_dU[X];
			prtl->U[Y] += prtl->_dU[Y];
			prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
			prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
			prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
			prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
		}

		for (i = 0; i < q->nparts; i++) {
			prtl = q->parts[i];
			prtl->U[X] = prtl->U[X] + prtl->_dU[X];
			prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
		}

		bndcheck(q);
		updcells(q);
		bndbuild(q, q->materials);
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

int bndbuild(struct Ini *q, struct Material *mtl) {
	int i, v, e, n;
	struct Particle *prtl, *prtl_old;
	struct Edge *ed;
	struct Corner *cn;

	for (i = 0; i < q->nbnd; i++)
		prtfree(q->bnd[i]);
	q->nbnd = 0;

	for (e = 0; e < 4; e++) {
		ed = &q->edges[e];
		int is_mirror = (ed->type == 0 || ed->type == 2);
		int src = (ed->type == 1) ? ed->opp : ed->adj;
		for (v = ed->perp_lo; v < ed->perp_hi; v++) {
			int gi, gj, si, sj;
			if (ed->coord == X) { gi = ed->ghost; gj = v; si = src; sj = v; }
			else                { gi = v; gj = ed->ghost; si = v; sj = src; }
			q->cells[gi][gj].n = 0;
			for (n = 0; n < q->cells[si][sj].n; n++) {
				prtl_old = q->cells[si][sj].data[n];
				prtl = is_mirror ? prtmirror(prtl_old, mtl) : prtimage(prtl_old);
				applybnd(ed->type, ed->coord, ed->refl, ed->shift, ed->U_bnd, prtl);
				prtl->cell_i = gi;
				prtl->cell_j = gj;
				if (q->nbnd >= q->bndcap)
					q->bnd = agrow(q->bnd, &q->bndcap, sizeof(*q->bnd));
				q->bnd[q->nbnd++] = prtl;
				cellpush(&q->cells[gi][gj], prtl);
			}
		}
	}

	for (e = 0; e < 4; e++) {
		cn = &q->corners[e];
		if (cn->type_x != cn->type_y) continue;
		int type = cn->type_x;
		int is_mirror = (type == 0 || type == 2);
		int si = (type == 1) ? cn->opp_i : cn->adj_i;
		int sj = (type == 1) ? cn->opp_j : cn->adj_j;
		q->cells[cn->ghost_i][cn->ghost_j].n = 0;
		for (n = 0; n < q->cells[si][sj].n; n++) {
			prtl_old = q->cells[si][sj].data[n];
			prtl = is_mirror ? prtmirror(prtl_old, mtl) : prtimage(prtl_old);
			applycorner(type, cn->refl_x, cn->shift_x, cn->U_x,
			                  cn->refl_y, cn->shift_y, cn->U_y, prtl);
			prtl->cell_i = cn->ghost_i;
			prtl->cell_j = cn->ghost_j;
			if (q->nbnd >= q->bndcap)
				q->bnd = agrow(q->bnd, &q->bndcap, sizeof(*q->bnd));
			q->bnd[q->nbnd++] = prtl;
			cellpush(&q->cells[cn->ghost_i][cn->ghost_j], prtl);
		}
	}
	return 0;
}

int bndcond(struct Ini *q) {
	int e, v, n;
	struct Particle *prtl;
	struct Edge *ed;
	struct Corner *cn;

	for (e = 0; e < 4; e++) {
		ed = &q->edges[e];
		int copy_type = (ed->type == 0 || ed->type == 2) ? 0 : 1;
		for (v = ed->perp_lo; v < ed->perp_hi; v++) {
			int gi, gj;
			if (ed->coord == X) { gi = ed->ghost; gj = v; }
			else                { gi = v; gj = ed->ghost; }
			for (n = 0; n < q->cells[gi][gj].n; n++) {
				prtl = q->cells[gi][gj].data[n];
				if (prtl->real == NULL) abort();
				prtcopy(prtl, prtl->real, copy_type);
				applybnd(ed->type, ed->coord, ed->refl, ed->shift, ed->U_bnd, prtl);
			}
		}
	}

	for (e = 0; e < 4; e++) {
		cn = &q->corners[e];
		if (cn->type_x != cn->type_y) continue;
		int copy_type = (cn->type_x == 0 || cn->type_x == 2) ? 0 : 1;
		for (n = 0; n < q->cells[cn->ghost_i][cn->ghost_j].n; n++) {
			prtl = q->cells[cn->ghost_i][cn->ghost_j].data[n];
			if (prtl->real == NULL) abort();
			prtcopy(prtl, prtl->real, copy_type);
			applycorner(cn->type_x, cn->refl_x, cn->shift_x, cn->U_x,
			                        cn->refl_y, cn->shift_y, cn->U_y, prtl);
		}
	}
	return 0;
}

int bndcheck(struct Ini *q) {
	int i, c;
	struct Particle *prtl;
	double *box_size = q->box_size;
	int types[2][2] = {{q->bxl, q->bxr}, {q->byd, q->byu}};

	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
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
