#ifdef __cplusplus
extern "C" {
#endif
struct Initiation;
struct Hydrodynamics;
struct Manager;
struct Boundary;
struct QuinticSpline;
struct Diagnose;
struct MLS;
void step(int *ite, struct Hydrodynamics *, struct Manager *, struct Boundary *, double *,
	  double D_time, struct Diagnose *, struct Initiation *, struct QuinticSpline *, struct MLS *);
#ifdef __cplusplus
}
#endif
