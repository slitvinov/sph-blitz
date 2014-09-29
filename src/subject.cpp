#include "subject.h"
#include <iostream>
Subject::Subject():
  currenttime_(0.0)
{
}

void Subject::Attach(Observer* o) {
  observers_.push_back(o);
}

void Subject::Detach(Observer* o) {
  observers_.remove(o);
}

double Subject::GetTime()  {
  return currenttime_;
}

void Subject::SetTime(double ntime) {
  currenttime_ = ntime;
}


void Subject::Notify(double ntime) {
  ///set new time for the subject
  SetTime(ntime);
  list<Observer*>::iterator i;
  currenttime_ = ntime;  
  for (i = observers_.begin(); i != observers_.end(); i++) {  
    (*i)->Update(this);
  }
}

// double  Subject::GetTime() {
  
// }
