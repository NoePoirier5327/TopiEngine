#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

#include "../renderable_item.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>

namespace topi::render::items {
  /**
   * @class ColoredFilledRectangle
   * @brief Rectangle plein affichable par le moteur de jeu.
   */
  class ColoredFilledRectangle : public RenderableItem {
    public:
      /**
       * @brief Construit un rectangle coloré plein.
       *
       * Instancie un rectangle coloré, affichable par le moteur topi.
       * Sa position en paramètre correspond au coin haut gauche du rectangle.
       * Le type de couleur utilisé est RGB avec un taux de transparence.
       *
       * @param x, position en x du nouveau rectangle.
       * @param y, position en y du nouveau rectangle.
       * @param w, largeur du nouveau rectangle.
       * @param h, hauteur du nouveau rectangle.
       * @param r, taux de rouge du nouveau rectangle.
       * @param g, taux de vert du nouveau rectangle.
       * @param b, taux de bleu du nouveau rectangle.
       * @param a, taux de transparence du nouveau rectangle.
       */
      ColoredFilledRectangle(
        int x,
        int y,
        size_t w,
        size_t h,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
      );

      /**
       * @brief Implémentation du ciblage de l'affichage pour l'objet courant (hérité de la classe parent).
       */
      void display(SDL_Renderer *renderer) const override;

      /**
       * @brief Accesseur, au format sdl2, de la forme du rectangle.
       */
      SDL_Rect get_sdl_rect() const;

      /**
       * @brief Accesseur, au format sdl2, de la couleur du rectangle.
       */
      SDL_Color get_sdl_color() const;

    private:
      SDL_Color sdl_color;
      SDL_Rect sdl_rect;
  };
}

#endif // !RECTANGLE_HEADER
