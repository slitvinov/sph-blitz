/// \file timesolver.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>  	
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>,
/// \author changes by: Sergey Litvinov <slitvinov@gmail.com>
//-----------------------------------------------------------------------

//      Time solver class
	  	
//      timesolver.cpp

//-----------------------------------------------------------------------

// ***** system includes *****
#include <glog/logging.h>
// ***** localincludes *****

#include "timesolver.h"

//----------------------------------------------------------------------------------------	
//              constructor
//-----------------------------------------------------------------------------
TimeSolver::TimeSolver() {
 LOG(INFO) << "constructor of base TimeSolver called";
}

TimeSolver::~TimeSolver() {
 LOG(INFO) << "destructor of base TimeSolver called";
}
