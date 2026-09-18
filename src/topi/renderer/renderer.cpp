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

Renderer& Renderer::on_instance() {
  if (INSTANCE == nullptr)
    throw std::runtime_error("You should instanciate the renderer in order to access it.");
  return *INSTANCE;
}

void Renderer::display() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
  SDL_RenderClear(this->renderer);

  SDL_RenderPresent(this->renderer);
}
