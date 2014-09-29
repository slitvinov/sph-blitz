#include "simpleparticlecommand.h"
#include "particle.h"
#include "polymerparticle.h"

SimpleParticleCommand::SimpleParticleCommand(const char code):
  code_(code)
{  
}

double SimpleParticleCommand::Execute(Particle* pa) {
  double val;
  switch (code_) {
  case 'T': 
    val = pa->getTemperature();
    break;
  case 't':
    val = pa->getParticleType();
    break;
  }
  return val;  
}

SimpleParticleCommand::~SimpleParticleCommand() {
}
