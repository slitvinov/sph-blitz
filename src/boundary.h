#ifdef __cplusplus
extern "C" {
#endif
struct Initiation;
struct ParticleManager;
struct Boundary
{
    double box_size[2];
    int x_clls;
    int y_clls;
    int xBl;
    int xBr;
    int yBd;
    int yBu;
    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    struct List *b;
};

struct Boundary *boundary_ini(struct Initiation*);
int boundary_fin(struct Boundary*);
int boundary_condition(struct Boundary*, struct List***);
int boundary_build(struct Boundary*, struct List***, struct Material*);
int boundary_check(struct Boundary*, struct List*);
int boundary_w(struct Boundary*, struct Particle*);
int boundary_e(struct Boundary*, struct Particle*);
int boundary_s(struct Boundary*, struct Particle*);
int boundary_n(struct Boundary*, struct Particle*);
int boundary_sw(struct Boundary*, struct Particle*);
int boundary_se(struct Boundary*, struct Particle*);
int boundary_nw(struct Boundary*, struct Particle*);
int boundary_ne(struct Boundary*, struct Particle*);
#ifdef __cplusplus
}
#endif
