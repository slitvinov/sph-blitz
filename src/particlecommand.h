#ifndef PARTICLECOMMAND_H
#define PARTICLECOMMAND_H
#include "command.h"
#include "particle.h"

template <class Receiver>
///simple command 
class ParticleCommand : public Command {
public:
  typedef double (Receiver::* Action)(Particle*);
  ParticleCommand<Receiver>(Receiver* r, Action a) { 
    _receiver = r;
    _action = a;
  };
  virtual double Execute(Particle*);

private:
  Action _action;
  Receiver* _receiver;
};

template <class Receiver>
inline double ParticleCommand<Receiver>::Execute(Particle* pa) {
  return (_receiver->*_action) (pa);
}
#endif
