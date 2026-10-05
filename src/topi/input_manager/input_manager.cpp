#include "input_manager.hpp"
#include <stdexcept>

namespace topi::input {
  static InputManager* INSTANCE = nullptr;

  /**
   * @brief Permet d'accéder à l'instance globale de manière sécurisée.
   * @throw std::runtime_error l'instance est inaccessible.
   */
  InputManager* access_instance() {
    if (INSTANCE == nullptr) {
      throw std::runtime_error("The input manager should be instanciated before being accessed.");
    }

    return INSTANCE;
  }

  ////////////////////
  /// Wrapper code ///
  ////////////////////

  bool is_key_held(keycode::TopiKey keycode) {
    InputManager *instance = access_instance();
    return instance->is_key_held(keycode);
  }

  bool is_key_pressed(keycode::TopiKey keycode) {
    InputManager *instance = access_instance();
    return instance->is_key_pressed(keycode);
  }

  /////////////////////////
  /// InputManager code ///
  /////////////////////////

  InputManager::InputManager() {
    if (INSTANCE != nullptr)
      throw std::runtime_error("There should only be one instance of the input manager running.");

    SDL_PumpEvents();
    this->keyboard_state = SDL_GetKeyboardState(NULL);

    // On copie l'état clavier dans son buffer d'entrées précédentes.
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
      this->prev_keyboard_states[i] = this->keyboard_state[i];

    INSTANCE = this;
  }

  InputManager::~InputManager() {
    INSTANCE = nullptr;
  }

  void InputManager::update() {
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
      this->prev_keyboard_states[i] = this->keyboard_state[i];

    SDL_PumpEvents();
  }

  bool InputManager::is_key_held(keycode::TopiKey key_code) const {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key_code);
    return this->keyboard_state[scancode] != 0;
  }

  bool InputManager::is_key_pressed(keycode::TopiKey key_code) const {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key_code);
    return this->keyboard_state[scancode] && !this->prev_keyboard_states[scancode];
  }
}
