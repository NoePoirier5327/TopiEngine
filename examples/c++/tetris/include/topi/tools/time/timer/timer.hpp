#ifndef TIMER_HEADER
#define TIMER_HEADER

namespace topi::tools::time {
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
       *
       * @throw std::invalid_argument si seconds_to_wait < 0
       */
      Timer(double seconds_to_wait);

      /**
       * @brief Mutateur du temps d'attente du minuteur courant.
       *
       * @throw std::invalid_argument si seconds_to_wait < 0
       */
      void set_seconds_to_wait(double seconds_to_wait);

      /**
       * @brief Accesseur du temps d'attente du minuteur courant.
       */
      double get_seconds_to_wait();

      /**
       * @brief Détermine si le minuteur a fini d'attendre.
       */
      bool finished_to_wait();

      /**
       * @brief Relance le minuteur.
       */
      void restart();

    private:
      double beginning;
      double seconds_to_wait;
  };
};

#endif // !TIMER_HEADER
