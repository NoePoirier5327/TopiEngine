#ifndef RENDERER_HEADER
#define RENDERER_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

/**
 * @class Renderer
 * @brief Instance static du gestionnaire d'affichage du moteur sous forme de singleton.
 */
class Renderer {
  public:
    /**
     * @brief Instancie, si possible, le singleton interne.
     *
     * Instancie le renderer sdl2 sous-jacent à partir de la fenêtre en paramètre.
     * Si une instance existe déjà, on la renvoie sans rien faire de plus.
     * 
     * @param window, fenêtre à partir de laquelle créer le renderer sdl2.
     *
     * @return Renvoie l'instance de renderer.
     *
     * @throw sdt::invalid_argument si window == nullptr.
     * @throw sdt::runtime_error si impossible de créer le renderer sdl2.
     */
    static Renderer& init(SDL_Window* window);

    /**
     * @brief Désalloue l'instance static global si elle existe.
     *
     * Désinstancie le renderer sdl2 sous jacent ainsi que toutes les
     * composantes internes qui ont besoin de l'être explicitement avant
     * de désallouer l'instance static interne.
     *
     * Si aucune instance à laquelle se rattacher, on ne fait rien.
     */
    static void destroy();

    /**
     * @brief Accesseur de l'instance interne du renderer.
     *
     * @throw std::runtime_error si aucune instance accessible (cad instancié).
     */
    static Renderer& on_instance();

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
