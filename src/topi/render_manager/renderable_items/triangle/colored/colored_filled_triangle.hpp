#ifndef COLORED_FILLED_TRIANGLE_HEADER
#define COLORED_FILLED_TRIANGLE_HEADER

#include "../../../../type/color/color.hpp"
#include "../../renderable_item.hpp"

namespace topi::render::items {
  /**
   * @class ColoredFilledTriangle
   * @brief Affiche un triangle coloré plein.
   */
  class ColoredFilledTriangle : public RenderableItem {
    public:
      /**
       * @brief Construit le triangle à afficher.
       *
       * @param x1, coordonnée en x du premier point du triangle.
       * @param y1, coordonnée en y du premier point du triangle.
       * @param x2, coordonnée en x du second point du triangle.
       * @param y2, coordonnée en y du second point du triangle.
       * @param x3, coordonnée en x du troisième point du triangle.
       * @param y3, coordonnée en y du troisième point du triangle.
       * @param color, couleur de remplissage du nouveau triangle.
       */
      ColoredFilledTriangle(
        int x1,
        int y1,
        int x2,
        int y2,
        int x3,
        int y3,
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Interface d'affichage générique du triangle courant.
       *
       * @param renderer, fenêtre sur laquelle afficher le triangle.
       * @throw std::runtime_error si renderer == nullptr.
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      int _x1, _x2, _x3;
      int _y1, _y2, _y3;
      topi::type::color::RGBAColor _color;
  };
}

#endif // !COLORED_FILLED_TRIANGLE_HEADER
