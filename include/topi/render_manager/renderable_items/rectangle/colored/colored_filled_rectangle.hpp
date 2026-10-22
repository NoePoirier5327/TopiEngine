#ifndef COLORED_FILLED_RECTANGLE_HEADER
#define COLORED_FILLED_RECTANGLE_HEADER

#include "../../renderable_item.hpp"
#include "../../../../type/color/color.hpp"
#include <cstdlib>

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
       * @param color, couleur au format rgba du rectangle à afficher.
       */
      ColoredFilledRectangle(
        int x,
        int y,
        size_t w,
        size_t h,
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Implémentation du ciblage de l'affichage pour l'objet courant (hérité de la classe parent).
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      topi::type::color::RGBAColor _color;
      SDL_Rect _rect;
  };
}

#endif // !COLORED_FILLED_RECTANGLE_HEADER
