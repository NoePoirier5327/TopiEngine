#include "text.hpp"
#include <stdexcept>

namespace topi::render::items {
  Text::Text(const std::string &text, TTF_Font *_font, int x, int y, double text_size, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (text_size < 0) {
      throw std::invalid_argument("The text size should'nt be negative.");
    }

    this->color = SDL_Color {r, g, b, a};
    this->font = _font;
    this->pos_x = x;
    this->pos_y = y;
    this->size = text_size;
    this->to_display = text;
  }

  void Text::display(SDL_Renderer *renderer) const {
    SDL_Surface *surface = TTF_RenderText_Blended(this->font, this->to_display.c_str(), this->color);

    if (!surface) {
      std::string error = "Failed to create the text surface.\n";
      error += TTF_GetError();
      throw std::runtime_error(error);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) {
      SDL_FreeSurface(surface);

      std::string error = "Failed to transform the text surface into a texture.\n";
      error += SDL_GetError();
      throw std::runtime_error(error);
    }

    SDL_Rect dst = SDL_Rect{this->pos_x, this->pos_y, static_cast<int>(static_cast<double>(surface->w) * this->size), static_cast<int>(static_cast<double>(surface->h) * this->size)};

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
  }
}
