#include <cstdlib>
#include <stdexcept>
#include "random.hpp"

namespace topi::tools::random {
  int randrange(int min, int max) {
    if (min > max) {
      throw std::invalid_argument("The upper boundary should be superior or equal to the lower one.");
    }

    return min + rand() % (max - min + 1);
  }

  double randrange(double min, double max) {
    if (min > max) {
      throw std::invalid_argument("The upper boundary should be superior or equal to the lower one.");
    }

    return min + (static_cast<double>(rand()) / RAND_MAX) * (max - min);
  }

  double random() {
    return static_cast<double>(rand()) / RAND_MAX;
  }
}
