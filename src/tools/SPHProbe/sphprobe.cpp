#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include <math.h>
#include "src/Utilities/utilities.h"
#include "src/Kernel/quinticspline.h"
#include "src/Kernel/cubicspline.h"
#include "src/Kernel/cubicspline1D.h"
#include "src/Kernel/bspline.h"
#include "src/Kernel/harmonic.h"
#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/assert.hpp>
#include <boost/program_options.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <glog/logging.h>
#include "src/vec2d.h"
namespace po = boost::program_options;
namespace blast = boost::numeric::ublas;

/// idexes of the particle configuration data
const int xidx = 0;
const int yidx = 1;
const int rhoidx = 2;
const int midx = 3;

/// number of required fields to do SPH approximation
/// x, y, rho, mass
const int nreqfields = 2;

std::vector<double> readRow(std::string row) {
  std::vector<double> retval;
  std::istringstream is(row);
  double num;
  while (is >> num) retval.push_back(num);
  return retval;
}

std::vector<std::vector<double> > readVector(std::istream &is) {
  std::string line;
  std::vector<std::vector<double> > retval;
  while (std::getline(is, line)) {
    retval.push_back(readRow(line));
  }
  return retval;
}

void printCellsOn(const blast::matrix<std::list<long> >& cell_lists, std::ostream& o) {
  for (int i=0; i< cell_lists.size1(); i++) {
    for (int j=0; j< cell_lists.size2(); j++) {
      o << "cell_lists(" << i << ", " << j << ") = " << cell_lists(i, j).size() << '\n';
    }
  }
}

void printMatirxOn(const blast::matrix<double>& mat, std::ostream& o) {
  for (int i=0; i< mat.size1(); i++) {
    for (int j=0; j< mat.size2(); j++) {
      o << mat(i, j) << ' ';
    }
    o << '\n';
  }
}

void printXYOut(const blast::matrix<double>& probe, const blast::matrix<double>& out, std::ostream& o) {
  for (int i=0; i< out.size1(); i++) {
    o << probe(i, xidx) << ' ' << probe(i, yidx) <<  ' ';
    for (int j=0; j< out.size2(); j++) {
      o << out(i, j) << ' ';
    }
    o << '\n';
  }
}

blast::matrix<double> nullMat(const int n, const int m) {
  blast::matrix<double> out(n, m) ;
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      out(i, j) = 0.0;
    }
  }
  return out;
}

double getMax(const blast::vector<double>& vec) {
  BOOST_ASSERT(vec.size() > 0);
  double max = vec(0); 
  for (int i=1; i<vec.size(); i++) {
    if (vec(i)>max) {
      max = vec(i);
    }
  }
  return max;
}

double getMin(const blast::vector<double>& vec) {
  BOOST_ASSERT(vec.size() > 0);
  double min = vec(0);
  for (int i=1; i<vec.size(); i++) {
    if (vec(i)<min) {
      min = vec(i);
    }
  }
  return min;
}

/// read matrix from the data file
blast::matrix<double> readMatrix(const std::string& filename ) {
  std::ifstream is(filename.c_str());
  if (!is.is_open()) {
    LOG(ERROR) << "cannot read file: " << filename;
    exit(EXIT_FAILURE);
  }
  // create a matrix to hold data from the file
  std::vector<std::vector<double> >  vec = readVector(is);
  is.close();
  const long n = vec.size();
  if (n==0) {
    LOG(ERROR) << "I did not find any points in the file: " << filename;
    exit(EXIT_FAILURE);
  }
  const long m = (*vec.begin()).size();
  BOOST_ASSERT(m>0);
  LOG(INFO) << "n = " << n;
  LOG(INFO) << "m = " << m;
  blast::matrix<double> data (n, m);
  for (long i=0; i<n; i++) {
    for (long j=0; j<m; j++) {
      data(i, j) = vec[i][j];
    }
  }
  LOG(INFO) << data;
  return data;
}

blast::matrix<double> getSPHApprox(const blast::matrix<double>& data, 
                                   const std::string& kernel_type,
                                   const double supportlength, 
				   const blast::matrix<double> probe) {
  /// find box size
  const Vec2d min_box(getMin( blast::matrix_column<const blast::matrix<double> >(data, xidx)), 
		      getMin( blast::matrix_column<const blast::matrix<double> >(data, yidx)));

  const Vec2d max_box(getMax( blast::matrix_column<const blast::matrix<double> >(data, xidx)), 
		      getMax( blast::matrix_column<const blast::matrix<double> >(data, yidx)));
  LOG(INFO) << "min_box = " << min_box;
  LOG(INFO) << "max_box = " << max_box;
  BOOST_ASSERT(max_box(xidx) > min_box(xidx));
  BOOST_ASSERT(max_box(yidx) > min_box(yidx));
  const Vec2d box_size = max_box - min_box;
  LOG(INFO) << "box_size = " << max_box;
  /// create a matrix of cell lists 
  blast::matrix<std::list<long> > cell_lists(floor( box_size(xidx) / supportlength ) + 1,  
					     floor( box_size(yidx) / supportlength ) + 1);
  /// put particles in the cell lists
  for (int iparticle = 0; iparticle<data.size1(); iparticle++) {
    const double x = data(iparticle, xidx);
    const double y = data(iparticle, yidx);
    const int icell = floor( (x - min_box(xidx)) / supportlength );
    const int jcell = floor( (y - min_box(yidx)) / supportlength );
    /// regestre a particle ID in the cell list
    cell_lists(icell, jcell).push_back( iparticle);
  }
  /// number of columns in particles configuration excluding x, y, rho, m
  BOOST_ASSERT(data.size2() - nreqfields > 0);
  blast::matrix<double> out = nullMat(probe.size1(), data.size2() - nreqfields);
  LOG(INFO) << "out.size1() = " << out.size1();
  LOG(INFO) << "out.size2() = " << out.size2();

  /// a pointer to Kernel function 
  /// harmonic parameter is not used
  boost::shared_ptr<Kernel> weight_function = chooseKernelType(kernel_type, supportlength, 3.0);
  const double sup2 = supportlength * supportlength;

  for (long iprobe=0; iprobe<probe.size1(); iprobe++) {
    LOG(INFO) << "iprobe = " << iprobe;
    /// a cell for the probe point
    const double x = probe(iprobe, xidx);
    const double y = probe(iprobe, yidx);
    const int icell = floor( (x - min_box(xidx)) / supportlength );
    const int jcell = floor( (y - min_box(yidx)) / supportlength );
    LOG(INFO) << "icell = " << icell;
    LOG(INFO) << "jcell = " << jcell;
    // iterate in the neighboring cells
    for (int i=std::max(icell-1, 0); i<std::min(icell+2, (int)cell_lists.size1()); i++) {
      for (int j=std::max(jcell-1, 0); j<std::min(jcell+2, (int)cell_lists.size2()); j++) {
	LOG(INFO) << "i = " << i;
	LOG(INFO) << "j = " << j;
	// iterate inside one cell
	BOOST_FOREACH(const long id, cell_lists(i, j)) {
	  const double xp = data(id, xidx);
	  const double yp = data(id, yidx);
          const double mass = data(id, midx);
          const double rho = data(id, rhoidx);
	  const double r2 = pow(x - xp, 2) + pow(y - yp, 2);
	  LOG(INFO) << "r2 = " << r2;
	  if (r2<sup2) {
	    const double w = weight_function->w(sqrt(r2));
	    /// iterate for all fields
            out(iprobe, rhoidx - nreqfields) += mass * w;
	    for (int ifield=2; ifield<data.size2() - nreqfields; ifield++) {
	      const double fieldvalue = data(id, ifield + nreqfields);
	      out(iprobe, ifield) += mass/rho * fieldvalue * w;
	    }
	  } // if (r2>sup2) {
	} // BOOST_FOREACH(const long id, cell_lists(i, j)) {
      }
    }
  } // for (long iprobe=1; iprobe<probe.size1(); iprobe++) {

  return out;
}


int main(int ac, char* av[]) {
  google::InitGoogleLogging(av[0]);
  LOG(INFO) << "sphprobe starts";
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
    ("sl,s", po::value<double>(), "support length for the kernel")
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
    t2 = t1;
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
  BOOST_ASSERT(tout>=t1);
  BOOST_ASSERT(tout<=t2);


  std::string kernel_type;
  if (vm.count("ktype")) {
    kernel_type = vm["ktype"].as<std::string>();
  } else {
    kernel_type = "QuinticSpline";
  }
  LOG(INFO) << "kernel_type = " << kernel_type;

  double supportlength;
  if (vm.count("sl")) {
    supportlength = vm["sl"].as<double>();
  } else {
    LOG(ERROR) << "supprt length must be given";
    return(EXIT_FAILURE);
  }
  BOOST_ASSERT(supportlength > 0.0);
  LOG(INFO) << "supprt length = " << supportlength;

  std::string c1;
  if (vm.count("c1")) {
    c1 = vm["c1"].as<std::string>();
  } else {
    LOG(ERROR) << "particle configuration must be given (--c1 parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "c1 = " << c1;

  std::string c2; 
  bool c2isgiven;
  if (vm.count("c2")) {
    c2= vm["c2"].as<std::string>();
    c2isgiven = true;
    LOG(INFO) << "c2 = " << c2;
  } else {
    c2isgiven = false;
  }

  std::string probe_file;
  if (vm.count("probe")) {
    probe_file= vm["probe"].as<std::string>();
  } else {
    LOG(ERROR) << "probe file be given (--probe parameter)";
    return EXIT_FAILURE;
  }
  LOG(INFO) << "probe_file = " << probe_file;
  
  const blast::matrix<double> probe = readMatrix(probe_file);
  const blast::matrix<double> data1 = readMatrix(c1);
  const blast::matrix<double> out1 = getSPHApprox(data1, kernel_type, supportlength, probe);
  if ( (t2>=tout) && (c2isgiven) ) {
    const blast::matrix<double> data2 = readMatrix(c2);
    const blast::matrix<double> out2 = getSPHApprox(data2, kernel_type, supportlength, probe);
    LOG(INFO) << "t1, t2, tout: " << t1 << ' ' <<  t2 << ' ' <<  tout;
    const blast::matrix<double> out =  ( (t2 - tout) * out1 + (tout - t1) * out2 ) / (t2 - t1);
    LOG(INFO) << "ouput time interpolation";
    printXYOut(probe, out, std::cout);
  } else {
    LOG(INFO) << "ouput without time  interpolation";
    printXYOut(probe, out1, std::cout);
  }

  return EXIT_SUCCESS;
}
