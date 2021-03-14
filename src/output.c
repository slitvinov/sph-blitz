#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sph/particle.h"
#include "sph/list.h"
#include "sph/ini.h"
#include "sph/material.h"
#include "sph/boundary.h"
#include "sph/macro.h"
#include "sph/err.h"
#include "sph/output.h"

struct Output {
    char Project_name[FILENAME_MAX];
    int number_of_materials;
};

struct Output *
output_ini(struct Ini *ini)
{
    struct Output *q;

    q = malloc(sizeof(struct Output));
    if (q == NULL)
        return NULL;
    strcpy(q->Project_name, ini->Project_name);
    q->number_of_materials = ini->number_of_materials;
    return q;
}

int
output_particles(struct Output *q, struct List *particle_list,
                 struct Material *materials, struct Boundary *boundary,
                 double Time)
{
    char file_name[FILENAME_MAX], file_list[FILENAME_MAX];
    double Itime;
    FILE *f;
    int i, j;
    int number_of_materials;
    struct List *blist;
    struct ListNode *p;
    struct Particle *prtl;

    blist = boundary_list(boundary);
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
output_restart(struct Output *q, struct List *particle_list, double Time)
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

int
output_fin(struct Output *q)
{
    free(q);
    return 0;
}
