#ifndef GAME_HEADER
#define GAME_HEADER

#include <cstdint>
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
    /**
     * @brief Détermine et renvoie le nombre de ligne pleine dans la carte du jeu.
     */
    size_t get_nb_full_line() const;

    /**
     * @brief Renvoie l'index de la première ligne pleine dans la carte du jeu.
     * Renvoie -1 sinon.
     */
    int get_full_line_index() const;

    /**
     * @brief Détruis, dans la carte du jeu, la ligne dont l'index est en paramètre.
     * 
     * Pour effectuer la destruction, rempli la ligne concernée de tuiles transparentes
     * et la remonte tout en haut de la carte.
     *
     * @param line_index, index de la ligne à détruire.
     */
    void destroy_line(size_t line_index);

    topi::object::tilemap::ColoredTilemap *map;
    Tetromino *tetromino;
    topi::tools::time::Timer *falling_timer;
    topi::tools::time::Timer *soft_drop_timer;
    uint64_t time_to_fall;
};

#endif // !GAME_HEADER
