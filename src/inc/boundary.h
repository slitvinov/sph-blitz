struct Initiation;
struct Material;
struct Boundary {
    double box_size[2];
    double UxBl[2];
    double UxBr[2];
    double UyBd[2];
    double UyBu[2];
    int xBl;
    int xBr;
    int x_clls;
    int yBd;
    int yBu;
    int y_clls;
    struct List *b;
};

struct Boundary *boundary_ini(struct Initiation *);
int boundary_fin(struct Boundary *);
int boundary_condition(struct Boundary *, struct List ***);
int boundary_build(struct Boundary *, struct List ***, struct Material *);
int boundary_check(struct Boundary *, struct List *);
