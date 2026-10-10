#include "tetromino.hpp"
#include <stdexcept>

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
  uint64_t tetro_type = static_cast<uint64_t>(topi::toolkit::random::randrange(0, 6));
  this->_size = TETROMINOS_SIZE[tetro_type];

  // On calcul la position du tetromino à récupérer dans la matrice les décrivants.
  size_t offset = 0;
  for (size_t i = 0; i < tetro_type; ++i)
    offset += TETROMINOS_SIZE[i] * TETROMINOS_SIZE[i];

  // On récupère la forme du tetromino
  for (size_t x = 0; x < this->_size; ++x) {
    for (size_t y = 0; y < this->_size; ++y) {
      this->_content[y * this->_size + x] = TETROMINOS[y * this->_size + x + offset];
    }
  }

  // On détermine la position du tetromino courant sur la grille de jeu.
  this->_pos_x = (this->_size % 2 == 0 ? static_cast<int>(static_cast<float>(MAP_WIDTH - this->_size) / 2) : MAP_WIDTH / 2 - 1);
  this->_pos_y = MAP_HEIGHT - 1;
}

void Tetromino::fall() {
  this->_pos_y -= 1;
}

void Tetromino::rotate() {
  TileType temp[16];

  for (size_t x = 0; x < this->_size; ++x) {
    for (size_t y = 0; y < this->_size; ++y) {
      temp[x + this->_size * y] = this->_content[y + this->_size * (this->_size - x - 1)];
    }
  }

  for (size_t x = 0; x < this->_size; ++x) {
    for (size_t y = 0; y < this->_size; ++y) {
      this->_content[x + this->_size * y] = temp[x + this->_size * y];
    }
  }
}

void Tetromino::move_right() {
  this->_pos_x --;
}

void Tetromino::move_left() {
  this->_pos_x ++;
}

int Tetromino::get_pos_x() const {
  return this->_pos_x;
}

int Tetromino::get_pos_y() const {
  return this->_pos_y;
}

size_t Tetromino::get_size() const {
  return this->_size;
}

TileType Tetromino::operator()(size_t x, size_t y) const {
  if (x >= this->_size || y >= this->_size) {
    throw std::out_of_range("Tetromino content index out of range.");
  }

  return this->_content[x + this->_size * y];
}
