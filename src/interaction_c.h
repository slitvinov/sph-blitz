#ifdef __cplusplus
extern "C" {
#endif
struct Particle;
struct Force;
struct Initiation;
struct QuinticSpline;
struct Interaction* interaction_ini(struct Particle*, struct Particle*, struct Force **, struct QuinticSpline *q, double);
int interaction_fin(struct Interaction*);

#ifdef __cplusplus
}
#endif

