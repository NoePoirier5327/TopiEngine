#include "topi/topi.hpp"

int main() {
  TopiEngine topi = TopiEngine("Test", 480, 300);
  topi.run();

  return 0;
}
