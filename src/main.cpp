#include "topi/topi.hpp"
#include <iostream>

int main() {
  topi::TopiEngine app = topi::TopiEngine("Test", 400, 500);

  topi::game_object::tilemap::ColoredTilemap tilemap = topi::game_object::tilemap::ColoredTilemap(10, 5, 3);

  int x = 0;
  bool is_rectangle_invisible = false;
  std::string to_disp = "";

  app.setup([&tilemap]() {
    tilemap.new_tile(0, {255, 100, 100, 255});
    tilemap.new_tile(1, {100, 255, 100, 255});
    tilemap.new_tile(2, {100, 100, 255, 255});

    for (size_t i = 0; i < 5; ++i)
      tilemap(0, i, 0) = 1;

    for (size_t i = 0; i < 10; ++i)
      tilemap(i, 0, 0) = 2;

    tilemap.exchange_columns(0, 3, 0);
    tilemap.exchange_lines(0, 3, 0);
    tilemap.exchange_layers(0, 1);
  });

  app.update([&x, &is_rectangle_invisible, &to_disp](double dt) {
    if (topi::input::is_key_held(topi::input::keycode::KEY_RIGHT)) x -= 200 * dt;
    if (topi::input::is_key_held(topi::input::keycode::KEY_LEFT)) x += 200 * dt;
    if (topi::input::is_key_pressed(topi::input::keycode::KEY_A)) is_rectangle_invisible = !is_rectangle_invisible;

    char to_add = topi::input::last_input_as_char();
    if (to_add != '\0') to_disp += to_add;

    std::cout << to_disp << std::endl;
  });

  app.display([&tilemap, &x, &is_rectangle_invisible](topi::render::RenderManager *renderer) {
    tilemap.display_layer(renderer, 1);

    renderer->set_line_thickness(20);
    renderer->set_draw_color(topi::type::color::GREEN);
    renderer->draw_line(0, 0, 400, 400);

    if (!is_rectangle_invisible) {
      renderer->set_line_thickness(10);
      renderer->set_draw_color(topi::type::color::YELLOW);
      renderer->draw_colored_rectangle(x, 200, 400, 100);
    }
  });

  app.run();

  return 0;
}
