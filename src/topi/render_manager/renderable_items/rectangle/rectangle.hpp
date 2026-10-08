#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

#include "../renderable_item.hpp"
#include "../../../type/color/color.hpp"
#include <SDL2/SDL.h>
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

#endif // !RECTANGLE_HEADER
