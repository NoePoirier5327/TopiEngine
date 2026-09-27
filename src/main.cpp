#include "topi/topi.hpp"
#include <iostream>

int main() {
  topi::tools::time::Timer timer = topi::tools::time::Timer(90.0);

  while (!timer.finished_to_wait()) {}

  std::cout << "Finished to wait !" << std::endl;

  return 0;
}
