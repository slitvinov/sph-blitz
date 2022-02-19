struct Ini;
struct Material;
struct List;

struct Ini *boundary_ini(struct Ini *);
int boundary_fin(struct Ini *);
int boundary_condition(struct Ini *, struct List ***);
int boundary_build(struct Ini *, struct List ***, struct Material *);
int boundary_check(struct Ini *, struct List *);
struct List *boundary_list(struct Ini *);
