#ifndef TOPI_HEADER
#define TOPI_HEADER

#include <SDL2/SDL.h>

/**
 * @class TopiEngine
 * @brief Instance static du jeu courant sous forme de singleton.
 */
class TopiEngine {
  public:
    /**
     * @brief Initialise l'instance de TopiEngine.
     *
     * Créer une fenêtre sdl2 dont l'écriture est régie par la classe renderer.
     * La taille, la position et le nom de la fenêtre sont en paramètre.
     *
     * Si une instance existe déjà, on la renvoie simplement.
     *
     * @param name, nom de la fenêtre sdl2 à afficher.
     * @param width, largeur de la fenêtre à instancier.
     * @param height, hauteur de la fenêtre à instancier.
     *
     * @return Référence vers l'instance interne initialisée.
     *
     * @throw std::runtime_error si erreur dans le chargement de la sdl2 et la création de sa fenêtre et ses composantes.
     */
    static TopiEngine& init(const char* name, int width, int height);

    /**
     * @brief Lance la logique de jeu représentée l'instance interne.
     * 
     * S'occupe de la boucle d'affichages, d'événements et de mise à jour de la logique.
     *
     * @throw std::runtime_error si l'instance interne n'est pas instanciée.
     */
    static void run();

    /**
     * @brief Accesseur de l'instance courante de TopiEngine.
     *
     * @throw std::runtime_error si l'instance sous-jacente n'est pas initialisée.
     */
    static TopiEngine& on_instance();

    /**
     * @brief Désalloue, si besoin, l'instance interne de TopiEngine ainsi que la sdl2.
     */
    static void destroy();

  private:
    SDL_Window *window;
};

#endif // !TOPI_HEADER
