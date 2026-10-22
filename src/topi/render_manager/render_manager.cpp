#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <stdexcept>
#include "render_manager.hpp"
#include "renderable_items/rectangle/rectangle.hpp"
#include "renderable_items/text/text.hpp"
#include "renderable_items/line/line.hpp"
#include "renderable_items/triangle/triangle.hpp"

namespace topi::render {
  // Nombre d'instance du moteur de rendu tournant en mémoire.
  static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

  RenderManager::RenderManager(SDL_Window *window, resource::ResourceManager &resource_manager) : _resource_manager(resource_manager) {
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

    this->_line_thickness = 1;
    this->_color = topi::type::color::BLACK;
    this->_font_path = "";
    this->_font_size = 1;

    AN_INSTANCE_IS_ALREADY_RUNNING = true;
  }

  RenderManager::~RenderManager() {
    if (this->_renderer != nullptr) {
      SDL_DestroyRenderer(this->_renderer);
    }

    AN_INSTANCE_IS_ALREADY_RUNNING = false;
  }

  void RenderManager::display() {
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

  void RenderManager::set_draw_color(const topi::type::color::RGBAColor &color) {
    this->_color = color;
  }

  void RenderManager::set_line_thickness(size_t line_thickness) {
    this->_line_thickness = line_thickness;
  }

  void RenderManager::set_font(const std::string &font_path, size_t font_size) {
    this->_resource_manager.load_font(font_path, font_size);
    this->_font_path = font_path;
    this->_font_size = font_size;
  }

  void RenderManager::draw_colored_filled_rectangle(int x, int y, size_t w, size_t h) {
    // On s'épargne de l'allocation si un objet est inaffichable car complétement transparent.
    if (this->_color.a != 0) {
      this->_rendering_queue.push_back(std::make_unique<items::ColoredFilledRectangle>(x, y, w, h, this->_color));
    }
  }

  void RenderManager::draw_colored_rectangle(int x, int y, size_t w, size_t h) {
    if (this->_color.a == 0) return;
    this->_rendering_queue.push_back(std::make_unique<items::ColoredRectangle>(x, y, w, h, this->_line_thickness, this->_color));
  }

  void RenderManager::draw_text(const std::string &text, int x, int y) {
    if (this->_font_path.empty())
      throw std::runtime_error("No font loaded to display the text.");

    if (this->_color.a == 0) return;

    TTF_Font *font = this->_resource_manager.get_font(this->_font_path, this->_font_size);
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), this->_color);

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

  void RenderManager::draw_line(int x1, int y1, int x2, int y2) {
    if (this->_color.a == 0) return;
    this->_rendering_queue.push_back(std::make_unique<items::Line>(x1, y1, x2, y2, this->_line_thickness, this->_color));
  }

  void RenderManager::draw_colored_filled_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (this->_color.a == 0) return;
    this->_rendering_queue.push_back(std::make_unique<items::ColoredFilledTriangle>(x1, y1, x2, y2, x3, y3, this->_color));
  }
}
