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
     * @brief Désalloue le tetromino courant.
     */
    ~Tetromino();

    /**
     * @brief Positionne le tetromino courant dans la carte en paramètre à sa couche dédiée (couche 2).
     */
    void insert_in_map(topi::object::tilemap::ColoredTilemap *map) const;

  private:
    TileType content[16];
    size_t size;
    topi::tools::vector::Vector2i *pos;
};

#endif // !TETROMINO_HEADER
