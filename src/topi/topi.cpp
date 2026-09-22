#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <chrono>
#include "topi.hpp"

using Clock = std::chrono::high_resolution_clock;

// Vérifie si une instance existe déjà en mémoire.
static bool AN_INSTANCE_IS_ALREADY_RUNNING = false;

TopiEngine::TopiEngine(const char *name, int width, int height) {
  if (AN_INSTANCE_IS_ALREADY_RUNNING) {
    throw std::runtime_error("There should be only as single instance of the engine running in memory.");
  }

  // On initialise la sdl2
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::string error = "Failed to init SDL2.\n";
    error += SDL_GetError();
    throw std::runtime_error(error);
  }

  // On initialise la fenêtre.
  this->window = nullptr;
  this->window = SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width,
      height,
      SDL_WINDOW_SHOWN
  );

  // On vérifie sa bonne initialisation.
  if (!this->window) {
    // On quitte la sdl.
    SDL_Quit();

    std::string error = "Failed to open new SDL2 window.\n";
    error += SDL_GetError();
    throw std::runtime_error(error);
  }

  this->renderer = nullptr;

  // On instancie le renderer du moteur.
  try {
    this->renderer = new Renderer(this->window);
  } 
  catch (std::runtime_error &e) {
    // On désalloue la fenêtre.
    SDL_DestroyWindow(window);

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
  this->command_manager.process_setup();

  // Mise en place de la gestion du delta time.
  double max_dt = 1.0 / 60.0; // 60 fps
  auto last_tick = Clock::now();

  // Boucle de jeu
  while (run) {
    // Gestion des évenements liés à la SDL.
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        run = false;
      }
    }

    // On calcul le delta time
    auto current_tick = Clock::now();
    double dt = (static_cast<std::chrono::duration<double>>(current_tick - last_tick)).count();
    last_tick = current_tick;
    dt = std::min(dt, max_dt); // qu'on cape à 1/60

    // On exécute les commandes du moteur.
    this->command_manager.process_input(this->input_manager, dt);
    this->command_manager.process_update(dt);
    this->command_manager.process_display(this->renderer);

    // On refraichi l'affichage.
    this->renderer->display();
  }
}

TopiEngine::~TopiEngine() {
  if (this->renderer != nullptr) {
    delete this->renderer;
  }

  if (this->window != nullptr) {
    SDL_DestroyWindow(this->window);
  }

  SDL_Quit();
  AN_INSTANCE_IS_ALREADY_RUNNING = false;
}

CommandManager& TopiEngine::on_command() {
  return this->command_manager;
}
