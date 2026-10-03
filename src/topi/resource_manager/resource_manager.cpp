#include "resource_manager.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <string>

namespace topi::resource {
  static bool ALREADY_INSTANCED = false;

  ResourceManager::ResourceManager() {
    if (ALREADY_INSTANCED) {
      throw std::runtime_error("Only one instance of the resource manager can run.");
    }

    this->next_font_id = 0;
    ALREADY_INSTANCED = true;
  }

  ResourceManager::~ResourceManager() {
    this->unload_everything();

    ALREADY_INSTANCED = false;
  }

  FontId ResourceManager::load_font(const std::string &font_path, int size) {
    FontId font_id;
    if (this->freed_font_id.empty()) {
      font_id = this->next_font_id;
      this->next_font_id++;
    }
    else {
      font_id = this->freed_font_id.back();
      this->freed_font_id.pop_back();
    }

    TTF_Font *font = TTF_OpenFont(font_path.c_str(), size);

    if (!font) {
      std::string error = "Failed to open the `" + font_path + "` font.\n" + TTF_GetError();
      throw std::runtime_error(error);
    }

    this->fonts[font_id] = font;
    return font_id;
  }

  TTF_Font *ResourceManager::get_font(FontId font_id) const {
    auto id = this->fonts.find(font_id);
    if (id == this->fonts.end()) {
      throw std::runtime_error("Failed to get the desired font `" + std::to_string(font_id) + "`.");
    }

    return id->second;
  }

  void ResourceManager::free_font(FontId font_id) {
    // Si la police qu'on cherche à décharger est introuvable,
    // on renvoie une erreur.
    auto id = this->fonts.find(font_id);
    if (id == this->fonts.end()) {
      throw std::runtime_error("Unable to unload the `" + std::to_string(font_id) + "` font.");
    }
    
    this->freed_font_id.push_back(font_id);
    TTF_CloseFont(id->second);
    this->fonts.erase(font_id);
  }

  void ResourceManager::unload_everything() {
    for (auto &pair: this->fonts) {
      if (pair.second != nullptr) {
        TTF_CloseFont(pair.second);
      }
    }
    this->fonts.clear();
    this->freed_font_id.clear();
    this->next_font_id = 0;
  }
}
