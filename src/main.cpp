#include "topi/input_manager/input_manager.hpp"
#include "topi/object/tilemap/tilemap.hpp"
#include "topi/topi.hpp"
#include <cstdint>

int main() {
  TopiEngine topi = TopiEngine("Test", 400, 800);

  ColoredTilemap tilemap = ColoredTilemap(10, 20);
  tilemap.new_tile(0, 255, 100, 100, 255);
  tilemap.new_tile(1, 100, 255, 100, 255);
  tilemap.new_tile(2, 100, 100, 255, 255);

  for (size_t x = 0; x < 10; ++x) {
    for (size_t y = 0; y < 20; ++y) {
      tilemap(x, y) = static_cast<uint64_t>((x + y) % 3);
    }
  }

  tilemap.flip_y();

  topi.on_command().on_display([&tilemap](Renderer *renderer) {
    tilemap.display(renderer);
  });

  topi.run();

  return 0;
}
