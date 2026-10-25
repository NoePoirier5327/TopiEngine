#include <topi/topi.hpp>
#include "game/game.hpp"

int main() {
  topi::TopiEngine app = topi::TopiEngine("Tetris", 640, 640);
  Game game;

  app.setup([]() {});

  app.update([&game](double dt) {
    // Le jeu n'est pas terminé, on joue.
    if (!game.game_is_over()) {
      game.handle_inputs();
      game.update();
    }
  });

  app.display([&game](topi::render::RenderManager *renderer) {
    game.display(renderer);

    if (game.game_is_over()) {
      renderer->set_draw_color(topi::type::color::BLACK);
      renderer->draw_colored_filled_rectangle(0, 256, 320, 128);

      renderer->set_draw_color(topi::type::color::WHITE);
      renderer->set_font("./res/JetBrainsMonoNerdFont-Bold.ttf", 32);
      renderer->draw_text("GAME OVER", 80, 292);
    }
  });

  app.run();
}
