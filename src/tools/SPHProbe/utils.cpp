#include <algorithm>
#include <cstdlib>
#include <list>
#include <glog/logging.h>
#include "src/tools/SPHProbe/utils.h"
//namespace po = boost::program_options;

std::vector<double> readRow(std::string row) {
  std::vector<double> retval;
  std::istringstream is(row);
  double num;
  while (is >> num) retval.push_back(num);
  return retval;
}

/// read a list of vectors from std stream
std::vector<std::vector<double> > readVector(std::istream &is) {
  std::string line;
  std::vector<std::vector<double> > retval;
  while (std::getline(is, line)) {
    retval.push_back(readRow(line));
  }
  return retval;
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
