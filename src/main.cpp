#include "topi/topi.hpp"
#include <iostream>

int main() {
  topi::TopiEngine app = topi::TopiEngine("Test", 400, 400);

  app.on_command().on_input([](const topi::input::InputManager& input_manager, double dt) {
    if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_UP)) {
      std::cout << "The player moves up." << std::endl;
    }

    if (input_manager.is_key_down(topi::input::keycode::KEY_DOWN)) {
      std::cout << "The player moves down." << std::endl;
    }
  });

  app.run();

  return 0;
}
