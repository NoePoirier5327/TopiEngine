#include <SDL2/SDL_render.h>
#include <stdexcept>
#include "renderer.hpp"

// Instance de référence pour la classe Renderer.
static Renderer* INSTANCE = nullptr;

Renderer& Renderer::init(SDL_Window *window) {
  if (window == nullptr) {
    throw std::invalid_argument("The given window should be instanciated to create renderer.");
  }

  if (INSTANCE == nullptr) {
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
      std::string error = "Failed to create renderer.\n";
      error += SDL_GetError();

      throw std::runtime_error(error);
    }

    INSTANCE = new Renderer;
    INSTANCE->renderer = renderer;
  }

  return *INSTANCE;
}

void Renderer::destroy() {
  if (INSTANCE != nullptr) {
    SDL_DestroyRenderer(INSTANCE->renderer);
    delete INSTANCE;
    INSTANCE = nullptr;
  }
}
