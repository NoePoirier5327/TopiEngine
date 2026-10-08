#ifndef MULTILAYER_COLORED_TILEMAP_HEADER
#define MULTILAYER_COLORED_TILEMAP_HEADER

#include <cstdint>
#include <cstdlib>
#include <map>
#include <SDL2/SDL.h>
#include "../../../render_manager/render_manager.hpp"

namespace topi::game_object::tilemap {
  /**
   * @class ColoredTilemap
   * @brief Tilemap 3D vue du dessus fait de rectangle de couleur.
   */
  class ColoredTilemap {
    public:
      /**
       * @brief Instancie une tilemap de la taille en paramètre avec au moins une couche.
       *
       * @param map_width, largeur de la tilemap à instancier.
       * @param map_height, hauteur de la tilemap à instancier.
       * @param nb_layer, nombre de couche du tilemap, au minimum 1.
       * @param tile_width, largeur des tuiles de la tilemap à instancier, par défaut à 32.
       * @param tile_height, hauteur des tuiles de la tilemap à instancier, par défaut à 32.
       * @param is_x_flipped, détermine si on affiche la dernière tuile en x de la tilemap à gauche ou non, par défaut false donc non.
       * @param is_y_flipped, détermine si on affiche la dernière tuile en y de la tilemap en haut ou non, par défaut false donc non.
       *
       * @throw std::invalid_argument si nb_layer < 1
       */
      ColoredTilemap(
        size_t map_width,
        size_t map_height,
        size_t nb_layer,
        size_t tile_width = 32,
        size_t tile_height = 32,
        bool is_x_flipped = false,
        bool is_y_fliiped = false
      );

      /**
       * @brief Désalloue le tilemap courante.
       */
      ~ColoredTilemap();

      /**
       * @brief Ajoute une nouvelle tuile au tileset interne.
       *
       * @param tile, tuile à ajouter au tileset.
       * @param r, taux de rouge de la tuile à ajouter.
       * @param g, taux de vert de la tuile à ajouter.
       * @param b, taux de bleu de la tuile à ajouter.
       * @param a, taux de transparence de la tuile à ajouter.
       */
      void new_tile(uint64_t tile, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
   
      /**
       * @brief Mutateur de la tilemap courante.
       *
       * @param tile, tuile à écrire à la position en paramètre.
       * @param x, coordonnée en abssice à laquelle accéder.
       * @param y, coordonnée en ordonnée à laquelle accéder.
       * @param layer, couche à laquelle accéder.
       * 
       * @throw std::out_of_range si x >= map_width || y >= map_height || layer >= nb_layer.
       * @throw std::invalid_argument tile inconnus dans le tileset.
       */
      void set(uint64_t tile, size_t x, size_t y, size_t layer);

      /**
       * @brief Accesseur de tuile à la position en paramètre.
       * 
       * @param x, coordonnée en abssice à laquelle accéder.
       * @param y, coordonnée en ordonnée à laquelle accéder.
       * @param layer, couche à laquelle accéder.
       *
       * @return valeur de la tuile dans la tilemap.
       *
       * @throw std::out_of_range si x >= map_width || y >= map_height || layer >= nb_layer
       */
      uint64_t get(size_t x, size_t y, size_t layer) const;

      /**
       * @brief Accesseur de la largeur de la carte.
       */
      size_t get_map_width() const;

      /**
       * @brief Accesseur de la hauteur de la carte.
       */
      size_t get_map_height() const;

      /**
       * @brief Accesseur du nombre de couche du tilemap.
       */
      size_t get_nb_layer() const;

      /**
       * @brief Accesseur de la largeur des tuiles dans le tilemap.
       */
      size_t get_tile_width() const;

      /**
       * @brief Accesseur de la hauteur des tuiles dans le tilemap.
       */
      size_t get_tile_height() const;

      /**
       * @brief Surcharge des parenthèses pour l'accès en lecture à la tilemap courante.
       *
       * @param x, coordonnée en abssice à laquelle accéder.
       * @param y, coordonnée en ordonnée à laquelle accéder.
       * @param layer, couche à laquelle accéder.
       *
       * @return valeur de la tuile dans la tilemap.
       *
       * @throw std::out_of_range si x >= map_width || y >= map_height || layer >= nb_layer
       */
      uint64_t operator()(size_t x, size_t y, size_t layer) const;

      /**
       * @brief Surcharge des parenthèses pour l'accès en écriture à la tilemap courante.
       *
       * @param x, coordonnée en abssice à laquelle accéder.
       * @param y, coordonnée en ordonnée à laquelle accéder.
       * @param layer, couche à laquelle accéder.
       *
       * @return référence vers la tuile dans la tilemap.
       *
       * @throw std::out_of_range si x >= map_width || y >= map_height || layer >= nb_layer
       */
      uint64_t& operator()(size_t x, size_t y, size_t layer);

      /**
       * @brief Echange deux tuiles dans la carte par leurs positions.
       *
       * @throw std::out_of_range si x1 >= map_width || x2 >= map_width || y1 >= map_height || y2 >= map_height || l1 >= nb_layer || l2 >= nb_layer.
       */
      void exchange_tiles(size_t x1, size_t x2, size_t y1, size_t y2, size_t l1, size_t l2);

      /**
       * @brief Permute la ligne 1 avec la ligne 2 de la couche en paramètre.
       *
       * @throw std::out_of_range si l1 >= map_height || l2 >= map_height.
       */
      void exchange_lines(size_t l1, size_t l2, size_t layer);

      /**
       * @brief Permute la colonne 1 avec la colonne 2 de la couche en paramètre.
       *
       * @throw std::out_of_range si c1 >= map_width || c2 >= map_width
       */
      void exchange_columns(size_t c1, size_t c2, size_t layer);

      /**
       * @brief Permute la couche 1 avec la couche 2.
       *
       * @throw std::out_of_range si l1 >= nb_layer || l2 >= nb_layer
       */
      void exchange_layers(size_t l1, size_t l2);

      /**
       * @brief Inverse l'ordre d'affichage de la tilemap en x.
       */
      void flip_x();

      /**
       * @brief Inverse l'ordre d'affichage de la tilemap en y.
       */
      void flip_y();

      /**
       * @brief Affiche une couche de la tilemap interne via le moteur de rendue du moteur.
       *
       * @param renderer, instance du moteur de rendue.
       * @param layer, couche à afficher
       * @param x_offset, offset d'affichage en x de la tilemap courante, par défaut à 0.0.
       * @param y_offset, offset d'affichage en y de la tilemap courante, par défaut à 0.0.
       * @param zoom, taux d'agrandissement d'affichage de la tilemap courante, par défaut à 1.0.
       *
       * @throw std::runtime_error si tileset vide.
       * @throw std::out_of_range si layer >= nb_layer.
       * @throw std::invalid_argument si zoom <= 0
       */
      void display_layer(render::RenderManager* renderer, size_t layer, double x_offset = 0.0, double y_offset = 0.0, double zoom = 1.0) const;

      /**
       * @brief Affiche l'entièretée des couches de la tilemap courante.
       *
       * @param renderer, instance du moteur de rendue.
       * @param x_offset, offset d'affichage en x, par défaut à 0.0.
       * @param y_offset, offset d'affichage en y, par défaut à 0.0.
       * @param zoom, taux d'agrandissement de l'affichage de la tilemap courante, par défaut à 1.0.
       *
       * @throw std::runtime_error si tileset vide.
       * @throw std::invalid_argument si soom <= 0;
       */
      void display(render::RenderManager *renderer, double x_offset = 0.0, double y_offset = 0.0, double zoom = 1.0) const;

      /**
       * @brief Affiche la couche en paramètre de la tilemap courante dans la console.
       * 
       * Pas de vérification sur la présence des tuiles durant l'affichage
       * pour simplifier le débuggage.
       *
       * @throw std::invalid_argument si layer >= nb_layer
       */
      void debug_disp(size_t layer) const;

    private:
      std::map<uint64_t, SDL_Color> _tileset;
      uint64_t *_tilemap;
      size_t _map_width;
      size_t _map_height;
      size_t _nb_layer;
      size_t _tile_width;
      size_t _tile_height;
      bool _is_x_flipped;
      bool _is_y_flipped;
  };
}

#endif // !MULTILAYER_COLORED_TILEMAP_HEADER
