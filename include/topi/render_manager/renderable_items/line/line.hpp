#ifndef LINE_HEADER
#define LINE_HEADER

#include "../renderable_item.hpp"
#include "../../../type/color/color.hpp"

namespace topi::render::items {
  /**
   * @class ColoredLine
   * @brief Dessine une ligne colorée avec une certaine épaisseur.
   */
  class Line : public RenderableItem {
    public:
      /**
       * @brief Créer une nouvelle ligne à afficher.
       *
       * @param x1, position en x du premier point caractérisant la ligne à afficher.
       * @param y1, position en y du premier point caractérisant la ligne à afficher.
       * @param x2, position en x du second point caractérisant la ligne à afficher.
       * @param y2, position en y du second point caractérisant la ligne à afficher.
       * @param thickness, épaisseur de la ligne à afficher.
       * @param color, couleur au format rgba de la ligne à afficher.
       */
      Line(
        int x1,
        int y1,
        int x2,
        int y2,
        size_t thickness,
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Affiche la ligne courante.
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      topi::type::color::RGBAColor _color;
      int _x1;
      int _x2;
      int _y1;
      int _y2;
      size_t _thickness;
  };
};

#endif // !LINE_HEADER
