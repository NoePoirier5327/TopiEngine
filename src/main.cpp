#include "topi/topi.hpp"
#include <iostream>

void setup_function() {
  std::cout << "I'm called on setup." << std::endl;
}

void update_function(double dt) {
  std::cout << "I'm called on update : " << dt << std::endl;
}

void drawing_function(Renderer* renderer) {
  renderer->new_colored_filled_rectangle(0, 0, 100, 300, 255, 100, 100, 255);
}

int main() {
  TopiEngine topi = TopiEngine("Test", 480, 300);

  topi.on_command().on_setup(setup_function);
  topi.on_command().on_update(update_function);
  topi.on_command().on_display(drawing_function);
  topi.run();

  return 0;
}
