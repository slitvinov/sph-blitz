#ifdef __cplusplus
extern "C" {
#endif
struct Particle;
struct Boundary;
struct Hydrodynamics;
struct Initiation;
struct Interaction;
struct Force;
struct QuinticSpline;

struct ParticleManager
{
  double smoothinglength;
  double cell_size;
  int cell_ratio;
  int x_clls;
  int y_clls;
  struct List ***cell_lists;
  struct List *NNP_list;
};

int manager_update_list(struct ParticleManager*);
void manager_build_particles(struct ParticleManager*, struct Material*, struct List*, struct Initiation*);
int manager_build_nnp(struct ParticleManager*, double[2]);
int manager_build_interaction(struct ParticleManager*,
			      struct IList*, struct List*, struct Force**, struct QuinticSpline*);
struct ParticleManager* manager_ini(struct Initiation*);
#ifdef __cplusplus
}
#endif
