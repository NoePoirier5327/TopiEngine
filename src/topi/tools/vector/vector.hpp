#ifndef VECTOR_HEADER
#define VECTOR_HEADER

namespace topi::tools::vector {
  /**
   * @class Vector2i
   * @brief Vecteur en deux dimensions composés d'entiers. 
   */
  class Vector2i {
    public:
      /**
       * @brief Constructeur simple du vecteur entiers en deux dimensions.
       *
       * @param x, premier élément du 2uplet du vecteur courant.
       * @param y, second élément du 2uplet du vecteur courant.
       */
      Vector2i(int x, int y);

      /**
       * @brief Constructeur en copie.
       *
       * Copie le contenu du vecteur en paramètre dans le but
       * dans instancier un nouveau.
       *
       * @param v, vecteur à copier pour la création.
       */
      Vector2i(const Vector2i& v);

      /**
       * @brief Constructeur en déplacement.
       *
       * Transfère le contenu du vecteur en paramètre dans
       * une nouvelle instance créer par ce constructeur.
       *
       * @param v, vecteur dont le contenu est à transférer.
       */
      Vector2i(Vector2i &&v) noexcept;

      /**
       * @brief Surcharge de l'opérateur d'égalité.
       *
       * Vérifie si le contenu du vecteur en paramètre est
       * le même que celui courant.
       *
       * @param v, vecteur à comparer avec l'instance courante.
       *
       * @return true s'ils sont égaux, false sinon.
       */
      bool operator==(const Vector2i &v) const;

      /**
       * @brief Surcharge de l'opérateur de multiplication.
       *
       * Multiplie le vecteur interne courant par l'entier en
       * paramètre et renvoie le résultat sous forme d'une nouvelle instance.
       *
       * @param a, entier à multiplier avec le vecteur courant.
       *
       * @return résultat de la multiplication.
       */
      Vector2i operator*(int a) const;

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
      Vector2i operator+(const Vector2i &v) const;

      /**
       * @brief Surchargeur de l'opérateur d'assignation.
       *
       * Copie le vecteur en paramètre dans celui courant.
       *
       * @param v, vecteur à assigner.
       *
       * @return vecteur résultant de l'assignation.
       */
      Vector2i& operator=(const Vector2i &v);

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
      Vector2i& operator=(Vector2i &&v) noexcept;

      /**
       * @brief Affiche le contenu du vecteur courant sur la console.
       */
      void debug_disp() const;

      int x;
      int y;
  };
};

#endif // !VECTOR_HEADER
