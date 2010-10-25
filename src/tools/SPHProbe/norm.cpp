#include <cstdlib>
#include <string>
#include <boost/program_options.hpp>
#include <glog/logging.h>
#include <gsl/gsl_spline.h>
#include "src/tools/SPHProbe/utils.h"

namespace po = boost::program_options;

int main(int ac, char* av[]) {
  google::InitGoogleLogging(av[0]);

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "print help message")
    ("c1", po::value<std::string>(), "a file with the first particle configuration")
    ("c2", po::value<std::string>(), "a file with the second particle configuration")
    ("norm,n", po::value<std::string>(), "norm type (L1, L2, Li)")
    ;
  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  std::string c1;
  if (vm.count("c1")) {
    c1 = vm["c1"].as<std::string>();
  } else {
    LOG(ERROR) << "line configuration must be given (--c1 parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "c1 = " << c1;

  std::string c2;
  if (vm.count("c2")) {
    c2 = vm["c2"].as<std::string>();
  } else {
    LOG(ERROR) << "line configuration must be given (--c2 parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "c2 = " << c2;

  std::string norm_type;
  if (vm.count("norm")) {
    norm_type = vm["norm"].as<std::string>();
  } else {
    norm_type = "L1";
  }
  LOG(INFO) << "norm = " << norm_type;

  const blast::matrix<double> data1 = readMatrix(c1);
  const blast::matrix<double> data2 = readMatrix(c2);

  gsl_interp_accel *acc 
      = gsl_interp_accel_alloc ();
  gsl_spline *spline 
      = gsl_spline_alloc (gsl_interp_cspline, data2.size1());


  gsl_spline_free (spline);
  gsl_interp_accel_free (acc);


  LOG(INFO) << "norm starts";
  return EXIT_SUCCESS;
}
