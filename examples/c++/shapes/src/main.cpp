#include <topi/topi.hpp>

int main() {
  topi::TopiEngine app = topi::TopiEngine("Example - Shapes", 600, 600);

  app.setup([]() {});

  app.update([](double dt) {});

  app.display([]() {
    topi::render::set_draw_color(topi::type::color::BLUE);
    topi::render::draw_colored_filled_rectangle(0, 0, 300, 300);

    topi::render::set_draw_color(topi::type::color::CYAN);
    topi::render::set_line_thickness(20);
    topi::render::draw_colored_rectangle(310, 10, 280, 280);

    topi::render::set_draw_color(topi::type::color::GREEN);
    topi::render::draw_colored_filled_triangle(300, 300, 300, 600, 600, 600);

    topi::render::set_draw_color(topi::type::color::RED);
    topi::render::draw_colored_filled_circle(150, 450, 150.0);
  });

  app.run();

  return 0;
}
