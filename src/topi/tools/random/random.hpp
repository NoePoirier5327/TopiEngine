#ifndef RANDOM_HEADER
#define RANDOM_HEADER

namespace topi::tools::random {
  /**
   * @brief Renvoie un entier aléatoire entre min et max.
   * Les deux bornes a et b sont incluses.
   *
   * @throw std::invalid_argument si min > max
   */
  int randrange(int min, int max);

  /**
   * @brief Renvoie un réel aléatoire entre min et max.
   * Les deux bornes a et b sont incluses.
   *
   * @throw std::invalid_argument si min > max
   */
  double randrange(double min, double max);

  /**
   * @brief Wrapper pour la fonction rand() de c.
   */
  double random();
}

#endif // !RANDOM_HEADER
