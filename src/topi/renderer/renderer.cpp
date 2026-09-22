#include <SDL2/SDL_render.h>
#include <memory>
#include <stdexcept>
#include "renderer.hpp"
#include "renderable_items/rectangle/rectangle.hpp"
#include "renderable_items/renderable_item.hpp"

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
  // On néttoie l'écran.
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
  SDL_RenderClear(this->renderer);

  // On ajoute les objets à afficher au buffer vidéo.
  for (const std::unique_ptr<RenderableItem> &item : this->rendering_queue) {
    item->display(this->renderer);
  }

  // On applique le buffer à l'écran.
  SDL_RenderPresent(this->renderer);
}

void Renderer::new_colored_filled_rectangle(int x, int y, size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  this->rendering_queue.push_back(std::make_unique<ColoredFilledRectangle>(ColoredFilledRectangle(x, y, w, h, r, g, b, a)));
}
