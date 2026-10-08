#include "text.hpp"

namespace topi::render::items {
  Text::Text(SDL_Texture *text_texture, const SDL_Rect &text_position) {
    this->_text_texture = text_texture;
    this->_text_position = text_position;
  }

  void Text::display(SDL_Renderer *renderer) const {
    SDL_RenderCopy(renderer, this->_text_texture, nullptr, &this->_text_position);
    SDL_DestroyTexture(this->_text_texture);
  }
}
