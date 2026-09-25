#ifndef TILESET_HEADER
#define TILESET_HEADER

#include <cstdint>
#include <topi/topi.hpp>

/**
 * @brief Initialise et renvoie une nouvelle carte vide pour le jeu.
 */
topi::object::tilemap::ColoredTilemap* new_map();

/**
 * @brief Type de données réprésentant les tuiles de la tilemap du jeu.
 */
enum TileType : uint64_t {
  tetro_tile_I,
  tetro_tile_O,
  tetro_tile_T,
  tetro_tile_J,
  tetro_tile_L,
  tetro_tile_S,
  tetro_tile_Z,
  empty_tile,
  transparent_tile
};

#endif // !TILESET_HEADER
