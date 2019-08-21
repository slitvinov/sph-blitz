#ifdef __cplusplus
extern "C" {
#endif
struct Material {
	///material name string
	char material_name[FILENAME_MAX];
	int number; ///<the material NO.

	///\brief material type
	///
	///- 0: solid;
	///-  1: liquid;
	///-  2: gas
	int material_type;

	double eta;///<viscosity
	double zeta;///<heat conduction rate
	double gamma; ///<???

	double nu; ///<kinetice viscosity
	double b0;///<reference pressure
	double rho0;///<reference density
	double a0; ///<reference <b>sound speed??? was not commented</b>
};

void Set_nu(struct Material*);
void Set_b0(struct Material*, double sound);
double get_p(struct Material*, double rho);
double get_rho(struct Material*, double p);
double get_Cs(struct Material*, double p, double rho);
#ifdef __cplusplus
}
#endif



