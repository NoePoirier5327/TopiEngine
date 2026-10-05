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

  app.setup([]() {});
  app.update([](double dt) {});

  app.display([&tilemap](topi::render::Renderer *renderer) {
    tilemap.display_layer(renderer, 0);
    renderer->draw_line(0, 0, 400, 400, 20, 255, 255, 0, 255);
    renderer->draw_colored_rectangle(200, 200, 400, 100, 10, 0, 255, 0, 255);
  });

  app.run();

  return 0;
}
