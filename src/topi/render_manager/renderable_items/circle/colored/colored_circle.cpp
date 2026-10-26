#include "colored_circle.hpp"
#include <stdexcept>
#include <cmath>

namespace topi::render::items {
  ColoredCircle::ColoredCircle(int x, int y, double radius, size_t line_thickness, const type::color::RGBAColor &color) {
    if (radius < 0)
      throw std::invalid_argument("A circle radius can't be negative.");

    this->_x = x;
    this->_y = y;
    this->_radius = radius;
    this->_line_thickness = line_thickness;
    this->_color = color;
  }

  void ColoredCircle::display(SDL_Renderer *renderer) const {
    if (renderer == nullptr)
      throw std::runtime_error("The sdl2 renderer is not initialized.");

    SDL_SetRenderDrawColor(renderer, this->_color.r, this->_color.g, this->_color.b, this->_color.a);

    const int radius = static_cast<int>(this->_radius);
    const int thickness = static_cast<int>(this->_line_thickness);
    const int innerRadius = std::max(0, radius - thickness);

    const int r2 = radius * radius;
    const int innerR2 = innerRadius * innerRadius;

    for (int y = -radius; y <= radius; ++y) {
      for (int x = -radius; x <= radius; ++x) {
        const int d2 = x * x + y * y;
        if (d2 <= r2 && d2 >= innerR2) {
          SDL_RenderDrawPoint(renderer, this->_x + x, this->_y + y);
        }
      }
    }
  }
}
