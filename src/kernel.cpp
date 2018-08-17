/// \file kernel.cpp
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief the abstract kernel base class
///


//----------------------------------------------------------------------------------------
//      The abstract kernel base class for the SPH method
//		kernel.cpp
//----------------------------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <cstdlib>

// ***** local includes *****
#include "glbcls.h"
#include "glbfunc.h"

//constructor to inizialize the data members
Kernel::Kernel(const double smoothingLength)
    : smoothingLength(smoothingLength)
{
    if (smoothingLength <= 0.0)
    {
      std::cout << "\n FAILURE: The Kernel gets a non-positive smoothing length \"" 
		<< smoothingLength << "\"!\n";
      std::cout << __FILE__ << ':' << __LINE__ << std::endl;
      exit(1);
    }
}
//----------------------------------------------------------------------------------------
//					de-constructor
//----------------------------------------------------------------------------------------
///deconstructor
Kernel::~Kernel()
{
}
