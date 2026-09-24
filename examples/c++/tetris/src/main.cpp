#include <topi/topi.hpp>
#include "game/game.hpp"

int main() {
  TopiEngine topi = TopiEngine("Tetris", 320, 640);

  Game game;

  topi.on_command().on_update([&game](double dt) {
    game.update();
  });

  topi.on_command().on_display([&game](Renderer *renderer) {
    game.display(renderer);
  });

  topi.run();
}
