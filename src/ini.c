#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "sph/err.h"
#include "sph/force.h"
#include "sph/ini.h"
#include "sph/kernel.h"
#include "sph/list.h"
#include "sph/macro.h"
#include "sph/material.h"
#include "sph/pair.h"
#include "sph/particle.h"
#include "sph/vv.h"

enum { X, Y };
enum { MAX_SIZE = 4096 };

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

int
initiation_ini(char *project_name, struct Ini *q)
{
    char Key_word[FILENAME_MAX];
    char *mkdir = "mkdir -p outdata";
    double delta;
    double smoothinglength;
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
    smoothinglength = q->smoothinglength;
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
manager_fin(struct Ini *q)
{
    struct List ***c;
    int x_clls, y_clls;
    int i, j;

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
    return 0;
}

void
UpdatePair(struct Ini *q, struct Kernel *kernel)
{
    struct ListNode *p;
    struct Pair *pair;

    ILOOP_P(pair, q->pair_list) {
        RenewPair(pair, kernel);
    }
}

void
UpdatePhaseGradient(struct Ini *q)
{
    struct ListNode *p;
    struct Pair *pair;

    Zero_PhaseGradient(q);
    ILOOP_P(pair, q->pair_list) {
        SummationPhaseGradient(pair);
    }
}

void
UpdateDensity(struct Ini *q)
{
    struct ListNode *p;
    struct Pair *pair;

    Zero_density(q);
    ILOOP_P(pair, q->pair_list) {
        SummationDensity(pair);
    }
    UpdateState(q);
}

void
UpdateChangeRate(struct Ini *q)
{
    struct ListNode *p;
    struct Pair *pair;

    ZeroChangeRate(q);
    ILOOP_P(pair, q->pair_list) {
        UpdateForces(pair);
    }
    AddGravity(q);
}

void
UpdateRandom(struct Ini *q, double sqrtdt)
{
    struct ListNode *p;
    struct Pair *pair;

    Zero_Random(q);
    ILOOP_P(pair, q->pair_list) {
        RandomForces(pair, sqrtdt);
    }
}

void
ZeroChangeRate(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->dedt = 0.0;
        prtl->drhodt = 0.0;
        prtl->dUdt[X] = prtl->dUdt[Y] = 0.0;
        prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void
Zero_density(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->rho = 0.0;
    }
}

void
Zero_PhaseGradient(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;
    struct List *blist;

    blist = boundary_list(q);

    LOOP_P(prtl, q->particle_list) {
        prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
    LOOP_P(prtl, blist) {
        prtl->del_phi[X] = prtl->del_phi[Y] = 0.0;
    }
}

void
Zero_Random(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->_dU[X] = prtl->_dU[Y] = 0.0;
    }
}

void
AddGravity(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->dUdt[X] += q->gravity[X];
        prtl->dUdt[Y] += q->gravity[Y];
    }
}

void
UpdateState(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->p = get_p(prtl->mtl, prtl->rho);
    }
}

void
UpdatePahseMatrix(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;
    int
     i, j, number_of_materials;
    struct List *blist;

    blist = boundary_list(q);
    number_of_materials = q->number_of_materials;
    LOOP_P(prtl, q->particle_list) {
        for (i = 0; i < number_of_materials; i++)
            for (j = 0; j < number_of_materials; j++) {
                if (i != j)
                    prtl->phi[i][j] = prtl->phi[i][j];
            }
    }
    LOOP_P(prtl, blist) {
        for (i = 0; i < number_of_materials; i++)
            for (j = 0; j < number_of_materials; j++) {
                if (i != j)
                    prtl->phi[i][j] = prtl->phi[i][j];
            }
    }
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
    struct List *blist;

    blist = boundary_list(q);

    LOOP_P(prtl, q->particle_list) {
        interm0 = 1.0 / (vv_abs(prtl->del_phi) + epsilon);
        interm1 = 0.5 * vv_sqdiff(prtl->del_phi);
        interm2 = prtl->del_phi[X] * prtl->del_phi[Y];
        prtl->del_phi[0] = interm1 * interm0;
        prtl->del_phi[1] = interm2 * interm0;
    }
    LOOP_P(prtl, blist) {
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

void
Predictor_summation(struct Ini *q, double dt)
{
    struct ListNode *p;
    struct Particle *prtl;

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
}

void
Corrector_summation(struct Ini *q, double dt)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->U[X] += prtl->_dU[X];
        prtl->U[Y] += prtl->_dU[Y];
        prtl->R[X] = prtl->R_I[X] + prtl->U[X] * dt;
        prtl->R[Y] = prtl->R_I[Y] + prtl->U[Y] * dt;
        prtl->U[X] = prtl->U_I[X] + prtl->dUdt[X] * dt;
        prtl->U[Y] = prtl->U_I[Y] + prtl->dUdt[Y] * dt;
    }
}

void
RandomEffects(struct Ini *q)
{
    struct ListNode *p;
    struct Particle *prtl;

    LOOP_P(prtl, q->particle_list) {
        prtl->U[X] = prtl->U[X] + prtl->_dU[X];
        prtl->U[Y] = prtl->U[Y] + prtl->_dU[Y];
    }
}

void
hydro_fin(struct Ini *q)
{
    int i;
    struct ListNode *p;
    struct Pair *pair;
    struct Particle *prtl;

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
    struct List *blist;
    struct ListNode *p;
    struct Particle *prtl;

    blist = boundary_list(q);
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
        LOOP_P(prtl, blist) {
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
    double integeral_time;
    double dt;
    int ite;

    ite = *pite;

    integeral_time = 0;
    while (integeral_time < D_time) {
        dt = GetTimestep(q);
        ite++;
        integeral_time += dt;
        *Time += dt;
        if (ite % 10 == 0)
            printf("N=%d Time: %g	dt: %g\n", ite, *Time, dt);
        manager_build_pair(q, q->pair_list,
                           q->particle_list, q->forces, kernel);
        UpdateDensity(q);
        boundary_condition(q, q->cell_lists);
        UpdatePhaseGradient(q);
        boundary_condition(q, q->cell_lists);
        UpdateSurfaceStress(q);
        UpdateChangeRate(q);
        Predictor_summation(q, dt);
        boundary_condition(q, q->cell_lists);
        UpdatePair(q, kernel);
        UpdateDensity(q);
        boundary_condition(q, q->cell_lists);
        UpdatePhaseGradient(q);
        boundary_condition(q, q->cell_lists);
        UpdateSurfaceStress(q);
        UpdateChangeRate(q);
        UpdateRandom(q, sqrt(dt));
        Corrector_summation(q, dt);
        RandomEffects(q);
        boundary_check(q, q->particle_list);
        manager_update_list(q);
        boundary_build(q, q->cell_lists, q->materials);
    }
    *pite = ite;
}
