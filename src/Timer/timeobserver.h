#ifndef SRC_TIMER_TIMEOBSERVER
#define SRC_TIMER_TIMEOBSERVER

/// members of this class get notify then global simulation time is updated
class TimeObserver {
  /// this function is called if simulation time is updated
  virtual void notify() = 0;
  friend class Timer;
};
#endif
