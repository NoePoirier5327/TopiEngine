#include "multilayer_colored_tilemap.hpp"
#include <iostream>

MultilayerColoredTilemap::MultilayerColoredTilemap(size_t _map_width, size_t _map_height, size_t _nb_layer, int _x_offset, int _y_offset, size_t _tile_width, size_t _tile_height) {
  this->map_width = _map_width;
  this->map_height = _map_height;
  this->nb_layer = _nb_layer;
  this->tile_width = _tile_width;
  this->tile_height = _tile_height;
  this->x_offset = _x_offset;
  this->y_offset = _y_offset;

  this->tilemap = new uint64_t [this->map_width * this->map_height * this->nb_layer];
  for (size_t i = 0; i < this->map_width * this->map_height * this->nb_layer; ++i) {
    this->tilemap[i] = 0;
  }
}

MultilayerColoredTilemap::~MultilayerColoredTilemap() {
  if (this->tilemap != nullptr) {
    delete[] this->tilemap;
  }
}

void MultilayerColoredTilemap::new_tile(uint64_t tile, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (this->tileset.find(tile) != this->tileset.end()) {
    std::cout << "WARNING : Redefination of the tile `" << tile << "` in the tileset." << std::endl;
  }

  this->tileset[tile] = SDL_Color {r, g, b, a};
}

void MultilayerColoredTilemap::set(size_t x, size_t y, size_t layer, uint64_t tile) {
  if (x >= this->map_width || y >= this->map_height || layer >= this->nb_layer) {
    throw std::invalid_argument("Tilemap indexes out of range.");
  }

  this->tilemap[x + this->map_width * (y + this->map_height * layer)] = tile;
}

uint64_t MultilayerColoredTilemap::get(size_t x, size_t y, size_t layer) const {
  if (x >= this->map_width || y >= this->map_height || layer >= this->nb_layer) {
    throw std::invalid_argument("Tilemap indexes out of range.");
  }

  return this->tilemap[x + this->map_width * (y + this->map_height * layer)];
}

size_t MultilayerColoredTilemap::get_map_width() const {
  return this->map_width;
}

size_t MultilayerColoredTilemap::get_map_height() const {
  return this->map_height;
}

size_t MultilayerColoredTilemap::get_nb_layer() const {
  return this->nb_layer;
}

size_t MultilayerColoredTilemap::get_tile_width() const {
  return this->tile_width;
}

size_t MultilayerColoredTilemap::get_tile_height() const {
  return this->tile_height;
}

size_t MultilayerColoredTilemap::operator()(size_t x, size_t y, size_t layer) const {
  return this->get(x, y, layer);
}

size_t& MultilayerColoredTilemap::operator()(size_t x, size_t y, size_t layer) {
  if (x >= this->map_width || y >= this->map_height || layer >= this->nb_layer) {
    throw std::invalid_argument("Tilemap indexes out of range.");
  }

  return this->tilemap[x + this->map_width * (y + this->map_height * layer)];
}

void MultilayerColoredTilemap::display(Renderer *renderer, size_t layer) const {
  if (this->tileset.empty()) {
    throw std::runtime_error("No tile to display.");
  }

  if (layer >= this->nb_layer) {
    std::string error = "The layer `" + std::to_string(layer) + "` is unaccessible.";
    throw std::invalid_argument(error);
  }

  for (size_t x = 0; x < this->map_width; ++x) {
    for (size_t y = 0; y < this->map_height; ++y) {
      uint64_t current_tile = this->get(x, y, layer);

      // On vérifie qu'on a une couleur d'affichage pour la tuile courante.
      if (this->tileset.find(current_tile) == this->tileset.end()) {
        std::string to_display = "Wether there is no color to display the `";
        to_display += std::to_string(current_tile);
        to_display += "` or the tilemap is not correctly initialised.";

        throw std::runtime_error(to_display);
      }

      SDL_Color current_color = this->tileset.at(current_tile);
      renderer->new_colored_filled_rectangle(
          static_cast<int>(x * this->tile_width + this->x_offset),
          static_cast<int>(y * this->tile_height + this->y_offset),
          this->tile_width,
          this->tile_height,
          current_color.r,
          current_color.g,
          current_color.b,
          current_color.a
      );
    }
  }
}
