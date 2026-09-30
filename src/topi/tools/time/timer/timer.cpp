#include "timer.hpp"
#include "../time.hpp"
#include <stdexcept>

namespace topi::tools::time {
  Timer::Timer(double _secondes_to_wait) {
    if (_secondes_to_wait < 0) {
      throw std::invalid_argument("You can't wait a negative time.");
    }

    this->beginning = now_as_seconds();
    this->seconds_to_wait = _secondes_to_wait;
  }

  void Timer::set_seconds_to_wait(double _seconds_to_wait) {
    if (_seconds_to_wait < 0) {
      throw std::invalid_argument("You can't wait a negative time.");
    }

    this->seconds_to_wait = _seconds_to_wait;
  }

  double Timer::get_seconds_to_wait() const {
    return this->seconds_to_wait;
  }

  bool Timer::finished_to_wait() const {
    return (now_as_seconds() - this->beginning) >= this->seconds_to_wait;
  }

  void Timer::restart() {
    this->beginning = now_as_seconds();
  }

  void Timer::wait_to_finish() const {
    while (this->finished_to_wait()) {}
  }
}
