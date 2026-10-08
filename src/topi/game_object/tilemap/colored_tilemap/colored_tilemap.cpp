#include "colored_tilemap.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace topi::game_object::tilemap {
  ColoredTilemap::ColoredTilemap(size_t map_width, size_t map_height, size_t nb_layer, size_t tile_width, size_t tile_height, bool is_x_flipped, bool is_y_flipped) {
    this->_map_width = map_width;
    this->_map_height = map_height;
    this->_nb_layer = nb_layer;
    this->_tile_width = tile_width;
    this->_tile_height = tile_height;
    this->_is_x_flipped = is_x_flipped;
    this->_is_y_flipped = is_y_flipped;

    this->_tilemap = new uint64_t [this->_map_width * this->_map_height * this->_nb_layer];
    for (size_t i = 0; i < this->_map_width * this->_map_height * this->_nb_layer; ++i) {
      this->_tilemap[i] = 0;
    }
  }

  ColoredTilemap::~ColoredTilemap() {
    if (this->_tilemap != nullptr) {
      delete[] this->_tilemap;
    }
  }

  void ColoredTilemap::new_tile(uint64_t tile, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (this->_tileset.find(tile) != this->_tileset.end()) {
      std::cout << "WARNING : Redefination of the tile `" << tile << "` in the tileset." << std::endl;
    }

    this->_tileset[tile] = SDL_Color {r, g, b, a};
  }

  void ColoredTilemap::set(uint64_t tile, size_t x, size_t y, size_t layer) {
    if (x >= this->_map_width || y >= this->_map_height || layer >= this->_nb_layer) {
      throw std::out_of_range("Tilemap indexes out of range.");
    }

    this->_tilemap[x + this->_map_width * (y + this->_map_height * layer)] = tile;
  }

  uint64_t ColoredTilemap::get(size_t x, size_t y, size_t layer) const {
    if (x >= this->_map_width || y >= this->_map_height || layer >= this->_nb_layer) {
      throw std::out_of_range("Tilemap indexes out of range.");
    }

    return this->_tilemap[x + this->_map_width * (y + this->_map_height * layer)];
  }

  size_t ColoredTilemap::get_map_width() const {
    return this->_map_width;
  }

  size_t ColoredTilemap::get_map_height() const {
    return this->_map_height;
  }

  size_t ColoredTilemap::get_nb_layer() const {
    return this->_nb_layer;
  }

  size_t ColoredTilemap::get_tile_width() const {
    return this->_tile_width;
  }

  size_t ColoredTilemap::get_tile_height() const {
    return this->_tile_height;
  }

  size_t ColoredTilemap::operator()(size_t x, size_t y, size_t layer) const {
    return this->get(x, y, layer);
  }

  size_t& ColoredTilemap::operator()(size_t x, size_t y, size_t layer) {
    if (x >= this->_map_width || y >= this->_map_height || layer >= this->_nb_layer) {
      throw std::out_of_range("Tilemap indexes out of range.");
    }

    return this->_tilemap[x + this->_map_width * (y + this->_map_height * layer)];
  }

  void ColoredTilemap::flip_x() {
    this->_is_x_flipped = !this->_is_x_flipped;
  }

  void ColoredTilemap::flip_y() {
    this->_is_y_flipped = !this->_is_y_flipped;
  }

  void ColoredTilemap::exchange_tiles(size_t x1, size_t x2, size_t y1, size_t y2, size_t l1, size_t l2) {
    uint64_t temp = (*this)(x1, y1, l1);
    (*this)(x1, y1, l1) = (*this)(x2, y2, l2);
    (*this)(x2, y2, l2) = temp;
  }

  void ColoredTilemap::exchange_lines(size_t l1, size_t l2, size_t layer) {
    if (l1 == l2) return;

    for (size_t x = 0; x < this->_map_width; ++x) {
      this->exchange_tiles(x, x, l1, l2, layer, layer);
    }
  }

  void ColoredTilemap::exchange_columns(size_t c1, size_t c2, size_t layer) {
    if (c1 == c2) return;

    for (size_t y = 0; y < this->_map_height; ++y) {
      this->exchange_tiles(c1, c2, y, y, layer, layer);
    }
  }

  void ColoredTilemap::exchange_layers(size_t l1, size_t l2) {
    if (l1 == l2) return;

    for (size_t x = 0; x < this->_map_width; ++x) {
      for (size_t y = 0; y < this->_map_height; ++y) {
        this->exchange_tiles(x, x, y, y, l1, l2);
      }
    }
  }

  void ColoredTilemap::display_layer(render::RenderManager *renderer, size_t layer, double x_offset, double y_offset, double zoom) const {
    if (this->_tileset.empty()) {
      throw std::runtime_error("No tile to display.");
    }

    if (layer >= this->_nb_layer) {
      std::string error = "The layer `" + std::to_string(layer) + "` is unaccessible.";
      throw std::out_of_range(error);
    }

    if (zoom <= 0.0) {
      throw std::invalid_argument("The zoom factor should be superior to 0.");
    }

    for (size_t x = 0; x < this->_map_width; ++x) {
      for (size_t y = 0; y < this->_map_height; ++y) {
        uint64_t current_tile = this->get(x, y, layer);

        // On vérifie qu'on a une couleur d'affichage pour la tuile courante.
        if (this->_tileset.find(current_tile) == this->_tileset.end()) {
          std::string to_display = "Whether there is no color to display the `";
          to_display += std::to_string(current_tile);
          to_display += "` or the tilemap is not correctly initialised.";

          throw std::runtime_error(to_display);
        }

        SDL_Color current_color = this->_tileset.at(current_tile);
        size_t dx = (this->_is_x_flipped ? this->_map_width - x - 1 : x);
        size_t dy = (this->_is_y_flipped ? this->_map_height - y - 1 : y);

        renderer->draw_colored_filled_rectangle(
          static_cast<int>(static_cast<double>(dx) * static_cast<double>(this->_tile_width) * zoom + x_offset),
          static_cast<int>(static_cast<double>(dy) * static_cast<double>(this->_tile_height) * zoom + y_offset),
          static_cast<size_t>(static_cast<double>(this->_tile_width) * zoom),
          static_cast<size_t>(static_cast<double>(this->_tile_height) * zoom),
          current_color.r,
          current_color.g,
          current_color.b,
          current_color.a
        );
      }
    }
  }

  void ColoredTilemap::display(render::RenderManager *renderer, double x_offset, double y_offset, double zoom) const {
    for (size_t layer = 0; layer < this->_nb_layer; ++layer) {
      this->display_layer(renderer, layer, x_offset, y_offset, zoom);
    }
  }

  void ColoredTilemap::debug_disp(size_t layer) const {
    std::cout << "Colored tilemap layer: " << layer << std::endl;

    for (size_t x = 0; x < this->_map_width; ++x) {
      for (size_t y = 0; y < this->_map_height; ++y) {
        std::cout << (*this)(x, y, layer) << " ";
      }
      std::cout << std::endl;
    }
  }
}
