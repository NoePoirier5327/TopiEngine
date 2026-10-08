#include "timer.hpp"
#include "../time.hpp"
#include <cstdint>

namespace topi::toolkit::time {
  Timer::Timer(uint64_t secondes_to_wait) {
    this->_beginning = now_as_milliseconds();
    this->_seconds_to_wait = secondes_to_wait;
  }

  void Timer::set_seconds_to_wait(uint64_t seconds_to_wait) {
    this->_seconds_to_wait = seconds_to_wait;
  }

  uint64_t Timer::get_seconds_to_wait() const {
    return this->_seconds_to_wait;
  }

  bool Timer::finished_to_wait() const {
    return (now_as_milliseconds() - this->_beginning) >= this->_seconds_to_wait;
  }

  void Timer::restart() {
    this->_beginning = now_as_milliseconds();
  }

  void Timer::wait_to_finish() const {
    while (this->finished_to_wait()) {}
  }
}
