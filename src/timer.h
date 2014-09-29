#ifndef TIMER
#define TIMER
#include "time.h"

///timer object to run sph program for given time
///gets maximum time from environment variable MAX_TIME (clock time in seconds)
class Timer {
public:
  ///timer object constructor
  Timer();
  ///returns true if time>MAX_TIME
  bool isEnd() const;
private:
  double max_time_sec_;
  bool isgiven_;
  time_t start_time_;
};

#endif
