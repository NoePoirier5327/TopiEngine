#include "game.hpp"
#include "tileset/tileset.hpp"

Game::Game() {
  this->map = new_map();
  this->tetromino = new Tetromino();
  this->time_to_fall = 800;
  this->falling_timer = new topi::tools::time::Timer(this->time_to_fall);
  this->soft_drop_timer = new topi::tools::time::Timer(100);
}

Game::~Game() {
  if (this->map != nullptr) delete this->map;
  if (this->tetromino != nullptr) delete this->tetromino;
  if (this->falling_timer != nullptr) delete this->falling_timer;
  if (this->soft_drop_timer != nullptr) delete this->soft_drop_timer;
}

void Game::handle_inputs(const topi::input::InputManager &input_manager) {
  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_UP)) {
    this->tetromino->rotate(this->map);
  }

  if (input_manager.is_key_down(topi::input::keycode::KEY_DOWN)) {
    if (this->soft_drop_timer->finished_to_wait()) {
      this->tetromino->fall();
      this->soft_drop_timer->restart();
    }
  }

  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_SPACE)) {
    this->tetromino->hard_drop(this->map);
  }

  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_RIGHT)) {
    this->tetromino->move_right(this->map);
  }

  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_LEFT)) {
    this->tetromino->move_left(this->map);
  }
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
    if (this->falling_timer->finished_to_wait()) {
      this->tetromino->fall();
      this->falling_timer->restart();
    }
  }

  for (int index = this->get_full_line_index(); index != -1; index = this->get_full_line_index()) {
    this->destroy_line(static_cast<size_t>(index));
  }
}

void Game::display(topi::render::Renderer *renderer) const {
  renderer->new_colored_filled_rectangle(0, 0, 320, 640, 27, 36, 71, 255);
  this->map->display(renderer, 0);
  this->map->display(renderer, 1);
}

size_t Game::get_nb_full_line() const {
  size_t nb_full_line = 0;

  for (size_t line = 0; line < MAP_HEIGHT; ++line) {
    bool line_is_full = true;
    size_t column = 0;

    while (column < MAP_WIDTH && line_is_full) {
      line_is_full = line_is_full & ((*this->map)(column, line, 0) != transparent_tile);
      ++column;
    }

    if (line_is_full) {
      nb_full_line++;
    }
  }

  return nb_full_line;
}

int Game::get_full_line_index() const {
  int index = -1;

  size_t line = 0;
  while (line < MAP_HEIGHT && index == -1) {
    bool line_is_full = true;
    size_t column = 0;

    while (column < MAP_WIDTH && line_is_full) {
      line_is_full = line_is_full & ((*this->map)(column, line, 0) != transparent_tile);
      ++column;
    }

    if (line_is_full) {
      index = static_cast<int>(line);
    }

    ++line;
  }

  return index;
}

void Game::destroy_line(size_t line_index) {
  for (size_t column = 0; column < MAP_WIDTH; ++column) {
    (*this->map)(column, line_index, 0) = transparent_tile;
  }

  for (size_t line = line_index + 1; line < MAP_HEIGHT; ++line) {
    this->map->exchange_lines(line_index, line, 0);
    line_index ++;
  }
}
