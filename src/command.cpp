#include "command.h"
Command::~Command() {
}

Command::Command() {
}

double Command::Execute() {
  return 0.0;
}

double Command::Execute(Particle*) {
  return 0.0;
}
