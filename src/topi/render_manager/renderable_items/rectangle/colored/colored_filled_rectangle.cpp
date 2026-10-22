#include "colored_filled_rectangle.hpp"

namespace topi::render::items {
  ColoredFilledRectangle::ColoredFilledRectangle(
    int x,
    int y,
    size_t w,
    size_t h,
    const topi::type::color::RGBAColor &color
  ) {
    this->_color = color;
    this->_rect = SDL_Rect {x, y, static_cast<int>(w), static_cast<int>(h) };
  }

  void ColoredFilledRectangle::display(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, this->_color.r, this->_color.g, this->_color.b, this->_color.a);
    SDL_RenderFillRect(renderer, &this->_rect);
  }
}
