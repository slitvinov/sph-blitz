#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "sph/err.h"
#include "sph/ini.h"
#include "sph/kernel.h"
#include "sph/list.h"
#include "sph/macro.h"
#include "sph/material.h"
#include "sph/particle.h"

enum { X, Y };
enum { MAX_SIZE = 4096 };
static double k_bltz = 1.380662e-023 / 0.02 / 0.02 / 0.02;
double pair_art_vis;
double pair_delta;
struct Pair {
    struct Particle *Org;
    struct Particle *Dest;
    struct Force **frc_ij;
    int noi;
    int noj;
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

static double
AMAX1(double a, double b)
{
    return a > b ? a : b;
}

static double
AMIN1(double a, double b)
{
    return a < b ? a : b;
}

static double
vv_distance(double a[2], double b[2])
{
    double x, y;

    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return sqrt(x * x + y * y);
}

static double
vv_abs(double v[2])
{
    return sqrt(v[X] * v[X] + v[Y] * v[Y]);
}

static double
vv_sq_distance(double a[2], double b[2])
{
    double x, y;

    x = a[X] - b[X];
    y = a[Y] - b[Y];
    return x * x + y * y;
}

static double
vv_sqdiff(double v[2])
{
    return v[X] * v[X] - v[Y] * v[Y];
}

static void
random_gaussian(double *y1, double *y2)
{
    double x1, x2, w;

    do {
        x1 = (double) rand() / RAND_MAX;
        x2 = (double) rand() / RAND_MAX;
        x1 = 2.0 * x1 - 1.0;
        x2 = 2.0 * x2 - 1.0;
        w = x1 * x1 + x2 * x2;
    } while (w >= 1.0 || w == 0.0);
    w = sqrt((-2.0 * log(w)) / w);
    *y1 = x1 * w;
    *y2 = x2 * w;
}

static struct Pair *
pair_ini(struct Particle *prtl_org, struct Particle *prtl_dest,
         struct Force **forces, struct Kernel *kernel, double dstc)
{
    struct Pair *q;
    struct Particle *Org, *Dest;
    double etai, etaj, rij, zetai, zetaj;
    int noi, noj;
    struct Force **frc_ij;

    q = malloc(sizeof(*q));
    if (q == NULL)
        ABORT(("can't allocate"));

    q->Org = Org = prtl_org;
    q->Dest = Dest = prtl_dest;
    q->noi = noi = Org->mtl->number;
    q->noj = noj = Dest->mtl->number;
    q->frc_ij = frc_ij = forces;
    q->mi = Org->m;
    q->mj = Dest->m;
    q->rmi = 1.0 / q->mi;
    q->rmj = 1.0 / q->mj;
    q->etai = etai = Org->eta;
    q->etaj = etaj = Dest->eta;
    q->zetai = zetai = Org->zeta;
    q->zetaj = zetaj = Dest->zeta;
    q->rij = rij = dstc;
    q->rrij = 1.0 / (rij + 1.0e-30);
    q->eij[X] = (Org->R[X] - Dest->R[X]) * q->rrij;
    q->eij[Y] = (Org->R[Y] - Dest->R[Y]) * q->rrij;
    q->Wij = w(kernel, rij);
    q->Fij = F(kernel, rij) * q->rrij;
    q->shear_rij =
        2.0 * etai * etaj * rij / (etai *
                                   (rij +
                                    2.0 * frc_ij[noj][noi].shear_slip)
                                   + etaj * (rij +
                                             2.0 *
                                             frc_ij[noi][noj].shear_slip) +
                                   1.0e-30);
    q->bulk_rij =
        2.0 * zetai * zetaj * rij / (zetai *
                                     (rij +
                                      2.0 * frc_ij[noj][noi].bulk_slip)
                                     + zetaj * (rij +
                                                2.0 *
                                                frc_ij[noi][noj].bulk_slip)
                                     + 1.0e-30);
    return q;
}

static int
pair_fin(struct Pair *q)
{
    free(q);
    return 0;
}

void
RenewPair(struct Pair *q, struct Kernel *kernel)
{
    struct Particle *Org, *Dest;
    double *eij;
    double rij, rrij;
    double etai, etaj, zetai, zetaj;
    struct Force **frc_ij;
    int noi, noj;

    Org = q->Org;
    Dest = q->Dest;
    eij = q->eij;
    etai = q->etai;
    etaj = q->etaj;
    zetai = q->zetai;
    zetaj = q->zetaj;
    frc_ij = q->frc_ij;
    noi = q->noi;
    noj = q->noj;

    rij = q->rij = vv_distance(q->Org->R, q->Dest->R);
    rrij = q->rrij = 1.0 / (q->rij + 1.0e-30);

    eij[X] = (Org->R[X] - Dest->R[X]) * rrij;
    eij[Y] = (Org->R[Y] - Dest->R[Y]) * rrij;
    q->Wij = w(kernel, rij);
    q->Fij = F(kernel, rij) * rrij;
    q->shear_rij =
        2.0 * etai * etaj * q->rij / (etai *
                                      (rij +
                                       2.0 * frc_ij[noj][noi].shear_slip)
                                      + etaj * (rij + 2.0 * frc_ij[noi]
                                                [noj].shear_slip) +
                                      1.0e-30);
    q->bulk_rij =
        2.0 * zetai * zetaj * rij / (zetai *
                                     (rij +
                                      2.0 * frc_ij[noj][noi].bulk_slip)
                                     + zetaj * (rij +
                                                2.0 *
                                                frc_ij[noi][noj].bulk_slip)
                                     + 1.0e-30);
}


void
SummationDensity(struct Pair *q)
{
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

void
SummationPhaseGradient(struct Pair *q)
{
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
    noi = q->noi;
    noj = q->noj;
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

void
UpdateForces(struct Pair *q)
{
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
    double delta = pair_delta;
    double art_vis = pair_art_vis;

    Csi = Org->Cs;
    Csj = Dest->Cs;
    theta = Uijdoteij * rij * delta / (rij * rij + 0.01 * delta * delta);
    NR_vis =
        Uijdoteij >
        0.0 ? 0.0 : art_vis * theta * (rhoi * Csi * mj +
                                       rhoj * Csj * mi) / (mi + mj);
    c = theta * Wij * art_vis / (rhoi + rhoj);
    dUi[X] = -eij[X] * c;
    dUi[Y] = -eij[Y] * c;
    dx = Ui[X] * Vi2 - Uj[X] * Vj2;
    dy = Ui[Y] * Vi2 - Uj[Y] * Vj2;
    drhodti = -Fij * rij * (dx * eij[X] + dy * eij[Y]);
    dPdti[X] = eij[X] * Fij * rij * (pi * Vi2 + pj * Vj2)
        - ((Uij[X] - eij[X] * Uijdoteij) * shear_rij +
           eij[X] * (Uijdoteij * 2.0 * bulk_rij + NR_vis))
        * Fij * (Vi2 + Vj2);
    dPdti[Y] = eij[Y] * Fij * rij * (pi * Vi2 + pj * Vj2)
        - ((Uij[Y] - eij[Y] * Uijdoteij) * shear_rij +
           eij[Y] * (Uijdoteij * 2.0 * bulk_rij + NR_vis))
        * Fij * (Vi2 + Vj2);
    double Surfi[2], Surfj[2], SurfaceForcei[2], SurfaceForcej[2];

    Surfi[X] = Org->del_phi[X];
    Surfi[Y] = Org->del_phi[Y];
    Surfj[X] = Dest->del_phi[X];
    Surfj[Y] = Dest->del_phi[Y];
    SurfaceForcei[X] = Surfi[X] * eij[X] + Surfi[Y] * eij[Y];
    SurfaceForcei[Y] = Surfi[Y] * eij[X] - Surfi[X] * eij[Y];
    SurfaceForcej[X] = Surfj[X] * eij[X] + Surfj[Y] * eij[Y];
    SurfaceForcej[Y] = Surfj[Y] * eij[X] - Surfj[X] * eij[Y];
    dPdti[X] +=
        (SurfaceForcei[X] * Vi2 + SurfaceForcej[X] * Vj2) * rij * Fij;
    dPdti[Y] +=
        (SurfaceForcei[Y] * Vi2 + SurfaceForcej[Y] * Vj2) * rij * Fij;
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

void
RandomForces(struct Pair *q, double sqrtdt)
{
    double Vi, Vj;
    double Ti, Tj;
    double v_eij[2];
    double Random_p, Random_v;
    struct Particle *Org, *Dest;
    double mi, mj;
    double shear_rij;
    double Fij;
    double *eij;
    double bulk_rij;
    double rmi, rmj;

    rmi = q->rmi;
    rmj = q->rmj;
    bulk_rij = q->bulk_rij;
    eij = q->eij;
    shear_rij = q->shear_rij;
    Fij = q->Fij;
    mi = q->mi;
    mj = q->mj;
    Org = q->Org;
    Dest = q->Dest;
    Ti = Org->T;
    Tj = Dest->T;
    if (Ti == 0 && Tj == 0)
        return;
    Vi = mi / Org->rho;
    Vj = mj / Dest->rho;
    random_gaussian(&Random_p, &Random_v);
    Random_p *= sqrtdt;
    Random_v *= sqrtdt;
    double _dUi[2];
    double Vi2 = Vi * Vi, Vj2 = Vj * Vj;

    v_eij[X] = v_eij[Y] = 0;
    _dUi[X] =
        v_eij[X] * Random_p * sqrt(16.0 * k_bltz * shear_rij * Ti * Tj /
                                   (Ti + Tj) * (Vi2 + Vj2) * Fij) +
        eij[X] * Random_v * sqrt(16.0 * k_bltz * bulk_rij * Ti * Tj /
                                 (Ti + Tj) * (Vi2 + Vj2) * Fij);
    _dUi[Y] =
        v_eij[Y] * Random_p * sqrt(16.0 * k_bltz * shear_rij * Ti * Tj /
                                   (Ti + Tj) * (Vi2 + Vj2) * Fij) +
        eij[Y] * Random_v * sqrt(16.0 * k_bltz * bulk_rij * Ti * Tj /
                                 (Ti + Tj) * (Vi2 + Vj2) * Fij);
    if (Dest->bd_type == 1) {
        Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi * 0.5;
        Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi * 0.5;
        Dest->rl_prtl->_dU[X] =
            Dest->rl_prtl->_dU[X] - _dUi[X] * rmj * 0.5;
        Dest->rl_prtl->_dU[Y] =
            Dest->rl_prtl->_dU[Y] - _dUi[Y] * rmj * 0.5;
    } else {
        Org->_dU[X] = Org->_dU[X] + _dUi[X] * rmi;
        Org->_dU[Y] = Org->_dU[Y] + _dUi[Y] * rmi;
        Dest->_dU[X] = Dest->_dU[X] - _dUi[X] * rmj;
        Dest->_dU[Y] = Dest->_dU[Y] - _dUi[Y] * rmj;
    }
}

int
initiation_ini(char *project_name, struct Ini *q)
{
    char Key_word[FILENAME_MAX];
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
    strcpy(q->inputfile, q->Project_name);
    strcat(q->inputfile, ".cfg");
    f = fopen(q->inputfile, "r");
    if (!f)
        ABORT(("can't open '%s'", q->inputfile));
    while (fscanf(f, "%s", Key_word) == 1) {
        if (!strcmp(Key_word, "INITIAL_CONDITION"))
            rc = fscanf(f, "%d", &q->initial_condition);
        if (!strcmp(Key_word, "CELLS"))
            rc = fscanf(f, "%d %d", &q->x_cells, &q->y_cells);
        if (!strcmp(Key_word, "CELL_SIZE"))
            rc = fscanf(f, "%lf", &q->cell_size);
        if (!strcmp(Key_word, "SMOOTHING_LENGTH"))
            rc = fscanf(f, "%lf", &q->smoothinglength);
        if (!strcmp(Key_word, "CELL_RATIO"))
            rc = fscanf(f, "%d", &q->cell_ratio);
        if (!strcmp(Key_word, "GRAVITY"))
            rc = fscanf(f, "%lf %lf", &q->gravity[0], &q->gravity[1]);
        if (!strcmp(Key_word, "ARTIFICIAL_VISCOSITY"))
            rc = fscanf(f, "%lf", &q->art_vis);
        if (!strcmp(Key_word, "NUMBER_OF_MATERIALS"))
            rc = fscanf(f, "%d", &q->number_of_materials);
        if (!strcmp(Key_word, "TIMING"))
            rc = fscanf(f, "%lf %lf %lf", &q->Start_time, &q->End_time,
                        &q->D_time);
        if (q->initial_condition == 0) {
            if (!strcmp(Key_word, "INITIAL_STATES"))
                rc = fscanf(f, "%lf %lf %lf %lf %lf", &q->U0[0], &q->U0[1],
                            &q->rho0, &q->p0, &q->T0);
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
    f = fopen(q->inputfile, "r");
    if (!f)
        ABORT(("can't open '%s'\n", q->inputfile));
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

    q->pair_list = list_ini();
    number_of_materials = q->number_of_materials;
    delta = q->delta;
    q->delta2 = delta * delta;
    q->delta3 = delta * delta * delta;
    q->materials = malloc(number_of_materials * sizeof(*q->materials));
    q->forces = malloc(number_of_materials * sizeof(*force));
    for (k = 0; k < number_of_materials; k++)
        q->forces[k] = malloc(number_of_materials * sizeof(*q->forces[k]));

    f = fopen(q->inputfile, "r");
    if (!f)
        ABORT(("can't open '%s'", q->inputfile));
    else
        printf("read the propeties of materials and forces\n");
    while (fscanf(f, "%s", Key_word) == 1) {
        if (!strcmp(Key_word, "MATERIALS"))
            for (k = 0; k < number_of_materials; k++) {
                mtl = &q->materials[k];
                mtl->number = k;
                if (fscanf
                    (f, "%s %d", mtl->material_name, &mtl->material_type)
                    != 2)
                    ABORT(("can't read material from '%s'", q->inputfile));
                if (fscanf
                    (f, "%lf %lf %lf %lf %lf", &mtl->eta, &mtl->zeta,
                     &mtl->gamma, &mtl->rho0, &mtl->a0) != 5)
                    ABORT(("can't read materal parameters from '%s'",
                           q->inputfile));
                Set_nu(mtl);
            }
        if (!strcmp(Key_word, "FORCES"))
            for (l = 0; l < number_of_materials; l++)
                for (n = 0; n < number_of_materials; n++) {
                    if (fscanf(f, "%d %d", &k, &m) != 2)
                        ABORT(("can't read materal from '%s'",
                               q->inputfile));
                    force = &q->forces[k][m];
                    if (fscanf(f, "%lf %lf %lf %lf",
                               &force->epsilon, &force->sigma,
                               &force->shear_slip, &force->bulk_slip) != 4)
                        ABORT(("can't read force from '%s'",
                               q->inputfile));
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
    q->dt_g_vis =
        AMIN1(sqrt(delta / vv_abs(q->gravity)),
              0.5 * q->delta2 / q->viscosity_max);
    q->dt_surf = 0.4 * sqrt(q->delta3 / q->surface_max);
    sound = AMAX1(vv_abs(q->gravity), q->viscosity_max);
    sound = AMAX1(q->surface_max, sound);
    for (k = 0; k < number_of_materials; k++)
        Set_b0(&q->materials[k], sound);
    q->particle_list = list_ini();

    return 0;
}

int
manager_update_list(struct Ini *q)
{

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
                    k = (int) ((prtl->R[0] + cell_size) / cell_size);
                    m = (int) ((prtl->R[1] + cell_size) / cell_size);
                    if (k != i || m != j) {
                        list_remove(cell_lists[i][j], p);
                        INSERT_P(prtl, cell_lists[k][m]);
                    } else
                        p = list_next(cell_lists[i][j], p);
                } else
                    p = list_next(cell_lists[i][j], p);
            }

        }
    }
    return 0;
}

int
manager_build_nnp(struct Ini *q, double point[2])
{
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
    k = (int) ((point[0] + cell_size) / cell_size);
    m = (int) ((point[1] + cell_size) / cell_size);
    for (i = k - 1; i <= k + 1; i++)
        for (j = m - 1; j <= m + 1; j++)
            if (i < x_clls && j < y_clls && i >= 0 && j >= 0)
                LOOP_P(prtl, cell_lists[i][j]) {
                dstc = vv_distance(point, prtl->R);
                if (dstc < smoothinglength)
                    INSERT_P(prtl, NNP_list);
                }
    return 0;
}

int
manager_build_pair(struct Ini *q,
                   struct List *pairs,
                   struct List *particle_list,
                   struct Force **forces, struct Kernel *kernel)
{
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

    ILOOP_P(pair, pairs) {
        pair_fin(pair);
    }
    list_clear(pairs);
    LOOP_P(prtl_org, particle_list) {
        if (prtl_org->bd == 0) {
            i = (int) ((prtl_org->R[0] + cell_size) / cell_size);
            j = (int) ((prtl_org->R[1] + cell_size) / cell_size);
            for (k = i - 1; k <= i + 1; k++)
                for (m = j - 1; m <= j + 1; m++) {
                    LOOP1_P(prtl_dest, cell_lists[k][m]) {
                        dstc = vv_sq_distance(prtl_org->R, prtl_dest->R);
                        if (dstc <= sm2 && prtl_org->ID >= prtl_dest->ID) {
                            pair =
                                pair_ini(prtl_org, prtl_dest,
                                         forces, kernel, sqrt(dstc));
                            INSERT_P(pair, pairs);
                        }
                    }
                }
        }
    }
    return 0;
}

void
manager_build_particles(struct Ini *q, struct Material *materials,
                        struct List *particle_list, struct Ini *ini)
{

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
                        position[0] =
                            (i - 1) * cell_size + (k + 0.5) * delta;
                        position[1] =
                            (j - 1) * cell_size + (m + 0.5) * delta;
                        material_no = 1;
                        velocity[X] = ini->U0[X];
                        velocity[Y] = ini->U0[Y];
                        Temperature = ini->T0;
                        density = materials[material_no].rho0;
                        pressure = get_p(&materials[material_no], density);
                        prtl =
                            particle_real(position, velocity, density,
                                          pressure, Temperature,
                                          &materials[material_no]);
                        prtl->cell_i = i;
                        prtl->cell_j = j;
                        INSERT_P(prtl, particle_list);
                        INSERT_P(prtl, cell_lists[i][j]);

                    }
                }
            }
        }
    }

    if (ini->initial_condition == 1) {
        strcpy(inputfile, ini->Project_name);
        strcat(inputfile, ".rst");
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
            ABORT(("can't read number of particles from '%s'", N));
        else
            WARN(("N = %d", N));
        for (n = 0; n < N; n++) {
            if (fgets(line, MAX_SIZE, f) == NULL)
                ABORT(("can't read a line from '%s'", inputfile));
            cnt = sscanf(line, "%s %lf %lf %lf %lf %lf %lf %lf",
                         material_name, &position[0], &position[1],
                         &velocity[0], &velocity[1], &density, &pressure,
                         &Temperature);
            if (cnt != 8) {
                WARN(("line: '%s'", line));
                WARN(("material_name: %s", material_name));
                ABORT(("can't read a particle from '%s' (cnt = %d, n = %d)", inputfile, cnt, n));
            }
            material_no = -1;
            for (k = 0; k < ini->number_of_materials; k++)
                if (strcmp(material_name, materials[k].material_name) == 0)
                    material_no = k;
            if (material_no != -1) {
                pressure = get_p(&materials[material_no], density);
                prtl =
                    particle_real(position, velocity, density, pressure,
                                  Temperature, &materials[material_no]);
                INSERT_P(prtl, particle_list);
                i = (int) (prtl->R[0] / cell_size) + 1;
                j = (int) (prtl->R[1] / cell_size) + 1;
                prtl->cell_i = i;
                prtl->cell_j = j;
                INSERT_P(prtl, cell_lists[i][j]);
            } else {
                ABORT(("The material in the restart file is not used by the program!"));
            }
        }
        fclose(f);
    }
}

int
initiation_fin(struct Ini *q)
{
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

    ILOOP_P(pair, q->pair_list) {
        pair_fin(pair);
    }
    list_fin(q->pair_list);

    LOOP_P(prtl, q->particle_list) {
        particle_fin(prtl);
    }
    list_fin(q->particle_list);

    return 0;
}


void
UpdateSurfaceStress(struct Ini *q)
{
    double
     epsilon = 1.0e-30;
    double
     interm0, interm1, interm2;
    struct Particle *prtl;
    struct ListNode *p;

    LOOP_P(prtl, q->particle_list) {
        interm0 = 1.0 / (vv_abs(prtl->del_phi) + epsilon);
        interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
        interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
        prtl->del_phi[0] = interm1 * interm0;
        prtl->del_phi[1] = interm2 * interm0;
    }
    LOOP_P(prtl, q->b) {
        interm0 = vv_abs(prtl->del_phi) + epsilon;
        interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
        interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
        prtl->del_phi[0] = interm1 / interm0;
        prtl->del_phi[1] = interm2 / interm0;
    }
}

double
GetTimestep(struct Ini *q)
{
    struct Particle *prtl;
    struct ListNode *p;
    double
     Cs_max = 0.0, V_max = 0.0, rho_min = 1.0e30, rho_max = 1.0;
    double
     dt;

    LOOP_P(prtl, q->particle_list) {
        Cs_max = AMAX1(Cs_max, prtl->Cs);
        V_max = AMAX1(V_max, vv_abs(prtl->U));
        rho_min = AMIN1(rho_min, prtl->rho);
        rho_max = AMAX1(rho_max, prtl->rho);
    }
    dt = AMIN1(sqrt(0.5 * (rho_min + rho_max)) * q->dt_surf, q->dt_g_vis);
    return 0.25 * AMIN1(dt, q->delta / (Cs_max + V_max));
}

int
output_particles(struct Ini *q, struct List *particle_list,
                 struct Material *materials, double Time)
{
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
    sprintf(file_list, "%.10lld", (long long) Itime);
    strcat(file_name, file_list);
    strcat(file_name, ".dat");

    f = fopen(file_name, "w");
    if (!f)
        ABORT(("can't write '%s'", file_name));
    fprintf(f, "%s", "title='particle position' \n");
    fprintf(f, "%s", "variables=x, y, Ux, Uy \n");
    for (i = 0; i < number_of_materials; i++) {
        j = 0;
        LOOP_P(prtl, particle_list) {
            if (strcmp
                (materials[i].material_name,
                 prtl->mtl->material_name) == 0) {
                j++;
                if (j == 1)
                    fprintf(f, "zone t='%s' \n",
                            materials[i].material_name);
                fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1],
                        prtl->U[0], prtl->U[1]);
            }
        }
        LOOP_P(prtl, q->b) {
            if (strcmp
                (materials[i].material_name,
                 prtl->mtl->material_name) == 0) {
                j++;
                if (j == 1)
                    fprintf(f, "zone t='%s' \n",
                            materials[i].material_name);
                fprintf(f, "%.6g %.6g %.6g %.6g\n", prtl->R[0], prtl->R[1],
                        prtl->U[0], prtl->U[1]);
            }
        }
    }
    fclose(f);
    return 0;
}

int
output_restart(struct Ini *q, struct List *particle_list, double Time)
{
    int n;
    char file_name[FILENAME_MAX];
    struct Particle *prtl;
    struct ListNode *p;
    FILE *f;

    strcpy(file_name, q->Project_name);
    strcat(file_name, ".rst");
    f = fopen(file_name, "w");
    if (!f)
        ABORT(("can't write '%s'", file_name));
    n = 0;
    LOOP_P(prtl, particle_list) {
        if (prtl->bd == 0)
            n++;
    }
    fprintf(f, "%.6g\n", Time);
    fprintf(f, "%d\n", n);
    LOOP_P(prtl, particle_list) {
        if (prtl->bd == 0)
            fprintf(f, "%s %.6g %.6g %.6g %.6g %.6g %.6g %.6g\n",
                    prtl->mtl->material_name, prtl->R[0], prtl->R[1],
                    prtl->U[0], prtl->U[1], prtl->rho, prtl->p, prtl->T);
    }
    fclose(f);
    return 0;
}

void
VolumeMass(struct List *particle_list, struct Ini *ini,
           struct Kernel *kernel)
{
    double reciprocV;
    double dstc;
    struct ListNode *p, *p1;
    struct Particle *prtl_org, *prtl_dest;

    LOOP_P(prtl_org, particle_list) {
        manager_build_nnp(ini, prtl_org->R);
        reciprocV = 0.0;
        LOOP1_P(prtl_dest, ini->NNP_list) {
            dstc = vv_distance(prtl_org->R, prtl_dest->R);
            reciprocV += w(kernel, dstc);
        }
        reciprocV = 1.0 / reciprocV;
        prtl_org->V = reciprocV;
        prtl_org->m = prtl_org->rho * reciprocV;
        list_clear(ini->NNP_list);
    }
}

void
step(int *pite, struct Ini *q,
     double *Time, double D_time, struct Kernel *kernel)
{
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
        dt = GetTimestep(q);
        sqrtdt = sqrt(dt);
        ite++;
        integeral_time += dt;
        *Time += dt;
        if (ite % 10 == 0)
            printf("N=%d Time: %g	dt: %g\n", ite, *Time, dt);
        manager_build_pair(q, q->pair_list,
                           q->particle_list, q->forces, kernel);
        LOOP_P(prtl, q->particle_list) {
            prtl->rho = 0.0;
        }
        ILOOP_P(pair, q->pair_list) {
            SummationDensity(pair);
        }
        LOOP_P(prtl, q->particle_list) {
            prtl->p = get_p(prtl->mtl, prtl->rho);
        }

        boundary_condition(q, q->cell_lists);
        LOOP_P(prtl, q->particle_list) {
            prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
        }
        LOOP_P(prtl, q->b) {
            prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
        }

        ILOOP_P(pair, q->pair_list) {
            SummationPhaseGradient(pair);
        }

        boundary_condition(q, q->cell_lists);
        UpdateSurfaceStress(q);
        LOOP_P(prtl, q->particle_list) {
            prtl->dedt = 0.0;
            prtl->drhodt = 0.0;
            prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
            prtl->_dU[X] = prtl->_dU[Y] = 0.0;
        }
        ILOOP_P(pair, q->pair_list) {
            UpdateForces(pair);
        }
        LOOP_P(prtl, q->particle_list) {
            prtl->dUdt[X] += q->gravity[X];
            prtl->dUdt[Y] += q->gravity[Y];
        }

        LOOP_P(prtl, q->particle_list) {
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

        ILOOP_P(pair, q->pair_list) {
            RenewPair(pair, kernel);
        }

        LOOP_P(prtl, q->particle_list) {
            prtl->rho = 0.0;
        }
        ILOOP_P(pair, q->pair_list) {
            SummationDensity(pair);
        }
        LOOP_P(prtl, q->particle_list) {
            prtl->p = get_p(prtl->mtl, prtl->rho);
        }

        boundary_condition(q, q->cell_lists);
        LOOP_P(prtl, q->particle_list) {
            prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
        }
        LOOP_P(prtl, q->b) {
            prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
        }

        ILOOP_P(pair, q->pair_list) {
            SummationPhaseGradient(pair);
        }

        boundary_condition(q, q->cell_lists);
        UpdateSurfaceStress(q);
        LOOP_P(prtl, q->particle_list) {
            prtl->dedt = 0.0;
            prtl->drhodt = 0.0;
            prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
            prtl->_dU[X] = prtl->_dU[Y] = 0.0;
        }
        ILOOP_P(pair, q->pair_list) {
            UpdateForces(pair);
        }
        LOOP_P(prtl, q->particle_list) {
            prtl->dUdt[X] += q->gravity[X];
            prtl->dUdt[Y] += q->gravity[Y];
        }

        LOOP_P(prtl, q->particle_list) {
            prtl->_dU[X] = prtl->_dU[Y] = 0.0;
        }
        ILOOP_P(pair, q->pair_list) {
            RandomForces(pair, sqrtdt);
        }

        LOOP_P(prtl, q->particle_list) {
            prtl->U[X] += prtl->_dU[X];
            prtl->U[Y] += prtl->_dU[Y];
            prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
            prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
            prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
            prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
        }

        LOOP_P(prtl, q->particle_list) {
            prtl->U[X] = prtl->U[X] + prtl->_dU[X];
            prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
        }

        boundary_check(q, q->particle_list);
        manager_update_list(q);
        boundary_build(q, q->cell_lists, q->materials);
    }
    *pite = ite;
}

#define A prtl = particle_mirror(prtl_old, mtl)
#define B prtl = particle_image(prtl_old)
#define C(t) do {                               \
	if (prtl->rl_prtl == NULL)		\
	    abort();				\
	particle_copy(prtl, prtl->rl_prtl, t);	\
    } while (0)

static int boundary_w(struct Ini *, struct Particle *);
static int boundary_e(struct Ini *, struct Particle *);
static int boundary_s(struct Ini *, struct Particle *);
static int boundary_n(struct Ini *, struct Particle *);
static int boundary_sw(struct Ini *, struct Particle *);
static int boundary_se(struct Ini *, struct Particle *);
static int boundary_nw(struct Ini *, struct Particle *);
static int boundary_ne(struct Ini *, struct Particle *);

int
boundary_build(struct Ini *q, struct List ***c, struct Material *mtl)
{
    int i, j;
    struct Particle *prtl, *prtl_old;
    int kb, ku, mb, mu;
    struct ListNode *p;
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
boundary_condition(struct Ini *q, struct List ***c)
{
    int i, j;
    int kb, ku, mb, mu;
    struct Particle *prtl;
    struct ListNode *p;
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
boundary_w(struct Ini *q, struct Particle *prtl)
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
boundary_e(struct Ini *q, struct Particle *prtl)
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
boundary_s(struct Ini *q, struct Particle *prtl)
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
boundary_n(struct Ini *q, struct Particle *prtl)
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
boundary_sw(struct Ini *q, struct Particle *prtl)
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
boundary_nw(struct Ini *q, struct Particle *prtl)
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
boundary_ne(struct Ini *q, struct Particle *prtl)
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
boundary_se(struct Ini *q, struct Particle *prtl)
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
boundary_check(struct Ini *q, struct List *list)
{
    struct ListNode *p;
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
