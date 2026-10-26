#include <topi/topi.hpp>
#include "game/game.hpp"

int main() {
  topi::TopiEngine app = topi::TopiEngine("Example - Tetris", 640, 640);
  Game game;

  app.setup([]() {});

  app.update([&game](double dt) {
    // Le jeu n'est pas terminé, on joue.
    if (!game.game_is_over()) {
      game.handle_inputs();
      game.update();
    }
  });

  app.display([&game]() {
    game.display();

    if (game.game_is_over()) {
      topi::render::set_draw_color(topi::type::color::BLACK);
      topi::render::draw_colored_filled_rectangle(0, 256, 320, 128);

      topi::render::set_draw_color(topi::type::color::WHITE);
      topi::render::set_font("./res/JetBrainsMonoNerdFont-Bold.ttf", 32);
      topi::render::draw_text("GAME OVER", 80, 292);
    }
  });

  app.run();
}
