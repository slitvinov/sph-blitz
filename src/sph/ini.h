struct Ini {
    char inputfile[FILENAME_MAX];
    char Project_name[FILENAME_MAX];
    double art_vis;
    double box_size[2];
    double cell_size;
    double delta;
    double D_time;
    double End_time;
    double gravity[2];
    double p0;
    double rho0;
    double smoothinglength;
    double Start_time;
    double T0;
    double U0[2];
    int cell_ratio;
    int diag;
    int initial_condition;
    int number_of_materials;
    int x_cells;
    int y_cells;

    int x_clls;
    int y_clls;
    struct List ***cell_lists;
    struct List *NNP_list;

    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    struct List *b;
};
int initiation_ini(char *, struct Ini *);
