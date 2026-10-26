#include "colored_filled_circle.hpp"
#include <stdexcept>
#include <cmath>

namespace topi::render::items {
  ColoredFilledCircle::ColoredFilledCircle(int x, int y, double radius, const topi::type::color::RGBAColor &color) {
    if (radius < 0)
      throw std::invalid_argument("A circle radius can't be negative.");

    this->_x = x;
    this->_y = y;
    this->_radius = radius;
    this->_color = color;
  }

  void ColoredFilledCircle::display(SDL_Renderer *renderer) const {
    if (renderer == nullptr)
      throw std::runtime_error("The sdl2 renderer is not initialized.");

    SDL_SetRenderDrawColor(renderer, this->_color.r, this->_color.g, this->_color.b, this->_color.a);

    int radius = static_cast<int>(this->_radius);
    for (double dy = 1.0; dy <= radius; ++dy) {
      int dx = static_cast<int>(floor(sqrt((2.0 * radius * dy) - (dy * dy))));
      int y_bottom = this->_y + static_cast<int>(dy) - radius;
      int y_top = this->_y - static_cast<int>(dy) + radius;

      SDL_RenderDrawLine(renderer, this->_x - dx, y_bottom, this->_x + dx, y_bottom);
      SDL_RenderDrawLine(renderer, this->_x -dx, y_top, this->_x + dx, y_top);
    }
  }
}
