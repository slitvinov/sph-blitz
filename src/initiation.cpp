/// \file initiation.cpp
/// \author author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      initialize the progam
//		initiation.cpp
//----------------------------------------------------------------------------------------
#include <fstream>
#include <glog/logging.h>
#include <boost/foreach.hpp>

// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "Kernel/kernel.h"
#include "initiation.h"
//----------------------------------------------------------------------------------------
//							constructor 
//----------------------------------------------------------------------------------------
Initiation::Initiation(const std::string& project_name, const std::string& ivs_file_name) {
  LOG(INFO) << "Run constructor of Initiation class";
  
  //the project name
  Project_name = project_name;
  //the ivs file name
  Ivs_file_name=ivs_file_name;
  
  //the input file name
  const std::string inputfile = Project_name + ".tcl";
  std::ifstream tclfilename;
  tclfilename.open (inputfile.c_str());
  if (!tclfilename.is_open()) {
    LOG(ERROR) << " cannot open project file: " << inputfile;
    exit(EXIT_FAILURE);
  }

  // get environment variable and run it as a TCL command
  // to use it run
  // SPH_TCL="set isim 10" ./sph <project>
  const std::string sph_tcl = CharPtrToStdString(std::getenv("SPH_TCL"));
  if (sph_tcl.size() > 0) {
    interp.eval(sph_tcl);
  }
  
  interp.eval(tclfilename);
  ///<li>reading key words and configuration data from configuration file and assign them to the appropriate variable
  disable_boundary  = interp.getval("DISABLE_BOUNDARY");
  initial_condition = interp.getval("INITIAL_CONDITION");
  assert( (initial_condition == 0) || (initial_condition == 1));
  simu_mode = interp.getval("SIMULATION_MODE");
  // assert(simu_mode==1||simu_mode==2); (already tested in sph.cpp)
  density_mode = interp.getval("DENSITY_MODE");
  assert(density_mode == 1 || density_mode == 2);
  kernel_type = static_cast<std::string>(interp.getval("KERNEL_TYPE"));
  // for harmonic kernel we need a parameter n
  if (kernel_type == "Harmonic") {
    harmonic_n = interp.getval("harmonic_n");
  }

  if (interp.exist("OUTDIR")) {
    outdir = static_cast<std::string>(interp.getval("OUTDIR"));
  } else {
    outdir = "outdata";
  }
  
  /// if gas dynamics
  if (simu_mode == 2) {
    //further markers exclusively applied to gas dynamics
    integration_scheme = interp.getval("INTEGRATION_SCHEME");//(already tested in sph.cpp)
    //assert(integration_scheme == 1 || integration_scheme == 2);
    splash_optimized_output = interp.getval("SPLASH_OPTIMIZED_OUTPUT");
    assert(splash_optimized_output==0||splash_optimized_output==1);
    /// read parameters of artificial viscosity 
    alpha_artVis = interp.getval("alpha_artVis");
    beta_artVis = interp.getval("beta_artVis");
    epsilon_artVis = interp.getval("epsilon_artVis");
    //read physical and artificial viscosity markers
    physical_viscosity_marker=interp.getval("PHYSICAL_VISCOSITY_MARKER");
    assert(physical_viscosity_marker==0||physical_viscosity_marker==1);
    artificial_viscosity_marker=interp.getval("ARTIFICIAL_VISCOSITY_MARKER");
    assert(artificial_viscosity_marker==0||artificial_viscosity_marker==1||artificial_viscosity_marker==2);
    autom_dt_control=interp.getval("AUTOMATIC_DT_CONTROL_MARKER");
    assert(autom_dt_control==0||autom_dt_control==1);
    if(autom_dt_control==0)//if dt_auto turned out, take man. choosen dt
      manually_choosen_dt = interp.getval("manually_choosen_dt");
  }
  x_cells = interp.getat("CELLS", 0);
  assert(x_cells > 0);
  y_cells = interp.getat ("CELLS", 1);
  assert(y_cells > 0);
  cell_size = interp.getval("CELL_SIZE");
  assert(cell_size>0.0);
  supportlength = interp.getval("SUPPORT_LENGTH");
  assert(supportlength > 0.0);
  hdelta = interp.getval("CELL_RATIO");
  assert(hdelta > 0.0);

  number_of_materials = interp.getval("NUMBER_OF_MATERIALS");
  
  if (interp.getndim("G_FORCE") == 1) {
    /// one dimensional vector make it for all materials
    LOG(INFO) << "G_FORCE is one dimensional";
    g_force.resize(number_of_materials, 2);
    for (int material_no=0; material_no<number_of_materials; material_no++) {
      g_force(material_no, 0) = interp.getat("G_FORCE", 0);
      g_force(material_no, 1) = interp.getat("G_FORCE", 1);
    }
  } else {
    g_force.resize(number_of_materials, 2);
    LOG(INFO) << "G_FORCE is two dimensional";
    for (int material_no=0; material_no<number_of_materials; material_no++) {
      g_force(material_no, 0) = interp.getat("G_FORCE", material_no, 0);
      g_force(material_no, 1) = interp.getat("G_FORCE", material_no, 1);
      LOG(INFO) << "g_force(" << material_no << ",0) = " << g_force(material_no, 0);
      LOG(INFO) << "g_force(" << material_no << ",1) = " << g_force(material_no, 1);
    }
  }
  assert(number_of_materials > 0);
  
  Start_time = interp.getval("Start_time");
  End_time = interp.getval("End_time");
  D_time = interp.getval("D_time");
  // can be zero for debugging
  assert(D_time>0.0);
  assert(End_time >= Start_time);
  
  if (initial_condition == 0) {
    //rho0 = interp.getval("rho0");
    //p0 = interp.getval("p0");
    T0 = interp.getval("T0");
    U0[0] = interp.getat("U0", 0);
    U0[1] = interp.getat("U0", 1);
  }
  
  ///<li>create outdata directory
  const std::string syscommand = "mkdir -p " + outdir;
  const int sys_return = system(syscommand.c_str());
  if (sys_return) {
    LOG(ERROR) << "system command: " << syscommand << " faild" << inputfile;
    exit(EXIT_FAILURE);
  }
  
  ///<li>process the data <b>!!!Question!!!</b>
  box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
  delta = cell_size/hdelta;///(line 104) this is only 
  /// true if h=cell_size (which is not necessarily given, as h, cell_size can be initiated independently in configuration file)
  
  ///<li>output information to screen
  show_information();
  LOG(INFO) << "Initiation object is created";
}



//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information() const 
{
  ///- output general information on screen
  LOG(INFO)<<"The simulation mode is"<<simu_mode<<"! (1=liquids, 2=gas dynamics)\n";
  LOG(INFO)<<"Output directory is "<< outdir;
  LOG(INFO)<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
  LOG(INFO)<<"The computational domain size is  "<<box_size[0]<<" micrometers x "<<box_size[1]<<" micrometers\n";
  LOG(INFO)<<"The cell size is "<<cell_size<<" micrometers \n";
  LOG(INFO)<<"The support length is "<<supportlength<<" micrometers \n";
  LOG(INFO)<<"The cell matrix size is "<<x_cells<<" x "<<y_cells<<"\n";
  LOG(INFO)<<"The ratio between cell size and initial particle width is "<<hdelta<<"\n";
  LOG(INFO)<<"The initial particle width is "<<delta<<" micrometers\n";
	///- output the timing information on screen
  LOG(INFO)<<"Ending time is "<<End_time<<" \n";
  LOG(INFO)<<"Output time interval is "<<D_time<<" \n";
  
  LOG(INFO)<<"initial_condition "<< initial_condition <<" \n";
  LOG(INFO)<<" simu_mode "<< simu_mode <<" \n";

  ///- output iniformation on initialization mode (.cfg file or .rst file)
  //Initialize the initial conditions from .cfg file
  if (initial_condition==0) {
    LOG(INFO)<<"The initial flow speed is "<<U0[0]<<" m/s x "<<U0[1]<<" m/s\n";
  }
	
  //Initialize the initial conditions from .rst file
  if (initial_condition == 1)
    LOG(INFO)<<"Read the initial conditions from separated restat file "
	<<Project_name<<".rst \n";
}

//----------------------------------------------------------------------------------------
//					predict the particle volume and mass
//----------------------------------------------------------------------------------------
void Initiation::VolumeMass(Hydrodynamics &hydro, ParticleManager &particles, 
			    spKernel weight_function)
{
  LOG(INFO)<<"Initiation::VolumeMass starts";
  ///mass initiation is different from 1DSPH code: 
  ///here: mass is calculated by summing up the kernel function contributions for easch particle, which gives a kind of the inverse volume taken by each particle (not perfectly true at the discontinuity). together with rho (from initialization) a mass for each particle can be obtained.
  ///within the discontinuity zone, this mass varies because of the smoothing effect of the kernel summation.
  ///The mass for each particle  stays constant during the simuation.

  /// <ul><li>iterate particles on the particle list
  BOOST_FOREACH(spParticle prtl_org, hydro.particle_list) {
    /// <ul><li> pick an origin particle
    assert(prtl_org != NULL);
    const std::list<spParticle> NNP_list = particles.BuildNNP(prtl_org->R);

    /// size of the list can be zero in some circumstances
    /// but in 1D (2D) shock it is not expected
    assert(NNP_list.size() > 0);
    double reciprocV = 0.0; 
    /// <li>iterate this Nearest Neighbor spParticle list
    BOOST_FOREACH(const spParticle prtl_dest, NNP_list) {
      /// <li> calculate distance (origin<-> neighbor)
      const double dstc = v_distance(prtl_org->R, prtl_dest->R);
      /// <li> calculate weight function for given distance (w=0, if dist>supportlengtg) an summ it up </ul> 
      reciprocV += weight_function->w(dstc);
    }
    /// <li> calculate volume as reciprocal value of weight function
    reciprocV = 1.0/reciprocV;
    /// <li> save volume and mass in the respective particle list node (whih is each a spParticle object with all the particle properties) 
    prtl_org->V = reciprocV;
    prtl_org->m = prtl_org->rho*reciprocV;
    LOG_EVERY_N(INFO, 1000) <<std::setprecision(10)<< "prtl ID"<<prtl_org->ID<<"prtl m  = " << prtl_org->m;
  }
  LOG(INFO)<<"Initiation::VolumeMass ends";
}

int Initiation::getParticleMaterialNo(const Vec2d& position) {
  // if no proc in the tcl file set default material number 
  if (!interp.isproc("getmatNo") ) {
    const int default_materail_number = 1;
    LOG(INFO) << "return default material number" ;
    return default_materail_number;
  } else {
    // set position of the particle and call the function
    interp.setdouble("x", position[0]);
    interp.setdouble("y", position[1]);
    interp.evalproc("getmatNo");
    const int no = interp.getval("no");
    if (no>number_of_materials - 1) {
      LOG(ERROR) << "number of material is " << no << '\n' << 
	"maximum material number is " << number_of_materials - 1;
      std::exit(EXIT_FAILURE);
    } 
    if (no < 0) {
      LOG(ERROR) << "number of material is " << no << '\n';
      std::exit(EXIT_FAILURE);
    }
    LOG(INFO) << "for particle " << position << " return material number " << no ;
    return no;
  } 
}

const char *CharPtrToStdString(const char *str)
{
    return (str) ? str : "";
} 
