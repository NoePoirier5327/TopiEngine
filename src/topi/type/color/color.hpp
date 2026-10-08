#ifndef COLOR_HEADER
#define COLOR_HEADER

#include <SDL2/SDL.h>

namespace topi::type::color {
  /**
   * @brief Définit une couleur comme un triplet de
   * proportion de rouge, vert et une certaine transparence.
   */
  struct RGBAColor : SDL_Color {};

  // Couleurs préprogrammées

  const RGBAColor BLACK = {0, 0, 0, 255};
  const RGBAColor WHITE = {255, 255, 255, 255};
  const RGBAColor RED = {255, 0, 0, 255};
  const RGBAColor BLUE = {0, 0, 255, 255};
  const RGBAColor GREEN = {0, 255, 0, 255};
  const RGBAColor CYAN = {0, 255, 241, 255};
  const RGBAColor ORANGE = {251, 108, 38, 255};
  const RGBAColor YELLOW = {255, 255, 0, 255};
  const RGBAColor PINK = {232, 107, 255, 255};
}

#endif // !COLOR_HEADER
