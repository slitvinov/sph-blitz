class QuinticSpline
{
public:
    explicit QuinticSpline(double smoothingLength);
    double w(double distance);
    double F(double distance);
    double LapW(double distance);
private:
    double reciprocH;
    double factorW;
    double factorGradW;
    double factorLapW;
    double smoothingLength;
};
