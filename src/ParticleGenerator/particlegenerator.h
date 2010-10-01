#ifndef SRC_PARTICLEGENERATOR_PARTICLEGENERATOR_H
#define SRC_PARTICLEGENERATOR_PARTICLEGENERATOR_H
#include "vec2d.h"
#include <boost/random.hpp>
class Initiation;

/// base class to generate particles for initial conditions
/// returns only position the rest is handled by ParticleManager
class ParticleGenerator {
public:
  ParticleGenerator();

  /// returns position of the new particle
  Vec2d getPosition(const Initiation& ini, 
		    const int i, const int k, const int j, const int m, 
		    const double delta, const double cll_sz) ;

  /// returns particle material number
  int getParticleMaterialNo(Initiation& ini ,
			    const Vec2d& position);

private:
  boost::mt19937 engine;
  boost::uniform_real<double> distrib;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > random_number;
};


#endif // SRC_PARTICLEGENERATOR_PARTICLEGENERATOR_H
