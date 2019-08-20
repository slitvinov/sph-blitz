struct Wiener {
    Wiener();
    double Random_p, Random_v;
    void get_wiener(double sqrtdt);
private:
    long int idum, idum2, iy, iseed;
    long int iv[32];
    void Ranils();
    double Ranuls();
    void Gaussian(double *y1, double *y2);
};
