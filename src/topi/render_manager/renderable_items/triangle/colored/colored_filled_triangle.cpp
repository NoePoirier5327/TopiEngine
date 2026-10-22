#include "colored_filled_triangle.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

namespace topi::render::items {
  ColoredFilledTriangle::ColoredFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const topi::type::color::RGBAColor &color) {
    this->_x1 = x1;
    this->_y1 = y1;
    this->_x2 = x2;
    this->_y2 = y2;
    this->_x3 = x3;
    this->_y3 = y3;
    this->_color = color;
  }

  void ColoredFilledTriangle::display(SDL_Renderer *renderer) const {
    if (renderer == nullptr)
      throw std::runtime_error("The sdl2 renderer is not initialized.");

    SDL_Vertex vertices[3] = {
      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x1), static_cast<float>(this->_y1)},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x2), static_cast<float>(this->_y2)},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x3), static_cast<float>(this->_y3)},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      }
    };

    const int indices[] = {0, 1, 2};
    SDL_RenderGeometry(renderer, nullptr, vertices, 3, indices, 3);
  }
}
