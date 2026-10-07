#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stdexcept>
#include "renderer.hpp"
#include "renderable_items/rectangle/rectangle.hpp"
#include "renderable_items/text/text.hpp"
#include "renderable_items/line/line.hpp"

namespace topi::render {
  // Nombre d'instance du moteur de rendu tournant en mémoire.
  static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

  Renderer::Renderer(SDL_Window *window, resource::ResourceManager &resource_manager) : _resource_manager(resource_manager) {
    if (window == nullptr) {
      throw std::invalid_argument("The given window should be instanciated to create renderer.");
    }

    if (AN_INSTANCE_IS_ALREADY_RUNNING) {
      throw std::runtime_error("There sould be only one instance of the renderer running.");
    }

    this->_renderer = nullptr;
    this->_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!this->_renderer) {
      std::string error = "Failed to create renderer.\n";
      error += SDL_GetError();

      throw std::runtime_error(error);
    }

    AN_INSTANCE_IS_ALREADY_RUNNING = true;
  }

  Renderer::~Renderer() {
    if (this->_renderer != nullptr) {
      SDL_DestroyRenderer(this->_renderer);
    }

    AN_INSTANCE_IS_ALREADY_RUNNING = false;
  }

  void Renderer::display() {
    // On néttoie l'écran.
    SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer);

    // On ajoute les objets à afficher au buffer vidéo.
    for (const std::unique_ptr<items::RenderableItem> &item : this->_rendering_queue) {
      item->display(this->_renderer);
    }

    this->_rendering_queue.clear();

    // On applique le buffer à l'écran.
    SDL_RenderPresent(this->_renderer);
  }

  void Renderer::draw_colored_filled_rectangle(int x, int y, size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    // On s'épargne de l'allocation si un objet est inaffichable car complétement transparent.
    if (a != 0) {
      this->_rendering_queue.push_back(std::make_unique<items::ColoredFilledRectangle>(x, y, w, h, r, g, b, a));
    }
  }

  void Renderer::draw_colored_rectangle(int x, int y, size_t w, size_t h, size_t line_thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (a == 0) return;
    this->_rendering_queue.push_back(std::make_unique<items::ColoredRectangle>(x, y, w, h, line_thickness, r, g, b, a));
  }

  void Renderer::draw_text(const std::string &text, const std::string &font_path, int x, int y, size_t font_size, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (a == 0) return;

    TTF_Font *font = this->_resource_manager.get_font(font_path, font_size);
    SDL_Color color = {r, g, b, a};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);

    if (!surface) {
      std::string error = "Failed to create the text surface.\n";
      error += TTF_GetError();
      throw std::runtime_error(error);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, surface);

    if (!texture) {
      SDL_FreeSurface(surface);

      std::string error = "Failed to transform the text surface into a texture.\n";
      error += SDL_GetError();
      throw std::runtime_error(error);
    }

    SDL_Rect dst = {x, y, surface->w, surface->h};

    this->_rendering_queue.push_back(std::make_unique<items::Text>(texture, dst));
  }

  void Renderer::draw_line(int x1, int y1, int x2, int y2, size_t thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (a == 0) return;

    this->_rendering_queue.push_back(std::make_unique<items::Line>(x1, y1, x2, y2, thickness, r, g, b, a));
  }
}
