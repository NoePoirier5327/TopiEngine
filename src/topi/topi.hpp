#ifndef TOPI_HEADER
#define TOPI_HEADER

#include <SDL2/SDL.h>
#include <functional>
#include "renderer/renderer.hpp"
#include "input_manager/input_manager.hpp"
#include "resource_manager/resource_manager.hpp"
#include "object/tilemap/tilemap.hpp"
#include "tools/tools.hpp"


namespace topi {
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
       * @throw std::runtime_error si erreur dans le chargement de la sdl2, la création de sa fenêtre et ses composantes.
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
       * @brief Permet d'exécuter du code à l'ouverture de l'application.
       */
      void setup(const std::function<void ()> &setup_handler);

      /**
       * @brief Permet d'exécuter du code de manière périodique en fonction du delta time.
       */
      void update(const std::function<void (double)> &update_handler);

      /**
       * @brief Permet d'exécuter du code à l'affichage de l'application.
       */
      void display(const std::function<void (render::Renderer *)> &display_handler);

      /**
       * @brief Accesseur de l'interface de gestions des ressources du moteur.
       */
      resource::ResourceManager& on_resource();

    private:
      SDL_Window *window;
      render::Renderer *renderer;
      input::InputManager input_manager;
      resource::ResourceManager resource_manager;

      std::function<void ()> setup_function;
      std::function<void (double)> update_function;
      std::function<void (render::Renderer *)> display_function;
  };
}

#endif // !TOPI_HEADER
