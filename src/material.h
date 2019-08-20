/// \file material.h 
/// \brief Material 

/// Material 
class Material {

	///total number of materials
	static int number_of_materials;
	static double smoothinglength;///<smoothinglenth
	static double delta;

public:
	
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

	///constructor
	Material();
	///constructor
	explicit Material(Initiation &ini);
	///constructor
	Material(char *material_name, Initiation &ini);
	///show properties
	void show_properties();

	///obtain parameter b0
	void Get_b0(double sound);
	
	///get pressure
	double get_p(double rho);
	///get rho from pressure
	double get_rho(double p);
	///get sound speed
	double get_Cs(double p, double rho);

};

