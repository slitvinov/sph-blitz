struct Initiation;
struct Hydrodynamics;
struct Boundary;
struct Manager;
struct MLS;
struct Output {
    char Project_name[25];
    double delta;
    int x_cells;
    int y_cells;
    int cell_ratio; 
};

int output_particles(struct Hydrodynamics*, struct Boundary*, double Time);
int output_states(struct Output*, struct Manager*, struct MLS*, struct QuinticSpline*, double Time);
int output_restart(struct Output*, struct Hydrodynamics*, double Time);
struct Output* output_ini(struct Initiation*);
int output_fin(struct Output*);
