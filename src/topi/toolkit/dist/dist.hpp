#ifndef DIST_HEADER
#define DIST_HEADER

namespace topi::toolkit {
  /**
   * @brief Calcul la distance entre les deux points en paramètre.
   *
   * @param x1, coordonnée en x du premier point.
   * @param y1, coordonnée en y du premier point.
   * @param x2, coordonnée en x du second point.
   * @param y2, coordonnée en y du second point.
   *
   * @return distance entre les deux points en paramètres.
   */
  double dist(int x1, int y1, int x2, int y2);

  /**
   * @brief Calcul la distance entre les deux points en paramètre.
   *
   * @param x1, coordonnée en x du premier point.
   * @param y1, coordonnée en y du premier point.
   * @param x2, coordonnée en x du second point.
   * @param y2, coordonnée en y du second point.
   *
   * @return distance entre les deux points en paramètres.
   */
  double dist(float x1, float y1, float x2, float y2);

  /**
   * @brief Calcul la distance entre les deux points en paramètre.
   *
   * @param x1, coordonnée en x du premier point.
   * @param y1, coordonnée en y du premier point.
   * @param x2, coordonnée en x du second point.
   * @param y2, coordonnée en y du second point.
   *
   * @return distance entre les deux points en paramètres.
   */
  double dist(double x1, double y1, double x2, double y2);
}

#endif // !DIST_HEADER
