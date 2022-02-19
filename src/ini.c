#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sph/err.h"
#include "sph/ini.h"
#include "sph/list.h"
#include "sph/material.h"
#include "sph/force.h"
#include "sph/vv.h"

enum { X, Y };
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
                    ABORT(("can't read material from '%s'",
                           q->inputfile));
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
