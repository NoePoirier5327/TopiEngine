#include "rectangle.hpp"

namespace topi::render::items {
  ColoredFilledRectangle::ColoredFilledRectangle(
    int x,
    int y,
    size_t w,
    size_t h,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a
  ) {
    this->sdl_color = SDL_Color {r, g, b, a};
    this->sdl_rect = SDL_Rect {x, y, static_cast<int>(w), static_cast<int>(h) };
  }

  void ColoredFilledRectangle::display(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, this->sdl_color.r, this->sdl_color.g, this->sdl_color.b, this->sdl_color.a);
    SDL_RenderFillRect(renderer, &this->sdl_rect);
  }


  ColoredRectangle::ColoredRectangle(int x, int y, size_t w, size_t h, size_t line_thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->_line_thickness = line_thickness;
    this->_rect = SDL_Rect {x, y, static_cast<int>(w), static_cast<int>(h)};
    this->_color = SDL_Color {r, g, b, a};
  }

  void ColoredRectangle::display(SDL_Renderer *renderer) const {
    Line(this->_rect.x - static_cast<int>(this->_line_thickness / 2), this->_rect.y, this->_rect.x + this->_rect.w + static_cast<int>(this->_line_thickness / 2), this->_rect.y, this->_line_thickness, this->_color.r, this->_color.g, this->_color.b, this->_color.a).display(renderer);

    Line(this->_rect.x + this->_rect.w, this->_rect.y, this->_rect.x + this->_rect.w, this->_rect.y + this->_rect.h, this->_line_thickness, this->_color.r, this->_color.g, this->_color.b, this->_color.a).display(renderer);

    Line(this->_rect.x, this->_rect.y, this->_rect.x, this->_rect.y + this->_rect.h, this->_line_thickness, this->_color.r, this->_color.g, this->_color.b, this->_color.a).display(renderer);

    Line(this->_rect.x - static_cast<int>(this->_line_thickness / 2), this->_rect.y + this->_rect.h, this->_rect.x + this->_rect.w + static_cast<int>(this->_line_thickness / 2), this->_rect.y + this->_rect.h, this->_line_thickness, this->_color.r, this->_color.g, this->_color.b, this->_color.a).display(renderer);
  }
}
