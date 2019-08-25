struct Initiation;
struct Hydrodynamics;
struct Boundary;
struct Manager;
struct MLS;
class Output {
    char Project_name[25];
    int number_of_materials;
    double delta;
    int x_cells;
    int y_cells;
    int cell_ratio; 
public:
    explicit Output(Initiation*);
    void OutputParticles(Hydrodynamics*, Boundary*, double Time);
    void OutputStates(Manager*, MLS*, QuinticSpline*, double Time);
    void OutRestart(Hydrodynamics*, double Time);
};
