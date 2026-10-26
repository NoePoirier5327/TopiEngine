#ifndef COLORED_CIRCLE_HEADER
#define COLORED_CIRCLE_HEADER

#include "../../renderable_item.hpp"
#include "../../../../type/color/color.hpp"
#include <SDL2/SDL.h>

namespace topi::render::items {
  /**
   * @class ColoredCircle
   * @brief Affiche un cercle coloré avec une certaine épaisseur de ligne.
   */
  class ColoredCircle : public RenderableItem {
    public:
      /**
       * @brief Construit un cercle coloré.
       *
       * @param x, position en x du centre du cercle à créer.
       * @param y, position en y du centre du cercle à créer.
       * @param radius, rayon du nouveau cercle.
       * @param line_thickness, épaisseur du cercle à créer.
       * @param color, couleur du nouveau cercle.
       *
       * @throw std::invalid_argument si radius < 0
       */
      ColoredCircle(
        int x,
        int y,
        double radius,
        size_t line_thickness,
        const type::color::RGBAColor &color
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
      size_t _line_thickness;
      type::color::RGBAColor _color;
  };
}

#endif // !COLORED_CIRCLE_HEADER
