#ifndef CHRONOMETER_HEADER
#define CHRONOMETER_HEADER

#include <cstdint>

namespace topi::tools::time {
  /**
   * @class Chronometer
   * @brief Chronomètre comptent le temps en seconde écoulé depuis son instanciation.
   */
  class Chronometer {
    public:
      /**
       * @brief Instancie un nouveau chronomètre basé sur l'heure en seconde lors de son instanciation.
       */
      Chronometer();

      /**
       * @brief Renvoie le temps écoulé depuis l'instanciation du chronomètre en secondes
       */
      uint64_t get_elapsed_seconds() const;

      /**
       * @brief Remets le chronomètre à zéro.
       */
      void restart();

    private:
      uint64_t _start_time;
  };
}

#endif // !CHRONOMETER_HEADER
