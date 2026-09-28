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
     * @brief Fait descendre le tetromino courant vers le bas.
     */
    void fall();

    /**
     * @brief Transpose la matrice interne au tetromino courant.
     * contentT(i, j) = content(j, i)
     */
    void rotate();

    /**
     * @brief Bouge le tetromino courant vers la droite.
     * Vérifie si on peut se déplacer avant de réaliser le déplacement.
     */
    void move_right(topi::object::tilemap::ColoredTilemap *map);

    /**
     * @brief Bouge le tetromino courant vers la gauche.
     * Vérifie si on peut se déplacer avant le déplacement.
     */
    void move_left(topi::object::tilemap::ColoredTilemap *map);

  private:
    /**
     * @brief Vérifie dans la carte, que le tetromino peut continuer sa chute.
     */
    bool can_fall(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Vérifie si le tetromino courant va toucher le sol ou non.
     */
    bool has_reached_ground() const;

    /**
     * @brief Vérifie la collision vers le bas entre le tétromino courant et ceux en bas de lui sur la carte.
     * ATTENTION, il faut vérifier d'abord que le tetromino courant n'a pas atteint le sol avant d'appeler cette fonction.
     */
    bool has_reached_another_tetromino(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Détermine si le tetromino courant peut se déplacer vers la droite ou non.
     */
    bool can_move_right(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Vérifie qu'on n'entre pas en collision avec le mur de droite.
     */
    bool collides_with_right_wall() const;

    /**
     * @brief Vérifie qu'on entre pas en collision à droite avec un autre tetromino.
     * ATTENTION, on doit d'abord vérifier qu'on n'entre pas en collision avec le mur droit avant (pour éviter les out of range).
     */
    bool collides_with_another_tetromino_on_the_right(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Vérifie qu'on peut se déplacer vers la gauche.
     */
    bool can_move_left(topi::object::tilemap::ColoredTilemap *map) const;

    /**
     * @brief Vérifie si on entre en collision ou non avec le mur de gauche.
     */
    bool collides_with_left_wall() const;

    /**
     * @brief Vérifie si on entre en collision avec un autre tetromino sur la gauche.
     * ATTENTION, on doit d'abord vérifier qu'on n'entre pas en collision avec le mut gauche (pour éviter les out of range).
     */
    bool collides_with_another_tetromino_on_the_left(topi::object::tilemap::ColoredTilemap *map) const;

    TileType content[16];
    size_t size;
    topi::tools::vector::Vector2i *pos;
};

#endif // !TETROMINO_HEADER
