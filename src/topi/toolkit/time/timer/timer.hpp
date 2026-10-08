#ifndef TIMER_HEADER
#define TIMER_HEADER

#include <cstdint>

namespace topi::toolkit::time {
  /**
   * @class Timer
   * @brief Minuteur gérant le temps sous forme de secondes.
   */
  class Timer {
    public:
      /**
       * @brief Construit le minuteur et stocke le temps qu'il doit attendre dans l'instance courante.
       *
       * @param seconds_to_wait, nombre de secondes que le minuteur doit attendre.
       */
      Timer(uint64_t seconds_to_wait);

      /**
       * @brief Mutateur du temps d'attente du minuteur courant.
       */
      void set_seconds_to_wait(uint64_t seconds_to_wait);

      /**
       * @brief Accesseur du temps d'attente du minuteur courant.
       */
      uint64_t get_seconds_to_wait() const;

      /**
       * @brief Détermine si le minuteur a fini d'attendre.
       */
      bool finished_to_wait() const;

      /**
       * @brief Relance le minuteur.
       */
      void restart();

      /**
       * @brief Attend que le minuteur ai finis de tourner.
       */
      void wait_to_finish() const;

    private:
      uint64_t _beginning;
      uint64_t _seconds_to_wait;
  };
};

#endif // !TIMER_HEADER
