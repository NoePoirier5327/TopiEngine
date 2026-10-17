#include "scoreboard.hpp"
#include <stdexcept>
#include <string>

const size_t PLAYER_NAME_MAX_SIZE = 12;

Scoreboard::Scoreboard(const std::string &path) {
  this->_file_path = path;
  this->_is_read_only = true;
  this->_score_to_add = 0;
  this->_player_name = "";

  if (this->_player_board.size() != this->_score_board.size())
    throw std::runtime_error("Incoherent scoreboard data format detected.");
}

Scoreboard::~Scoreboard() {

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
  // On prépare l'interface qu'on va afficher sous
  // forme de tui.
  std::string to_disp[17];

  std::string temp = "";
  for (size_t i = 0; i < 34; ++i) temp += ' ';
  to_disp[0] = temp;

  temp = "";
  for (size_t i = 0; i < 12; ++i) temp += ' ';
  temp += "SCOREBOARD";
  for (size_t i = 0; i < 12; ++i) temp += ' ';
  to_disp[1] = temp;

  temp = "";
  for (size_t i = 0; i < 34; ++i) temp += ' ';
  to_disp[2] = temp;

  temp = "    +";
  for (size_t i = 0; i < 24; ++i) temp += '-';
  temp += "+    ";
  to_disp[3] = temp;

  // Si on est en mode édition, on affiche la saisie courante
  // et les meilleurs scores réalisés.
  if (!this->_is_read_only) {
    // On complète la saisie avec des _ pour indiquer
    // qu'il y a encore de la place pour écrire.
    temp = "    | > " + this->_player_name;
    for (size_t i = 0; i < PLAYER_NAME_MAX_SIZE - this->_player_name.size(); ++i)
      temp += '_';

    int spaces_to_add = 28 - static_cast<int>(std::to_string(this->_score_to_add).size());
    if (spaces_to_add > 0)
      for (;temp.size() != static_cast<size_t>(spaces_to_add);)
        temp += ' ';

    temp += std::to_string(this->_score_to_add);
    temp += " |    ";
    to_disp[4] = temp;

    temp = "    +";
    for (size_t i = 0; i < 24; ++i) temp += '-';
    temp += "+    ";
    to_disp[5] = temp;

    // On affiche sur une fenêtre, en bas de celle de saisie
    // les meilleurs scores des joueurs avec leurs noms.
    temp = "";
    for (size_t i = 0; i < 34; ++i) temp += ' ';
    to_disp[6] = temp;

    temp = "    +";
    for (size_t i = 0; i < 24; ++i) temp += '-';
    temp += "+    ";
    to_disp[7] = temp;

    // On récupère les scores avec les noms.
    size_t n = (this->_player_board.size() > 8 ? 8 : this->_player_board.size());
    for (size_t i = 0; i < 8; ++i) {
      temp = "    |";
      if (i < n) {
        // On affiche le nom
        temp += ' ' + this->_player_board[i];

        // On complète l'affichage avec des espaces entre le nom et son score.
        int k = 28 - static_cast<int>(std::to_string(this->_score_board[i]).size());
        if (k > 0)
          for (;temp.size() != static_cast<size_t>(k);)
            temp += ' ';

        // On affiche le score associé au nom.
        temp += std::to_string(this->_score_board[i]) + ' ';
      }
      else {
        for (size_t j = 0; j < 24; ++j)
          temp += ' ';
      }
      temp += "|    ";
      to_disp[i+8] = temp;
    }

    // On met la ligne de fin de l'affichage.
    temp = "    +";
    for (size_t i = 0; i < 24; ++i) temp += '-';
    temp += "+    ";
    to_disp[16] = temp;
  }

  for (size_t i = 0; i < 17; ++i)
    renderer->draw_text(to_disp[i], "./res/JetBrainsMonoNerdFont-Bold.ttf", 0, static_cast<int>(i * 32), 32, {255, 255, 255, 255});
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
