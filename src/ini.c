#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sph/err.h"
#include "sph/ini.h"
#include "sph/list.h"

enum { X, Y };
int
initiation_ini(char *project_name, struct Ini *q)
{
    char Key_word[FILENAME_MAX];
    char *mkdir = "mkdir -p outdata";
    FILE *f;
    int rc;
    int i;
    int j;
    int n;

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

    return 0;
}
