#include "topi/topi.hpp"

using namespace topi::object::tilemap;

int main() {
  ColoredTilemap tilemap = ColoredTilemap(20, 20, 2);

  tilemap(0, 1) = 1;

  tilemap.debug_disp(0);
  tilemap.debug_disp(1);

  return 0;
}
