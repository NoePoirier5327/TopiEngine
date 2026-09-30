#include "time.hpp"
#include <chrono>

namespace topi::tools::time {
  double now_as_seconds() {
    auto now = std::chrono::system_clock::now();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return static_cast<double>(secs);
  }
};
