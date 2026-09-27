#include "timer.hpp"
#include <chrono>

namespace topi::tools::time {
  /**
   * @brief Renvoie le temps courant sous forme de secondes.
   */
  uint64_t now_as_secondes() {
    auto now = std::chrono::system_clock::now();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return static_cast<uint64_t>(secs);
  }

  Timer::Timer(uint64_t _secondes_to_wait) {
    this->beginning = now_as_secondes();
    this->seconds_to_wait = _secondes_to_wait;
  }

  void Timer::set_seconds_to_wait(uint64_t _seconds_to_wait) {
    this->seconds_to_wait = _seconds_to_wait;
  }

  uint64_t Timer::get_seconds_to_wait() {
    return this->seconds_to_wait;
  }

  bool Timer::finished_to_wait() {
    return (now_as_secondes() - this->beginning) >= this->seconds_to_wait;
  }

  void Timer::restart() {
    this->beginning = now_as_secondes();
  }
}
