struct Initiation;
struct Hydrodynamics;
struct Boundary;
struct Manager;
struct MLS;
struct Output {
    char Project_name[25];
    int number_of_materials;
    double delta;
    int x_cells;
    int y_cells;
    int cell_ratio; 
    Output(struct Initiation*);
    //    void OutputStates(struct Manager*, struct MLS*, struct QuinticSpline*, double Time);
    //    void OutRestart(struct Hydrodynamics*, double Time);
};

int output_particles(struct Hydrodynamics*, struct Boundary*, double Time);
int output_states(struct Output*, struct Manager*, struct MLS*, struct QuinticSpline*, double Time);
int output_restart(struct Output*, struct Hydrodynamics*, double Time);
