#include "tetromino.hpp"

const TileType TETROMINOS[65] = {
  // I
  transparent_tile, tetro_tile_I, transparent_tile, transparent_tile,
  transparent_tile, tetro_tile_I, transparent_tile, transparent_tile,
  transparent_tile, tetro_tile_I, transparent_tile, transparent_tile,
  transparent_tile, tetro_tile_I, transparent_tile, transparent_tile,

  // O
  tetro_tile_O, tetro_tile_O,
  tetro_tile_O, tetro_tile_O,

  // T
  tetro_tile_T,     tetro_tile_T,     tetro_tile_T,
  transparent_tile, tetro_tile_T,     transparent_tile,
  transparent_tile, transparent_tile, transparent_tile,

  // J
  transparent_tile, transparent_tile, tetro_tile_J,
  transparent_tile, transparent_tile, tetro_tile_J,
  transparent_tile, tetro_tile_J,     tetro_tile_J,

  // L
  tetro_tile_L, transparent_tile, transparent_tile,
  tetro_tile_L, transparent_tile, transparent_tile,
  tetro_tile_L, tetro_tile_L,     transparent_tile,

  // S
  transparent_tile, tetro_tile_S, tetro_tile_S,
  tetro_tile_S, tetro_tile_S, transparent_tile,
  transparent_tile, transparent_tile, transparent_tile,

  // Z
  tetro_tile_Z,     tetro_tile_Z,     transparent_tile,
  transparent_tile, tetro_tile_Z,     tetro_tile_Z,
  transparent_tile, transparent_tile, transparent_tile,
};

const size_t TETROMINOS_SIZE[7] = {4, 2, 3, 3, 3, 3, 3};


Tetromino::Tetromino() {
  uint64_t tetro_type = static_cast<uint64_t>(topi::tools::random::randrange(0, 6));
  this->size = TETROMINOS_SIZE[tetro_type];

  // On calcul la position du tetromino à récupérer dans la matrice les décrivants.
  size_t offset = 0;
  for (size_t i = 0; i < tetro_type; ++i)
    offset += TETROMINOS_SIZE[i] * TETROMINOS_SIZE[i];

  // On récupère la forme du tetromino
  for (size_t x = 0; x < this->size; ++x) {
    for (size_t y = 0; y < this->size; ++y) {
      this->content[y * this->size + x] = TETROMINOS[y * this->size + x + offset];
    }
  }

  // On détermine la position du tetromino courant sur la grille de jeu.
  this->pos = new topi::tools::vector::Vector2i((this->size % 2 == 0 ? static_cast<int>(static_cast<float>(MAP_WIDTH - this->size) / 2) : MAP_WIDTH / 2 - 1), MAP_HEIGHT - 1);
  //this->pos->cli_disp();
}

Tetromino::~Tetromino() {
  if (this->pos != nullptr) {
    delete pos;
  }
}

void Tetromino::insert_in_map(topi::object::tilemap::ColoredTilemap *map) const {
  for (size_t x = 0; x < this->size; ++x) {
    for (size_t y = 0; y < this->size; ++y) {
      (*map)(static_cast<size_t>(this->pos->x) + x, static_cast<size_t>(this->pos->y) - y, 2) = this->content[x + y * this->size];
    }
  }
}
