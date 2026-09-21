#ifndef RENDERER_HEADER
#define RENDERER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <memory>
#include <vector>
#include "renderable_items/renderable_item.hpp"

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
     *
     * @throw sdt::invalid_argument si window == nullptr.
     * @throw std::runtime_error si erreur lors de la création du renderer.
     * @throw std::runtime_error si une autre instance tourne.
     */
    Renderer(SDL_Window* window);

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
     * @brief Créer un nouveau rectangle plein coloré.
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
    void new_colored_filled_rectangle(
        int x,
        int y,
        size_t w,
        size_t h,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a
    );

  private:
    SDL_Renderer *renderer;

    // On utilise unique_ptr pour des raisons de sécurité mémoire car désalloué automatiquement.
    // Et copie le caractère enfant des RenderableItems dans la file.
    std::vector<std::unique_ptr<RenderableItem>> rendering_queue;
};

#endif // !RENDERER_HEADER
