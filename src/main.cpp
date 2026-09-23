#include "topi/input_manager/input_manager.hpp"
#include "topi/object/tilemap/tilemap.hpp"
#include "topi/topi.hpp"
#include <cstdint>

int main() {
  TopiEngine topi = TopiEngine("Test", 400, 800);

  MultilayerColoredTilemap tilemap = MultilayerColoredTilemap(10, 20, 2);
  tilemap.new_tile(0, 255, 100, 100, 255);
  tilemap.new_tile(1, 100, 255, 100, 255);
  tilemap.new_tile(2, 100, 100, 255, 255);

  for (size_t x = 0; x < 9; ++x) {
    for (size_t y = 0; y < 19; ++y) {
      tilemap(x, y, 0) = static_cast<uint64_t>((x + y) % 3);
      tilemap(x, y, 1) = 2;
      tilemap(9, y, 1) = 1;
    }
    tilemap(x, 19, 1) = 0;
  }

  tilemap.flip_y();
  tilemap.flip_x();

  topi.on_command().on_display([&tilemap](Renderer *renderer) {
    tilemap.display(renderer, 1);
  });

  topi.run();

  return 0;
}
