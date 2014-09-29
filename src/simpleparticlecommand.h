#ifndef SIMPLEPARTICLECOMMAND_H
#define SIMPLEPARTICLECOMMAND_H
#include "polymerparticle.h"
#include "command.h"
class SimpleParticleCommand: public Command {
public:
  ///command constructot with the code
  explicit SimpleParticleCommand(const char);
  virtual double Execute(Particle*);
  virtual ~SimpleParticleCommand();
private:
  const char code_;
};
#endif
