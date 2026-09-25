#include "game.hpp"
#include "tileset/tileset.hpp"

Game::Game() {
  this->map = new_map();
}

Game::~Game() {
  if (this->map != nullptr)
    delete this->map;
}

void Game::update() {

}

void Game::display(topi::render::Renderer *renderer) const {
  for (size_t i = 0; i < 3; ++i)
    this->map->display(renderer, i);
}
