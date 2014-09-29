#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"
#include <list> 
using namespace std;

class Observer;
///subject to observer pattern
class Subject {
public:
  virtual ~Subject() {};
  ///attach observer
  virtual void Attach(Observer*);
  ///detach observer
  virtual void Detach(Observer*);
  ///notify all observers that the subject changed
  virtual void Notify(double);
  /// get time
  virtual double GetTime() ;
  
  ///set time
  virtual void SetTime(double);

protected:
  Subject();
private:
  //   ///set new time
  //   virtual SetTime(double);
  ///a list of all observers
  list<Observer*> observers_;
  double currenttime_;
};
#endif

