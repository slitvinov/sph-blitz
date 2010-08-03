/// \file timesolver.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>  	
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 
//-----------------------------------------------------------------------

//      Time solver class
	  	
//      timesolver.cpp

//-----------------------------------------------------------------------

// ***** system includes *****
#include <glog/logging.h>
// ***** localincludes *****

#include "hydrodynamics.h"
#include "particlemanager.h"
#include "timesolver.h"
#include "initiation.h"
#include "boundary.h"


using namespace std;
	  	

//----------------------------------------------------------------------------------------	
//              constructor
//-----------------------------------------------------------------------------
TimeSolver::TimeSolver() {
 LOG(INFO) << "\n constructor of base TimeSolver";
}

TimeSolver::~TimeSolver() {

 LOG(INFO) << "destructor of base TimeSolver is called";

}
