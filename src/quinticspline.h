struct QuinticSpline {
    double reciprocH;
    double factorW;
    double factorGradW;
    double smoothingLength;
};

int quinticspline_ini(double smoothingLength, struct QuinticSpline *);
double w(struct QuinticSpline *, double);
double F(struct QuinticSpline *, double);
