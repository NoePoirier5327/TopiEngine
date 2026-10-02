#include "time.hpp"
#include <chrono>

namespace topi::tools::time {
  uint64_t now_as_milliseconds() {
    auto now = std::chrono::system_clock::now();
    auto millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return static_cast<uint64_t>(millisecs);
  }
};
