#ifndef COLORED_TRIANGLE_HEADER
#define COLORED_TRIANGLE_HEADER

#include "../../renderable_item.hpp"
#include "../../../../type/color/color.hpp"
#include <SDL2/SDL.h>

namespace topi::render::items {
  /**
   * @class ColoredTriangle
   * @brief Triangle colorée non plein affichable via le moteur de rendu de topi.
   */
  class ColoredTriangle : public RenderableItem {
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
       * @param line_thickness, épaisseur de la ligne du triangle non plein.
       * @param color, couleur de remplissage du nouveau triangle.
       */
      ColoredTriangle(
        int x1,
        int y1,
        int x2,
        int y2,
        int x3,
        int y3,
        size_t line_thickness,
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Interface d'affichage générique du triangle.
       *
       * @param renderer, fenêtre de rendu sur laquelle afficher le triangle courant.
       * @throw std::runtime_error si renderer == nullptr
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      int _x1, _x2, _x3;
      int _y1, _y2, _y3;
      topi::type::color::RGBAColor _color;
      size_t _line_thickness;
  };
}

#endif // !COLORED_TRIANGLE_HEADER
