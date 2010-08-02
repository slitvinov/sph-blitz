/// \file glbtype.h
/// \brief Global types

#ifndef GLBTYPE_H
#define GLBTYPE_H

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>

class Material;
class Particle;
class Interaction;
class TimeSolver;
class Kernel;

///a shared pointer to Material
typedef boost::shared_ptr<Material> spMaterial;

///a shared pointer to Particle
typedef boost::shared_ptr<Particle> spParticle;

///a shared pointer to Interaction
typedef boost::shared_ptr<Interaction> spInteraction;

///a shared pointer to time solver
typedef boost::shared_ptr<TimeSolver> spTimeSolver;

///a shared pointer to time kernel
typedef boost::shared_ptr<Kernel> spKernel;

namespace blast = boost::numeric::ublas;

///a vector of shared_ptr to material
typedef blast::vector< spMaterial > vecMaterial;

#endif
