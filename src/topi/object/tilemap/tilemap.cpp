#include "tilemap.hpp"
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <string>

ColoredTilemap::ColoredTilemap(size_t _map_width, size_t _map_height, size_t _tile_width, size_t _tile_height) {
  this->map_width = _map_width;
  this->map_height = _map_height;
  this->tile_width = _tile_width;
  this->tile_height = _tile_height;

  this->tilemap = new uint64_t [this->map_width * this->map_height];
  for (size_t i = 0; i < this->map_width * this->map_height; ++i) {
    this->tilemap[i] = 0;
  }
}

ColoredTilemap::~ColoredTilemap() {
  if (this->tilemap != nullptr) {
    delete[] this->tilemap;
  }
}

void ColoredTilemap::new_tile(uint64_t tile, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (this->tileset.find(tile) != this->tileset.end()) {
    std::cout << "WARNING : Redefination of the tile `" << tile << "` in the tileset." << std::endl;
  }

  this->tileset[tile] = SDL_Color {r, g, b, a};
}

void ColoredTilemap::set(size_t x, size_t y, uint64_t tile) {
  if (x >= this->map_width || y >= this->map_height) {
    throw std::invalid_argument("Tilemap indexes out of range.");
  }

  this->tilemap[y * this->map_width + x] = tile;
}

uint64_t ColoredTilemap::get(size_t x, size_t y) const {
  if (x >= this->map_width || y >= this->map_height) {
    throw std::invalid_argument("Tilemap indexes out of range.");
  }

  return this->tilemap[y * this->map_width + x];
}

size_t ColoredTilemap::get_map_width() const {
  return this->map_width;
}

size_t ColoredTilemap::get_map_height() const {
  return this->map_height;
}

size_t ColoredTilemap::get_tile_width() const {
  return this->tile_width;
}

size_t ColoredTilemap::get_tile_height() const {
  return this->tile_height;
}

size_t ColoredTilemap::operator()(size_t x, size_t y) const {
  return this->get(x, y);
}

size_t& ColoredTilemap::operator()(size_t x, size_t y) {
  if (x >= this->map_width || y >= this->map_height) {
    throw std::invalid_argument("Tilemap indexes out of range.");
  }

  return this->tilemap[y * this->map_width + x];
}

void ColoredTilemap::display(Renderer *renderer) const {
  if (this->tileset.empty()) {
    throw std::runtime_error("No tile to display.");
  }

  for (size_t x = 0; x < this->map_width; ++x) {
    for (size_t y = 0; y < this->map_height; ++y) {
      uint64_t current_tile = this->get(x, y);

      // On vérifie qu'on a une couleur d'affichage pour la tuile courante.
      if (this->tileset.find(current_tile) == this->tileset.end()) {
        std::string to_display = "Wether there is no color to display the `";
        to_display += std::to_string(current_tile);
        to_display += "` or the tilemap is not correctly initialised.";

        throw std::runtime_error(to_display);
      }

      SDL_Color current_color = this->tileset.at(current_tile);
      renderer->new_colored_filled_rectangle(
          static_cast<int>(x * this->tile_width),
          static_cast<int>(y * this->tile_height),
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
