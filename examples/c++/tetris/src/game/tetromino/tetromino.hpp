#ifndef TETROMINO_HEADER
#define TETROMINO_HEADER

#include <topi/topi.hpp>
#include "../tileset/tileset.hpp"

/**
 * @class Tetromino
 * @brief Représente le comportement d'un tetromino dans le jeu.
 */
class Tetromino {
  public:
    /**
     * @brief Détermine aléatoirement le tetromino courant.
     */
    Tetromino();

    /**
     * @brief Fait descendre le tetromino courant vers le bas.
     */
    void fall();

    /**
     * @brief Transpose la matrice interne au tetromino courant.
     * Suppose qu'on peut effectuer une rotation.
     */
    void rotate();

    /**
     * @brief Bouge le tetromino courant vers la droite.
     * Suppose qu'on peut se déplacer vers la droite.
     */
    void move_right();

    /**
     * @brief Bouge le tetromino courant vers la gauche.
     * Suppose qu'on peut se déplacer vers la gauche.
     */
    void move_left();

    /**
     * @brief Renvoie la taille du tetromino courant.
     */
    size_t get_size() const;

    /**
     * @brief Renvoie la position en x du tetromino courant.
     */
    int get_pos_x() const;

    /**
     * @brief Renvoie la position en y du tetromino courant.
     */
    int get_pos_y() const;

    /**
     * @brief Accesseur en lecture de la matrice de contenu du tetromino.
     *
     * @throw std::out_of_range si x >= this->size || y >= this->size
     */
    TileType operator()(size_t x, size_t y) const;

  private:
    TileType content[16];
    size_t size;
    int pos_x;
    int pos_y;
};

#endif // !TETROMINO_HEADER
