#include <iostream>
#include <cstdlib>
#include <boost/program_options.hpp>
#include <glog/logging.h>
namespace po = boost::program_options;

int main(int ac, char* av[]) {
  google::InitGoogleLogging(av[0]);
  LOG(INFO) << "sphprobe starts";
  /// read parameters of the kernel
  ///    cutoff, kernell type
  ///    times t1, t2
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "print help message")
    ("t1", po::value<double>(), "time for the first particle configuration")
    ("t2", po::value<double>(), "time for the second particle configuration")
    ("tout", po::value<double>(), "time for the interpolation")
    ("c1", po::value<std::string>(), "a file with the first particle configuration")
    ("c2", po::value<std::string>(), "a file with the second particle configuration")
    ("probe,p", po::value<std::string>(), "a probe file (format: x, y, rho, m, field1, field2, ...)")
    ("ktype", po::value<std::string>(), "Kernel type (default: QuinticSpline)")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return EXIT_SUCCESS;
  }
  
  double t1;
  if (vm.count("t1")) {
    t1 = vm["t1"].as<double>();
  } else {
    t1 = 0.0;
  }
  LOG(INFO) << "t1 = " << t1;

  double t2;
  if (vm.count("t2")) {
    t2 = vm["t2"].as<double>();
  } else {
    t2 = 1.0;
  }
  LOG(INFO) << "t2 = " << t2;

  double tout;
  if (vm.count("tout")) {
    tout = vm["tout"].as<double>();
  } else {
    tout = t1;
    LOG(INFO) << "default value for the tout is used";
  }
  LOG(INFO) << "tout = " << tout;


  std::string kernel_type;
  if (vm.count("ktype")) {
    kernel_type = vm["ktype"].as<std::string>();
  } else {
    kernel_type = "QuinticSpline";
  }
  LOG(INFO) << "kernel_type = " << kernel_type;

  std::string c1;
  if (vm.count("c1")) {
    c1 = vm["c1"].as<std::string>();
  } else {
    LOG(ERROR) << "particle configuration must be given (--c1 parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "c1 = " << c1;

  std::string c2;
  if (vm.count("c2")) {
    c2= vm["c2"].as<std::string>();
  } else {
    LOG(ERROR) << "particle configuration must be given (--c2 parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "c2 = " << c2;

  std::string probe_file;
  if (vm.count("probe")) {
    probe_file= vm["probe"].as<std::string>();
  } else {
    LOG(ERROR) << "probe file be given (--probe parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "probe_file = " << probe_file;


  
  /// read input files
  /// create a cell structure  (no boundary)
  /// project to the grid
  /// approximate in time
  /// output 
  return EXIT_SUCCESS;
}
