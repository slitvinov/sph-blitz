#include <iostream>
#include <cstdlib>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/make_shared.hpp> 
#include "src/Timer/timer.h"
#include "src/Timer/timeobserver.h"
#include <glog/logging.h>

class Observer : public TimeObserver {
public: 
  Observer(const std::string& name ):
    name(name) {
  }
private:
  void notify() {
    std::cout << name << ": Time update\n";
  }
  const std::string name;
};

int main(int , char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  /// create timer
  Timer tm(0.0);

  /// create observer
  boost::shared_ptr<Observer> obs1 = boost::make_shared<Observer>(std::string("number 1"));
  boost::shared_ptr<Observer> obs2 = boost::make_shared<Observer>(std::string("number 2"));

  /// attache observer to timer
  tm.addTimeObserver(obs1);
  tm.addTimeObserver(obs2);
  
  /// call update
  tm.updateTime(1.0);
  tm.updateTime(2.0);

  std::cout << "tm.getTime() = " << tm.getTime() << '\n';
  tm.rmTimeObserver(obs2);

  tm.updateTime(3.0);

  /// try to remove again
  tm.rmTimeObserver(obs2);
  /// nothing changes
  tm.updateTime(4.0);
  return EXIT_SUCCESS;
}
