#ifndef RENDERER_HEADER
#define RENDERER_HEADER

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "renderable_items/renderable_item.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "../type/color/color.hpp"

namespace topi::render {
  /**
   * @class Renderer
   * @brief Gestionnaire de rendu pour le moteur de jeu.
   * Une seule instance peut tourner à la fois.
  */
  class RenderManager {
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
      RenderManager(SDL_Window* window, resource::ResourceManager &resource_manager);

      /**
       * @brief Désalloue l'instance courante.
       *
       * Repasse le nombre d'instance courante à 0 et désalloue le renderer SDL2 interne.
       */
      ~RenderManager();

      /**
       * @brief Se charge de rafraichir le buffer d'affichage sdl2 interne.
       *
       * Pour ça, néttoie l'écran, vide sa queue d'objets affichable en mettant à jour
       * le buffer de rendu sdl2 et les affiches.
       */
      void display();

      /**
       * @brief Change la couleur courante du moteur de rendu.
       *
       * @param color, couleur d'affichage du moteur.
       */
      void set_draw_color(
        const topi::type::color::RGBAColor &color
      );

      /**
       * @brief Change l'épaisseur des lignes affichable par le moteur.
       *
       * @param line_thickness, nouvelle épaisseur des lignes affichable par le moteur.
       */
      void set_line_thickness(
        size_t line_thickness
      );

      /**
       * @brief Charge la police d'écriture dans le moteur de rendu.
       *
       * Met la police d'écriture en paramètre comme courante
       * dans le moteur de rendue.
       *
       * @param font_path, chemin vers la police à charger.
       * @param font_size, taille de la police à charger.
       *
       * @throw std::runtime_error si impossible de charger la police en paramètre.
       */
      void set_font(
        const std::string &font_path,
        size_t font_size
      );

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
       */
      void draw_colored_filled_rectangle(
        int x,
        int y,
        size_t w,
        size_t h
      );

      /**
       * @brief Affiche un rectangle coloré pas plein.
       *
       * @param x, coordonnée en x du haut gauche du rectangle à afficher.
       * @param y, coordonnée en y du haut gauche du rectangle à afficher.
       * @param w, largeur du rectangle à afficher.
       * @param h, hauteur du rectangle à afficher.
       */
      void draw_colored_rectangle(
        int x,
        int y,
        size_t w,
        size_t h
      );

      /**
       * @brief Affiche le texte en paramètre sur l'écran courant.
       *
       * @param text, texte à afficher sur la fenêtre de rendu.
       * @param x, position en x du texte à afficher.
       * @param y, position en y du texte à afficher.
       *
       * @throw std::runtime_error si aucune police n'est chargée.
       * @throw std::runtime_error si impossible de charger la texture de rendu du texte.
       */
      void draw_text(
        const std::string &text,
        int x,
        int y
      );

      /**
       * @brief Affiche une ligne coloré d'une certaine épaisseur.
       *
       * @param x1, position en x du premier point de la ligne.
       * @param y1, position en y du premier point de la ligne.
       * @param x2, position en x du second point de la ligne.
       * @param y2, position en y du second point de la ligne.
       */
      void draw_line(
        int x1,
        int y1,
        int x2,
        int y2
      );

    private:
      SDL_Renderer *_renderer;
      resource::ResourceManager &_resource_manager;

      // On utilise unique_ptr pour des raisons de sécurité mémoire car désalloué automatiquement.
      // Et copie le caractère enfant des RenderableItems dans la file.
      std::vector<std::unique_ptr<items::RenderableItem>> _rendering_queue;

      // Paramètres d'affichage.
      size_t _line_thickness;
      topi::type::color::RGBAColor _color;
      std::string _font_path;
      size_t _font_size;
  };
}

#endif // !RENDERER_HEADER
