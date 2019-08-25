class Particle;
class Boundary;
class Hydrodynamics;
class Initiation;
class Interaction;
class Force;
class QuinticSpline;

class ParticleManager
{
  double smoothinglength;
  double cell_size;
  int cell_ratio;
public:
  int x_clls;
  int y_clls;
  List ***cell_lists;
  List *NNP_list;
  explicit ParticleManager(Initiation*);
  ~ParticleManager();
  void BuildRealParticles(Material*, List*, Initiation*);
  void UpdateCellLinkedLists();
  void BuildNNP(double[2]);
  void BuildNNP_MLSMapping(double[2]);
  void BuildInteraction(IList*, List*, Force**, QuinticSpline*);
};
