#ifdef __cplusplus
extern "C" {
#endif
struct QuinticSpline {
    double reciprocH;
    double factorW;
    double factorGradW;
    double factorLapW;
    double smoothingLength;
};

int quinticspline_ini(double smoothingLength, struct QuinticSpline*);
double w(struct QuinticSpline*, double);
double F(struct QuinticSpline*, double);
double LapW(struct QuinticSpline*, double);
#ifdef __cplusplus
}
#endif
