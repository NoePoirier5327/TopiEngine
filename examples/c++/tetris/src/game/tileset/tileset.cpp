#include "tileset.hpp"

topi::object::tilemap::ColoredTilemap* new_map() {
  topi::object::tilemap::ColoredTilemap* map = new topi::object::tilemap::ColoredTilemap(10, 20, 3, 32, 32, false, true);

  map->new_tile(empty_tile, 20, 52, 100, 255);
  map->new_tile(transparent_tile, 0, 0, 0, 0);
  map->new_tile(tetro_tile_I, 32, 214, 199, 255);
  map->new_tile(tetro_tile_T, 255, 252, 64, 255);
  map->new_tile(tetro_tile_O, 188, 74, 155, 255);
  map->new_tile(tetro_tile_L, 250, 106, 10, 255);
  map->new_tile(tetro_tile_J, 40, 92, 196, 255);
  map->new_tile(tetro_tile_Z, 89, 193, 53, 255);
  map->new_tile(tetro_tile_S, 180, 32, 42, 255);

  // On initialise la carte
  for (size_t x = 0; x < 10; ++x) {
    for (size_t y = 0; y < 20; ++y) {
      (*map)(x, y, 0) = empty_tile;
      (*map)(x, y, 1) = transparent_tile;
      (*map)(x, y, 2) = transparent_tile;
    }
  }

  return map;
}
