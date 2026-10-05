#include "topi/topi.hpp"

int main() {
  topi::TopiEngine app = topi::TopiEngine("Test", 400, 400);

  topi::object::tilemap::ColoredTilemap tilemap = topi::object::tilemap::ColoredTilemap(10, 5, 3);
  tilemap.new_tile(0, 255, 100, 100, 255);
  tilemap.new_tile(1, 100, 255, 100, 255);
  tilemap.new_tile(2, 100, 100, 255, 255);

  for (size_t i = 0; i < 5; ++i)
    tilemap(0, i, 0) = 1;

  for (size_t i = 0; i < 10; ++i)
    tilemap(i, 0, 0) = 2;

  tilemap.exchange_columns(0, 3, 0);
  tilemap.exchange_lines(0, 3, 0);
  tilemap.exchange_layers(0, 1);

  int x = 0;
  bool is_rectangle_invisible = false;

  app.setup([]() {});

  app.update([&x, &is_rectangle_invisible](double dt) {
    if (topi::input::is_key_held(topi::input::keycode::KEY_RIGHT)) x -= 200 * dt;
    if (topi::input::is_key_held(topi::input::keycode::KEY_LEFT)) x += 200 * dt;
    if (topi::input::is_key_pressed(topi::input::keycode::KEY_A)) is_rectangle_invisible = !is_rectangle_invisible;
  });

  app.display([&tilemap, &x, &is_rectangle_invisible](topi::render::Renderer *renderer) {
    tilemap.display_layer(renderer, 0);
    renderer->draw_line(0, 0, 400, 400, 20, 255, 255, 0, 255);
    if (!is_rectangle_invisible) renderer->draw_colored_rectangle(x, 200, 400, 100, 10, 0, 255, 0, 255);
  });

  app.run();

  return 0;
}
