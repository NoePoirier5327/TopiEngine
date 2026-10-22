#include <topi/topi.hpp>

int main() {
  topi::TopiEngine app = topi::TopiEngine("Example - Shapes", 600, 600);

  app.setup([]() {});

  app.update([](double dt) {});

  app.display([](topi::render::RenderManager *renderer) {
    renderer->set_draw_color(topi::type::color::BLUE);
    renderer->draw_colored_filled_rectangle(0, 0, 300, 300);

    renderer->set_draw_color(topi::type::color::CYAN);
    renderer->set_line_thickness(20);
    renderer->draw_colored_rectangle(310, 10, 280, 280);

    renderer->set_draw_color(topi::type::color::GREEN);
    renderer->draw_colored_filled_triangle(300, 300, 300, 600, 600, 600);

    renderer->set_draw_color(topi::type::color::RED);
    renderer->draw_colored_filled_circle(150, 450, 150.0);
  });

  app.run();

  return 0;
}
