class Hydrodynamics;
class Boundary;
class ParticleManager;
class Output {
    char Project_name[25];
    int number_of_materials;
    double delta;
    int x_cells;
    int y_cells;
    int hdelta; 
public:
    explicit Output(Initiation *ini);
    void OutputParticles(Hydrodynamics *hydro, Boundary *boundary, double Time);
    void OutputStates(ParticleManager *particles, MLS *mls, QuinticSpline *weight_function, double Time);
    void OutRestart(Hydrodynamics *hydro, double Time);
};
