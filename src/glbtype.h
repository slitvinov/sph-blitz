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
class ParticleContext;
class Timer;

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

///a shared pointer to time Context Class
typedef boost::shared_ptr<ParticleContext> spParticleContext;

///a shared pointer to time Timer Class
typedef boost::shared_ptr<Timer> spTimer;

namespace blast = boost::numeric::ublas;

///a vector of shared_ptr to material
typedef blast::vector< spMaterial > vecMaterial;

/// a matrix for gforce
typedef boost::numeric::ublas::matrix<double> TMatrix;

/// compiled body force function type
typedef void(*TBodyF)(double, double, double&, double&);

#endif
