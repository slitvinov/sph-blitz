class Initiation;
class Hydrodynamics;
class ParticleManager;
class Boundary;
class QuinticSpline;
class Diagnose;
class MLS;
void step(int ite, Hydrodynamics *hydro, ParticleManager *particles, Boundary *boundary, double *Time, double D_time, Diagnose *diagnose, Initiation *ini, QuinticSpline *weight_function, MLS *mls);
