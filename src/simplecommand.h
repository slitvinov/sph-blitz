#ifndef SIMPLECOMMAND_H
#define SIMPLECOMMAND_H
#include "command.h"

template <class Receiver>
///simple command 
class SimpleCommand : public Command {
public:
  typedef double (Receiver::* Action)();
  SimpleCommand<Receiver>(Receiver* r, Action a) { 
    _receiver = r;
    _action = a;
  };
  
  virtual double Execute();

private:
  Action _action;
  Receiver* _receiver;
};

template <class Receiver>
inline double SimpleCommand<Receiver>::Execute() {
  return (_receiver->*_action) ();
}


#endif
