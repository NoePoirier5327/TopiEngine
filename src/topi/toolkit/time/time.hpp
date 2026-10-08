#ifndef TIME_HEADER
#define TIME_HEADER

#include <cstdint>

namespace topi::toolkit::time {
  /**
   * @brief Renvoie le temps courant sous forme de milisecondes.
   */
  uint64_t now_as_milliseconds();
};

#endif // !TIME_HEADER
