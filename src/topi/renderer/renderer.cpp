#include <SDL2/SDL_render.h>
#include <stdexcept>
#include "renderer.hpp"

// Nombre d'instance du moteur de rendu tournant en mémoire.
static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

Renderer::Renderer(SDL_Window *window) {
  if (window == nullptr) {
    throw std::invalid_argument("The given window should be instanciated to create renderer.");
  }

  if (AN_INSTANCE_IS_ALREADY_RUNNING) {
    throw std::runtime_error("There sould be only one instance of the renderer running.");
  }

  this->renderer = nullptr;
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!this->renderer) {
    std::string error = "Failed to create renderer.\n";
    error += SDL_GetError();

    throw std::runtime_error(error);
  }

  AN_INSTANCE_IS_ALREADY_RUNNING = true;
}

Renderer::~Renderer() {
  if (this->renderer != nullptr) {
    SDL_DestroyRenderer(this->renderer);
  }

  AN_INSTANCE_IS_ALREADY_RUNNING = false;
}

void Renderer::display() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
  SDL_RenderClear(this->renderer);

  SDL_RenderPresent(this->renderer);
}
