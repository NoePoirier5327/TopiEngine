#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <stdexcept>
#include <string>
#include "renderer/renderer.hpp"
#include "topi.hpp"

// Instance de référence pour la classe TopiEngine.
static TopiEngine* INSTANCE = nullptr;

TopiEngine& TopiEngine::init(const char *name, int width, int height) {
  // Si ce n'est pas déjà le cas, on alloue l'instance sous-jacente.
  if (INSTANCE == nullptr) {
    // On initialise la sdl2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      std::string error = "Failed to init SDL2.\n";
      error += SDL_GetError();
      throw std::runtime_error(error);
    }

    // On initialise la fenêtre.
    SDL_Window *window = nullptr;
    window = SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width,
      height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    // On vérifie sa bonne initialisation.
    if (!window) {
      // On quitte la sdl.
      SDL_Quit();

      std::string error = "Failed to open new SDL2 window.\n";
      error += SDL_GetError();
      throw std::runtime_error(error);
    }

    // On instancie le renderer du moteur.
    try {
      Renderer::init(window);
    } 
    catch (std::runtime_error &e) {
      // On désalloue la fenêtre.
      SDL_DestroyWindow(window);

      // On quitte la sdl.
      SDL_Quit();

      // On resignal l'erreur.
      throw std::runtime_error(e);
    }

    // On instancie le singleton.
    INSTANCE = new TopiEngine;

    // On renvoie la propriétée de la fenêtre à l'instance sous-jacente.
    INSTANCE->window = window;
  }

  // On renvoie l'instance
  return *INSTANCE;
}

void TopiEngine::run() {
  if (INSTANCE == nullptr) {
    throw std::runtime_error("You should instanciate the topi engine before trying to run the game.");
  }

  bool run = true;
  SDL_Event event;

  while (run) {
    // Gestion des évenements liés à la SDL.
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        run = false;
      }
    }

    // On refraichi l'affichage.
    Renderer::on_instance().display();
  }
}

TopiEngine& TopiEngine::on_instance() {
  if (INSTANCE == nullptr) {
    throw std::runtime_error("You should instanciate the topi engine before trying to access it.");
  }

  return *INSTANCE;
}

void TopiEngine::destroy() {
  if (INSTANCE != nullptr) {
    // On désalloue la fenêtre.
    SDL_DestroyWindow(INSTANCE->window);

    // le renderer.
    Renderer::destroy();

    // et enfin la sdl.
    SDL_Quit();

    // Puis l'instance interne.
    delete INSTANCE;
    INSTANCE = nullptr;
  }
}
