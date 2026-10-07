#include "resource_manager.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <tuple>

namespace topi::resource {
  static ResourceManager *INSTANCE = nullptr;
  const size_t FONT_CACHE_SIZE_PER_ELEMENT = 10;
  const size_t GLOBAL_FONT_CACHE_SIZE = 20; 

  /// Code du wrapper ///

  ResourceManager *get_manager_instance() {
    if (INSTANCE == nullptr)
      throw std::runtime_error("The resource manager should be instanciated before performing this action.");

    return INSTANCE;
  }

  void load_font(const std::string &font_path, size_t font_size) {
    get_manager_instance()->load_font(font_path, font_size);
  }

  void unload_font(const std::string &font_path) {
    get_manager_instance()->unload_fonts(font_path);
  }

  /// Code de ResourceManager ///

  ResourceManager::ResourceManager() {
    if (INSTANCE != nullptr) {
      throw std::runtime_error("Only one instance of the resource manager can run.");
    }

    INSTANCE = this;
  }

  ResourceManager::~ResourceManager() {
    this->unload_everything();
    INSTANCE = nullptr;
  }

  void ResourceManager::load_font(const std::string &font_path, size_t font_size) {
    // Si elle est déjà chargée, on ne fait rien.
    Font target_font = {font_path, font_size};
    if (this->fonts.find(target_font) != this->fonts.end()) return;

    // On gère les exigences du cache.
    this->handle_font_cache_size(font_path);

    // Efin, on charge la nouvelle police.
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), static_cast<int>(font_size));

    if (!font) {
      std::string error = "Failed to open the `" + font_path + "` font.\n" + TTF_GetError();
      throw std::runtime_error(error);
    }

    this->fonts[target_font] = font;
  }

  TTF_Font *ResourceManager::get_font(const std::string &font_path, size_t font_size) {
    // Si la police est introuvable, alors, on la charge puis la renvoie.
    Font target_font = {font_path, font_size};
    auto font_id_wrapper = this->fonts.find(target_font);
    if (font_id_wrapper == this->fonts.end()) {
      this->load_font(font_path, font_size);
      font_id_wrapper = this->fonts.find(target_font);
    }

    // Puis, on la renvoie
    return this->fonts[font_id_wrapper->first];
  }

  void ResourceManager::unload_fonts(const std::string &font_path) {
    for (auto pair = this->fonts.begin(); pair != this->fonts.end();) {
      if (pair->first.font_path == font_path) {
        TTF_CloseFont(pair->second);
        pair = this->fonts.erase(pair);
      }
      else {
        pair++;
      }
    }
  }

  void ResourceManager::unload_everything() {
    // On désalloue les polices chargées.
    for (auto &pair: this->fonts) {
      if (pair.second != nullptr) {
        TTF_CloseFont(pair.second);
      }
    }

    // On désalloue les structures de stockages.
    this->fonts.clear();
  }

  void ResourceManager::handle_font_cache_size(const std::string &font_path) {
    // si le groupe de polices avec le même 
    // chemin que celui qu'on souhaite allouer est plein,
    // alors on en récupère un au hasard et on le désalloue.
    if (this->get_nb_of_font_in_cache_by_path(font_path) >= FONT_CACHE_SIZE_PER_ELEMENT) {
      // On sait que les préconditions de pick_font_by_path sont remplis
      // donc on va forcément obtenir un pointeur vers une font.
      const Font *font = this->pick_font_by_path(font_path);
      this->unload_font_by_path_and_size(*font);
    }

    // Si on a désalloué une police ayant le même chemin
    // que celui en paramètre, alors la taille global du
    // dictionnaire sous-jacent à diminué.
    // Donc la condition ci-dessous permet la rupture de séquence

    // Si la taille global est plus petite que la taille autorisée
    // alors, on ne fait rien.
    if (this->get_global_font_cache_size() < GLOBAL_FONT_CACHE_SIZE) return;

    // Sinon, on en désalloue un quelconque pour faire de la place
    // et permettre l'allocation.
    this->unload_font_by_path_and_size(this->fonts.begin()->first);
  }

  size_t ResourceManager::get_global_font_cache_size() const {
    return this->fonts.size();
  }

  size_t ResourceManager::get_nb_of_font_in_cache_by_path(const std::string &font_path) const {
    size_t nb_font = 0;

    for (const auto &pair : this->fonts) {
      if (pair.first.font_path == font_path) nb_font++;
    }

    return nb_font;
  }

  void ResourceManager::unload_font_by_path_and_size(const Font &font) {
    auto iterator = this->fonts.find(font);
    if (iterator == this->fonts.end()) return;

    TTF_CloseFont(iterator->second);
    this->fonts.erase(iterator);
  }

  const Font *ResourceManager::pick_font_by_path(const std::string &font_path) const {
    for (const auto &iterator : this->fonts) {
      if (iterator.first.font_path == font_path) {
        return &iterator.first;
      }
    }

    std::string error = "There should be at least one font loaded with this path " + font_path + " in memory.";
    throw std::runtime_error(error);
  }

  bool Font::operator<(const Font &other) const {
    return std::tie(font_path, font_size) < std::tie(other.font_path, other.font_size);
  }
}
