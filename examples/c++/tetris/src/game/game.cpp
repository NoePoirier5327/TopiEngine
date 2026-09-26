#include "game.hpp"
#include "tileset/tileset.hpp"

Game::Game() {
  this->map = new_map();
  this->tetromino = new Tetromino();
}

Game::~Game() {
  if (this->map != nullptr) delete this->map;
  if (this->tetromino != nullptr) delete this->tetromino;
}

void Game::update() {
  for (size_t x = 0; x < MAP_WIDTH; ++x) {
    for (size_t y = 0; y < MAP_HEIGHT; ++y) {
      (*this->map)(x, y, 1) = transparent_tile;
    }
  }

  bool can_fall = this->tetromino->insert_in_map(this->map);

  if (!can_fall) {
    delete tetromino;
    this->tetromino = new Tetromino();
  } else {
    this->tetromino->fall();
  }
}

void Game::display(topi::render::Renderer *renderer) const {
  renderer->new_colored_filled_rectangle(0, 0, 320, 640, 27, 36, 71, 255);
  this->map->display(renderer, 0);
  this->map->display(renderer, 1);
}
