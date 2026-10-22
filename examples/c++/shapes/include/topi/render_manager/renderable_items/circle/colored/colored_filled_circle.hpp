#ifndef COLORED_FILLED_CIRCLE_HEADER
#define COLORED_FILLED_CIRCLE_HEADER

#include "../../renderable_item.hpp"
#include "../../../../type/color/color.hpp"
#include <SDL2/SDL.h>

namespace topi::render::items {
  /**
   * @class ColoredFilledCircle
   * @brief Cercle coloré plein affichable par le moteur de rendu de topi.
   */
  class ColoredFilledCircle : public RenderableItem {
    public:
      /**
       * @brief Construit un cercle coloré plein.
       *
       * @param x, position en x du cercle à créer.
       * @param y, position en y du cercle à créer.
       * @param radius, rayon du cercle à créer.
       * @param color, couleur du cercle à créer.
       *
       * @throw std::runtime_error si radius < 0
       */
      ColoredFilledCircle(
        int x,
        int y,
        double radius,
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Interface générique pour l'affichage du cercle courant.
       *
       * @param renderer, fenêtre de rendu sdl2 sur laquelle afficher le cercle.
       * @throw std::runtime_error si renderer == nullptr
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      int _x, _y;
      double _radius;
      topi::type::color::RGBAColor _color;
  };
}

#endif // !COLORED_FILLED_CIRCLE_HEADER
