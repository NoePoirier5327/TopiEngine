#include "input_manager.hpp"
#include <stdexcept>
#include <SDL2/SDL.h>

static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

InputManager::InputManager() {
  if (AN_INSTANCE_IS_ALREADY_RUNNING)
    throw std::runtime_error("There should only be one instance of the input manager running.");

  this->keyboard_state = SDL_GetKeyboardState(NULL);
  AN_INSTANCE_IS_ALREADY_RUNNING = true;
}

InputManager::~InputManager() {
  AN_INSTANCE_IS_ALREADY_RUNNING = false;
}

bool InputManager::is_key_down(uint16_t key_code) {
  SDL_Scancode scancode = SDL_GetScancodeFromKey(key_code);
  return this->keyboard_state[scancode] != 0;
}
