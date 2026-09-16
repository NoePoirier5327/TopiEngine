#include "topi/topi.hpp"

int main() {
  TopiEngine::init("Test", 480, 300);

  TopiEngine::run();

  TopiEngine::destroy();
  return 0;
}
