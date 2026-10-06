#include <topi/topi.hpp>
#include "game/game.hpp"

int main() {
  topi::TopiEngine app = topi::TopiEngine("Tetris", 640, 640);
  Game game;

  app.setup([]() {});

  app.update([&game](double dt) {
    if (!game.game_is_over()) {
      game.handle_inputs();
      game.update();
    }
  });

  app.display([&game](topi::render::Renderer *renderer) {
    game.display(renderer);
  });

  app.run();
}
