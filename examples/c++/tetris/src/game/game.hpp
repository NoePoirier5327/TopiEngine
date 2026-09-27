#ifndef GAME_HEADER
#define GAME_HEADER

#include <topi/topi.hpp>
#include "tetromino/tetromino.hpp"

/**
 * @class Game
 * @brief Classe gérant la logique de jeu.
 */
class Game {
  public:
    /**
     * @brief Instancie et démarre la logique d'une partie du jeu.
     */
    Game();

    /**
     * @brief Désalloue la carte du jeu.
     */
    ~Game();

    /**
     * @brief Gère les entrées claviers du joueur.
     */
    void handle_inputs(const topi::input::InputManager &input_manager);

    /**
     * @brief Met à jour la logique du jeu courant.
     */
    void update();

    /**
     * @brief Met à jour l'affichage du jeu.
     */
    void display(topi::render::Renderer *renderer) const;

  private:
    topi::object::tilemap::ColoredTilemap *map;
    Tetromino *tetromino;
    topi::tools::time::Timer *falling_timer;
    double time_to_fall;
};

#endif // !GAME_HEADER
