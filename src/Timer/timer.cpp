#include <boost/foreach.hpp>
#include <glog/logging.h>
#include "Timer/timer.h"
#include "Timer/timeobserver.h"

Timer::Timer():
  _wasSet(false) {
  // Timer is created but time is unknown
}

void Timer::updateTime(const double new_time){
  _wasSet = true;
  LOG(INFO) << "update global time";
  _globalTime = new_time;
  notifyAll();
}

void Time::update_dt(const double new_dt) {
  _dt = new_dt;
}

double Time::get_dt() const {
  return _dt;
}

double Timer::getTime() const {
  assert(_wasSet);
  return _globalTime;
}

void Timer::addTimeObserver(spTimeObserver obj) {
  _notificationList.push_back(obj);
  LOG(INFO) << "addTimeObserver" ;
  LOG(INFO) << "_notificationList.size() = " << _notificationList.size();
}

void Timer::rmTimeObserver(spTimeObserver obj) {
  _notificationList.remove(obj);
  LOG(INFO) << "rmTimeObserver" ;
  LOG(INFO) << "_notificationList.size() = " << _notificationList.size();
}

void Timer::notifyAll() const {
  LOG(INFO) << "notifyAll is called";
  BOOST_FOREACH(const spTimeObserver obj, _notificationList) {
    LOG(INFO) << "notify an observer";
    obj->notify();
  }
}
