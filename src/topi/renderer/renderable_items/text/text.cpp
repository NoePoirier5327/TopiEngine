#include "text.hpp"

namespace topi::render::items {
  Text::Text(SDL_Texture *text_texture, const SDL_Rect &text_position) {
    this->texture = text_texture;
    this->position = text_position;
  }

  void Text::display(SDL_Renderer *renderer) const {
    SDL_RenderCopy(renderer, this->texture, nullptr, &this->position);
    SDL_DestroyTexture(this->texture);
  }
}
