#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sph/err.h"
#include "sph/ini.h"
int
initiation_ini(char *project_name, struct Ini *q)
{
    char Key_word[FILENAME_MAX];
    char *mkdir = "mkdir -p outdata";
    FILE *f;
    int rc;

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
    return 0;
}
