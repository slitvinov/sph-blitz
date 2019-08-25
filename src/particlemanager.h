class Particle;
class Boundary;
class Hydrodynamics;
class Initiation;
class Interaction;
class Force;
class QuinticSpline;

struct ParticleManager
{
  double smoothinglength;
  double cell_size;
  int cell_ratio;
  int x_clls;
  int y_clls;
  List ***cell_lists;
  List *NNP_list;
  explicit ParticleManager(Initiation*);
  ~ParticleManager();
  void BuildInteraction(IList*, List*, Force**, QuinticSpline*);
};

int manager_update_list(struct ParticleManager*);
void manager_build_particles(struct ParticleManager*, struct Material*, struct List*, struct Initiation*);
int manager_build_nnp(struct ParticleManager*, double[2]);
