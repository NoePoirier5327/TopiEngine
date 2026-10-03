#include "game.hpp"
#include "tileset/tileset.hpp"

const uint64_t SCORE_FOR_A_TETRO_INSERTED = 10;
const uint64_t SCORE_FOR_1_AND_2_LINES_DESTROYED = 20;
const uint64_t SCORE_FOR_3_LINES_DESTROYED = 50;
const uint64_t SCORE_FOR_4_LINES_DESTROYED = 100;

Game::Game() {
  this->map = new_map();
  this->tetromino = new Tetromino();
  this->time_to_fall = 800;
  this->falling_timer = new topi::tools::time::Timer(this->time_to_fall);
  this->fast_fall_timer = new topi::tools::time::Timer(100);
  this->insert_timer = nullptr;
  this->time_before_insertion = 450;
  this->score = 0;
}

Game::~Game() {
  if (this->map != nullptr) delete this->map;
  if (this->tetromino != nullptr) delete this->tetromino;
  if (this->falling_timer != nullptr) delete this->falling_timer;
  if (this->fast_fall_timer != nullptr) delete this->fast_fall_timer;
  if (this->insert_timer != nullptr) delete this->insert_timer;
}

void Game::handle_inputs(const topi::input::InputManager &input_manager) {
  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_UP)) {
    if (this->tetromino_can_rotate()) this->tetromino->rotate();
  }

  if (input_manager.is_key_down(topi::input::keycode::KEY_DOWN)) {
    this->tetromino_fast_fall();
  }

  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_SPACE)) {
    this->tetromino_hard_drop();
  }

  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_RIGHT)) {
    if (this->tetromino_can_move_right()) this->tetromino->move_right();
  }

  if (input_manager.is_just_key_pressed(topi::input::keycode::KEY_LEFT)) {
    if (this->tetromino_can_move_left()) this->tetromino->move_left();
  }
}

void Game::update() {
  this->tetromino_insert_in_current_map_layer();

  if (!this->tetromino_can_fall()) {
    // On lance le minuteur avant de poser définitivement le tetromino dans la carte.
    if (this->insert_timer == nullptr) {
      this->insert_timer = new topi::tools::time::Timer(this->time_before_insertion);
    }

    // S'il a fini, on pose tetromino, on en créer un nouveau
    // et on vérifie qu'on est pas en game over.
    if (this->insert_timer->finished_to_wait()) {
      this->tetromino_insert_in_final_map_layer();

      delete tetromino;
      this->tetromino = new Tetromino();

      delete this->insert_timer;
      this->insert_timer = nullptr;
      this->time_before_insertion = 450;
      
      this->game_over = !this->tetromino_can_fall();

      // On affiche le nouveau tetromino pour montrer qu'on est dans une situation de game over.
      this->tetromino_insert_in_current_map_layer();

      this->score += SCORE_FOR_A_TETRO_INSERTED;
    }
  } 
  else {
    if (this->falling_timer->finished_to_wait()) {
      this->tetromino->fall();
      this->falling_timer->restart();
    }
  }

  size_t nb_line_destroyed = 0;
  for (int index = this->get_full_line_index(); index != -1; index = this->get_full_line_index()) {
    this->destroy_line(static_cast<size_t>(index));
    nb_line_destroyed++;
  }

  // On attribut le score en fonction des lignes détruites.
  switch (nb_line_destroyed) {
    case 1:
      this->score += SCORE_FOR_1_AND_2_LINES_DESTROYED;
      break;

    case 2:
      this->score += SCORE_FOR_1_AND_2_LINES_DESTROYED;
      break;

    case 3:
      this->score += SCORE_FOR_3_LINES_DESTROYED;
      break;

    case 4:
      this->score += SCORE_FOR_4_LINES_DESTROYED;
      break;

    default:
      break;
  }
}

void Game::display(topi::render::Renderer *renderer) const {
  renderer->draw_colored_filled_rectangle(0, 0, 320, 640, 27, 36, 71, 255);
  this->map->display(renderer);
  renderer->draw_text("Score = " + std::to_string(this->score), 0, 340, 16, 1.0, 255, 255, 255, 255);
}

bool Game::game_is_over() const {
  return this->game_over;
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

bool Game::tetromino_can_fall() const {
  bool can_fall = true;

  size_t x = 0;
  while (x < this->tetromino->get_size() && can_fall) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_fall) {
      if ((*this->tetromino)(x, y) != transparent_tile) {
        can_fall = can_fall & (static_cast<int>(this->tetromino->get_pos_y()) - static_cast<int>(y) > 0);
      }
      y++;
    }
    x++;
  }

  if (!can_fall) return false;

  x = 0;
  while (x < this->tetromino->get_size() && can_fall) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_fall) {
      if ((*this->tetromino)(x, y) != transparent_tile) {
        can_fall = can_fall & ((*this->map)(static_cast<size_t>(this->tetromino->get_pos_x()) + x, static_cast<size_t>(this->tetromino->get_pos_y()) - y - 1, 0) == transparent_tile);
      }
      y++;
    }
    x++;
  }

  return can_fall;
}

void Game::tetromino_hard_drop() {
  this->time_before_insertion = 0;
  while (this->tetromino_can_fall()) {
    this->tetromino->fall();
  }
}

void Game::tetromino_fast_fall() const {
  if (!this->tetromino_can_fall()) return;

  if (this->fast_fall_timer->finished_to_wait()) {
    this->tetromino->fall();
    this->fast_fall_timer->restart();
  }
}

bool Game::tetromino_can_move_right() const {
  bool can_move = true;

  size_t x = 0;
  while (x < this->tetromino->get_size() && can_move) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_move) {
      if ((*tetromino)(x, y) != transparent_tile) {
        can_move = can_move & (this->tetromino->get_pos_x() + static_cast<int>(x) > 0);
      }
      y++;
    }
    x++;
  }

  if (!can_move) return false;

  x = 0;
  while (x < this->tetromino->get_size() && can_move) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_move) {
      if ((*this->tetromino)(x, y) != transparent_tile) {
        can_move = can_move & ((*this->map)(static_cast<size_t>(this->tetromino->get_pos_x()) + x - 1, static_cast<size_t>(this->tetromino->get_pos_y()) - y, 0) == transparent_tile);
      }
      y++;
    }
    x++;
  }

  return can_move;
}

bool Game::tetromino_can_move_left() const {
  bool can_move = true;

  size_t x = 0;
  while (x < this->tetromino->get_size() && can_move) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_move) {
      if ((*this->tetromino)(x, y) != transparent_tile) {
        can_move = can_move & (static_cast<size_t>(this->tetromino->get_pos_x()) + x < MAP_WIDTH - 1);
      }
      y++;
    }
    x++;
  }

  if (!can_move) return false;

  x = 0;
  while (x < this->tetromino->get_size() && can_move) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_move) {
      if ((*tetromino)(x, y) != transparent_tile) {
        can_move = can_move & ((*this->map)(static_cast<size_t>(this->tetromino->get_pos_x()) + x + 1, static_cast<size_t>(this->tetromino->get_pos_y()) - y, 0) == transparent_tile);
      }
      y++;
    }
    x++;
  }

  return can_move;
}

bool Game::tetromino_can_rotate() const {
  bool can_rotate = true;

  size_t x = 0;
  while (x < this->tetromino->get_size() && can_rotate) {
    size_t y = 0;
    while (y < this->tetromino->get_size() && can_rotate) {
      size_t px = this->tetromino->get_size() - x - 1;
      size_t py = y;
      if ((*tetromino)(py, px) != transparent_tile) {
        // Collision avec les bords de la carte
        int final_pos_x = this->tetromino->get_pos_x() + static_cast<int>(px);
        int final_pos_y = this->tetromino->get_pos_y() - static_cast<int>(y);

        can_rotate = can_rotate & (final_pos_x >= 0); // bord droit
        can_rotate = can_rotate & (final_pos_x <= static_cast<int>(MAP_WIDTH) - 1); // bord gauche
        can_rotate = can_rotate & (final_pos_y >= 0); // bord inférieur

        // Collision de rotation entre tetromino qui tombe et tetromino dans la grille.
        if (can_rotate) {
          can_rotate = can_rotate & ((*this->map)(static_cast<size_t>(final_pos_x), static_cast<size_t>(final_pos_y), 0) == transparent_tile);
        }
      }
      ++y;
    }
    ++x;
  }

  return can_rotate;
}

void Game::tetromino_insert_in_final_map_layer() const {
  for (size_t x = 0; x < this->tetromino->get_size(); ++x) {
    for (size_t y = 0; y < this->tetromino->get_size(); ++y) {
      if ((*this->tetromino)(x, y) != transparent_tile) {
        (*this->map)(static_cast<size_t>(this->tetromino->get_pos_x()) + x, static_cast<size_t>(this->tetromino->get_pos_y()) - y, 0) = (*this->tetromino)(x, y);
      }
    }
  }
}

void Game::tetromino_insert_in_current_map_layer() const {
  for (size_t x = 0; x < MAP_WIDTH; ++x) {
    for (size_t y = 0; y < MAP_HEIGHT; ++y) {
      (*this->map)(x, y, 1) = transparent_tile;
    }
  }

  for (size_t x = 0; x < this->tetromino->get_size(); ++x) {
    for (size_t y = 0; y < this->tetromino->get_size(); ++y) {
      if ((*this->tetromino)(x, y) != transparent_tile) {
        (*this->map)(static_cast<size_t>(this->tetromino->get_pos_x()) + x, static_cast<size_t>(this->tetromino->get_pos_y()) - y, 1) = (*this->tetromino)(x, y);
      }
    }
  }
}
