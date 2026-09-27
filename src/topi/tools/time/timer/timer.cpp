#include "timer.hpp"
#include <chrono>
#include <stdexcept>

namespace topi::tools::time {
  /**
   * @brief Renvoie le temps courant sous forme de secondes.
   */
  double now_as_secondes() {
    auto now = std::chrono::system_clock::now();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return static_cast<double>(secs);
  }

  Timer::Timer(double _secondes_to_wait) {
    if (_secondes_to_wait < 0) {
      throw std::invalid_argument("You can't wait a negative time.");
    }

    this->beginning = now_as_secondes();
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
    return (now_as_secondes() - this->beginning) >= this->seconds_to_wait;
  }

  void Timer::restart() {
    this->beginning = now_as_secondes();
  }

  void Timer::wait_to_finish() const {
    while (this->finished_to_wait()) {}
  }
}
