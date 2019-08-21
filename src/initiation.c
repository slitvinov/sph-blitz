#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tgmath.h>
#include "initiation.h"

int initiation_ini(const char *project_name, struct Initiation *q) {
    char Key_word[FILENAME_MAX];
    FILE *f;

    //the project name
    strcpy(q->Project_name, project_name);

    //the input file name
    strcpy(q->inputfile, q->Project_name);
    strcat(q->inputfile, ".cfg");

    ///<ul><li>check if inputfile exists (if not exit the program)
    f = fopen(q->inputfile, "r");
    if (!f) {
	fprintf(stderr, "%s:%d: %s : fail to open\n", __FILE__, __LINE__, q->inputfile);
	exit(1);
    }

    ///<li>reading key words and configuration data from configuration file and assign them to the appropriate variable
    while (fscanf(f, "%s", Key_word) == 1) {
	//comparing the key words for initial condition input
	//0: Initialize the initial conditions from .cfg file
	//1: restart from a .rst file
	if(!strcmp(Key_word, "INITIAL_CONDITION"))
	    fscanf(f, "%d", &q->initial_condition);

	//output diagnose information
	if(!strcmp(Key_word, "DIAGNOSE"))
	    fscanf(f, "%d", &q->diagnose);

	//comparing the key words for domian size
	if(!strcmp(Key_word, "CELLS"))
	    fscanf(f, "%d %d", &q->x_cells, &q->y_cells);

	//comparing the key words for cell size
	if(!strcmp(Key_word, "CELL_SIZE"))
	    fscanf(f, "%lf", &q->cell_size);

	//comparing the key words for smoothinglength
	if(!strcmp(Key_word, "SMOOTHING_LENGTH"))
	    fscanf(f, "%lf", &q->smoothinglength);

	//comparing the key words for the ratio between cell size and initial particle width
	if(!strcmp(Key_word, "CELL_RATIO"))
	    fscanf(f, "%d", &q->hdelta);

	//comparing the key words for the g force
	if(!strcmp(Key_word, "G_FORCE"))
	    fscanf(f, "%lf %lf",
		   &q->g_force[0], &q->g_force[1]);

	//comparing the key words for the artificial viscosity
	if(!strcmp(Key_word, "ARTIFICIAL_VISCOSITY"))
	    fscanf(f, "%lf", &q->art_vis);

	//comparing the key words for number ofmaterials
	if(!strcmp(Key_word, "NUMBER_OF_MATERIALS"))
	    fscanf(f, "%d", &q->number_of_materials);

	//comparing the key words for timing
	if(!strcmp(Key_word, "TIMING"))
	    fscanf(f, "%lf %lf %lf", &q->Start_time, &q->End_time, &q->D_time);

	//Premitted max particle number for MLS approximation
	if(!strcmp(Key_word, "MLS_MAX"))
	    fscanf(f, "%d", &q->MLS_MAX);

	//Initialize the initial conditions from .cfg file
	if (q->initial_condition==0) {
	    //comparing the key words for the initial state
	    if(!strcmp(Key_word, "INITIAL_STATES"))
		fscanf(f, "%lf %lf %lf %lf %lf", &q->U0[0], &q->U0[1], &q->rho0, &q->p0, &q->T0);
	}

    }
    fclose(f);

    ///<li>create outdata directory
    system("mkdir -p outdata");

    ///<li>process the data <b>!!!Question!!!</b>
    q->box_size[0] = q->x_cells*q->cell_size;
    q->box_size[1] = q->y_cells*q->cell_size;
    q->delta = q->cell_size/q->hdelta;
    ///(line 104) this is only true if h=cell_size (which is not necessarily given, as h, cell_size can be initiated independently in configuration file)

    ///<li>output information to screen
    return 0;
}
