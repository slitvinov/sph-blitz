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

static double W(struct Ini *q, double r) {
	double d = 3.0 * r * q->rh;
	double a = 3.0 - d, b = 2.0 - d, c = 1.0 - d;

	if (d < 1.0)
		return q->fw * (a*a*a*a*a - 6.0*b*b*b*b*b + 15.0*c*c*c*c*c);
	if (d < 2.0)
		return q->fw * (a*a*a*a*a - 6.0*b*b*b*b*b);
	if (d < 3.0)
		return q->fw * a*a*a*a*a;
	return 0.0;
}

static double dW(struct Ini *q, double r) {
	double d = 3.0 * r * q->rh;
	double a = 3.0 - d, b = 2.0 - d, c = 1.0 - d;

	if (d < 1.0)
		return q->fg * (a*a*a*a - 6.0*b*b*b*b + 15.0*c*c*c*c);
	if (d < 2.0)
		return q->fg * (a*a*a*a - 6.0*b*b*b*b);
	if (d < 3.0)
		return q->fg * a*a*a*a;
	return 0.0;
}

static double getp(struct Material *m, double rho) {
	return m->b0 * pow(rho / m->rho0, m->gamma);
}


/* particle */

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
	q->bd = 0;
	q->btype = 0;
	q->mtl = material;
	q->R[X] = position[X];
	q->R[Y] = position[Y];
	q->rho = density;
	q->p = pressure;
	q->T = temperature;
	q->U[X] = velocity[X];
	q->U[Y] = velocity[Y];
	q->U_I[X] = velocity[X];
	q->U_I[Y] = velocity[Y];
	q->m = 0.0;
	q->R_I[X] = position[X];
	q->R_I[Y] = position[Y];
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
	q->real = s;
	q->mtl = mtl;
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
	q->p = s->p;
	q->T = s->T;
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
#define K_BLTZ (1.380662e-023 / 0.02 / 0.02 / 0.02)

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

#define PAIRVARS \
	double rij, rrij, eij[2], Wij, Fij, sr, br

#define PAIRCOMP(a, b, q, d2) do { \
	double _ei = (a)->mtl->eta, _ej = (b)->mtl->eta; \
	double _zi = (a)->mtl->zeta, _zj = (b)->mtl->zeta; \
	int _ni = (a)->mtl->number, _nj = (b)->mtl->number; \
	rij = sqrt(d2); \
	rrij = 1.0 / (rij + 1.0e-30); \
	eij[X] = ((a)->R[X] - (b)->R[X]) * rrij; \
	eij[Y] = ((a)->R[Y] - (b)->R[Y]) * rrij; \
	Wij = W((q), rij); \
	Fij = dW((q), rij) * rrij; \
	sr = 2.0 * _ei * _ej * rij / \
		(_ei * (rij + 2.0 * (q)->forces[_nj][_ni].shear_slip) + \
		 _ej * (rij + 2.0 * (q)->forces[_ni][_nj].shear_slip) + 1.0e-30); \
	br = 2.0 * _zi * _zj * rij / \
		(_zi * (rij + 2.0 * (q)->forces[_nj][_ni].bulk_slip) + \
		 _zj * (rij + 2.0 * (q)->forces[_ni][_nj].bulk_slip) + 1.0e-30); \
} while(0)

static void updforces(struct Particle *Org, struct Particle *Dest,
	double rij, double rrij, double eij[2], double Wij, double Fij,
	double sr, double br, double art_vis, double delta) {
	double mi = Org->m, mj = Dest->m;
	double rmi = 1.0 / mi, rmj = 1.0 / mj;
	double rhoi = Org->rho, rhoj = Dest->rho;
	double Vi = mi / rhoi, Vj = mj / rhoj;
	double Vi2 = Vi * Vi, Vj2 = Vj * Vj;
	double pi = Org->p, pj = Dest->p;
	double Uij[2], Uijdoteij, c;
	double dPdti[2], dUi[2], dx, dy;
	double theta, NR_vis;

	Uij[X] = Org->U[X] - Dest->U[X];
	Uij[Y] = Org->U[Y] - Dest->U[Y];
	Uijdoteij = Uij[X] * eij[X] + Uij[Y] * eij[Y];
	theta = Uijdoteij * rij * delta / (rij * rij + 0.01 * delta * delta);
	NR_vis = Uijdoteij > 0.0 ? 0.0
		: art_vis * theta * (rhoi * sqrt(Org->mtl->gamma * Org->p / Org->rho) * mj + rhoj * sqrt(Dest->mtl->gamma * Dest->p / Dest->rho) * mi) / (mi + mj);
	c = theta * Wij * art_vis / (rhoi + rhoj);
	dUi[X] = -eij[X] * c;
	dUi[Y] = -eij[Y] * c;
	dx = Org->U[X] * Vi2 - Dest->U[X] * Vj2;
	dy = Org->U[Y] * Vi2 - Dest->U[Y] * Vj2;
	dPdti[X] = eij[X] * Fij * rij * (pi * Vi2 + pj * Vj2) -
		((Uij[X] - eij[X] * Uijdoteij) * sr +
		 eij[X] * (Uijdoteij * 2.0 * br + NR_vis)) * Fij * (Vi2 + Vj2);
	dPdti[Y] = eij[Y] * Fij * rij * (pi * Vi2 + pj * Vj2) -
		((Uij[Y] - eij[Y] * Uijdoteij) * sr +
		 eij[Y] * (Uijdoteij * 2.0 * br + NR_vis)) * Fij * (Vi2 + Vj2);
	double si[2], sj[2], fi[2], fj[2];
	si[X] = Org->dphi[X]; si[Y] = Org->dphi[Y];
	sj[X] = Dest->dphi[X]; sj[Y] = Dest->dphi[Y];
	fi[X] = si[X]*eij[X] + si[Y]*eij[Y]; fi[Y] = si[Y]*eij[X] - si[X]*eij[Y];
	fj[X] = sj[X]*eij[X] + sj[Y]*eij[Y]; fj[Y] = sj[Y]*eij[X] - sj[X]*eij[Y];
	dPdti[X] += (fi[X]*Vi2 + fj[X]*Vj2) * rij * Fij;
	dPdti[Y] += (fi[Y]*Vi2 + fj[Y]*Vj2) * rij * Fij;
	Org->_dU[X] += dUi[X]*mi;  Org->_dU[Y] += dUi[Y]*mi;
	Dest->_dU[X] -= dUi[X]*mj; Dest->_dU[Y] -= dUi[Y]*mj;
	Org->dUdt[X] += dPdti[X]*rmi;  Org->dUdt[Y] += dPdti[Y]*rmi;
	Dest->dUdt[X] -= dPdti[X]*rmj; Dest->dUdt[Y] -= dPdti[Y]*rmj;
}

int iniread(char *project_name, struct Ini *q) {
	char Key_word[FILENAME_MAX];
	char inputfile[FILENAME_MAX];
	char *mkdir = "mkdir -p outdata";
	double delta, sound, numax, sigmax;
	FILE *f;
	int i, j, k;
	int nx, ny;
	int l;
	int m;
	int n;
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
			{"CELLS",              "%d %d",           {&nx, &ny}},
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
				int mtype;
				mtl = &q->materials[k];
				mtl->number = k;
				if (fscanf(f, "%s %d", mtl->name, &mtype) != 2)
					ABORT(("can't read material from '%s'", inputfile));
				if (fscanf(f, "%lf %lf %lf %lf %lf", &mtl->eta, &mtl->zeta, &mtl->gamma,
									 &mtl->rho0, &mtl->a0) != 5)
					ABORT(("can't read materal parameters from '%s'", inputfile));
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
					double eps;
					force = &q->forces[k][m];
					if (fscanf(f, "%lf %lf %lf %lf", &eps, &force->sigma,
										 &force->shear_slip, &force->bulk_slip) != 4)
						ABORT(("can't read force from '%s'", inputfile));
				}
		}
	}
	fclose(f);
	if (system(mkdir) != 0)
		ABORT(("command '%s' faild", mkdir));
	q->box_size[0] = nx * q->cs;
	q->box_size[1] = ny * q->cs;
	q->delta = q->cs / q->cr;
	delta = q->delta;
	{
		double norm = 63.0 / 478.0 / 3.141592653589793;
		q->rh = 1.0 / q->h;
		q->fw = norm * pow(q->rh, 2);
		q->fg = 15.0 * norm * pow(q->rh, 3);
	}

	q->mx = nx + 2;
	q->my = ny + 2;
	q->cells = malloc(q->mx * sizeof(*q->cells));
	for (i = 0; i < q->mx; i++)
		q->cells[i] = calloc(q->my, sizeof(struct Cell));

	q->nnp = NULL; q->nnnp = 0; q->nnpcap = 0;
	q->bnd = NULL; q->nbnd = 0; q->bndcap = 0;

	numax = 0.0;
	sigmax = 0.0;
	for (k = 0; k < nmat; k++) {
		numax = dmax(numax, dmax(q->materials[k].eta, q->materials[k].zeta) / q->materials[k].rho0);
		for (l = 0; l < nmat; l++)
			sigmax = dmax(sigmax, q->forces[k][l].sigma);
	}
	q->dt_g_vis = dmin(sqrt(delta / vnorm(q->gravity)),
											0.5 * delta * delta / numax);
	q->dt_surf = 0.4 * sqrt(delta * delta * delta / sigmax);
	sound = dmax(vnorm(q->gravity), numax);
	sound = dmax(sigmax, sound);
	for (k = 0; k < nmat; k++)
		q->materials[k].b0 = q->materials[k].a0 * sound / q->materials[k].gamma;

	q->parts = NULL;
	q->nparts = 0;
	q->partcap = 0;

	nmat = q->nmat;

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

	for (i = 0; i < q->nparts; i++)
		prtfree(q->parts[i]);
	free(q->parts);

	for (i = 0; i < q->nbnd; i++)
		prtfree(q->bnd[i]);
	free(q->bnd);

	return 0;
}

static void updsurface(struct Ini *q) {
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

void volmass(struct Ini *q) {
	
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
			reciprocV += W(q, dstc);
		}
		reciprocV = 1.0 / reciprocV;
		
		prtl_org->m = prtl_org->rho * reciprocV;
	}
}

#define PAIRLOOP(q) \
	for (n = 0; n < (q)->nparts; n++) { \
	a = (q)->parts[n]; \
	ci = (int)((a->R[0] + (q)->cs) / (q)->cs); \
	cj = (int)((a->R[1] + (q)->cs) / (q)->cs); \
	for (k = ci - 1; k <= ci + 1; k++) \
	for (m = cj - 1; m <= cj + 1; m++) \
	for (n1 = 0; n1 < (q)->cells[k][m].n; n1++) { \
	b = (q)->cells[k][m].data[n1]; \
	{ double dx_ = a->R[X]-b->R[X], dy_ = a->R[Y]-b->R[Y]; \
	d2 = dx_*dx_ + dy_*dy_; } \
	if (d2 <= (q)->h*(q)->h && a >= b) { \
	PAIRCOMP(a, b, q, d2);

#define ENDPAIR }}}

static void halfstep(struct Ini *q) {
	int i, n, n1, k, m, ci, cj;
	struct Particle *prtl, *a, *b;
	PAIRVARS;
	double d2;

	for (i = 0; i < q->nparts; i++) q->parts[i]->rho = 0.0;
	PAIRLOOP(q)
		a->rho += a->m * Wij;
		if (a != b) b->rho += b->m * Wij;
	ENDPAIR
	for (i = 0; i < q->nparts; i++) { prtl = q->parts[i]; prtl->p = getp(prtl->mtl, prtl->rho); }

	bndcond(q);
	for (i = 0; i < q->nparts; i++) { prtl = q->parts[i]; prtl->dphi[X] = prtl->dphi[Y] = 0.0; }
	for (i = 0; i < q->nbnd; i++) { prtl = q->bnd[i]; prtl->dphi[X] = prtl->dphi[Y] = 0.0; }
	PAIRLOOP(q) {
		double mi = a->m, mj = b->m;
		double Vi = mi / a->rho, Vj = mj / b->rho;
		double Vi2 = Vi*Vi, Vj2 = Vj*Vj;
		double c = Fij * rij * q->forces[a->mtl->number][b->mtl->number].sigma;
		double px = eij[X]*c, py = eij[Y]*c;
		a->dphi[X] += px*Vj2/Vi; a->dphi[Y] += py*Vj2/Vi;
		b->dphi[X] -= px*Vi2/Vj; b->dphi[Y] -= py*Vi2/Vj;
	} ENDPAIR

	bndcond(q);
	updsurface(q);
	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
		prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
		prtl->_dU[X] = prtl->_dU[Y] = 0.0;
	}
	PAIRLOOP(q)
		updforces(a, b, rij, rrij, eij, Wij, Fij, sr, br, q->art_vis, q->delta);
	ENDPAIR
	for (i = 0; i < q->nparts; i++) {
		prtl = q->parts[i];
		prtl->dUdt[X] += q->gravity[X];
		prtl->dUdt[Y] += q->gravity[Y];
	}
}

void step(int *pite, struct Ini *q, double *Time, double tout) {
	double dt;
	double integeral_time;
	double sqrtdt;
	int i, n, n1, k, m, ci, cj;
	int ite;
	struct Particle *prtl, *a, *b;
	PAIRVARS;
	double d2;

	ite = *pite;

	integeral_time = 0;
	while (integeral_time < tout) {
		{
			double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
			for (i = 0; i < q->nparts; i++) {
				prtl = q->parts[i];
				Cs_max = dmax(Cs_max, sqrt(prtl->mtl->gamma * prtl->p / prtl->rho));
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
		bndcheck(q);
		updcells(q);
		bndbuild(q, q->materials);

		halfstep(q);

		for (i = 0; i < q->nparts; i++) { prtl = q->parts[i]; prtl->_dU[X] = prtl->_dU[Y] = 0.0; }
		PAIRLOOP(q) {
			double rmi = 1.0 / a->m, rmj = 1.0 / b->m;
			double Ti = a->T, Tj = b->T;
			if (Ti == 0 && Tj == 0)
				continue;
			double mi = a->m, mj = b->m;
			double Vi = mi / a->rho, Vj = mj / b->rho;
			double Rp, Rv;
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
				Rp = x1 * wg * sqrtdt;
				Rv = x2 * wg * sqrtdt;
			}
			double _dUi[2];
			double Vi2 = Vi * Vi, Vj2 = Vj * Vj;
			double ve[2];
			double kf = 16.0 * K_BLTZ * Ti * Tj / (Ti + Tj) * (Vi2 + Vj2) * Fij;
			ve[X] = -eij[Y]; ve[Y] = eij[X];
			_dUi[X] = ve[X]*Rp*sqrt(kf*sr) + eij[X]*Rv*sqrt(kf*br);
			_dUi[Y] = ve[Y]*Rp*sqrt(kf*sr) + eij[Y]*Rv*sqrt(kf*br);
			if (b->btype == 1) {
				a->_dU[X] += _dUi[X] * rmi * 0.5;
				a->_dU[Y] += _dUi[Y] * rmi * 0.5;
				b->real->_dU[X] -= _dUi[X] * rmj * 0.5;
				b->real->_dU[Y] -= _dUi[Y] * rmj * 0.5;
			} else {
				a->_dU[X] += _dUi[X] * rmi;
				a->_dU[Y] += _dUi[Y] * rmi;
				b->_dU[X] -= _dUi[X] * rmj;
				b->_dU[Y] -= _dUi[Y] * rmj;
		} } ENDPAIR

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
