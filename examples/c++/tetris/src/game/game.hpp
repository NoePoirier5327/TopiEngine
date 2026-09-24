#ifndef GAME_HEADER
#define GAME_HEADER

#include <topi/topi.hpp>

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
     * @brief Met à jour la logique du jeu courant.
     */
    void update();

    /**
     * @brief Met à jour l'affichage du jeu.
     */
    void display(Renderer *renderer) const;

  private:
    ColoredTilemap *map;
};

#endif // !GAME_HEADER
