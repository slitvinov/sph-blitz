#ifndef MAIN_H
#define MAIN_H
#include "initiation.h"
#include "betaspline.h"
#include "material.h"
#include "boundary.h"
#include "mls.h"
#include "diagnose.h" 
#include "output.h"
#include "particle.h"
#include "force.h"
#include "particlemanager.h"
#include "quinticspline.h"
#include "hydrodynamics.h"
#include "timesolver.h"
#include "interaction.h"
#include "wiener.h"
#include "kernel.h" 
#include "polymerparticle.h"
#include "interactionstate.h"
#include "node.h"
#include "abspolymercreator.h"
#include "simplepolymercreator.h"
#include "datacollector.h"
#include "simpledatacollector.h"
#include "compositedatacollector.h"
#include "polymerdatacollector.h"
#include "massdatacollector.h"
#include "outputstream.h"
#include "textoutputstream.h"
#include "simplecommand.h"
#include "netcdfoutputstream.h"
#include "particlecommand.h"
#include "timer.h"
#include "rgdatacollector.h"
#include "torrgdatacollector.h"
#include "newrgdatacollector.h"
#include "glbfunc.h"

#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/propertyconfigurator.h>
#endif

// Boltzmann constant
double k_bltz  = 1.380662e-023; //[J/K]
//double k_bltz  = 1.380662e-023 * 1.0e12; // [kg*micrometer^2/s^2/K]

#endif
