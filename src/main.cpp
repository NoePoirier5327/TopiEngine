#include "topi/topi.hpp"

int main() {
  TopiEngine& instance = TopiEngine::init("Test", 480, 300);

  TopiEngine::destroy();
  return 0;
}
