class QuinticSpline
{
public:
    explicit QuinticSpline(const double smoothingLength);
    double w(const double distance) const;
    double F(const double distance) const;
    double LapW(const double distance) const;
private:
    double norm;
    double reciprocH;
    double factorW;
    double factorGradW;
    double factorLapW;
    double smoothingLength;
};
