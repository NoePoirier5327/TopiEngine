#include <topi/topi.hpp>
#include "game/game.hpp"

int main() {
  topi::TopiEngine topi = topi::TopiEngine("Tetris", 320, 640);

  Game game;

  topi.on_command().on_input([&game](const topi::input::InputManager &input_manager, double dt) {
    if (!game.game_is_over()) game.handle_inputs(input_manager);
  });

  topi.on_command().on_update([&game](double dt) {
    if (!game.game_is_over()) game.update();
  });

  topi.on_command().on_display([&game](topi::render::Renderer *renderer) {
    game.display(renderer);
  });

  topi.run();
}
