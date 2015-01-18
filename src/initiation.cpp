/// \file initiation.cpp
/// \author author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
/// \author changes by: Sergey Litvinov <slitvinov@gmail.com>
//----------------------------------------------------------------------------------------
//      initialize the progam
//		initiation.cpp
//----------------------------------------------------------------------------------------
#include <fstream>
#include <dlfcn.h>
#include <glog/logging.h>
#include <boost/foreach.hpp>
#include <boost/smart_ptr/make_shared.hpp>
// ***** localincludes *****
#include "hydrodynamics.h"
#include "particlemanager.h"
#include "Kernel/kernel.h"

#include "initiation.h"
#include "ParticleContext/solidcontext.h"
#include "ParticleContext/nocontext.h"
#include "ParticleContext/rotcontext.h"

//----------------------------------------------------------------------------------------
//							constructor 
//----------------------------------------------------------------------------------------
Initiation::Initiation(const std::string& project_name, const std::string& ivs_file_name):
  Project_Name(project_name), Ivs_File_Name(ivs_file_name), interp(boost::make_shared<Tcl::interpreter>()),
  timer(boost::make_shared<Timer>())
{
  LOG(INFO) << "Run constructor of Initiation class";
  //the input file name
  const std::string inputfile = Project_Name + ".tcl";
  std::ifstream tclfilename;
  tclfilename.open(inputfile.c_str());
  if (!tclfilename.is_open()) {
    LOG(ERROR) << " cannot open project file: " << inputfile;
    exit(EXIT_FAILURE);
  }
  // get environment variable and run it as a TCL command
  // to use it run
  // SPH_TCL="set isim 10" ./sph <project>
  const std::string sph_tcl = CharPtrToStdString(std::getenv("SPH_TCL"));
  if (sph_tcl.size() > 0) {
    LOG(INFO) << "Find this SPH_TCL: " << sph_tcl;
    interp->eval(sph_tcl);
  }
  interp->eval(tclfilename);
  ///<li>reading key words and configuration data from configuration 
  ///file and assign them to the appropriate variable
  disable_boundary  = interp->getval("DISABLE_BOUNDARY");
  initial_condition = interp->getval("INITIAL_CONDITION");
  assert( (initial_condition == 0) || (initial_condition == 1));
  if (!interp->exist("initial_perturb")) {
    LOG(INFO) << "initial_perturb is not found, assume 0";
    initial_perturb = 0.0;
  } else {
    initial_perturb = interp->getval("initial_perturb");
    LOG(INFO) << "found initial_perturb: " << initial_perturb;
    assert( (initial_perturb >= 0) && (initial_perturb < 0.5) );
  }
  simu_mode = interp->getval("SIMULATION_MODE");
  assert(simu_mode==1||simu_mode==2||simu_mode==3||simu_mode==4);

  // if S1 scheme read the number of subiterations
  if (simu_mode == 4) {
    s1_niter = interp->getval("s1_niter");
    assert(s1_niter > 0);
    LOG(INFO) << "s1_niter: " << s1_niter;
  }
  density_mode = interp->getval("DENSITY_MODE");
  assert(density_mode == 1 || density_mode == 2);
  kernel_type = static_cast<std::string>(interp->getval("KERNEL_TYPE"));
  if (interp->exist("OutputType")) {
      OutputType = static_cast<std::string>(interp->getval("OutputType"));
  } else {
    OutputType = "Tecplot";
  }
  LOG(INFO) << "read OutputType: " << OutputType;
     
  // for harmonic kernel we need a parameter n
  if (kernel_type == "Harmonic") {
    harmonic_n = interp->getval("harmonic_n");
  }
  
  if (interp->exist("OUTDIR")) {
    outdir = static_cast<std::string>(interp->getval("OUTDIR"));
  } else {
    outdir = "outdata";
  }
  ///<li>create outdata directory
  const std::string syscommand = "mkdir -p " + outdir;
  const int sys_return = system(syscommand.c_str());
  if (sys_return) {
    LOG(ERROR) << "system command: " << syscommand << " faild" << inputfile;
    exit(EXIT_FAILURE);
  }
  // output directory created,  try to dump a config file into it
  const std::string dfile = outdir + "/config.tcl";
  interp->dump(dfile);
  LOG(INFO) << "configuration dumpt in " <<  dfile;
  
  /// if gas dynamics
  if (simu_mode == 2) {
    //further markers exclusively applied to gas dynamics
    integration_scheme = interp->getval("INTEGRATION_SCHEME");//(already tested in sph.cpp)
    //assert(integration_scheme == 1 || integration_scheme == 2);
    splash_optimized_output = interp->getval("SPLASH_OPTIMIZED_OUTPUT");
    assert(splash_optimized_output==0||splash_optimized_output==1);
    /// read parameters of artificial viscosity 
    alpha_artVis = interp->getval("alpha_artVis");
    beta_artVis = interp->getval("beta_artVis");
    epsilon_artVis = interp->getval("epsilon_artVis");
    //read physical and artificial viscosity markers
    physical_viscosity_marker=interp->getval("PHYSICAL_VISCOSITY_MARKER");
    assert(physical_viscosity_marker==0||physical_viscosity_marker==1);
    artificial_viscosity_marker=interp->getval("ARTIFICIAL_VISCOSITY_MARKER");
    assert(artificial_viscosity_marker==0||artificial_viscosity_marker==1||artificial_viscosity_marker==2);
    autom_dt_control=interp->getval("AUTOMATIC_DT_CONTROL_MARKER");
    assert(autom_dt_control==0||autom_dt_control==1);
    if (autom_dt_control==0)//if dt_auto turned out, take man. choosen dt
      manually_choosen_dt = interp->getval("manually_choosen_dt");
  }
  x_cells = interp->getat("CELLS", 0);
  assert(x_cells > 0);
  y_cells = interp->getat ("CELLS", 1);
  assert(y_cells > 0);
  cell_size = interp->getval("CELL_SIZE");
  assert(cell_size>0.0);
  supportlength = interp->getval("SUPPORT_LENGTH");
  assert(supportlength > 0.0);
  hdelta = interp->getval("CELL_RATIO");
  assert(hdelta > 0);
  number_of_materials = interp->getval("NUMBER_OF_MATERIALS");
  assert(number_of_materials > 0);
  DefineBodyForce();
  
  Start_time = interp->getval("Start_time");
  timer->updateTime(Start_time);
  End_time = interp->getval("End_time");
  
  End_time = interp->getval("End_time");
  
  // read hook time 
  if (!interp->exist("Hook_time")) {
    Hook_time = 2*End_time;
  } else {
    Hook_time = interp->getval("Hook_time");
    // 
    if (!interp->isproc("filter_hook")) {
      LOG(ERROR) << "Cannot find filter proc: filter_hook in the configuration file";
      exit(EXIT_FAILURE);
    }

    if (!interp->isproc("after_hook")) {
      LOG(ERROR) << "Cannot find filter proc: after_hook in the configuration file";
      exit(EXIT_FAILURE);
    }
  }

  D_time = interp->getval("D_time");
  // can be zero for debugging
  assert(D_time>0.0);
  assert(End_time >= Start_time);
  if (!interp->exist("output_file_format_factor")) {
    output_file_format_factor = 1e6;
  } else {
    output_file_format_factor = interp->getval("output_file_format_factor");
  }
  
  if (initial_condition == 0) {
    //rho0 = interp->getval("rho0");
    //p0 = interp->getval("p0");
    T0 = interp->getval("T0");
    U0[0] = interp->getat("U0", 0);
    U0[1] = interp->getat("U0", 1);
  }

  /// Initialize Context 
  if (interp->isproc("getSolid")) {
    LOG(INFO) << "Found getSolid: some particles are solid";
    context = boost::make_shared<SolidContext>(*this);
  } else if (interp->isproc("getRot")) {
    LOG(INFO) << "Found getRot: some particles are rotating";
    context = boost::make_shared<RotContext>(*this);
    timer->addTimeObserver(context);
  } else {
    LOG(INFO) << "No getSolid: assuming NoContext (all particles are normal)" ;
    context = boost::make_shared<NoContext>();
  }
  
  if (!interp->exist("movePartilces")) {
    movePartilces = true;
  } else {
    movePartilces = interp->getval("movePartilces");
  }
  
  ///<li>process the data <b>!!!Question!!!</b>
  box_size[0] = x_cells*cell_size; box_size[1] = y_cells*cell_size;
  LOG(INFO) << "Domain size: " << box_size;
  delta = cell_size/hdelta;///(line 104) this is only 
  /// true if h=cell_size (which is not necessarily given, as h, cell_size can be initiated independently in configuration file)
  
  ///<li>output information to screen
  show_information();
  LOG(INFO) << "Initiation object is created";
}

//----------------------------------------------------------------------------------------
//					show information to screen
//----------------------------------------------------------------------------------------
void Initiation::show_information() const  {
  ///- output general information on screen
  LOG(INFO)<<"The simulation mode is"<<simu_mode<<"! (1=liquids, 2=gas dynamics)\n";
  LOG(INFO)<<"Output directory is "<< outdir;
  LOG(INFO)<<"The number of materials in the simulation is  "<<number_of_materials<<"\n";
  LOG(INFO)<<"The computational domain size is  " << box_size;
  LOG(INFO)<<"The cell size is "<<cell_size;
  LOG(INFO)<<"The support length is "<<supportlength;
  LOG(INFO)<<"The cell matrix size is "<<x_cells<<" x "<<y_cells<<"\n";
  LOG(INFO)<<"The ratio between cell size and initial particle width is "<<hdelta<<"\n";
  LOG(INFO)<<"The initial particle width is "<<delta;
  LOG(INFO)<<"Perturbing initial particles (fraction of delta)"<< initial_perturb;
	///- output the timing information on screen
  LOG(INFO)<<"Ending time is "<<End_time<<" \n";
  LOG(INFO)<<"Output time interval is "<<D_time<<" \n";
  LOG(INFO)<<"Hook time is "<< Hook_time <<" \n";
  LOG(INFO) << "Output format factor is " << output_file_format_factor << '\n';
  LOG(INFO)<<"initial_condition "<< initial_condition <<" \n";
  LOG(INFO)<<"movePartilces is "<< movePartilces << '\n';
  LOG(INFO)<<" simu_mode "<< simu_mode <<" \n";
  ///- output iniformation on initialization mode (.cfg file or .rst file)
  //Initialize the initial conditions from .cfg file
  if (initial_condition==0) {
    LOG(INFO)<<"The initial flow speed is "<< U0;
  }
  //Initialize the initial conditions from .rst file
  if (initial_condition == 1) {
    LOG(INFO)<<"Read the initial conditions from separated restat file "
	     <<Project_Name<<".rst \n";
  }
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
    double revPartilceVolume = 0.0; 
    /// <li>iterate this Nearest Neighbor spParticle list
    BOOST_FOREACH(const spParticle prtl_dest, NNP_list) {
      /// <li> calculate distance (origin<-> neighbor)
      const double dstc = v_distance(prtl_org->R, prtl_dest->R);
      /// <li> calculate weight function for given distance (w=0, if dist>supportlengtg) an summ it up </ul> 
      revPartilceVolume += weight_function->w(dstc);
    }
    /// <li> calculate volume as reciprocal value of weight function
    assert(revPartilceVolume  > 0.0);
    /// <li> save volume and mass in the respective particle list node (whih is each a spParticle object with all the particle properties) 
    prtl_org->V = 1.0/revPartilceVolume;
    prtl_org->m = prtl_org->rho*prtl_org->V;
    assert(prtl_org->m > 0.0);
    LOG_EVERY_N(INFO, 1000) <<std::setprecision(10)
			    << "prtl ID"<<prtl_org->ID
			    <<"prtl m  = " << prtl_org->m;
  }
  LOG(INFO)<<"Initiation::VolumeMass ends";
}

void Initiation::DefineBodyForce() {
  /// try compiled body force 
  /// if I can find in config file the cBodyForce 
  /// variable I try to compile it into the shared library
  if (interp->exist("cBodyForce")) {
    useCompiledBodyForce = true;
    LOG(INFO) << "I find cBodyForce. Be hold";
    LOG(INFO) << "a path to plugin directory " << PLUGIN_PATH;
    LOG(INFO) << "try to source compile.tcl and compile the plugin";
    const std::string ctcl = std::string(PLUGIN_PATH) 
      + std::string("/compile.tcl");
    interp->eval("source " + ctcl);
    LOG(INFO) << "try to compile cBodyForce";
    const std::string pfile = std::string(PLUGIN_PATH) + std::string("/libforce.so");
    LOG(INFO) << "plugin file is " << pfile; 
    interp->eval("compile $cBodyForce " + pfile);
    externalFunHandle = dlopen(pfile.c_str(), RTLD_LAZY);
    if (!externalFunHandle) {
      LOG(ERROR) << "Cannot open library: " << dlerror();
      exit(EXIT_FAILURE);
    }
    bodyF = (TBodyF)dlsym(externalFunHandle, "bodyforce");
    if (!bodyF) {
      LOG(ERROR) << "Cannot load symbol 'bodyforce': " << dlerror();
      dlclose(externalFunHandle);
      exit(EXIT_FAILURE);
    }
    LOG(INFO) << "body force is loaded";
    assert(number_of_materials>0);
    g_force.resize(number_of_materials, 2);
    if (!interp->exist("G_REF")) {
      LOG(ERROR) << "I need G_REF: reference body force for time step estimation";
      exit(EXIT_FAILURE);
    }
    for (int material_no=0; material_no<number_of_materials; material_no++) {
      g_force(material_no, 0) = interp->getat("G_REF", 0);
      g_force(material_no, 1) = interp->getat("G_REF", 1);
    }
    /// read gravity vector for dt calculations
  } else {
    /// normal case no compiled body force
    LOG(INFO) << "I did not find cBodyForce. Use normal gravity force";
    useCompiledBodyForce = false;
    if (interp->getndim("G_FORCE") == 1) {
      /// one dimensional vector make it for all materials
      LOG(INFO) << "G_FORCE is one dimensional";
      g_force.resize(number_of_materials, 2);
      for (int material_no=0; material_no<number_of_materials; material_no++) {
	g_force(material_no, 0) = interp->getat("G_FORCE", 0);
	g_force(material_no, 1) = interp->getat("G_FORCE", 1);
      }
    } else {
      assert(number_of_materials > 0);
      g_force.resize(number_of_materials, 2);
      LOG(INFO) << "G_FORCE is two dimensional";
      for (int material_no=0; material_no<number_of_materials; material_no++) {
	g_force(material_no, 0) = interp->getat("G_FORCE", material_no, 0);
	g_force(material_no, 1) = interp->getat("G_FORCE", material_no, 1);
	LOG(INFO) << "g_force(" << material_no << ",0) = " << g_force(material_no, 0);
	LOG(INFO) << "g_force(" << material_no << ",1) = " << g_force(material_no, 1);
      }
    }
   }
}

// need a destructor to unload shared library
Initiation::~Initiation() {
  if (useCompiledBodyForce) {
    dlclose(externalFunHandle);
  }
}

const char *CharPtrToStdString(const char *str) {
    return (str) ? str : "";
} 
