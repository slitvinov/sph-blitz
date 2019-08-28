struct Ini;
struct Material;
struct Boundary;
struct List;

struct Boundary *boundary_ini(struct Ini *);
int boundary_fin(struct Boundary *);
int boundary_condition(struct Boundary *, struct List ***);
int boundary_build(struct Boundary *, struct List ***, struct Material *);
int boundary_check(struct Boundary *, struct List *);
struct List *boundary_list(struct Boundary *);
