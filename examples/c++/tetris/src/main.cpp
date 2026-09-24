#include <topi/topi.hpp>

int main() {
  TopiEngine topi = TopiEngine("Tetris", 320, 640);

  topi.run();
}
