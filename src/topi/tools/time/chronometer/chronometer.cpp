#include "chronometer.hpp"
#include <chrono>

namespace topi::tools::time {
  /**
   * @brief renvoie le temps actuel sous forme de seconde en uint64_t
   */
  uint64_t now_as_seconds() {
    auto now = std::chrono::system_clock::now();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return static_cast<uint64_t>(secs);
  }

  Chronometer::Chronometer() {
    this->start_time = now_as_seconds();
  }

  uint64_t Chronometer::get_elapsed_seconds() const {
    return now_as_seconds() - this->start_time;
  }

  void Chronometer::restart() {
    this->start_time = now_as_seconds();
  }
};
