#ifndef TEXT_HEADER
#define TEXT_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
       * @param text_texture, texte à afficher sur la fenêtre de rendu.
       * @param text_position, position du texte à afficher.
       */
      Text(
        SDL_Texture *text_texture,
        const SDL_Rect &text_position
      );

      /**
       * @brief Interface d'affichage du texte.
       */
      void display(SDL_Renderer *renderer) const override;

    private:
      SDL_Texture *texture;
      SDL_Rect position;
  };
}

#endif // !TEXT_HEADER
