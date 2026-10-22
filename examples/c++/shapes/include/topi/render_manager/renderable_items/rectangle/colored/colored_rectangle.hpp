#ifndef COLORED_RECTANGLE_HEADER
#define COLORED_RECTANGLE_HEADER

#include "../../renderable_item.hpp"
#include "../../../../type/color/color.hpp"
#include <cstdlib>

namespace topi::render::items {
  /**
   * @class ColoredRectangle
   * @brief Affiche un rectangle coloré mais pas plein.
   */
  class ColoredRectangle : public RenderableItem {
    public:
      /**
       * @brief Créer un nouveau rectangle coloré.
       *
       * @param x, position en x du nouveau rectangle.
       * @param y, position en y du nouveau rectangle.
       * @param w, largeur du nouveau rectangle.
       * @param h, hauteur du nouveau rectangle.
       * @param line_thickness, épaisseur des lignes composant le rectangle.
       * @param color, couleur au format rgba du rectangle à afficher.
       */
      ColoredRectangle(
        int x,
        int y,
        size_t w,
        size_t h,
        size_t line_thickness,
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Affiche le rectangle courant.
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      SDL_Rect _rect;
      topi::type::color::RGBAColor _color;
      size_t _line_thickness;
  };
}

#endif // !COLORED_RECTANGLE_HEADER
