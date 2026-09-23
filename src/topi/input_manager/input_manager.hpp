#ifndef INPUT_MANAGER_HEADER
#define INPUT_MANAGER_HEADER

#include <cstdint>
#include <SDL2/SDL.h>

// Interface vers les touches clavier générique du moteur.
const uint16_t KEY_RETURN         = SDLK_RETURN;
const uint16_t KEY_ESCAPE         = SDLK_ESCAPE;
const uint16_t KEY_BACKSPACE      = SDLK_BACKSPACE;
const uint16_t KEY_TAB            = SDLK_TAB;
const uint16_t KEY_SPACE          = SDLK_SPACE;
const uint16_t KEY_0              = SDLK_0;
const uint16_t KEY_1              = SDLK_1;
const uint16_t KEY_2              = SDLK_2;
const uint16_t KEY_3              = SDLK_3;
const uint16_t KEY_4              = SDLK_4;
const uint16_t KEY_5              = SDLK_5;
const uint16_t KEY_6              = SDLK_6;
const uint16_t KEY_7              = SDLK_7;
const uint16_t KEY_8              = SDLK_8;
const uint16_t KEY_9              = SDLK_9;
const uint16_t KEY_A              = SDLK_a;
const uint16_t KEY_B              = SDLK_b;
const uint16_t KEY_C              = SDLK_c;
const uint16_t KEY_D              = SDLK_d;
const uint16_t KEY_E              = SDLK_e;
const uint16_t KEY_F              = SDLK_f;
const uint16_t KEY_G              = SDLK_g;
const uint16_t KEY_H              = SDLK_h;
const uint16_t KEY_I              = SDLK_i;
const uint16_t KEY_J              = SDLK_j;
const uint16_t KEY_K              = SDLK_k;
const uint16_t KEY_L              = SDLK_l;
const uint16_t KEY_M              = SDLK_m;
const uint16_t KEY_N              = SDLK_n;
const uint16_t KEY_O              = SDLK_o;
const uint16_t KEY_P              = SDLK_p;
const uint16_t KEY_Q              = SDLK_q;
const uint16_t KEY_R              = SDLK_r;
const uint16_t KEY_S              = SDLK_s;
const uint16_t KEY_T              = SDLK_t;
const uint16_t KEY_U              = SDLK_u;
const uint16_t KEY_V              = SDLK_v;
const uint16_t KEY_W              = SDLK_w;
const uint16_t KEY_X              = SDLK_x;
const uint16_t KEY_Y              = SDLK_y;
const uint16_t KEY_Z              = SDLK_z;

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
    bool is_key_down(uint16_t key_code) const;

    /**
     * @brief Détermine si la touche en paramètre est appuyé mais pas maintenu par l'utilisateur.
     *
     * @param key_code, identifiant de la touche dont on veut savoir si elle est pressée.
     *
     * @return true si touche pressé, false sinon.
     */
    bool is_just_key_pressed(uint16_t key_code) const;

  private:
    const uint8_t *keyboard_state;
    uint8_t prev_keyboard_states[SDL_NUM_SCANCODES];
};

#endif // !INPUT_MANAGER_HEADER
