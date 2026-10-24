#ifndef VECTOR2F_HEADER
#define VECTOR2F_HEADER

namespace topi::type::vector {
  /**
   * @class Vector2f
   * @brief Vecteur en deux dimensions composés de flottant simple précision.
   */
  class Vector2f {
    public:
      /**
       * @brief Constructeur simple du vecteur flottant en deux dimensions.
       *
       * @param x, premier élément du 2uplet du vecteur courant.
       * @param y, second élément du 2uplet du vecteur courant.
       */
      Vector2f(float x, float y);

      /**
       * @brief Constructeur en copie.
       *
       * Copie le contenu du vecteur en paramètre dans le but
       * dans instancier un nouveau.
       *
       * @param v, vecteur à copier pour la création.
       */
      Vector2f(const Vector2f& v);

      /**
       * @brief Constructeur en déplacement.
       *
       * Transfère le contenu du vecteur en paramètre dans
       * une nouvelle instance créer par ce constructeur.
       *
       * @param v, vecteur dont le contenu est à transférer.
       */
      Vector2f(Vector2f &&v) noexcept;

      /**
       * @brief Surcharge de l'opérateur d'égalité.
       *
       * Vérifie si le contenu du vecteur en paramètre est
       * le même que celui courant.
       *
       * @param v, vecteur à comparer avec l'instance courante.
       * @return true s'ils sont égaux, false sinon.
       */
      bool operator==(const Vector2f &v) const;

      /**
       * @brief Surcharge de l'opérateur d'inégalité.
       *
       * Vérifie si le contenu du vecteur en paramètre est
       * le même que celui courant.
       *
       * @param v, vecteur à comparer avec l'instance courante.
       * @return true s'ils ne sont pas égaux, false sinon.
       */
      bool operator!=(const Vector2f &v) const;

      /**
       * @brief Surcharge de l'opérateur d'addition.
       *
       * Additionne le vecteur en paramètre avec le vecteur courant
       * et renvoie le résultat sous forme d'une nouvelle instance.
       *
       * @param v, vecteur à ajouter avec le vecteur courant.
       *
       * @return résultat de l'addition.
       */
      Vector2f operator+(const Vector2f &v) const;

      /**
       * @brief Surchargeur de l'opérateur d'assignation.
       *
       * Copie le vecteur en paramètre dans celui courant.
       *
       * @param v, vecteur à assigner.
       *
       * @return vecteur résultant de l'assignation.
       */
      Vector2f& operator=(const Vector2f &v);

      /**
       * @brief Surchargeur de l'opérateur d'assignation.
       *
       * Transfère le contenu du vecteur en paramètre dans
       * celui courant.
       *
       * @param v, vecteur à assigner au vecteur courant.
       *
       * @return vecteur résultant de l'assignation.
       */
      Vector2f& operator=(Vector2f &&v) noexcept;

      /**
       * @brief Affiche le contenu du vecteur courant sur la console.
       */
      void debug_disp() const;

      float x;
      float y;
  };


  /**
   * @brief Surcharge de l'opérateur de multiplication.
   *
   * Multiplie le vecteur en paramètre par l'entier en
   * paramètre et renvoie le résultat sous forme d'une nouvelle instance.
   * Les valeurs dans le nouveau vecteur sont transtypés en float.
   *
   * @param v, vecteur flottant à multiplier.
   * @param a, entier à multiplier avec le vecteur courant.
   *
   * @return résultat de la multiplication.
   */
  Vector2f operator*(Vector2f v, int a);

  /**
   * @brief Surcharge de l'opérateur de multiplication.
   *
   * Multiplie le vecteur en paramètre par l'entier en
   * paramètre et renvoie le résultat sous forme d'une nouvelle instance.
   * Les valeurs de la nouvelle instance sont transtypé en float.
   *
   * @param a, entier à multiplier avec le vecteur courant.
   * @param v, vecteur flottant à multiplier.
   *
   * @return résultat de la multiplication.
   */
  Vector2f operator*(int a, Vector2f v);

  /**
   * @brief Surcharge de l'opérateur de multiplication.
   *
   * Multiplie le vecteur en paramètre par le flottant simple précision en
   * paramètre et renvoie le résultat.
   *
   * @param v, vecteur flottant à multiplier.
   * @param a, flottant simple précision à multiplier.
   *
   * @return vecteur résultant de la multiplication.
   */
  Vector2f operator*(Vector2f v, float a);

  /**
   * @brief Surcharge de l'opérateur de multiplication.
   *
   * Multiplie le vecteur en paramètre par le flottant simple précision en
   * paramètre et renvoie le résultat.
   *
   * @param a, flottant simple précision à multiplier.
   * @param v, vecteur entier à multiplier.
   *
   * @return vecteur résultant de la multiplication.
   */
  Vector2f operator*(float a, Vector2f v);

  /**
   * @brief Surcharge de l'opérateur de multiplication.
   *
   * Multiplie le vecteur en paramètre par le flottant double précision en
   * paramètre et renvoie le résultat transtypé vers float.
   *
   * @param v, vecteur simple précision à multiplier.
   * @param a, flottant double précision à multiplier.
   *
   * @return vecteur résultant de la multiplication.
   */
  Vector2f operator*(Vector2f v, double a);

  /**
   * @brief Surcharge de l'opérateur de multiplication.
   *
   * Multiplie le vecteur en paramètre par le flottant double précision en
   * paramètre et renvoie le résultat transtypé vers float.
   *
   * @param a, flottant double précision à multiplier.
   * @param v, vecteur simple précision à multiplier.
   *
   * @return vecteur résultant de la multiplication.
   */
  Vector2f operator*(double a, Vector2f v);
};

#endif // !VECTOR2F_HEADER
