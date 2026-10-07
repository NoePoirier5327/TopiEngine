#ifndef RENDERER_HEADER
#define RENDERER_HEADER

#include <SDL2/SDL.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "renderable_items/renderable_item.hpp"
#include "../resource_manager/resource_manager.hpp"

namespace topi::render {
  /**
   * @class Renderer
   * @brief Gestionnaire de rendu pour le moteur de jeu.
   * Une seule instance peut tourner à la fois.
  */
  class Renderer {
    public:
      /**
       * @brief Instancie un gestionnaire de rendu pour le moteur topi.
       *
       * Instancie le renderer sdl2 sous-jacent à partir de la fenêtre en paramètre.
       * 
       * @param window, fenêtre à partir de laquelle créer le renderer sdl2.
       * @param resource, référence vers le gestionnaire de ressource du moteur.
       *
       * @throw sdt::invalid_argument si window == nullptr.
       * @throw std::runtime_error si erreur lors de la création du renderer.
       * @throw std::runtime_error si une autre instance tourne.
       */
      Renderer(SDL_Window* window, resource::ResourceManager &resource_manager);

      /**
       * @brief Désalloue l'instance courante.
       *
       * Repasse le nombre d'instance courante à 0 et désalloue le renderer SDL2 interne.
       */
      ~Renderer();

      /**
       * @brief Se charge de rafraichir le buffer d'affichage sdl2 interne.
       *
       * Pour ça, néttoie l'écran, vide sa queue d'objets affichable en mettant à jour
       * le buffer de rendu sdl2 et les affiches.
       */
      void display();

      /**
       * @brief Affiche un nouveau rectangle plein coloré.
       *
       * Créer une nouvelle instance de ColoredFilledRectangle et l'ajoute à la file
       * d'objets à afficher.
       *
       * @param x, coordonnée en abcisse du haut gauche du rectangle à afficher.
       * @param y, coordonnée en ordonnée du haut gauche du rectangle à afficher.
       * @param w, largeur du rectangle à afficher.
       * @param h, hauteur du rectangle à afficher.
       * @param r, taux de rouge de la couleur du rectangle.
       * @param g, taux de vert de la couleur du rectangle.
       * @param a, taux de transparence du rectangle.
       */
      void draw_colored_filled_rectangle(
        int x,
        int y,
        size_t w,
        size_t h,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
      );

      /**
       * @brief Affiche un rectangle coloré pas plein.
       *
       * @param x, coordonnée en x du haut gauche du rectangle à afficher.
       * @param y, coordonnée en y du haut gauche du rectangle à afficher.
       * @param w, largeur du rectangle à afficher.
       * @param h, hauteur du rectangle à afficher.
       * @param line_thickness, épaisseur des lignes du rectangle à afficher.
       * @param r, taux de rouge du rectangle à afficher.
       * @param g, taux de vert du rectangle à afficher.
       * @param b, taux de bleu du rectangle à afficher.
       * @param a, taux de transparence du rectangle à afficher.
       */
      void draw_colored_rectangle(
        int x,
        int y,
        size_t w,
        size_t h,
        size_t line_thickness,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
      );

      /**
       * @brief Affiche le texte en paramètre sur l'écran courant.
       *
       * @param text, texte à afficher sur la fenêtre de rendu.
       * @param font_path, chemin vers la police du texte à afficher.
       * @param x, position en x du texte à afficher.
       * @param y, position en y du texte à afficher.
       * @param font_size, taille de la police du texte à afficher.
       * @param r, taux de rouge du texte à afficher.
       * @param g, taux de vert du texte à afficher.
       * @param b, taux de bleu du texte à afficher.
       * @param a, taux de transparence du texte à afficher.
       *
       * @throw std::runtime_error si font_id ne renvoie pas à une police chargée.
       * @throw std::runtime_error si impossible de charger la texture de rendu du texte.
       */
      void draw_text(
        const std::string &text,
        const std::string &font_path,
        int x,
        int y,
        size_t text_size,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
      );

      /**
       * @brief Affiche une ligne coloré d'une certaine épaisseur.
       *
       * @param x1, position en x du premier point de la ligne.
       * @param y1, position en y du premier point de la ligne.
       * @param x2, position en x du second point de la ligne.
       * @param y2, position en y du second point de la ligne.
       * @param thickness, épaisseur de la ligne à afficher.
       * @param r, taux de rouge de la ligne à afficher.
       * @param g, taux de vert de la ligne à afficher.
       * @param b, taux de bleu de la ligne à afficher.
       * @param a, taux de transparence de la ligne à afficher.
       */
      void draw_line(
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

    private:
      SDL_Renderer *_renderer;
      resource::ResourceManager &_resource_manager;

      // On utilise unique_ptr pour des raisons de sécurité mémoire car désalloué automatiquement.
      // Et copie le caractère enfant des RenderableItems dans la file.
      std::vector<std::unique_ptr<items::RenderableItem>> _rendering_queue;
  };
}

#endif // !RENDERER_HEADER
