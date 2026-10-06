#ifndef RESOURCE_MANAGER_HEADER
#define RESOURCE_MANAGER_HEADER

#include <cstdlib>
#include <string>
#include <map>
#include <SDL2/SDL_ttf.h>

namespace topi::resource {
  /**
   * @brief Représente un doublet font_path et size.
   *
   * Cette structure est utilisée pour le cache des polices
   * d'écritures, elle permet la réallocation de police avec une
   * taille différente si besoin.
   */
  struct Font {
    std::string font_path;
    size_t font_size;

    bool operator<(const Font &other) const;
  };

  /**
   * @class ResourceManager
   * @brief Gestionnaire de ressource graphique du moteur.
   *
   * S'occupe de l'allocation et la desallocation des images,
   * sons et polices d'écritures.
   *
   * Il ne peut y avoir qu'une seule intance à tourner à la fois.
   */
  class ResourceManager {
    public:
      /**
       * @brief Instancie le gestionnaire de ressources.
       *
       * @throw std::runtime_error une instance est déjà en fonctionnement.
       */
      ResourceManager();

      /**
       * @brief Désalloue toutes les ressources sdl2 chargées depuis l'instanciation.
       */
      ~ResourceManager();

      /**
       * @brief Charge une police d'écriture et renvoie son point d'accès dans le gestionnaire.
       *
       * @throw std::runtime_error si impossible de charger la police d'écriture.
       */
      void load_font(const std::string &font_path, size_t font_size);

      /**
       * @brief Renvoie la police de caractère en paramètre.
       *
       * Si la police demandée n'est pas chargée, alors, la charge dans
       * le cache et la renvoie.
       *
       * @param font_path, chemin vers la police à laquelle on tente d'accéder.
       * @param font_size, taille de la police à laquelle on tente d'accéder.
       *
       * @return pointeur vers la police à afficher.
       *
       * @throw std::runtime_error si impossible de charger la police d'écriture.
       */
      TTF_Font *get_font(const std::string &font_path, size_t font_size);

      /**
       * @brief Désalloue la police en paramètre.
       *
       * Supprime du cache toute occurrence de la police désignée 
       * par le paramètre.
       */
      void unload_fonts(const std::string &font_path);

      /**
       * @brief Décharge toute la mémoire accumulée par le gestionnaire de ressources.
       */
      void unload_everything();

    private:
      /**
       * @brief Gère le cache des polices d'écriture.
       *
       * Est appelé au chargement d'une nouvelle police.
       * Si le nombre total de police ayant le même chemin que celui
       * en paramètre est dépassé,
       * alors, on en désalloue un au hasard pour permettre l'allocation de nouveau.
       *
       * Sinon, si la taille global autorisée est dépassée,
       * alors, on en désalloue une au hasard.
       *
       * @param font_path, police décriture à vérifier.
       */
      void handle_font_cache_size(const std::string &font_path);

      /**
       * @brief Renvoie le nombre totale de polices chargée dans le cache.
       */
      size_t get_global_font_cache_size() const;

      /**
       * @brief Renvoie le nombre d'occurrence de polices chargée ayant pour source celle en paramètre.
       */
      size_t get_nb_of_font_in_cache_by_path(const std::string &font_path) const;

      /**
       * @brief Décharge la police en paramètre.
       */
      void unload_font_by_path_and_size(const Font &font);

      /**
       * @brief Récupère l'identifiant d'une police ayant le même chemin que celui en paramètre.
       *
       * @throw std::runtime_error si aucune police chargée depuis le chemin en paramètre.
       */
      const Font *pick_font_by_path(const std::string &font_path) const;

      std::map<Font, TTF_Font*> fonts;
  };
}

#endif // !RESOURCE_MANAGER_HEADER
