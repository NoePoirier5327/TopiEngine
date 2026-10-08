#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include "topi.hpp"

namespace topi {
  // Vérifie si une instance existe déjà en mémoire.
  static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

  TopiEngine::TopiEngine(const char *name, int width, int height) {
    // Démarrage de l'aléatoire sur le système.
    srand(static_cast<unsigned int>(time(nullptr)));

    if (AN_INSTANCE_IS_ALREADY_RUNNING) {
      throw std::runtime_error("There should be only as single instance of the engine running in memory.");
    }

    // On initialise la sdl2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      std::string error = "Failed to init SDL2.\n";
      error += SDL_GetError();
      throw std::runtime_error(error);
    }

    if (TTF_Init() < 0) {
      std::string error = "Failed to init the ttf sdl2 module.\n";
      error += TTF_GetError();
      throw std::runtime_error(error);
    }

    // On initialise la fenêtre.
    this->_window = nullptr;
    this->_window = SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width,
      height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
    );

    // On vérifie sa bonne initialisation.
    if (!this->_window) {
      // On quitte la sdl.
      SDL_Quit();

      std::string error = "Failed to open new SDL2 window.\n";
      error += SDL_GetError();
      throw std::runtime_error(error);
    }

    this->_render_manager = nullptr;

    // On instancie le renderer du moteur.
    try {
      this->_render_manager = new render::RenderManager(this->_window, this->_resource_manager);
    } 
    catch (std::runtime_error &e) {
      // On désalloue la fenêtre.
      SDL_DestroyWindow(this->_window);

      // On quitte la sdl.
      SDL_Quit();

      // On resignal l'erreur.
      throw std::runtime_error(e);
    }

    AN_INSTANCE_IS_ALREADY_RUNNING = true;
  }

  void TopiEngine::run() {
    bool run = true;
    SDL_Event event;

    // On exécute les commandes de mise en place du jeu.
    this->_setup_function();

    // Mise en place de la gestion du delta time.
    constexpr double TARGET_FPS = 60.0;
    constexpr double MAX_DT = 1.0 / TARGET_FPS;
    constexpr auto TARGET_FRAME_TIME = std::chrono::duration<double>(MAX_DT);
    
    auto last_tick = std::chrono::steady_clock::now();

    // Boucle de jeu
    while (run) {
      auto frame_start = std::chrono::steady_clock::now();

      // Gestion des évenements liés à la SDL.
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          run = false;
        }
      }

      // On calcul le delta time
      auto current_tick = std::chrono::steady_clock::now();
      std::chrono::duration<double> dt = current_tick - last_tick;
      last_tick = current_tick;

      // On clamp la valeur pour éviter les gros sauts.
      double dt_seconds = dt.count();
      if (dt_seconds > MAX_DT) {
        dt_seconds = MAX_DT;
      }

      // On exécute les commandes du moteur.
      this->_update_function(dt_seconds);
      this->_display_function(this->_render_manager);

      // On met à jour les buffers d'entrées utilisateur.
      this->_input_manager.update();

      // On refraichi l'affichage.
      this->_render_manager->display();

      // Si la frame courante s'est exécuté trop rapidement, on attend
      auto frame_duration = std::chrono::steady_clock::now() - frame_start;
      auto time_to_sleep = TARGET_FRAME_TIME - frame_duration;
      if (time_to_sleep.count() > 0.0) {
        std::this_thread::sleep_for(time_to_sleep);
      }
    }
  }

  TopiEngine::~TopiEngine() {
    if (this->_render_manager != nullptr) {
      delete this->_render_manager;
    }

    if (this->_window != nullptr) {
      SDL_DestroyWindow(this->_window);
    }

    this->_resource_manager.unload_everything();

    TTF_Quit();
    SDL_Quit();
    AN_INSTANCE_IS_ALREADY_RUNNING = false;
  }

  void TopiEngine::setup(const std::function<void ()> &setup_handler) {
    this->_setup_function = setup_handler;
  }

  void TopiEngine::update(const std::function<void (double)> &update_handler) {
    this->_update_function = update_handler;
  }

  void TopiEngine::display(const std::function<void (render::RenderManager *)> &display_handler) {
    this->_display_function = display_handler;
  }
}
