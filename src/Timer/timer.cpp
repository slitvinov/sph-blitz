#include <boost/foreach.hpp>
#include <glog/logging.h>
#include "Timer/timer.h"
#include "Timer/timeobserver.h"

Timer::Timer(const double init_time):
  _globalTime(init_time) {
}

void Timer::updateTime(const double new_time){
  LOG(INFO) << "update global time";
  _globalTime = new_time;
  notifyAll();
}

double Timer::getTime() const {
  return _globalTime;
}

void Timer::addTimeObserver(spTimeObserver obj) {
  _notificationList.push_back(obj);
}

void Timer::rmTimeObserver(spTimeObserver obj) {
  _notificationList.remove(obj);
}

void Timer::notifyAll() const {
  LOG(INFO) << "notifyAll is called";
  BOOST_FOREACH(const spTimeObserver obj, _notificationList) {
    LOG(INFO) << "notify an observer";
    obj->notify();
}
