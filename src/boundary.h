struct Initiation;
struct ParticleManager;
struct Boundary
{
    double box_size[2];
    int x_clls, y_clls;
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    List *b;
    Boundary(Initiation*, List***);
    ~Boundary();
};

int boundary_condition(Boundary*, List***);
int boundary_build(Boundary*, List***, Material*);
int boundary_check(Boundary*, List*);
int boundary_w(Boundary*, Particle*);
int boundary_e(Boundary*, Particle*);
int boundary_s(Boundary*, Particle*);
int boundary_n(Boundary*, Particle*);
int boundary_sw(Boundary*, Particle*);
int boundary_se(Boundary*, Particle*);
int boundary_nw(Boundary*, Particle*);
int boundary_ne(Boundary*, Particle*);
