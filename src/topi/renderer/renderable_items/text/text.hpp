#ifndef TEXT_HEADER
#define TEXT_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdint>
#include "../renderable_item.hpp"

namespace topi::render::items {
  /**
   * @class Text
   * @brief Affiche du texte lorsqu'il est appelé par le moteur de rendu.
   */
  class Text : public RenderableItem {
    public:
      /**
       * @brief Instancie le texte à afficher par le moteur de rendu.
       *
       * @param text, texte à afficher sur la fenêtre de rendu.
       * @param font, police d'affichage du texte à afficher.
       * @param x, position en x du texte à afficher.
       * @param y, position en y du texte à afficher.
       * @param text_size, taille du texte à afficher.
       * @param r, taux de rouge du texte à afficher.
       * @param g, taux de vert du texte à afficher.
       * @param b, taux de bleu du texte à afficher.
       * @param a, taux de transparence du texte à afficher.
       */
      Text(
        const std::string &text,
        TTF_Font *font,
        int x,
        int y,
        size_t text_size,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
      );

      /**
       * @brief Interface d'affichage du texte.
       * @throw std::runtime_error si problème lors des créations des surfaces et textures de rendu.
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      SDL_Color color;
      int pos_x;
      int pos_y;
      TTF_Font *font;
      std::string to_display;
      size_t size;
  };
}

#endif // !TEXT_HEADER
