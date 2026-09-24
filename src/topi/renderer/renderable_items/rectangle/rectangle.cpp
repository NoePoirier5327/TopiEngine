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

  SDL_Rect ColoredFilledRectangle::get_sdl_rect() const {
    return this->sdl_rect;
  }

  SDL_Color ColoredFilledRectangle::get_sdl_color() const {
    return this->sdl_color;
  }
}
