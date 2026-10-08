#ifndef LINE_HEADER
#define LINE_HEADER

#include "../renderable_item.hpp"
#include <cstdint>

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
       * @param r, taux de rouge de la ligne à afficher.
       * @param g, taux de vert de la ligne à afficher.
       * @param b, taux de bleu de la ligne à afficher.
       * @param a, taux de transparence de la ligne à afficher.
       */
      Line(
        int x1,
        int y1,
        int x2,
        int y2,
        size_t thickness,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
      );

      /**
       * @brief Affiche la ligne courante.
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      SDL_Color _color;
      int _x1;
      int _x2;
      int _y1;
      int _y2;
      size_t _thickness;
  };
};

#endif // !LINE_HEADER
