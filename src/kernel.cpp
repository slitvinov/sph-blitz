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

//#include <iostream>

//#include <cstdlib>

// ***** local includes *****
#include "kernel.h"
//#include "glbfunc.h"

using namespace std;

//constructor to inizialize the data members
Kernel::Kernel(double smoothingLength)
    : smoothingLength(smoothingLength)
{
    if (smoothingLength <= 0.0)
    {
        cout << "\n FAILURE: The Kernel gets a non-positive smoothing length \"" << smoothingLength << "\"!\n";
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
