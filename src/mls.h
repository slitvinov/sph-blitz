struct Initiation;
struct Particle;
struct QuinticSpline;
struct MLS {
    int N;
    int MLS_MAX;
    double A[3*3], *B[3];
    double p[3], *pi[3];
    double *Wi;
    double *phi;
};

int mls_solve(struct MLS*, int order);
int mls_map(struct MLS*, double point[2], List*, QuinticSpline*, int order);
int mls_fin(struct MLS*);
struct MLS* mls_ini(int MLS_MAX);
