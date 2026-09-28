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
}

Tetromino::~Tetromino() {
  if (this->pos != nullptr) {
    delete pos;
  }
}

bool Tetromino::insert_in_map(topi::object::tilemap::ColoredTilemap *map) const {
  bool can_fall = this->can_fall(map);

  for (size_t x = 0; x < this->size; ++x) {
    for (size_t y = 0; y < this->size; ++y) {
      if (this->content[x + y * this->size] != transparent_tile) {
        (*map)(static_cast<size_t>(this->pos->x) + x, static_cast<size_t>(this->pos->y) - y, can_fall ? 1 : 0) = this->content[x + y * this->size];
      }
    }
  }

  return can_fall;
}

bool Tetromino::can_fall(topi::object::tilemap::ColoredTilemap *map) const {
  // Si on a déjà atteint le sol, on s'épargne la suite des calculs.
  if (this->has_reached_ground()) {
    return false;
  }

  return !this->has_reached_another_tetromino(map);
}

void Tetromino::fall() {
  this->pos->y -= 1;
}

bool Tetromino::has_reached_ground() const {
  bool has_reached_ground = false;

  size_t x = 0;
  while (x < this->size && !has_reached_ground) {
    size_t y = 0;
    while (y < this->size && !has_reached_ground) {
      if (this->content[x + y * this->size] != transparent_tile) {
        has_reached_ground = has_reached_ground | (this->pos->y - static_cast<int>(y) <= 0);
      }
      ++y;
    }
    ++x;
  }

  return has_reached_ground;
}

bool Tetromino::has_reached_another_tetromino(topi::object::tilemap::ColoredTilemap *map) const {
  bool has_reached_another_tetromino = false;

  size_t x = 0;
  while (x < this->size && !has_reached_another_tetromino) {
    size_t y = 0;
    while (y < this->size && !has_reached_another_tetromino) {
      if (this->content[x + y * this->size] != transparent_tile) {
        has_reached_another_tetromino = has_reached_another_tetromino | ((*map)(static_cast<size_t>(this->pos->x) + x, static_cast<size_t>(this->pos->y) - y - 1, 0) != transparent_tile);
      }
      ++y;
    }
    ++x;
  }

  return has_reached_another_tetromino;
}

void Tetromino::rotate() {
  TileType temp[16];

  for (size_t x = 0; x < this->size; ++x) {
    for (size_t y = 0; y < this->size; ++y) {
      temp[x + this->size * y] = this->content[y + this->size * (this->size - x - 1)];
    }
  }

  for (size_t x = 0; x < this->size; ++x) {
    for (size_t y = 0; y < this->size; ++y) {
      this->content[x + this->size * y] = temp[x + this->size * y];
    }
  }
}

void Tetromino::move_right(topi::object::tilemap::ColoredTilemap *map) {
  if (!this->can_move_right(map)) {
    return;
  }

  this->pos->x --;
}

void Tetromino::move_left(topi::object::tilemap::ColoredTilemap *map) {
  if (!this->can_move_left(map)) {
    return;
  }

  this->pos->x ++;
}

bool Tetromino::can_move_right(topi::object::tilemap::ColoredTilemap *map) const {
  // Si on a déjà une collision avec le mur, on s'épargne le reste des calculs.
  if (this->collides_with_right_wall()) {
    return false;
  }

  return !this->collides_with_another_tetromino_on_the_right(map);
}

bool Tetromino::collides_with_another_tetromino_on_the_right(topi::object::tilemap::ColoredTilemap *map) const {
  bool collides = false;

  size_t x = 0;
  while (x < this->size && !collides) {
    size_t y = 0;
    while (y < this->size && !collides) {
      if (this->content[x + this->size * y] != transparent_tile) {
        collides = collides | ((*map)(static_cast<size_t>(this->pos->x) + x - 1, static_cast<size_t>(this->pos->y) - y, 0) != transparent_tile);
      }
      ++y;
    }
    ++x;
  }

  return collides;
}

bool Tetromino::collides_with_right_wall() const {
  bool collides = false;

  size_t x = 0;
  while (x < this->size && !collides) {
    size_t y = 0;
    while (y < this->size && !collides) {
      if (this->content[x + y * this->size] != transparent_tile) {
        collides = collides | (this->pos->x + static_cast<int>(x) <= 0);
      }
      ++y;
    }
    ++x;
  }

  return collides;
}

bool Tetromino::can_move_left(topi::object::tilemap::ColoredTilemap *map) const {
  if (this->collides_with_left_wall()) {
    return false;
  }

  return !this->collides_with_another_tetromino_on_the_left(map);
}

bool Tetromino::collides_with_left_wall() const {
  bool collides = false;

  size_t x = 0;
  while (x < this->size && !collides) {
    size_t y = 0;
    while (y < this->size && !collides) {
      if (this->content[x + y * this->size] != transparent_tile) {
        collides = collides | (static_cast<size_t>(this->pos->x) + x >= MAP_WIDTH - 1);
      }
      ++y;
    }
    ++x;
  }

  return collides;
}

bool Tetromino::collides_with_another_tetromino_on_the_left(topi::object::tilemap::ColoredTilemap *map) const {
  bool collides = false;

  size_t x = 0;
  while (x < this->size && !collides) {
    size_t y = 0;
    while (y < this->size && !collides) {
      if (this->content[x + this->size * y] != transparent_tile) {
        collides = collides | ((*map)(static_cast<size_t>(this->pos->x) + x + 1, static_cast<size_t>(this->pos->y) - y, 0) != transparent_tile);
      }
      ++y;
    }
    ++x;
  }

  return collides;

}
