class Particle;
class Boundary;
class Hydrodynamics;
class Initiation;
class Interaction;
class Force;

class ParticleManager
{
  char Project_name[FILENAME_MAX];
  int number_of_materials;
  double smoothinglength;
  double smoothinglengthsquare;
  double cll_sz;
  double box_size[2];
  int initial_condition;
  double delta;
  int hdelta;
  double U0[2];
  double rho0;
  double p0;
  double T0;
  void BuildWallParticles(Hydrodynamics&, Boundary&);
public:
  int x_clls;
  int y_clls;
  List **cell_lists;
  List NNP_list;
  explicit ParticleManager(Initiation*);
  void BuildRealParticles(Hydrodynamics&, Initiation*);
  void UpdateCellLinkedLists();
  void BuildNNP(double[2]);
  void BuildNNP_MLSMapping(double[2]);
  void BuildInteraction(IList&, List&, Force**, QuinticSpline&);
};
