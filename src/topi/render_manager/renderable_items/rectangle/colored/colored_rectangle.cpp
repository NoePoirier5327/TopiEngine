#include "../../line/line.hpp"
#include "colored_rectangle.hpp"

namespace topi::render::items {
  ColoredRectangle::ColoredRectangle(int x, int y, size_t w, size_t h, size_t line_thickness, const topi::type::color::RGBAColor &color) {
    this->_line_thickness = line_thickness;
    this->_rect = SDL_Rect {x, y, static_cast<int>(w), static_cast<int>(h)};
    this->_color = color;
  }

  void ColoredRectangle::display(SDL_Renderer *renderer) const {
    Line(this->_rect.x - static_cast<int>(this->_line_thickness / 2), this->_rect.y, this->_rect.x + this->_rect.w + static_cast<int>(this->_line_thickness / 2), this->_rect.y, this->_line_thickness, this->_color).display(renderer);

    Line(this->_rect.x + this->_rect.w, this->_rect.y, this->_rect.x + this->_rect.w, this->_rect.y + this->_rect.h, this->_line_thickness, this->_color).display(renderer);

    Line(this->_rect.x, this->_rect.y, this->_rect.x, this->_rect.y + this->_rect.h, this->_line_thickness, this->_color).display(renderer);

    Line(this->_rect.x - static_cast<int>(this->_line_thickness / 2), this->_rect.y + this->_rect.h, this->_rect.x + this->_rect.w + static_cast<int>(this->_line_thickness / 2), this->_rect.y + this->_rect.h, this->_line_thickness, this->_color).display(renderer);
  }
}
