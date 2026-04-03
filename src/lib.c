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

int list_endp(struct List *q, struct ListNode *n) { return n->next == q->node; }

struct ListNode *list_first(struct List *q) {
  return q->node;
}

struct ListNode *list_next(struct List *q, struct ListNode *n) {
  (void)q;
  return n->next;
}

void *list_retrieve(struct List *q, struct ListNode *n) {
  (void)q;
  return n->next->data;
}

void list_insert(struct List *q, struct ListNode *n, void *p) {
  struct ListNode *node;

  node = malloc(sizeof(struct ListNode));
  node->data = p;
  node->next = n->next;
  n->next = node;
}

void list_remove(struct List *q, struct ListNode *p) {
  struct ListNode *t = p->next;

  p->next = t->next;
  free(t);
}

void list_clear(struct List *q) {
  while (q->node != q->node->next)
    list_remove(q, q->node);
}

struct List *list_ini(void) {
  struct List *q;
  struct ListNode *node;

  q = malloc(sizeof(struct List));
  node = malloc(sizeof(struct ListNode));
  node->data = NULL;
  node->next = node;
  q->node = node;
  return q;
}

void list_fin(struct List *q) {
  while (q->node != q->node->next)
    list_remove(q, q->node);
  free(q->node);
  free(q);
}

/* kernel */

struct Kernel {
  double reciprocH;
  double factorW;
  double factorGradW;
  double smoothingLength;
};

static double pi = 3.141592653589793;
struct Kernel *kernel_ini(double smoothingLength) {
  double norm;
  struct Kernel *q;

  q = malloc(sizeof(*q));
  if (q == NULL) {
    ABORT(("fail to alloc"));
    return q;
  }

  norm = 63.0 / 478.0 / pi;
  q->smoothingLength = smoothingLength;
  q->reciprocH = 1.0 / smoothingLength;
  q->factorW = norm * pow(q->reciprocH, 2);
  q->factorGradW = 15.0 * norm * pow(q->reciprocH, 3);
  return q;
}

int kernel_fin(struct Kernel *q) {
  free(q);
  return 0;
}

double w(struct Kernel *q, double r) {
  double d = 3.0 * r * q->reciprocH;
  double a, b, c;

  a = (3.0 - d);
  b = (2.0 - d);
  c = (1.0 - d);
  if (d < 1.0) {
    return q->factorW * (a * a * a * a * a - 6.0 * b * b * b * b * b +
                         15.0 * c * c * c * c * c);
  } else if (d < 2.0) {
    return q->factorW * (a * a * a * a * a - 6.0 * b * b * b * b * b);
  } else if (d < 3.0) {
    return q->factorW * a * a * a * a * a;
  } else {
    return 0.0;
  }
}

double F(struct Kernel *q, double r) {
  double a, b, c, d;

  d = 3.0 * r * q->reciprocH;
  a = (3.0 - d);
  b = (2.0 - d);
  c = (1.0 - d);

  if (d < 1.0) {
    return q->factorGradW *
           (a * a * a * a - 6.0 * b * b * b * b + 15.0 * c * c * c * c);
  } else if (d < 2.0) {
    return q->factorGradW * (a * a * a * a - 6.0 * b * b * b * b);
  } else if (d < 3.0) {
    return q->factorGradW * a * a * a * a;
  } else {
    return 0.0;
  }
}

/* material */

double get_p(struct Material *q, double rho) {
  return q->b0 * pow(rho / q->rho0, q->gamma);
}

double get_Cs(struct Material *q, double p, double rho) {
  return sqrt(q->gamma * p / rho);
}


/* particle */

long particle_ID_max;
int particle_number_of_materials;

static double **phi_ini(void) {
  int n, i, j;
  double **q;

  n = particle_number_of_materials;
  q = malloc(n * sizeof(*q));
  for (i = 0; i < n; i++)
    q[i] = malloc(n * sizeof(**q));
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      q[i][j] = 0.0;
  return q;
}

int particle_fin(struct Particle *q) {
  int i;

  for (i = 0; i < particle_number_of_materials; i++)
    free(q->phi[i]);
  free(q->phi);
  free(q);
  return 0;
}

struct Particle *particle_real(double position[2], double velocity[2],
                               double density, double pressure,
                               double temperature, struct Material *material) {
  struct Particle *q;

  q = malloc(sizeof(*q));
  if (q == NULL) abort();
  particle_ID_max++;
  q->bd = 0;
  q->bd_type = 0;
  q->ID = particle_ID_max;
  q->mtl = material;
  q->eta = material->eta;
  q->zeta = material->zeta;
  q->R[X] = position[X];
  q->R[Y] = position[Y];
  q->rho = density;
  q->p = pressure;
  q->T = temperature;
  q->Cs = get_Cs(material, pressure, density);
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
  q->phi = phi_ini();
  return q;
}

struct Particle *particle_image(struct Particle *s) {
  struct Particle *q;

  q = malloc(sizeof(*q));
  if (q == NULL) abort();
  q->bd = 1;
  q->bd_type = 1;
  q->ID = 0;
  q->rl_prtl = s;
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
  q->phi = phi_ini();
  return q;
}

struct Particle *particle_mirror(struct Particle *s,
                                 struct Material *material) {
  struct Particle *q;

  q = malloc(sizeof(*q));
  if (q == NULL) abort();
  q->bd = 1;
  q->bd_type = 0;
  q->ID = 0;
  q->rl_prtl = s;
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
  q->phi = phi_ini();
  return q;
}

int particle_copy(struct Particle *q, struct Particle *s, int type) {
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
    q->del_phi[X] = s->del_phi[X];
    q->del_phi[Y] = s->del_phi[Y];
    for (i = 0; i < particle_number_of_materials; i++)
      for (j = 0; j < particle_number_of_materials; j++)
        q->phi[i][j] = s->phi[i][j];
  }
  if (type == 0) {
    q->phi[0][0] = 0;
    for (i = 1; i < particle_number_of_materials; i++)
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
  double shear_rij;
  double bulk_rij;
};
struct Force {
  double epsilon;
  double sigma;
  double shear_slip, bulk_slip;
};

static double AMAX1(double a, double b) { return a > b ? a : b; }

static double AMIN1(double a, double b) { return a < b ? a : b; }

static double vv_distance(double a[2], double b[2]) {
  double x, y;

  x = a[X] - b[X];
  y = a[Y] - b[Y];
  return sqrt(x * x + y * y);
}

static double vv_abs(double v[2]) { return sqrt(v[X] * v[X] + v[Y] * v[Y]); }

static double vv_sqdiff(double v[2]) { return v[X] * v[X] - v[Y] * v[Y]; }

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
  Org->del_phi[X] += dphi[X] * rVi * Vj2;
  Org->del_phi[Y] += dphi[Y] * rVi * Vj2;
  Dest->del_phi[X] -= dphi[X] * rVj * Vi2;
  Dest->del_phi[Y] -= dphi[Y] * rVj * Vi2;
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
  double shear_rij;
  double bulk_rij;
  double rmi, rmj;

  Org = q->Org;
  Dest = q->Dest;
  Wij = q->Wij;
  mi = q->mi;
  mj = q->mj;
  Fij = q->Fij;
  rij = q->rij;
  eij = q->eij;
  shear_rij = q->shear_rij;
  bulk_rij = q->bulk_rij;
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
             ((Uij[X] - eij[X] * Uijdoteij) * shear_rij +
              eij[X] * (Uijdoteij * 2.0 * bulk_rij + NR_vis)) *
                 Fij * (Vi2 + Vj2);
  dPdti[Y] = eij[Y] * Fij * rij * (pi * Vi2 + pj * Vj2) -
             ((Uij[Y] - eij[Y] * Uijdoteij) * shear_rij +
              eij[Y] * (Uijdoteij * 2.0 * bulk_rij + NR_vis)) *
                 Fij * (Vi2 + Vj2);
  double Surfi[2], Surfj[2], SurfaceForcei[2], SurfaceForcej[2];

  Surfi[X] = Org->del_phi[X];
  Surfi[Y] = Org->del_phi[Y];
  Surfj[X] = Dest->del_phi[X];
  Surfj[Y] = Dest->del_phi[Y];
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

int initiation_ini(char *project_name, struct Ini *q) {
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
  int number_of_materials;
  int rc;
  struct Force *force;
  struct Material *mtl;

  strcpy(q->Project_name, project_name);
  strcpy(inputfile, q->Project_name);
  strcat(inputfile, ".cfg");
  f = fopen(inputfile, "r");
  if (!f)
    ABORT(("can't open '%s'", inputfile));
  {
    struct { const char *name; const char *fmt; void *dst[5]; } keys[] = {
      {"INITIAL_CONDITION",  "%d",              {&q->initial_condition}},
      {"CELLS",              "%d %d",           {&q->x_cells, &q->y_cells}},
      {"CELL_SIZE",          "%lf",             {&q->cell_size}},
      {"SMOOTHING_LENGTH",   "%lf",             {&q->smoothinglength}},
      {"CELL_RATIO",         "%d",              {&q->cell_ratio}},
      {"GRAVITY",            "%lf %lf",         {&q->gravity[0], &q->gravity[1]}},
      {"ARTIFICIAL_VISCOSITY","%lf",            {&q->art_vis}},
      {"NUMBER_OF_MATERIALS","%d",              {&q->number_of_materials}},
      {"TIMING",             "%lf %lf %lf",    {&q->Start_time, &q->End_time, &q->D_time}},
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
  q->box_size[0] = q->x_cells * q->cell_size;
  q->box_size[1] = q->y_cells * q->cell_size;
  q->delta = q->cell_size / q->cell_ratio;

  q->x_clls = q->x_cells + 2;
  q->y_clls = q->y_cells + 2;
  q->cell_lists = malloc(q->x_clls * sizeof(struct List **));
  for (i = 0; i < q->x_clls; i++) {
    q->cell_lists[i] = malloc(q->y_clls * sizeof(struct List *));
    for (j = 0; j < q->y_clls; j++)
      q->cell_lists[i][j] = list_ini();
  }
  q->NNP_list = list_ini();

  q->b = list_ini();
  f = fopen(inputfile, "r");
  if (!f)
    ABORT(("can't open '%s'\n", inputfile));
  while (fscanf(f, "%s", Key_word) == 1)
    if (!strcmp(Key_word, "BOUNDARY")) {
      n = fscanf(f, "%d %lf %lf %d %lf %lf %d %lf %lf %d %lf %lf", &q->xBl,
                 &q->UxBl[X], &q->UxBl[Y], &q->xBr, &q->UxBr[X], &q->UxBr[Y],
                 &q->yBd, &q->UyBd[X], &q->UyBd[Y], &q->yBu, &q->UyBu[X],
                 &q->UyBu[Y]);
      if (n != 3 * 4)
        ABORT(("can't read BOUNDARY keyword (n = %d)", n));
    }
  fclose(f);
  printf("The left, right, lower and upper boundary %d %d %d %d\n", q->xBl,
         q->xBr, q->yBd, q->yBu);
  puts("0: wall boundary condition");
  puts("1: perodic boundary condition");
  puts("2: free slip wall boundary condition");
  puts("3: symmetry boundary condition");

  q->pair_list = list_ini();
  number_of_materials = q->number_of_materials;
  delta = q->delta;
  q->delta2 = delta * delta;
  q->delta3 = delta * delta * delta;
  q->materials = malloc(number_of_materials * sizeof(*q->materials));
  q->forces = malloc(number_of_materials * sizeof(*q->forces));
  for (k = 0; k < number_of_materials; k++)
    q->forces[k] = malloc(number_of_materials * sizeof(*q->forces[k]));

  f = fopen(inputfile, "r");
  if (!f)
    ABORT(("can't open '%s'", inputfile));
  else
    printf("read the propeties of materials and forces\n");
  while (fscanf(f, "%s", Key_word) == 1) {
    if (!strcmp(Key_word, "MATERIALS"))
      for (k = 0; k < number_of_materials; k++) {
        mtl = &q->materials[k];
        mtl->number = k;
        if (fscanf(f, "%s %d", mtl->material_name, &mtl->material_type) != 2)
          ABORT(("can't read material from '%s'", inputfile));
        if (fscanf(f, "%lf %lf %lf %lf %lf", &mtl->eta, &mtl->zeta, &mtl->gamma,
                   &mtl->rho0, &mtl->a0) != 5)
          ABORT(("can't read materal parameters from '%s'", inputfile));
        mtl->nu = AMAX1(mtl->eta, mtl->zeta) / mtl->rho0;
      }
    if (!strcmp(Key_word, "FORCES"))
      for (l = 0; l < number_of_materials; l++)
        for (n = 0; n < number_of_materials; n++) {
          if (fscanf(f, "%d %d", &k, &m) != 2)
            ABORT(("can't read materal from '%s'", inputfile));
          force = &q->forces[k][m];
          if (fscanf(f, "%lf %lf %lf %lf", &force->epsilon, &force->sigma,
                     &force->shear_slip, &force->bulk_slip) != 4)
            ABORT(("can't read force from '%s'", inputfile));
        }
  }
  fclose(f);
  q->viscosity_max = 0.0;
  q->surface_max = 0.0;
  for (k = 0; k < number_of_materials; k++) {
    q->viscosity_max = AMAX1(q->viscosity_max, q->materials[k].nu);
    for (l = 0; l < number_of_materials; l++) {
      q->surface_max = AMAX1(q->surface_max, q->forces[k][l].sigma);
    }
  }
  q->dt_g_vis = AMIN1(sqrt(delta / vv_abs(q->gravity)),
                      0.5 * q->delta2 / q->viscosity_max);
  q->dt_surf = 0.4 * sqrt(q->delta3 / q->surface_max);
  sound = AMAX1(vv_abs(q->gravity), q->viscosity_max);
  sound = AMAX1(q->surface_max, sound);
  for (k = 0; k < number_of_materials; k++)
    q->materials[k].b0 = q->materials[k].a0 * sound / q->materials[k].gamma;
  q->particle_list = list_ini();
  particle_number_of_materials = q->number_of_materials;
  particle_ID_max = 0;

  return 0;
}

int manager_update_list(struct Ini *q) {

  int i, j;
  int k, m;
  struct ListNode *p;
  struct Particle *prtl;

  int x_clls;
  int y_clls;
  double cell_size;
  struct List ***cell_lists;

  x_clls = q->x_clls;
  y_clls = q->y_clls;
  cell_size = q->cell_size;
  cell_lists = q->cell_lists;

  for (i = 0; i < x_clls; i++) {
    for (j = 0; j < y_clls; j++) {
      p = list_first(cell_lists[i][j]);
      while (!list_endp(cell_lists[i][j], p)) {
        prtl = list_retrieve(cell_lists[i][j], p);
        if (prtl->bd == 0) {
          k = (int)((prtl->R[0] + cell_size) / cell_size);
          m = (int)((prtl->R[1] + cell_size) / cell_size);
          if (k != i || m != j) {
            list_remove(cell_lists[i][j], p);
            list_insert(cell_lists[k][m], list_first(cell_lists[k][m]), prtl);
          } else
            p = list_next(cell_lists[i][j], p);
        } else
          p = list_next(cell_lists[i][j], p);
      }
    }
  }
  return 0;
}

int manager_build_nnp(struct Ini *q, double point[2]) {
  int i, j;
  int k, m;
  double dstc;
  struct ListNode *p;
  struct Particle *prtl;

  struct List *NNP_list;
  int x_clls;
  int y_clls;
  double cell_size;
  double smoothinglength;
  struct List ***cell_lists;

  x_clls = q->x_clls;
  y_clls = q->y_clls;
  cell_size = q->cell_size;
  cell_lists = q->cell_lists;
  smoothinglength = q->smoothinglength;
  NNP_list = q->NNP_list;

  list_clear(NNP_list);
  k = (int)((point[0] + cell_size) / cell_size);
  m = (int)((point[1] + cell_size) / cell_size);
  for (i = k - 1; i <= k + 1; i++)
    for (j = m - 1; j <= m + 1; j++)
      if (i < x_clls && j < y_clls && i >= 0 && j >= 0)
        for (p = list_first(cell_lists[i][j]); !list_endp(cell_lists[i][j], p); p = list_next(cell_lists[i][j], p)) { prtl = (struct Particle *)list_retrieve(cell_lists[i][j], p);
          dstc = vv_distance(point, prtl->R);
          if (dstc < smoothinglength)
            list_insert(NNP_list, list_first(NNP_list), prtl);
        }
  return 0;
}

int manager_build_pair(struct Ini *q, struct List *pairs,
                       struct List *particle_list, struct Force **forces,
                       struct Kernel *kernel) {
  struct ListNode *p, *p1;
  int i, j, k, m;
  double dstc;
  double sm2;
  struct Particle *prtl_org, *prtl_dest;
  struct Pair *pair;

  double smoothinglength;
  double cell_size;
  struct List ***cell_lists;

  cell_size = q->cell_size;
  cell_lists = q->cell_lists;
  smoothinglength = q->smoothinglength;

  sm2 = smoothinglength * smoothinglength;

  for (p = list_first(pairs); !list_endp(pairs, p); p = list_next(pairs, p)) { pair = (struct Pair *)list_retrieve(pairs, p);
    free(pair);
  }
  list_clear(pairs);
  for (p = list_first(particle_list); !list_endp(particle_list, p); p = list_next(particle_list, p)) { prtl_org = (struct Particle *)list_retrieve(particle_list, p);
    if (prtl_org->bd == 0) {
      i = (int)((prtl_org->R[0] + cell_size) / cell_size);
      j = (int)((prtl_org->R[1] + cell_size) / cell_size);
      for (k = i - 1; k <= i + 1; k++)
        for (m = j - 1; m <= j + 1; m++) {
          for (p1 = list_first(cell_lists[k][m]); !list_endp(cell_lists[k][m], p1); p1 = list_next(cell_lists[k][m], p1)) { prtl_dest = (struct Particle *)list_retrieve(cell_lists[k][m], p1);
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
              pair->shear_rij = 2.0 * etai * etaj * rij /
                (etai * (rij + 2.0 * frc_ij[noj][noi].shear_slip) +
                 etaj * (rij + 2.0 * frc_ij[noi][noj].shear_slip) + 1.0e-30);
              pair->bulk_rij = 2.0 * zetai * zetaj * rij /
                (zetai * (rij + 2.0 * frc_ij[noj][noi].bulk_slip) +
                 zetaj * (rij + 2.0 * frc_ij[noi][noj].bulk_slip) + 1.0e-30);
              list_insert(pairs, list_first(pairs), pair);
            }
          }
        }
    }
  }
  return 0;
}

void manager_build_particles(struct Ini *q, struct Material *materials,
                             struct List *particle_list, struct Ini *ini) {

  int i, j, k, m;
  double position[2];
  double velocity[2];
  double delta;
  double density, pressure, Temperature;
  int material_no;
  struct Particle *prtl;
  int n, N, cnt;
  char inputfile[FILENAME_MAX], line[MAX_SIZE];
  char material_name[MAX_SIZE];
  FILE *f;

  int x_clls;
  int y_clls;
  int cell_ratio;
  double cell_size;
  struct List ***cell_lists;

  x_clls = q->x_clls;
  y_clls = q->y_clls;
  cell_size = q->cell_size;
  cell_lists = q->cell_lists;
  cell_ratio = ini->cell_ratio;

  delta = cell_size / cell_ratio;
  if (ini->initial_condition == 0) {
    for (i = 1; i < x_clls - 1; i++) {
      for (j = 1; j < y_clls - 1; j++) {
        for (k = 0; k < cell_ratio; k++) {
          for (m = 0; m < cell_ratio; m++) {
            position[0] = (i - 1) * cell_size + (k + 0.5) * delta;
            position[1] = (j - 1) * cell_size + (m + 0.5) * delta;
            material_no = 1;
            velocity[X] = ini->U0[X];
            velocity[Y] = ini->U0[Y];
            Temperature = ini->T0;
            density = materials[material_no].rho0;
            pressure = get_p(&materials[material_no], density);
            prtl = particle_real(position, velocity, density, pressure,
                                 Temperature, &materials[material_no]);
            prtl->cell_i = i;
            prtl->cell_j = j;
            list_insert(particle_list, list_first(particle_list), prtl);
            list_insert(cell_lists[i][j], list_first(cell_lists[i][j]), prtl);
          }
        }
      }
    }
  }

  if (ini->initial_condition == 1) {
    strcpy(inputfile, ini->Project_name);
    strcat(inputfile, ".txt");
    f = fopen(inputfile, "r");
    if (!f)
      ABORT(("can't open file '%s'", inputfile));
    else
      WARN(("Read real particles from '%s'", inputfile));
    if (fgets(line, MAX_SIZE, f) == NULL)
      ABORT(("can't read a line from '%s'", inputfile));
    sscanf(line, "%lf", &ini->Start_time);
    ini->End_time += ini->Start_time;
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
      cnt = sscanf(line, "%s %lf %lf %lf %lf %lf %lf %lf", material_name,
                   &position[0], &position[1], &velocity[0], &velocity[1],
                   &density, &pressure, &Temperature);
      if (cnt != 8) {
        WARN(("line: '%s'", line));
        WARN(("material_name: %s", material_name));
        ABORT(("can't read a particle from '%s' (cnt = %d, n = %d)", inputfile,
               cnt, n));
      }
      material_no = -1;
      for (k = 0; k < ini->number_of_materials; k++)
        if (strcmp(material_name, materials[k].material_name) == 0)
          material_no = k;
      if (material_no != -1) {
        pressure = get_p(&materials[material_no], density);
        prtl = particle_real(position, velocity, density, pressure, Temperature,
                             &materials[material_no]);
        list_insert(particle_list, list_first(particle_list), prtl);
        i = (int)(prtl->R[0] / cell_size) + 1;
        j = (int)(prtl->R[1] / cell_size) + 1;
        prtl->cell_i = i;
        prtl->cell_j = j;
        list_insert(cell_lists[i][j], list_first(cell_lists[i][j]), prtl);
      } else {
        ABORT(("The material in the restart file is not used by the program!"));
      }
    }
    fclose(f);
  }
}

int initiation_fin(struct Ini *q) {
  int i;
  int j;
  int x_clls;
  int y_clls;
  struct List ***c;
  struct ListNode *p;
  struct Pair *pair;
  struct Particle *prtl;

  x_clls = q->x_clls;
  y_clls = q->y_clls;
  c = q->cell_lists;
  for (i = 0; i < x_clls; i++) {
    for (j = 0; j < y_clls; j++) {
      list_fin(c[i][j]);
    }
    free(c[i]);
  }
  free(c);
  list_fin(q->NNP_list);

  for (i = 0; i < q->number_of_materials; i++)
    free(q->forces[i]);
  free(q->forces);
  free(q->materials);

  for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p);
    free(pair);
  }
  list_fin(q->pair_list);

  for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p); particle_fin(prtl); }
  list_fin(q->particle_list);

  return 0;
}

static void UpdateSurfaceStress(struct Ini *q) {
  double epsilon = 1.0e-30;
  double interm0, interm1, interm2;
  struct Particle *prtl;
  struct ListNode *p;

  for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
    interm0 = 1.0 / (vv_abs(prtl->del_phi) + epsilon);
    interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
    interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
    prtl->del_phi[0] = interm1 * interm0;
    prtl->del_phi[1] = interm2 * interm0;
  }
  for (p = list_first(q->b); !list_endp(q->b, p); p = list_next(q->b, p)) { prtl = (struct Particle *)list_retrieve(q->b, p);
    interm0 = vv_abs(prtl->del_phi) + epsilon;
    interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
    interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
    prtl->del_phi[0] = interm1 / interm0;
    prtl->del_phi[1] = interm2 / interm0;
  }
}

int output_particles(struct Ini *q, struct List *particle_list,
                     struct Material *materials, double Time) {
  char file_name[FILENAME_MAX], file_list[FILENAME_MAX];
  double Itime;
  FILE *f;
  int i, j;
  int number_of_materials;
  struct ListNode *p;
  struct Particle *prtl;

  number_of_materials = q->number_of_materials;

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
  for (i = 0; i < number_of_materials; i++) {
    j = 0;
    for (p = list_first(particle_list); !list_endp(particle_list, p); p = list_next(particle_list, p)) { prtl = (struct Particle *)list_retrieve(particle_list, p);
      if (strcmp(materials[i].material_name, prtl->mtl->material_name) == 0) {
        j++;
        if (j == 1)
          fprintf(f, "zone t='%s' \n", materials[i].material_name);
        fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0],
                prtl->U[1]);
      }
    }
    for (p = list_first(q->b); !list_endp(q->b, p); p = list_next(q->b, p)) { prtl = (struct Particle *)list_retrieve(q->b, p);
      if (strcmp(materials[i].material_name, prtl->mtl->material_name) == 0) {
        j++;
        if (j == 1)
          fprintf(f, "zone t='%s' \n", materials[i].material_name);
        fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1], prtl->U[0],
                prtl->U[1]);
      }
    }
  }
  fclose(f);
  return 0;
}

int output_restart(struct Ini *q, struct List *particle_list, double Time) {
  int n;
  char file_name[FILENAME_MAX];
  struct Particle *prtl;
  struct ListNode *p;
  FILE *f;

  strcpy(file_name, q->Project_name);
  strcat(file_name, ".txt");
  f = fopen(file_name, "w");
  if (!f)
    ABORT(("can't write '%s'", file_name));
  n = 0;
  for (p = list_first(particle_list); !list_endp(particle_list, p); p = list_next(particle_list, p)) { prtl = (struct Particle *)list_retrieve(particle_list, p);
    if (prtl->bd == 0)
      n++;
  }
  fprintf(f, "%.6g\n", Time);
  fprintf(f, "%d\n", n);
  for (p = list_first(particle_list); !list_endp(particle_list, p); p = list_next(particle_list, p)) { prtl = (struct Particle *)list_retrieve(particle_list, p);
    if (prtl->bd == 0)
      fprintf(f, "%s %.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
              prtl->mtl->material_name, prtl->R[0], prtl->R[1], prtl->U[0],
              prtl->U[1], prtl->rho, prtl->p, prtl->T);
  }
  fclose(f);
  return 0;
}

void VolumeMass(struct List *particle_list, struct Ini *ini,
                struct Kernel *kernel) {
  double reciprocV;
  double dstc;
  struct ListNode *p, *p1;
  struct Particle *prtl_org, *prtl_dest;

  for (p = list_first(particle_list); !list_endp(particle_list, p); p = list_next(particle_list, p)) { prtl_org = (struct Particle *)list_retrieve(particle_list, p);
    manager_build_nnp(ini, prtl_org->R);
    reciprocV = 0.0;
    for (p1 = list_first(ini->NNP_list); !list_endp(ini->NNP_list, p1); p1 = list_next(ini->NNP_list, p1)) { prtl_dest = (struct Particle *)list_retrieve(ini->NNP_list, p1);
      dstc = vv_distance(prtl_org->R, prtl_dest->R);
      reciprocV += w(kernel, dstc);
    }
    reciprocV = 1.0 / reciprocV;
    prtl_org->V = reciprocV;
    prtl_org->m = prtl_org->rho * reciprocV;
    list_clear(ini->NNP_list);
  }
}

void step(int *pite, struct Ini *q, double *Time, double D_time,
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
  while (integeral_time < D_time) {
    {
      double Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
      for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
        Cs_max = AMAX1(Cs_max, prtl->Cs);
        V_max = AMAX1(V_max, vv_abs(prtl->U));
        rho_min = AMIN1(rho_min, prtl->rho);
        rho_max = AMAX1(rho_max, prtl->rho);
      }
      dt = AMIN1(sqrt(0.5 * (rho_min + rho_max)) * q->dt_surf, q->dt_g_vis);
      dt = 0.25 * AMIN1(dt, q->delta / (Cs_max + V_max));
    }
    sqrtdt = sqrt(dt);
    ite++;
    integeral_time += dt;
    *Time += dt;
    if (ite % 10 == 0)
      printf("N=%d Time: %g\tdt: %g\n", ite, *Time, dt);
    manager_build_pair(q, q->pair_list, q->particle_list, q->forces, kernel);
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p); prtl->rho = 0.0; }
    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p); SummationDensity(pair); }
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p); prtl->p = get_p(prtl->mtl, prtl->rho); }

    boundary_condition(q, q->cell_lists);
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    for (p = list_first(q->b); !list_endp(q->b, p); p = list_next(q->b, p)) { prtl = (struct Particle *)list_retrieve(q->b, p); prtl->del_phi[X] = prtl->del_phi[Y] = 0.0; }

    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p); SummationPhaseGradient(pair); }

    boundary_condition(q, q->cell_lists);
    UpdateSurfaceStress(q);
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->drhodt = 0.0;
      prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
      prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p); UpdateForces(pair, q->art_vis, q->delta); }
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->dUdt[X] += q->gravity[X];
      prtl->dUdt[Y] += q->gravity[Y];
    }

    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
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
    boundary_condition(q, q->cell_lists);

    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p);
      struct Particle *Org = pair->Org, *Dest = pair->Dest;
      double *eij = pair->eij;
      double etai = pair->etai, etaj = pair->etaj;
      double zetai = pair->zetai, zetaj = pair->zetaj;
      struct Force **frc_ij = pair->frc_ij;
      int noi = Org->mtl->number, noj = Dest->mtl->number;
      double rij, rrij;

      rij = pair->rij = vv_distance(pair->Org->R, pair->Dest->R);
      rrij = pair->rrij = 1.0 / (pair->rij + 1.0e-30);
      eij[X] = (Org->R[X] - Dest->R[X]) * rrij;
      eij[Y] = (Org->R[Y] - Dest->R[Y]) * rrij;
      pair->Wij = w(kernel, rij);
      pair->Fij = F(kernel, rij) * rrij;
      pair->shear_rij = 2.0 * etai * etaj * pair->rij /
        (etai * (rij + 2.0 * frc_ij[noj][noi].shear_slip) +
         etaj * (rij + 2.0 * frc_ij[noi][noj].shear_slip) + 1.0e-30);
      pair->bulk_rij = 2.0 * zetai * zetaj * rij /
        (zetai * (rij + 2.0 * frc_ij[noj][noi].bulk_slip) +
         zetaj * (rij + 2.0 * frc_ij[noi][noj].bulk_slip) + 1.0e-30);
    }

    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p); prtl->rho = 0.0; }
    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p); SummationDensity(pair); }
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p); prtl->p = get_p(prtl->mtl, prtl->rho); }

    boundary_condition(q, q->cell_lists);
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    for (p = list_first(q->b); !list_endp(q->b, p); p = list_next(q->b, p)) { prtl = (struct Particle *)list_retrieve(q->b, p); prtl->del_phi[X] = prtl->del_phi[Y] = 0.0; }

    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p); SummationPhaseGradient(pair); }

    boundary_condition(q, q->cell_lists);
    UpdateSurfaceStress(q);
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->drhodt = 0.0;
      prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
      prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p); UpdateForces(pair, q->art_vis, q->delta); }
    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->dUdt[X] += q->gravity[X];
      prtl->dUdt[Y] += q->gravity[Y];
    }

    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p); prtl->_dU[X] = prtl->_dU[Y] = 0.0; }
    for (p = list_first(q->pair_list); !list_endp(q->pair_list, p); p = list_next(q->pair_list, p)) { pair = (struct Pair *)list_retrieve(q->pair_list, p);
      double rmi = pair->rmi, rmj = pair->rmj;
      double bulk_rij = pair->bulk_rij;
      double *eij = pair->eij;
      double shear_rij = pair->shear_rij;
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
                    sqrt(16.0 * k_bltz * shear_rij * Ti * Tj / (Ti + Tj) *
                         (Vi2 + Vj2) * Fij) +
                eij[X] * Random_v *
                    sqrt(16.0 * k_bltz * bulk_rij * Ti * Tj / (Ti + Tj) *
                         (Vi2 + Vj2) * Fij);
      _dUi[Y] = v_eij[Y] * Random_p *
                    sqrt(16.0 * k_bltz * shear_rij * Ti * Tj / (Ti + Tj) *
                         (Vi2 + Vj2) * Fij) +
                eij[Y] * Random_v *
                    sqrt(16.0 * k_bltz * bulk_rij * Ti * Tj / (Ti + Tj) *
                         (Vi2 + Vj2) * Fij);
      if (Dest->bd_type == 1) {
        Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi * 0.5;
        Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi * 0.5;
        Dest->rl_prtl->_dU[X] = Dest->rl_prtl->_dU[X] - _dUi[X] * rmj * 0.5;
        Dest->rl_prtl->_dU[Y] = Dest->rl_prtl->_dU[Y] - _dUi[Y] * rmj * 0.5;
      } else {
        Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi;
        Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi;
        Dest->_dU[X] = Dest->_dU[X] - _dUi[X] * rmj;
        Dest->_dU[Y] = Dest->_dU[Y] - _dUi[Y] * rmj;
      }
    }

    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->U[X] += prtl->_dU[X];
      prtl->U[Y] += prtl->_dU[Y];
      prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
      prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
      prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
      prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
    }

    for (p = list_first(q->particle_list); !list_endp(q->particle_list, p); p = list_next(q->particle_list, p)) { prtl = (struct Particle *)list_retrieve(q->particle_list, p);
      prtl->U[X] = prtl->U[X] + prtl->_dU[X];
      prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
    }

    boundary_check(q, q->particle_list);
    manager_update_list(q);
    boundary_build(q, q->cell_lists, q->materials);
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

static void apply_bnd(int type, int c, double refl, double shift,
                      double *U_bnd, struct Particle *prtl) {
  int t = c ^ 1;
  if (bnd[type][3])
    prtl->R[c] += shift;
  else
    prtl->R[c] = 2.0 * refl - prtl->R[c];
  if (bnd[type][0]) prtl->U[c] = 2.0 * U_bnd[c] - prtl->U[c];
  if (bnd[type][1]) prtl->U[t] = 2.0 * U_bnd[t] - prtl->U[t];
  if (bnd[type][2]) prtl->del_phi[c] = -prtl->del_phi[c];
}

static void apply_corner(int type,
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
    prtl->del_phi[X] = -prtl->del_phi[X];
    prtl->del_phi[Y] = -prtl->del_phi[Y];
  }
}

int boundary_build(struct Ini *q, struct List ***c, struct Material *mtl) {
  int i, v, e;
  struct Particle *prtl, *prtl_old;
  struct ListNode *p;
  int x_clls, y_clls;
  struct List *b;

  x_clls = q->x_clls;
  y_clls = q->y_clls;
  b = q->b;

  for (p = list_first(b); !list_endp(b, p); p = list_next(b, p)) { prtl = (struct Particle *)list_retrieve(b, p); particle_fin(prtl); }
  list_clear(b);

  struct {
    int type, coord, ghost, adj, opp, perp_lo, perp_hi;
    double refl, shift, *U_bnd;
  } edges[4] = {
    {q->xBl, X, 0,         1,         x_clls-2, 1, y_clls-1, 0,              -q->box_size[X], q->UxBl},
    {q->xBr, X, x_clls-1,  x_clls-2,  1,        1, y_clls-1, q->box_size[X],  q->box_size[X], q->UxBr},
    {q->yBd, Y, 0,         1,         y_clls-2, 0, x_clls,   0,              -q->box_size[Y], q->UyBd},
    {q->yBu, Y, y_clls-1,  y_clls-2,  1,        0, x_clls,   q->box_size[Y],  q->box_size[Y], q->UyBu},
  };
  /* adjust south/north perp ranges to avoid corner overlap */
  if (q->xBl == q->yBd) edges[2].perp_lo = 1;
  if (q->xBr == q->yBd) edges[2].perp_hi = x_clls - 1;
  if (q->xBl == q->yBu) edges[3].perp_lo = 1;
  if (q->xBr == q->yBu) edges[3].perp_hi = x_clls - 1;
  /* X-edges (west+east) interleaved per j */
  for (v = edges[0].perp_lo; v < edges[0].perp_hi; v++) {
    for (e = 0; e < 2; e++) {
      int type = edges[e].type;
      int is_mirror = (type == 0 || type == 2);
      int src = (type == 1) ? edges[e].opp : edges[e].adj;
      list_clear(c[edges[e].ghost][v]);
      for (p = list_first(c[src][v]); !list_endp(c[src][v], p); p = list_next(c[src][v], p)) { prtl_old = (struct Particle *)list_retrieve(c[src][v], p);
        prtl = is_mirror ? particle_mirror(prtl_old, mtl) : particle_image(prtl_old);
        apply_bnd(type, X, edges[e].refl, edges[e].shift, edges[e].U_bnd, prtl);
        prtl->cell_i = edges[e].ghost;
        prtl->cell_j = v;
        list_insert(b, list_first(b), prtl);
        list_insert(c[edges[e].ghost][v], list_first(c[edges[e].ghost][v]), prtl);
      }
    }
  }
  /* Y-edges (south, north) */
  for (e = 2; e < 4; e++) {
    int type = edges[e].type;
    int is_mirror = (type == 0 || type == 2);
    int src = (type == 1) ? edges[e].opp : edges[e].adj;
    for (v = edges[e].perp_lo; v < edges[e].perp_hi; v++) {
      list_clear(c[v][edges[e].ghost]);
      for (p = list_first(c[v][src]); !list_endp(c[v][src], p); p = list_next(c[v][src], p)) { prtl_old = (struct Particle *)list_retrieve(c[v][src], p);
        prtl = is_mirror ? particle_mirror(prtl_old, mtl) : particle_image(prtl_old);
        apply_bnd(type, Y, edges[e].refl, edges[e].shift, edges[e].U_bnd, prtl);
        prtl->cell_i = v;
        prtl->cell_j = edges[e].ghost;
        list_insert(b, list_first(b), prtl);
        list_insert(c[v][edges[e].ghost], list_first(c[v][edges[e].ghost]), prtl);
      }
    }
  }

  struct {
    int type_x, type_y;
    int ghost_i, ghost_j, adj_i, adj_j, opp_i, opp_j;
    double refl_x, shift_x, refl_y, shift_y;
    double *U_x, *U_y;
  } corners[4] = {
    {q->xBl, q->yBd, 0,        0,        1,        1,        x_clls-2, y_clls-2,
     0,              -q->box_size[X], 0,              -q->box_size[Y], q->UxBl, q->UyBd},
    {q->xBl, q->yBu, 0,        y_clls-1, 1,        y_clls-2, x_clls-2, 1,
     0,              -q->box_size[X], q->box_size[Y],  q->box_size[Y], q->UxBl, q->UyBu},
    {q->xBr, q->yBu, x_clls-1, y_clls-1, x_clls-2, y_clls-2, 1,       1,
     q->box_size[X],  q->box_size[X], q->box_size[Y],  q->box_size[Y], q->UxBr, q->UyBu},
    {q->xBr, q->yBd, x_clls-1, 0,        x_clls-2, 1,        1,       y_clls-2,
     q->box_size[X],  q->box_size[X], 0,              -q->box_size[Y], q->UxBr, q->UyBd},
  };
  for (e = 0; e < 4; e++) {
    if (corners[e].type_x != corners[e].type_y) continue;
    int type = corners[e].type_x;
    int is_mirror = (type == 0 || type == 2);
    int si = (type == 1) ? corners[e].opp_i : corners[e].adj_i;
    int sj = (type == 1) ? corners[e].opp_j : corners[e].adj_j;
    int gi = corners[e].ghost_i, gj = corners[e].ghost_j;
    list_clear(c[gi][gj]);
    for (p = list_first(c[si][sj]); !list_endp(c[si][sj], p); p = list_next(c[si][sj], p)) { prtl_old = (struct Particle *)list_retrieve(c[si][sj], p);
      prtl = is_mirror ? particle_mirror(prtl_old, mtl) : particle_image(prtl_old);
      apply_corner(type, corners[e].refl_x, corners[e].shift_x, corners[e].U_x,
                         corners[e].refl_y, corners[e].shift_y, corners[e].U_y, prtl);
      prtl->cell_i = gi;
      prtl->cell_j = gj;
      list_insert(b, list_first(b), prtl);
      list_insert(c[gi][gj], list_first(c[gi][gj]), prtl);
    }
  }
  return 0;
}

int boundary_condition(struct Ini *q, struct List ***c) {
  int e, v;
  struct Particle *prtl;
  struct ListNode *p;
  int x_clls = q->x_clls, y_clls = q->y_clls;

  struct {
    int type, coord, ghost, perp_lo, perp_hi;
    double refl, shift, *U_bnd;
  } edges[4] = {
    {q->xBl, X, 0,        1, y_clls-1, 0,              -q->box_size[X], q->UxBl},
    {q->xBr, X, x_clls-1, 1, y_clls-1, q->box_size[X],  q->box_size[X], q->UxBr},
    {q->yBd, Y, 0,        0, x_clls,   0,              -q->box_size[Y], q->UyBd},
    {q->yBu, Y, y_clls-1, 0, x_clls,   q->box_size[Y],  q->box_size[Y], q->UyBu},
  };
  if (q->xBl == q->yBd) edges[2].perp_lo = 1;
  if (q->xBr == q->yBd) edges[2].perp_hi = x_clls - 1;
  if (q->xBl == q->yBu) edges[3].perp_lo = 1;
  if (q->xBr == q->yBu) edges[3].perp_hi = x_clls - 1;

  for (e = 0; e < 4; e++) {
    int type = edges[e].type;
    int coord = edges[e].coord;
    int copy_type = (type == 0 || type == 2) ? 0 : 1;
    for (v = edges[e].perp_lo; v < edges[e].perp_hi; v++) {
      int gi, gj;
      if (coord == X) { gi = edges[e].ghost; gj = v; }
      else             { gi = v; gj = edges[e].ghost; }
      for (p = list_first(c[gi][gj]); !list_endp(c[gi][gj], p); p = list_next(c[gi][gj], p)) { prtl = (struct Particle *)list_retrieve(c[gi][gj], p);
        if (prtl->rl_prtl == NULL) abort();
        particle_copy(prtl, prtl->rl_prtl, copy_type);
        apply_bnd(type, coord, edges[e].refl, edges[e].shift, edges[e].U_bnd, prtl);
      }
    }
  }

  struct {
    int type_x, type_y, ghost_i, ghost_j;
    double refl_x, shift_x, refl_y, shift_y;
    double *U_x, *U_y;
  } corners[4] = {
    {q->xBl, q->yBd, 0,        0,
     0,              -q->box_size[X], 0,              -q->box_size[Y], q->UxBl, q->UyBd},
    {q->xBl, q->yBu, 0,        y_clls-1,
     0,              -q->box_size[X], q->box_size[Y],  q->box_size[Y], q->UxBl, q->UyBu},
    {q->xBr, q->yBu, x_clls-1, y_clls-1,
     q->box_size[X],  q->box_size[X], q->box_size[Y],  q->box_size[Y], q->UxBr, q->UyBu},
    {q->xBr, q->yBd, x_clls-1, 0,
     q->box_size[X],  q->box_size[X], 0,              -q->box_size[Y], q->UxBr, q->UyBd},
  };
  for (e = 0; e < 4; e++) {
    if (corners[e].type_x != corners[e].type_y) continue;
    int type = corners[e].type_x;
    int copy_type = (type == 0 || type == 2) ? 0 : 1;
    for (p = list_first(c[corners[e].ghost_i][corners[e].ghost_j]); !list_endp(c[corners[e].ghost_i][corners[e].ghost_j], p); p = list_next(c[corners[e].ghost_i][corners[e].ghost_j], p)) { prtl = (struct Particle *)list_retrieve(c[corners[e].ghost_i][corners[e].ghost_j], p);
      if (prtl->rl_prtl == NULL) abort();
      particle_copy(prtl, prtl->rl_prtl, copy_type);
      apply_corner(type, corners[e].refl_x, corners[e].shift_x, corners[e].U_x,
                         corners[e].refl_y, corners[e].shift_y, corners[e].U_y, prtl);
    }
  }
  return 0;
}

int boundary_check(struct Ini *q, struct List *list) {
  struct ListNode *p;
  struct Particle *prtl;
  double *box_size = q->box_size;
  int types[2][2] = {{q->xBl, q->xBr}, {q->yBd, q->yBu}};
  int c;

  for (p = list_first(list); !list_endp(list, p); p = list_next(list, p)) { prtl = (struct Particle *)list_retrieve(list, p);
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
