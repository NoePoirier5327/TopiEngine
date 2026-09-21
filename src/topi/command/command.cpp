#include "command.hpp"
#include <stdexcept>

static bool ANOTHER_ISTANCE_IS_RUNNING = false;

Command::Command() {
  if (ANOTHER_ISTANCE_IS_RUNNING) {
    throw std::runtime_error("There should be only one instance of the command processor running.");
  }

  ANOTHER_ISTANCE_IS_RUNNING = true;
}

Command::~Command() {
  ANOTHER_ISTANCE_IS_RUNNING = false;
}

void Command::on_setup(void (*func)()) {
  this->setup_queue.push_back(func);
}

void Command::on_update(void (*func)(double)) {
  this->update_queue.push_back(func);
}

void Command::on_display(void (*func)(Renderer*)) {
  this->rendering_queue.push_back(func);
}

void Command::process_setup() {
  for (auto &func : this->setup_queue) {
    func();
  }

  this->setup_queue.clear();
}

void Command::process_update(double dt) const {
  for (auto &func : this->update_queue) {
    func(dt);
  }
}

void Command::process_display(Renderer *renderer) const {
  for (auto &func : this->rendering_queue) {
    func(renderer);
  }
}
