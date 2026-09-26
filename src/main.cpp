#include "topi/topi.hpp"

using namespace topi::tools::vector;

int main() {
  Vector2i u = Vector2i(4, 7);
  Vector2i v = u * 2;
  Vector2i w = u + v;

  u.debug_disp();
  v.debug_disp();
  w.debug_disp();

  return 0;
}
