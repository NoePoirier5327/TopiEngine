#include "topi/topi.hpp"
#include <iostream>

using namespace topi::tools::vector;

int main() {
  Vector2i u = Vector2i(4, 7);
  Vector2i v = u * 2;
  Vector2i w = u + v;

  u.cli_disp();
  v.cli_disp();
  w.cli_disp();

  return 0;
}
