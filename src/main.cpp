#include "topi/topi.hpp"
#include <cstdint>
#include <iostream>

int main() {
  topi::TopiEngine topi = topi::TopiEngine("Test", 800, 1600);

  topi::object::tilemap::ColoredTilemap tilemap = topi::object::tilemap::ColoredTilemap(10, 20, 2);
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

  size_t current_layer = 1;

  topi.on_command().on_input([&tilemap, &current_layer](const topi::input::InputManager& input_manager, double dt) {
    if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_A)) {
      tilemap.flip_x();
    }
    if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_Z)) {
      tilemap.flip_y();
    }
    if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_E)) {
      current_layer = (current_layer + 1) % 2;
    }
  });

  topi.on_command().on_update([](double dt) {
    std::cout << topi::tools::random::randrange(-3, 8) << std::endl;
    std::cout << topi::tools::random::randrange(-5.0, 8.0) << std::endl;
  });

  topi.on_command().on_display([&tilemap, &current_layer](topi::render::Renderer *renderer) {
    tilemap.display(renderer, current_layer, 80.0, 140.0, 2.0);
  });

  topi.run();

  return 0;
}
