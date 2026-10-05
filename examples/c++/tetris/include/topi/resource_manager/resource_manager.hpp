#ifndef RESOURCE_MANAGER_HEADER
#define RESOURCE_MANAGER_HEADER

#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL_ttf.h>

namespace topi::resource {
  using FontId = size_t;
  //using TextureId = size_t;
  
  /**
   * @brief Charge une police d'écriture dans le gestionnaire de ressource.
   *
   * @param font_path, chemin vers la police à charger.
   * @param font_size, taille de la police d'écriture à charger.
   * @return identifiant associé à la police chargée.
   *
   * @throw std::runtime_error si impossible de charger la police.
   * @throw std::runtime_error si l'application n'est pas instanciée.
   */
  FontId load_font(const std::string &font_path, int font_size);

  /**
   * @brief Décharge la police d'écriture en paramètre.
   *
   * @param font, police à décharger.
   *
   * @throw std::runtime_error si la police qu'on veut décharger est introuvable dans le gestionnaire de ressource.
   * @throw std::runtime_error si l'application n'est pas chargée.
   */
  void unload_font(FontId font);

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
      FontId load_font(const std::string &font_path, int font_size);

      /**
       * @brief Renvoie la police de caractère en paramètre.
       *
       * @throw std::runtime_error la police est introuvable.
       */
      TTF_Font *get_font(FontId font_id) const;

      /**
       * @brief Désalloue la police en paramètre.
       *
       * @throw std::runtime_error si police non trouvée.
       */
      void unload_font(FontId font);

      /**
       * @brief Décharge toute la mémoire accumulée par le gestionnaire de ressources.
       */
      void unload_everything();

    private:
      FontId next_font_id;
      std::vector<FontId> freed_font_id;
      std::map<FontId, TTF_Font*> fonts;
  };
}

#endif // !RESOURCE_MANAGER_HEADER
