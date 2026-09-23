#include "input_manager.hpp"
#include <stdexcept>

static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

InputManager::InputManager() {
  if (AN_INSTANCE_IS_ALREADY_RUNNING)
    throw std::runtime_error("There should only be one instance of the input manager running.");

  SDL_PumpEvents();
  this->keyboard_state = SDL_GetKeyboardState(NULL);

  // On copie l'état clavier dans son buffer d'entrées précédentes.
  for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
    this->prev_keyboard_states[i] = this->keyboard_state[i];

  AN_INSTANCE_IS_ALREADY_RUNNING = true;
}

InputManager::~InputManager() {
  AN_INSTANCE_IS_ALREADY_RUNNING = false;
}

void InputManager::update() {
  for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
    this->prev_keyboard_states[i] = this->keyboard_state[i];

  SDL_PumpEvents();
}

bool InputManager::is_key_down(uint16_t key_code) const {
  SDL_Scancode scancode = SDL_GetScancodeFromKey(key_code);
  return this->keyboard_state[scancode] != 0;
}

bool InputManager::is_just_key_pressed(uint16_t key_code) const {
  SDL_Scancode scancode = SDL_GetScancodeFromKey(key_code);
  return this->keyboard_state[scancode] && !this->prev_keyboard_states[scancode];
}
