#include "command_manager.hpp"
#include <stdexcept>

namespace topi::command {
  static bool ANOTHER_ISTANCE_IS_RUNNING = false;

  CommandManager::CommandManager() {
    if (ANOTHER_ISTANCE_IS_RUNNING) {
      throw std::runtime_error("There should be only one instance of the command processor running.");
    }

    ANOTHER_ISTANCE_IS_RUNNING = true;
  }

  CommandManager::~CommandManager() {
    ANOTHER_ISTANCE_IS_RUNNING = false;
  }

  void CommandManager::on_setup(const std::function<void ()> &func) {
    this->setup_queue.push_back(func);
  }

  void CommandManager::on_update(const std::function<void (double)> &func) {
    this->update_queue.push_back(func);
  }

  void CommandManager::on_input(const std::function<void (const input::InputManager &, double)> &func) {
    this->input_queue.push_back(func);
  }

  void CommandManager::on_display(const std::function<void (render::Renderer*)> &func) {
    this->rendering_queue.push_back(func);
  }

  void CommandManager::process_setup() {
    for (auto &func : this->setup_queue) {
      func();
    }

    this->setup_queue.clear();
  }

  void CommandManager::process_update(double dt) const {
    for (auto &func: this->update_queue) {
      func(dt);
    }
  }

  void CommandManager::process_input(const input::InputManager& input_manager, double dt) const {
    for (auto &func: this->input_queue) {
      func(input_manager, dt);
    }
  }

  void CommandManager::process_display(render::Renderer *renderer) const {
    for (auto &func : this->rendering_queue) {
      func(renderer);
    }
  }
}
