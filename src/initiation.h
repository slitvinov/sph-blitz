#ifdef __cplusplus
extern "C" {
#endif
struct Initiation {
    char Project_name[FILENAME_MAX];
    int number_of_materials;
    char inputfile[FILENAME_MAX];
    int initial_condition;
    int diagnose;
    double art_vis;
    double smoothinglength;
    double box_size[2];
    double cell_size;
    double delta;
    int hdelta;
    int x_cells
    int y_cells;
    double g_force[2];
    double Start_time;
    double End_time;
    double D_time;
    double U0[2];
    double rho0;
    double p0;
    double T0;
    int MLS_MAX;
};
int initiation_ini(const char*, struct Initiation*);
#ifdef __cplusplus
}
#endif
