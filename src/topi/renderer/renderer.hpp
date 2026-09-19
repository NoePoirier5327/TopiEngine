#ifndef RENDERER_HEADER
#define RENDERER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

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

  private:
    SDL_Renderer *renderer;
};

#endif // !RENDERER_HEADER
