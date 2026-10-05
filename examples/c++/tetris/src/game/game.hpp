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
    void handle_inputs();

    /**
     * @brief Met à jour la logique du jeu courant.
     */
    void update();

    /**
     * @brief Met à jour l'affichage du jeu.
     */
    void display(topi::render::Renderer *renderer) const;

    /**
     * @brief Vérifie si le joueur a perdu.
     */
    bool game_is_over() const;

  private:
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

    /**
     * @brief Vérifie que le tetromino peut continuer de descendre dans la carte.
     */
    bool tetromino_can_fall() const;

    /**
     * @brief Fait descendre le tetromino au plus bas possible.
     */
    void tetromino_hard_drop();

    /**
     * @brief Fait descendre le tetromino plus rapidement qu'à l'ordinaire.
     */
    void tetromino_fast_fall() const;

    /**
     * @brief Vérifie que le tetromino courant peut se déplacer vers la droite.
     */
    bool tetromino_can_move_right() const;

    /**
     * @brief Vérifie que le tetromino courant peut se déplacer vers la gauche.
     */
    bool tetromino_can_move_left() const;

    /**
     * @brief Vérifie que le tetromino courant peut effectuer une rotation.
     */
    bool tetromino_can_rotate() const;

    /**
     * @brief Appeler à la destruction du tetromino, l'insert dans la carte de manière permanente.
     */
    void tetromino_insert_in_final_map_layer() const;

    /**
     * @brief Insert le tetromino courant dans la carte.
     */
    void tetromino_insert_in_current_map_layer() const;

    /**
     * @brief Détermine le score et le niveau qui dépend de lui à un moment donné.
     * Attribut aussi la vitesse de chute en fonction du niveau.
     */
    void attribute_score_and_level(uint64_t score_to_attribute);

    topi::object::tilemap::ColoredTilemap *map;
    Tetromino *tetromino;
    topi::tools::time::Timer *falling_timer;
    topi::tools::time::Timer *fast_fall_timer;
    topi::tools::time::Timer *insert_timer;
    uint64_t time_to_fall;
    uint64_t time_before_insertion;
    uint64_t score;
    uint8_t level;
    bool game_over;
};

#endif // !GAME_HEADER
