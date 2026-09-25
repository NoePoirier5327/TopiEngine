#include <topi/topi.hpp>
#include <ctime>
#include "game/game.hpp"

int main() {
  topi::TopiEngine topi = topi::TopiEngine("Tetris", 320, 640);

  Game game;

  topi.on_command().on_update([&game](double dt) {
    game.update();
  });

  topi.on_command().on_display([&game](topi::render::Renderer *renderer) {
    game.display(renderer);
  });

  topi.run();
}
