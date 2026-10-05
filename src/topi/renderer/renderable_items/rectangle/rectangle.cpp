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
    this->thickness = line_thickness;
    this->rect = SDL_Rect {x, y, static_cast<int>(w), static_cast<int>(h)};
    this->color = SDL_Color {r, g, b, a};
  }

  void ColoredRectangle::display(SDL_Renderer *renderer) const {
    Line(this->rect.x - static_cast<int>(this->thickness / 2), this->rect.y, this->rect.x + this->rect.w + static_cast<int>(this->thickness / 2), this->rect.y, this->thickness, this->color.r, this->color.g, this->color.b, this->color.a).display(renderer);

    Line(this->rect.x + this->rect.w, this->rect.y, this->rect.x + this->rect.w, this->rect.y + this->rect.h, this->thickness, this->color.r, this->color.g, this->color.b, this->color.a).display(renderer);

    Line(this->rect.x, this->rect.y, this->rect.x, this->rect.y + this->rect.h, this->thickness, this->color.r, this->color.g, this->color.b, this->color.a).display(renderer);

    Line(this->rect.x - static_cast<int>(this->thickness / 2), this->rect.y + this->rect.h, this->rect.x + this->rect.w + static_cast<int>(this->thickness / 2), this->rect.y + this->rect.h, this->thickness, this->color.r, this->color.g, this->color.b, this->color.a).display(renderer);
  }
}
