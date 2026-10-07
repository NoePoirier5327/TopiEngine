#include "chronometer.hpp"
#include "../time.hpp"
#include <cstdint>

namespace topi::tools::time {
  Chronometer::Chronometer() {
    this->_start_time = now_as_milliseconds();
  }

  uint64_t Chronometer::get_elapsed_seconds() const {
    return now_as_milliseconds() - this->_start_time;
  }

  void Chronometer::restart() {
    this->_start_time = now_as_milliseconds();
  }
};
