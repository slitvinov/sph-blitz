struct Wiener {
    long int idum, idum2, iy, iseed;
    long int iv[32];
    double trace_d;
    double Random_p, Random_v;
    Wiener();
    void get_wiener_Espanol(double sqrtdt);
    void Ranils();
    double Ranuls();
    void Gaussian(double *y1, double *y2);
};
