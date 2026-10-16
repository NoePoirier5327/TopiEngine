#ifndef INPUT_MANAGER_HEADER
#define INPUT_MANAGER_HEADER

#include <SDL2/SDL_keycode.h>
#include <cstdint>
#include <SDL2/SDL.h>

namespace topi::input::keycode {
  using TopiKey = uint32_t;

  // Toûches de contrôle.
  constexpr TopiKey KEY_RETURN         = SDLK_RETURN;
  constexpr TopiKey KEY_ESCAPE         = SDLK_ESCAPE;
  constexpr TopiKey KEY_BACKSPACE      = SDLK_BACKSPACE;
  constexpr TopiKey KEY_TAB            = SDLK_TAB;
  constexpr TopiKey KEY_RSHIFT         = SDLK_RSHIFT;
  constexpr TopiKey KEY_LSHIFT         = SDLK_LSHIFT;
  constexpr TopiKey KEY_CAPSLOCK       = SDLK_CAPSLOCK;
  constexpr TopiKey KEY_SPACE          = SDLK_SPACE;
  constexpr TopiKey KEY_RCTRL          = SDLK_RCTRL;
  constexpr TopiKey KEY_LCTRL          = SDLK_LCTRL;

  // Symboles et caractères spéciaux
  constexpr TopiKey KEY_EXCLAM         = SDLK_EXCLAIM;
  constexpr TopiKey KEY_AT             = SDLK_AT;
  constexpr TopiKey KEY_HASH           = SDLK_HASH;
  constexpr TopiKey KEY_DOLLAR         = SDLK_DOLLAR;
  constexpr TopiKey KEY_PERCENT        = SDLK_PERCENT;
  constexpr TopiKey KEY_CARET          = SDLK_CARET;
  constexpr TopiKey KEY_AMPERSAND      = SDLK_AMPERSAND;
  constexpr TopiKey KEY_ASTERISK       = SDLK_ASTERISK;
  constexpr TopiKey KEY_LEFTPAREN      = SDLK_LEFTPAREN;
  constexpr TopiKey KEY_RIGHTPAREN     = SDLK_RIGHTPAREN;
  constexpr TopiKey KEY_MINUS          = SDLK_MINUS;
  constexpr TopiKey KEY_UNDERSCORE     = SDLK_UNDERSCORE;
  constexpr TopiKey KEY_PLUS           = SDLK_PLUS;
  constexpr TopiKey KEY_EQUAL          = SDLK_EQUALS;
  constexpr TopiKey KEY_LEFTBRACKET    = SDLK_LEFTBRACKET;
  constexpr TopiKey KEY_RIGHTBRACKET   = SDLK_RIGHTBRACKET;
  constexpr TopiKey KEY_SEMICOLON      = SDLK_SEMICOLON;
  constexpr TopiKey KEY_COLON          = SDLK_COLON;
  constexpr TopiKey KEY_SINGLEQUOTE    = SDLK_QUOTE;
  constexpr TopiKey KEY_DOUBLEQUOTE    = SDLK_QUOTEDBL;
  constexpr TopiKey KEY_GRAVE          = SDLK_BACKQUOTE;
  constexpr TopiKey KEY_COMMA          = SDLK_COMMA;
  constexpr TopiKey KEY_DOT            = SDLK_PERIOD;
  constexpr TopiKey KEY_SLASH          = SDLK_SLASH;
  constexpr TopiKey KEY_ANTISLASH      = SDLK_BACKSLASH;
  constexpr TopiKey KEY_LESS           = SDLK_LESS;
  constexpr TopiKey KEY_GREATER        = SDLK_GREATER;
  constexpr TopiKey KEY_QUESTION       = SDLK_QUESTION;

  // Chiffres
  constexpr TopiKey KEY_0              = SDLK_0;
  constexpr TopiKey KEY_1              = SDLK_1;
  constexpr TopiKey KEY_2              = SDLK_2;
  constexpr TopiKey KEY_3              = SDLK_3;
  constexpr TopiKey KEY_4              = SDLK_4;
  constexpr TopiKey KEY_5              = SDLK_5;
  constexpr TopiKey KEY_6              = SDLK_6;
  constexpr TopiKey KEY_7              = SDLK_7;
  constexpr TopiKey KEY_8              = SDLK_8;
  constexpr TopiKey KEY_9              = SDLK_9;

  // Lettres
  constexpr TopiKey KEY_A              = SDLK_a;
  constexpr TopiKey KEY_B              = SDLK_b;
  constexpr TopiKey KEY_C              = SDLK_c;
  constexpr TopiKey KEY_D              = SDLK_d;
  constexpr TopiKey KEY_E              = SDLK_e;
  constexpr TopiKey KEY_F              = SDLK_f;
  constexpr TopiKey KEY_G              = SDLK_g;
  constexpr TopiKey KEY_H              = SDLK_h;
  constexpr TopiKey KEY_I              = SDLK_i;
  constexpr TopiKey KEY_J              = SDLK_j;
  constexpr TopiKey KEY_K              = SDLK_k;
  constexpr TopiKey KEY_L              = SDLK_l;
  constexpr TopiKey KEY_M              = SDLK_m;
  constexpr TopiKey KEY_N              = SDLK_n;
  constexpr TopiKey KEY_O              = SDLK_o;
  constexpr TopiKey KEY_P              = SDLK_p;
  constexpr TopiKey KEY_Q              = SDLK_q;
  constexpr TopiKey KEY_R              = SDLK_r;
  constexpr TopiKey KEY_S              = SDLK_s;
  constexpr TopiKey KEY_T              = SDLK_t;
  constexpr TopiKey KEY_U              = SDLK_u;
  constexpr TopiKey KEY_V              = SDLK_v;
  constexpr TopiKey KEY_W              = SDLK_w;
  constexpr TopiKey KEY_X              = SDLK_x;
  constexpr TopiKey KEY_Y              = SDLK_y;
  constexpr TopiKey KEY_Z              = SDLK_z;

  // Touches directionnelles
  constexpr TopiKey KEY_UP             = SDLK_UP;
  constexpr TopiKey KEY_DOWN           = SDLK_DOWN;
  constexpr TopiKey KEY_LEFT           = SDLK_RIGHT;
  constexpr TopiKey KEY_RIGHT          = SDLK_LEFT;
}

namespace topi::input {
  /**
   * @brief Vérifie si la touche en paramètre est maintenu.
   *
   * @throw std::runtime_error si l'application n'est pas instanciée.
   */
  bool is_key_held(keycode::TopiKey keycode);

  /**
   * @brief Vérifie si la touche en paramètre juste appuyé.
   *
   * @throw std::runtime_error si l'application n'est pas instanciée.
   */
  bool is_key_pressed(keycode::TopiKey keycode);

  /**
   * @class InputManager
   * @brief Gestionnaire des entrées du moteur.
   * Il ne peut y avoir qu'une seule instance de et classe en vie.
   */
  class InputManager {
    public:
      /**
       * @brief Instancie la classe courante.
       *
       * Vérifie qu'aucune autre instance ne tourne et initialise le buffer de touche
       * clavier à null.
       *
       * @throw std::runtime_error si une autre instance tourne.
       */
      InputManager();

      /**
       * @brief Désalloue la classe courante.
       */
      ~InputManager();

      /**
       * @brief Met à jour les buffers de scan des entrées utilisateur vers le programme.
       */
      void update();

      /**
       * @brief Vérifie que la touche en paramètre est pressé par l'utilisateur.
       *
       * @param key_code, identifiant de la touche du clavier pressé dont on veut savoir si elle est pressée.
       *
       * @return true si touche pressée, false sinon.
       */
      bool is_key_held(keycode::TopiKey key_code) const;

      /**
       * @brief Détermine si la touche en paramètre est appuyé mais pas maintenu par l'utilisateur.
       *
       * @param key_code, identifiant de la touche dont on veut savoir si elle est pressée.
       *
       * @return true si touche pressé, false sinon.
       */
      bool is_key_pressed(keycode::TopiKey key_code) const;

    private:
      const uint8_t *_keyboard_state;
      uint8_t _prev_keyboard_states[SDL_NUM_SCANCODES];
  };
}

#endif // !INPUT_MANAGER_HEADER
