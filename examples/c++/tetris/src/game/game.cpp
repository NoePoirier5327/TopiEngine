#include "game.hpp"
#include "tetromino/tetromino.hpp"
#include "tileset/tileset.hpp"

const uint64_t SCORE_FOR_A_TETRO_INSERTED = 10;
const uint64_t SCORE_FOR_1_AND_2_LINES_DESTROYED = 20;
const uint64_t SCORE_FOR_3_LINES_DESTROYED = 50;
const uint64_t SCORE_FOR_4_LINES_DESTROYED = 100;

Game::Game() {
  this->_map = new_map();
  this->_tetromino = new Tetromino(static_cast<eTetroType>(topi::toolkit::random::randrange(0, 6)));
  this->_next_tetromino = new Tetromino(static_cast<eTetroType>(topi::toolkit::random::randrange(0, 6)));
  this->_time_to_fall = 600;
  this->_falling_timer = new topi::toolkit::time::Timer(this->_time_to_fall);
  this->_fast_fall_timer = new topi::toolkit::time::Timer(100);
  this->_insert_timer = nullptr;
  this->_time_before_insertion = 450;
  this->_score = 0;
  this->_level = 0;
}

Game::~Game() {
  if (this->_map != nullptr) delete this->_map;
  if (this->_tetromino != nullptr) delete this->_tetromino;
  if (this->_falling_timer != nullptr) delete this->_falling_timer;
  if (this->_fast_fall_timer != nullptr) delete this->_fast_fall_timer;
  if (this->_insert_timer != nullptr) delete this->_insert_timer;
  if (this->_next_tetromino != nullptr) delete this->_next_tetromino;
}

void Game::handle_inputs() {
  if (topi::input::is_key_pressed(topi::input::keycode::KEY_UP)) {
    if (this->tetromino_can_rotate()) this->_tetromino->rotate();
  }

  if (topi::input::is_key_held(topi::input::keycode::KEY_DOWN)) {
    this->tetromino_fast_fall();
  }

  if (topi::input::is_key_pressed(topi::input::keycode::KEY_SPACE)) {
    this->tetromino_hard_drop();
  }

  if (topi::input::is_key_pressed(topi::input::keycode::KEY_RIGHT)) {
    if (this->tetromino_can_move_right()) this->_tetromino->move_right();
  }

  if (topi::input::is_key_pressed(topi::input::keycode::KEY_LEFT)) {
    if (this->tetromino_can_move_left()) this->_tetromino->move_left();
  }
}

void Game::update() {
  this->tetromino_insert_in_current_map_layer();

  if (!this->tetromino_can_fall()) {
    // On lance le minuteur avant de poser définitivement le tetromino dans la carte.
    if (this->_insert_timer == nullptr) {
      this->_insert_timer = new topi::toolkit::time::Timer(this->_time_before_insertion);
    }

    // S'il a fini, on pose tetromino, on en créer un nouveau
    // et on vérifie qu'on est pas en game over.
    if (this->_insert_timer->finished_to_wait()) {
      this->tetromino_insert_in_final_map_layer();

      this->pick_next_tetromino();

      delete this->_insert_timer;
      this->_insert_timer = nullptr;
      this->_time_before_insertion = 450;
      
      this->_game_over = !this->tetromino_can_fall();

      // On affiche le nouveau tetromino pour montrer qu'on est dans une situation de game over.
      this->tetromino_insert_in_current_map_layer();

      this->attribute_score_and_level(SCORE_FOR_A_TETRO_INSERTED);
    }
  } 
  else {
    if (this->_falling_timer->finished_to_wait()) {
      this->_tetromino->fall();
      this->_falling_timer->restart();
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
      this->attribute_score_and_level(SCORE_FOR_1_AND_2_LINES_DESTROYED);
      break;

    case 2:
      this->attribute_score_and_level(SCORE_FOR_1_AND_2_LINES_DESTROYED);
      break;

    case 3:
      this->attribute_score_and_level(SCORE_FOR_3_LINES_DESTROYED);
      break;

    case 4:
      this->attribute_score_and_level(SCORE_FOR_4_LINES_DESTROYED);
      break;

    default:
      break;
  }
}

void Game::display(topi::render::RenderManager *renderer) const {
  // On affiche le terrain de jeu.
  renderer->draw_colored_filled_rectangle(0, 0, 320, 640, {27, 36, 71, 255});
  this->_map->display(renderer);

  // On affiche le score.
  renderer->draw_text("Score = " + std::to_string(this->_score), "./res/JetBrainsMonoNerdFont-Bold.ttf", 350, 300, 32, {255, 255, 255, 255});
  renderer->draw_text("Level = " + std::to_string(this->_level), "./res/JetBrainsMonoNerdFont-Bold.ttf", 350, 332, 32, {255, 255, 255, 255});

  // On affiche la prévisualisation du prochain tetromino.
  renderer->draw_colored_rectangle(416, 96, 128, 128, 2, {255, 255, 255, 255});

  size_t tile_size = this->_map->get_tile_width();
  size_t tetro_size = this->_next_tetromino->get_size();
  eTetroType tetro_type = this->_next_tetromino->get_type();
  topi::type::color::RGBAColor tetro_color = this->_map->get_tile_color(tetro_type);

  // On centre l'affichage de la prévisualisation.
  int x_offset = 414;
  int y_offset = 96;

  if (tetro_size == 3) {
    x_offset += 16;
    y_offset += 16;
  }

  if (tetro_size == 2) {
    x_offset += 32;
    y_offset += 32;
  }

  for (size_t x = 0; x < tetro_size; ++x) {
    for (size_t y = 0; y < tetro_size; ++y) {
      if ((*this->_next_tetromino)(x, y) != transparent_tile) {
        renderer->draw_colored_filled_rectangle(
          static_cast<int>(x * tile_size) + x_offset,
          static_cast<int>(y * tile_size) + y_offset,
          tile_size,
          tile_size,
          tetro_color
        );
      }
    }
  }
}

bool Game::game_is_over() const {
  return this->_game_over;
}

uint64_t Game::get_score() const {
  return this->_score;
}

int Game::get_full_line_index() const {
  int index = -1;

  size_t line = 0;
  while (line < MAP_HEIGHT && index == -1) {
    bool line_is_full = true;
    size_t column = 0;

    while (column < MAP_WIDTH && line_is_full) {
      line_is_full = line_is_full & ((*this->_map)(column, line, 0) != transparent_tile);
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
    (*this->_map)(column, line_index, 0) = transparent_tile;
  }

  for (size_t line = line_index + 1; line < MAP_HEIGHT; ++line) {
    this->_map->exchange_lines(line_index, line, 0);
    line_index ++;
  }
}

bool Game::tetromino_can_fall() const {
  bool can_fall = true;

  size_t x = 0;
  while (x < this->_tetromino->get_size() && can_fall) {
    size_t y = 0;
    while (y < this->_tetromino->get_size() && can_fall) {
      if ((*this->_tetromino)(x, y) != transparent_tile) {
        can_fall = can_fall & (static_cast<int>(this->_tetromino->get_pos_y()) - static_cast<int>(y) > 0);

        if (can_fall) {
          can_fall = can_fall & ((*this->_map)(static_cast<size_t>(this->_tetromino->get_pos_x()) + x, static_cast<size_t>(this->_tetromino->get_pos_y()) - y - 1, 0) == transparent_tile);
        }
      }
      y++;
    }
    x++;
  }

  return can_fall;
}

void Game::tetromino_hard_drop() {
  this->_time_before_insertion = 0;
  while (this->tetromino_can_fall()) {
    this->_tetromino->fall();
  }
}

void Game::tetromino_fast_fall() const {
  if (!this->tetromino_can_fall()) return;

  if (this->_fast_fall_timer->finished_to_wait()) {
    this->_tetromino->fall();
    this->_fast_fall_timer->restart();
  }
}

bool Game::tetromino_can_move_right() const {
  bool can_move = true;

  size_t x = 0;
  while (x < this->_tetromino->get_size() && can_move) {
    size_t y = 0;
    while (y < this->_tetromino->get_size() && can_move) {
      if ((*this->_tetromino)(x, y) != transparent_tile) {
        can_move = can_move & (this->_tetromino->get_pos_x() + static_cast<int>(x) > 0);

        if (can_move) {
          can_move = can_move & ((*this->_map)(static_cast<size_t>(this->_tetromino->get_pos_x()) + x - 1, static_cast<size_t>(this->_tetromino->get_pos_y()) - y, 0) == transparent_tile);
        }
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
  while (x < this->_tetromino->get_size() && can_move) {
    size_t y = 0;
    while (y < this->_tetromino->get_size() && can_move) {
      if ((*this->_tetromino)(x, y) != transparent_tile) {
        can_move = can_move & (static_cast<size_t>(this->_tetromino->get_pos_x()) + x < MAP_WIDTH - 1);

        if (can_move) {
          can_move = can_move & ((*this->_map)(static_cast<size_t>(this->_tetromino->get_pos_x()) + x + 1, static_cast<size_t>(this->_tetromino->get_pos_y()) - y, 0) == transparent_tile);
        }
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
  while (x < this->_tetromino->get_size() && can_rotate) {
    size_t y = 0;
    while (y < this->_tetromino->get_size() && can_rotate) {
      size_t px = this->_tetromino->get_size() - x - 1;
      size_t py = y;
      if ((*this->_tetromino)(py, px) != transparent_tile) {
        // Collision avec les bords de la carte
        int final_pos_x = this->_tetromino->get_pos_x() + static_cast<int>(px);
        int final_pos_y = this->_tetromino->get_pos_y() - static_cast<int>(y);

        can_rotate = can_rotate & (final_pos_x >= 0); // bord droit
        can_rotate = can_rotate & (final_pos_x <= static_cast<int>(MAP_WIDTH) - 1); // bord gauche
        can_rotate = can_rotate & (final_pos_y >= 0); // bord inférieur

        // Collision de rotation entre tetromino qui tombe et tetromino dans la grille.
        if (can_rotate) {
          can_rotate = can_rotate & ((*this->_map)(static_cast<size_t>(final_pos_x), static_cast<size_t>(final_pos_y), 0) == transparent_tile);
        }
      }
      ++y;
    }
    ++x;
  }

  return can_rotate;
}

void Game::tetromino_insert_in_final_map_layer() const {
  for (size_t x = 0; x < this->_tetromino->get_size(); ++x) {
    for (size_t y = 0; y < this->_tetromino->get_size(); ++y) {
      if ((*this->_tetromino)(x, y) != transparent_tile) {
        (*this->_map)(static_cast<size_t>(this->_tetromino->get_pos_x()) + x, static_cast<size_t>(this->_tetromino->get_pos_y()) - y, 0) = (*this->_tetromino)(x, y);
      }
    }
  }
}

void Game::tetromino_insert_in_current_map_layer() const {
  for (size_t x = 0; x < MAP_WIDTH; ++x) {
    for (size_t y = 0; y < MAP_HEIGHT; ++y) {
      (*this->_map)(x, y, 1) = transparent_tile;
    }
  }

  for (size_t x = 0; x < this->_tetromino->get_size(); ++x) {
    for (size_t y = 0; y < this->_tetromino->get_size(); ++y) {
      if ((*this->_tetromino)(x, y) != transparent_tile) {
        (*this->_map)(static_cast<size_t>(this->_tetromino->get_pos_x()) + x, static_cast<size_t>(this->_tetromino->get_pos_y()) - y, 1) = (*this->_tetromino)(x, y);
      }
    }
  }
}

void Game::attribute_score_and_level(uint64_t score_to_attribute) {
  this->_score += score_to_attribute;

  if (this->_score % 200 == 0) {
    this->_level ++;

    if (static_cast<int>(this->_time_to_fall) - 50 >= 0) {
      this->_time_to_fall -= 50;
      this->_falling_timer->set_seconds_to_wait(this->_time_to_fall);
    }
  }
}

void Game::pick_next_tetromino() {
  if (this->_tetromino != nullptr) delete this->_tetromino;
  this->_tetromino = this->_next_tetromino;
  this->_next_tetromino = new Tetromino(static_cast<eTetroType>(topi::toolkit::random::randrange(0, 6)));
}
