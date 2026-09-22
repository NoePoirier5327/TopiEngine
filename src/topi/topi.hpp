#ifndef TOPI_HEADER
#define TOPI_HEADER

#include <SDL2/SDL.h>
#include "renderer/renderer.hpp"
#include "command/command.hpp"
#include "input_manager/input_manager.hpp"

/**
 * @class TopiEngine
 * @brief Instance du moteur de jeu.
 * Une seule instance peut fonctionner en mémoire.
 */
class TopiEngine {
  public:
    /**
     * @brief Initialise l'instance de TopiEngine.
     *
     * Créer une fenêtre sdl2 dont l'écriture est régie par la classe renderer.
     * La taille, la position et le nom de la fenêtre sont en paramètre.
     * Créer aussi l'instance du renderer du moteur.
     *
     * @param name, nom de la fenêtre sdl2 à afficher.
     * @param width, largeur de la fenêtre à instancier.
     * @param height, hauteur de la fenêtre à instancier.
     *
     * @throw std::runtime_error si une instance déjà existante en mémoire.
     * @throw std::runtime_error si erreur dans le chargement de la sdl2 et la création de sa fenêtre et ses composantes.
     * @throw std::runtime_error si erreur dans la création de l'instance du renderer.
     * @throw std::invalid_argument si erreur dans la création de l'instance du renderer.
     */
    TopiEngine(const char* name, int width, int height);

    /**
     * @brief Désalloue, si besoin, l'instance interne de TopiEngine ainsi que la sdl2.
     *
     * Désalloue aussi le renderer du moteur.
     */
    ~TopiEngine();

    /**
     * @brief Lance la logique de jeu représentée l'instance interne.
     * 
     * S'occupe de la boucle d'affichages, d'événements et de mise à jour de la logique.
     */
    void run();

    /**
     * @brief Accesseur de l'interface des commandes du moteur.
     */
    Command& on_command();

  private:
    SDL_Window *window;
    Renderer *renderer;
    Command command;
    InputManager input_manager;
};

#endif // !TOPI_HEADER
