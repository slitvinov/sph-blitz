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
    void OutputParticles(struct Hydrodynamics*, struct Boundary*, double Time);
    void OutputStates(struct Manager*, struct MLS*, struct QuinticSpline*, double Time);
    void OutRestart(struct Hydrodynamics*, double Time);
};

