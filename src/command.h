#ifndef COMMAND_H
#define COMMAND_H
class Particle;

///abstract command class (used by OutputStream)
class Command {
public:
  ///virtual destructor
  virtual ~Command();
  
  ///execute command (should return double)
  ///change to more complex data types
  virtual double Execute();

  ///execute command (should return double)
  ///change to more complex data types
  virtual double Execute(Particle*);

protected:
  ///constructor
  Command();
};

#endif
