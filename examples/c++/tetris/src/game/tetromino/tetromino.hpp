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
     * @brief Positionne le tetromino courant dans la carte en paramètre.
     *
     * Si il peut tomber, alors, on le met au premier plan.
     * Sinon, ajoute la méthode ajoute le tetromino courant à la couche finale de la carte.
     *
     * @return false si le tetromino a été insérer dans le plan finale de la carte, true sinon.
     */
    bool insert_in_map(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Vérifie dans la carte, que le tetromino peut continuer sa chute.
     */
    bool can_fall(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Fait descendre le tetromino courant vers le bas.
     */
    void fall();

  private:
    TileType content[16];
    size_t size;
    topi::tools::vector::Vector2i *pos;
};

#endif // !TETROMINO_HEADER
