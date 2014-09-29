#include "timer.h"
#include "stdlib.h"
#include "initiation.h"
#include <iostream>

#include "glbfunc.h"
#ifndef NOLOG
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#endif

using namespace std;

Timer::Timer():
  start_time_(time(NULL))
{
  max_time_sec_ = Initiation::Instance()->MAX_TIME;
  //is less then 1e-3 
  //the time is infinite
  isgiven_ = (max_time_sec_>1e-3);
}

bool Timer::isEnd() const {
    //  cout << "time passed: " << time(NULL) - start_time_ << '\n';
  if (!isgiven_) {
      return false;
    }
  else {
    if ((time(NULL) - start_time_) > max_time_sec_) {
      return true;
    }
    else {
      return false;
    }
  }
}
