#ifndef OBSERVER_H
#define OBSERVER_H
class Subject;

///observer class (pattern)
class Observer {
public:
  virtual ~Observer();
  virtual void Update(Subject* theChangeSubject) = 0;
protected:
  Observer();
private:
  ///current time
  double currenttime_;
};
#endif
