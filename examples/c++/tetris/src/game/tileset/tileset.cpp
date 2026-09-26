#include "tileset.hpp"

topi::object::tilemap::ColoredTilemap* new_map() {
  topi::object::tilemap::ColoredTilemap* map = new topi::object::tilemap::ColoredTilemap(MAP_WIDTH, MAP_HEIGHT, 3, 32, 32, false, true);

  map->new_tile(empty_tile, 27, 36, 71, 255);
  map->new_tile(transparent_tile, 0, 0, 0, 0);
  map->new_tile(tetro_tile_I, 0, 255, 241, 255);
  map->new_tile(tetro_tile_O, 255, 255, 0, 255);
  map->new_tile(tetro_tile_T, 232, 107, 255, 255);
  map->new_tile(tetro_tile_L, 251, 108, 38, 255);
  map->new_tile(tetro_tile_J, 0, 0, 255, 255);
  map->new_tile(tetro_tile_Z, 0, 255, 0, 255);
  map->new_tile(tetro_tile_S, 255, 0, 0, 255);

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
