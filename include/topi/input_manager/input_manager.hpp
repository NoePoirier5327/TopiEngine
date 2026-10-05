#ifndef INPUT_MANAGER_HEADER
#define INPUT_MANAGER_HEADER

#include <SDL2/SDL_keycode.h>
#include <cstdint>
#include <SDL2/SDL.h>

namespace topi::input::keycode {
  using TopiKey = uint32_t;

  // Interface vers les touches clavier générique du moteur.
  const TopiKey KEY_RETURN         = SDLK_RETURN;
  const TopiKey KEY_ESCAPE         = SDLK_ESCAPE;
  const TopiKey KEY_BACKSPACE      = SDLK_BACKSPACE;
  const TopiKey KEY_TAB            = SDLK_TAB;
  const TopiKey KEY_SPACE          = SDLK_SPACE;
  const TopiKey KEY_0              = SDLK_0;
  const TopiKey KEY_1              = SDLK_1;
  const TopiKey KEY_2              = SDLK_2;
  const TopiKey KEY_3              = SDLK_3;
  const TopiKey KEY_4              = SDLK_4;
  const TopiKey KEY_5              = SDLK_5;
  const TopiKey KEY_6              = SDLK_6;
  const TopiKey KEY_7              = SDLK_7;
  const TopiKey KEY_8              = SDLK_8;
  const TopiKey KEY_9              = SDLK_9;
  const TopiKey KEY_A              = SDLK_a;
  const TopiKey KEY_B              = SDLK_b;
  const TopiKey KEY_C              = SDLK_c;
  const TopiKey KEY_D              = SDLK_d;
  const TopiKey KEY_E              = SDLK_e;
  const TopiKey KEY_F              = SDLK_f;
  const TopiKey KEY_G              = SDLK_g;
  const TopiKey KEY_H              = SDLK_h;
  const TopiKey KEY_I              = SDLK_i;
  const TopiKey KEY_J              = SDLK_j;
  const TopiKey KEY_K              = SDLK_k;
  const TopiKey KEY_L              = SDLK_l;
  const TopiKey KEY_M              = SDLK_m;
  const TopiKey KEY_N              = SDLK_n;
  const TopiKey KEY_O              = SDLK_o;
  const TopiKey KEY_P              = SDLK_p;
  const TopiKey KEY_Q              = SDLK_q;
  const TopiKey KEY_R              = SDLK_r;
  const TopiKey KEY_S              = SDLK_s;
  const TopiKey KEY_T              = SDLK_t;
  const TopiKey KEY_U              = SDLK_u;
  const TopiKey KEY_V              = SDLK_v;
  const TopiKey KEY_W              = SDLK_w;
  const TopiKey KEY_X              = SDLK_x;
  const TopiKey KEY_Y              = SDLK_y;
  const TopiKey KEY_Z              = SDLK_z;
  const TopiKey KEY_UP             = SDLK_UP;
  const TopiKey KEY_DOWN           = SDLK_DOWN;
  const TopiKey KEY_LEFT           = SDLK_RIGHT;
  const TopiKey KEY_RIGHT          = SDLK_LEFT;
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
      const uint8_t *keyboard_state;
      uint8_t prev_keyboard_states[SDL_NUM_SCANCODES];
  };
}

#endif // !INPUT_MANAGER_HEADER
