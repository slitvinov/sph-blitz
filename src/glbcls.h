#ifndef GLBCLS_H
#define GLBCLS_H
/// \file glbcls.h
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief Global class declarations

#include "vec2d.h"
#include "wiener.h"
#include "dllist.h"

class Initiation; class Kernel; class MLS; class Interaction; class ParticleManager;
class Particle; class Initiation; class Boundary; class Force; class Output; class Diagnose;
class Hydrodynamics; class ListNode; class Material; class BetaSpline; class QuinticSpline;

#include "initiation.h"
#include "kernel.h"
#include "betaspline.h"
#include "particle.h"
#include "particlemanager.h"
#include "boundary.h"
#include "material.h"
#include "force.h"
#include "interaction.h"
#include "hydrodynamics.h"

#endif //GLBCLS_H
