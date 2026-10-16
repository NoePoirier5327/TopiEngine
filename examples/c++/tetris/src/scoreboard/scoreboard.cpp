#include "scoreboard.hpp"
#include <iostream>

const size_t PLAYER_NAME_MAX_SIZE = 15;

Scoreboard::Scoreboard(const std::string &path) {
  this->_is_read_only = true;
  this->_score_to_add = 0;
  this->_player_name = "";
}

Scoreboard::~Scoreboard() {
  if (this->_file.is_open())
    this->_file.close();
}

void Scoreboard::update() {
  if (this->_is_read_only) {

  }
  else {
    // Si on appui sur entrée, on termine la saisie du nom.
    if (topi::input::is_key_pressed(topi::input::keycode::KEY_RETURN)) {
      this->add_entry();
    }

    // Sinon, on fait la saisie du nom.
    else {
      if (topi::input::is_key_pressed(topi::input::keycode::KEY_BACKSPACE) && !this->_player_name.empty()) 
        this->_player_name.pop_back();
      else {
        char last_input = topi::input::last_input_as_char();

        // On limite la taille de la saisie à 10 caractères
        // et on empêche la saisie d'une touche non saisie.
        if (last_input != '\0' && this->_player_name.size() < PLAYER_NAME_MAX_SIZE)
          this->_player_name += last_input;
      }
    }
  }
}

void Scoreboard::display(topi::render::RenderManager *renderer) const {
  // Si on est en mode édition, on affiche la saisie courante.
  if (!this->_is_read_only) {
    // On complète la saisie avec des _ pour indiquer
    // qu'il y a encore de la place pour écrire.
    std::string to_disp = this->_player_name;
    for (size_t i = 0; i < PLAYER_NAME_MAX_SIZE - this->_player_name.size(); ++i)
      to_disp += '_';

    // Puis, on l'affiche sur le milieu haut de l'écran.
    renderer->draw_text("Scoreboard", "./res/JetBrainsMonoNerdFont-Bold.ttf", 230, 30, 32, {255, 255, 255, 255});
    renderer->draw_text(to_disp, "./res/JetBrainsMonoNerdFont-Bold.ttf", 180, 90, 32, {255, 255, 255, 255});
  }
}

void Scoreboard::set_read_only_mode() {
  this->_is_read_only = true;
}

void Scoreboard::set_edit_mode() {
  this->_is_read_only = false;
}

void Scoreboard::set_score_to_add(size_t score) {
  this->_score_to_add = score;
}

void Scoreboard::add_entry() {
  if (this->_is_read_only) return;

  this->_player_name = "";
  this->_score_to_add = 0;
  this->set_read_only_mode();
}
