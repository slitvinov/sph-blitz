struct Material {
    char material_name[FILENAME_MAX];
    int number;
    int material_type;
    double eta;
    double zeta;
    double gamma;
    double nu;
    double b0;
    double rho0;
    double a0;
};

void Set_b0(struct Material *, double sound);
double get_p(struct Material *, double rho);
double get_Cs(struct Material *, double p, double rho);
