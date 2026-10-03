#include <topi/topi.hpp>
#include "game/game.hpp"

int main() {
  topi::TopiEngine app = topi::TopiEngine("Tetris", 640, 640);
  Game game;

  app.on_resource().load_font("./res/JetBrainsMonoNerdFont-Bold.ttf", 32);

  app.on_command().on_input([&game](const topi::input::InputManager &input_manager, double dt) {
    if (!game.game_is_over()) game.handle_inputs(input_manager);
  });

  app.on_command().on_update([&game](double dt) {
    if (!game.game_is_over()) game.update();
  });

  app.on_command().on_display([&game](topi::render::Renderer *renderer) {
    game.display(renderer);
  });

  app.run();
}
