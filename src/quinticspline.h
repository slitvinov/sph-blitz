class QuinticSpline
{
public:
    explicit QuinticSpline(double smoothingLength);
    double reciprocH;
    double factorW;
    double factorGradW;
    double factorLapW;
    double smoothingLength;
};

double w(QuinticSpline *q, double distance);
double F(QuinticSpline *q, double distance);
double LapW(QuinticSpline *q, double distance);
