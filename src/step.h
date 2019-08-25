class Initiation;
class Hydrodynamics;
class Manager;
class Boundary;
class QuinticSpline;
class Diagnose;
class MLS;
void step(int ite, Hydrodynamics*, Manager*, Boundary*, double*, double D_time, Diagnose*, Initiation*, QuinticSpline*, MLS*);
