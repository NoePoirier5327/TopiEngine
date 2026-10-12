#ifndef TETROMINO_HEADER
#define TETROMINO_HEADER

#include <cstddef>
#include <topi/topi.hpp>
#include "../tileset/tileset.hpp"

/**
 * @brief Représente le type d'un tetromino.
 */
enum eTetroType : size_t {
  tetro_I,
  tetro_O,
  tetro_T,
  tetro_J,
  tetro_L,
  tetro_S,
  tetro_Z
};

/**
 * @class Tetromino
 * @brief Représente le comportement d'un tetromino dans le jeu.
 */
class Tetromino {
  public:
    /**
     * @brief Détermine aléatoirement le tetromino courant.
     * @param tetro_type, type du tetromino à créer.
     */
    Tetromino(eTetroType tetro_type);

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

    /**
     * @brief Renvoie le type du tetromino courant.
     */
    eTetroType get_type() const;

  private:
    TileType _content[16];
    size_t _size;
    int _pos_x;
    int _pos_y;
    eTetroType _tetro_type;
};

#endif // !TETROMINO_HEADER
