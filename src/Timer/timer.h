#ifndef SRC_TIMER_TIMER
#define SRC_TIMER_TIMER
#include <boost/smart_ptr/shared_ptr.hpp>
#include <list>

class TimeObserver;
typedef boost::shared_ptr<TimeObserver> spTimeObserver;

/// class to keep global simulation time
class Timer {
public:
  ///constructor
  Timer();
  ///update time to a new value
  void updateTime(const double new_time);
  ///get current value of time
  double getTime() const;
  ///update time to a new value
  void update_dt(const double new_dt);
  ///get current value of time
  double get_dt() const;
  ///add observer to the list
  void addTimeObserver( spTimeObserver );
  ///remove observer from the list
  void rmTimeObserver( spTimeObserver );
private:
  ///notify all observer that time was changed
  void notifyAll() const;
  ///current simulation time 
  double _globalTime;
  ///simulation time step
  double _dt;
  ///a list of all attached observers
  std::list<spTimeObserver> _notificationList;
  /// to make sure timer was set at least once
  bool _wasSet;
};
#endif
