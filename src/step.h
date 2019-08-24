class Initiation;
class Hydrodynamics;
class ParticleManager;
class Boundary;
class QuinticSpline;
class Diagnose;
class MLS;
void step(int ite, Hydrodynamics*, ParticleManager*, Boundary*, double*, double D_time, Diagnose*, Initiation*, QuinticSpline*, MLS*);
