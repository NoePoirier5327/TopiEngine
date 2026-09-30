#include "chronometer.hpp"
#include "../time.hpp"

namespace topi::tools::time {
  Chronometer::Chronometer() {
    this->start_time = now_as_seconds();
  }

  double Chronometer::get_elapsed_seconds() const {
    return now_as_seconds() - this->start_time;
  }

  void Chronometer::restart() {
    this->start_time = now_as_seconds();
  }
};
