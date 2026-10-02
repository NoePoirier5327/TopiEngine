#include "timer.hpp"
#include "../time.hpp"
#include <cstdint>

namespace topi::tools::time {
  Timer::Timer(uint64_t _secondes_to_wait) {
    this->beginning = now_as_milliseconds();
    this->seconds_to_wait = _secondes_to_wait;
  }

  void Timer::set_seconds_to_wait(uint64_t _seconds_to_wait) {
    this->seconds_to_wait = _seconds_to_wait;
  }

  uint64_t Timer::get_seconds_to_wait() const {
    return this->seconds_to_wait;
  }

  bool Timer::finished_to_wait() const {
    return (now_as_milliseconds() - this->beginning) >= this->seconds_to_wait;
  }

  void Timer::restart() {
    this->beginning = now_as_milliseconds();
  }

  void Timer::wait_to_finish() const {
    while (this->finished_to_wait()) {}
  }
}
