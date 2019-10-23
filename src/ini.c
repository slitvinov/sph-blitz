#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "err.h"
#include "ini.h"
int
initiation_ini(char *project_name, struct Ini *q)
{
    char Key_word[FILENAME_MAX];
    char *mkdir = "mkdir -p outdata";
    FILE *f;

    strcpy(q->Project_name, project_name);
    strcpy(q->inputfile, q->Project_name);
    strcat(q->inputfile, ".cfg");
    f = fopen(q->inputfile, "r");
    if (!f)
        ABORT(("can't open '%s'", q->inputfile));
    while (fscanf(f, "%s", Key_word) == 1) {
        if (!strcmp(Key_word, "INITIAL_CONDITION"))
            fscanf(f, "%d", &q->initial_condition);
        if (!strcmp(Key_word, "DIAGNOSE"))
            fscanf(f, "%d", &q->diag);
        if (!strcmp(Key_word, "CELLS"))
            fscanf(f, "%d %d", &q->x_cells, &q->y_cells);
        if (!strcmp(Key_word, "CELL_SIZE"))
            fscanf(f, "%lf", &q->cell_size);
        if (!strcmp(Key_word, "SMOOTHING_LENGTH"))
            fscanf(f, "%lf", &q->smoothinglength);
        if (!strcmp(Key_word, "CELL_RATIO"))
            fscanf(f, "%d", &q->cell_ratio);
        if (!strcmp(Key_word, "GRAVITY"))
            fscanf(f, "%lf %lf", &q->gravity[0], &q->gravity[1]);
        if (!strcmp(Key_word, "ARTIFICIAL_VISCOSITY"))
            fscanf(f, "%lf", &q->art_vis);
        if (!strcmp(Key_word, "NUMBER_OF_MATERIALS"))
            fscanf(f, "%d", &q->number_of_materials);
        if (!strcmp(Key_word, "TIMING"))
            fscanf(f, "%lf %lf %lf", &q->Start_time, &q->End_time,
                   &q->D_time);
        if (!strcmp(Key_word, "MLS_MAX"))
            fscanf(f, "%d", &q->MLS_MAX);
        if (q->initial_condition == 0) {
            if (!strcmp(Key_word, "INITIAL_STATES"))
                fscanf(f, "%lf %lf %lf %lf %lf", &q->U0[0], &q->U0[1],
                       &q->rho0, &q->p0, &q->T0);
        }
    }
    fclose(f);
    if (system(mkdir) != 0)
        ABORT(("command '%s' faild", mkdir));
    q->box_size[0] = q->x_cells * q->cell_size;
    q->box_size[1] = q->y_cells * q->cell_size;
    q->delta = q->cell_size / q->cell_ratio;
    return 0;
}
