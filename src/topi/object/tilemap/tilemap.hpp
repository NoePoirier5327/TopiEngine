#ifndef TILEMAP_HEADER
#define TILEMAP_HEADER

#include <cstdint>
#include <cstdlib>
#include <map>
#include <SDL2/SDL.h>
#include "../../renderer/renderer.hpp"

/**
 * @class ColoredTilemap
 * @brief Tilemap 2D vue du dessus fait de rectangle de couleur.
 */
class ColoredTilemap {
  public:
    /**
     * @brief Instancie une tilemap de la taille en paramètre.
     *
     * @param map_width, largeur de la tilemap à instancier.
     * @param map_height, hauteur de la tilemap à instancier.
     * @param tile_width, largeur des tuiles de la tilemap à instancier.
     * @param tile_height, hauteur des tuiles de la tilemap à instancier.
     */
    ColoredTilemap(size_t map_width, size_t map_height, size_t tile_width, size_t tile_height);

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
     * @param x, coordonnée en abssice à laquelle accéder.
     * @param y, coordonnée en ordonnée à laquelle accéder.
     * @param tile, tuile à écrire à la position en paramètre.
     * 
     * @throw std::invalid_argument si x >= map_width || y >= map_height.
     * @throw std::invalid_argument tile inconnus dans le tileset.
     */
    void set(size_t x, size_t y, uint64_t tile);

    /**
     * @brief Accesseur de tuile à la position en paramètre.
     * 
     * @param x, coordonnée en abssice à laquelle accéder.
     * @param y, coordonnée en ordonnée à laquelle accéder.
     *
     * @return valeur de la tuile dans la tilemap.
     *
     * @throw std::invalid_argument si x >= map_width || y >= map_height
     */
    uint64_t get(size_t x, size_t y) const;

    /**
     * @brief Accesseur de la largeur de la carte.
     */
    size_t get_map_width() const;

    /**
     * @brief Accesseur de la hauteur de la carte.
     */
    size_t get_map_height() const;

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
     *
     * @return valeur de la tuile dans la tilemap.
     *
     * @throw std::invalid_argument si x >= map_width || y >= map_height
     */
    uint64_t operator()(size_t x, size_t y) const;

    /**
     * @brief Surcharge des parenthèses pour l'accès en écriture à la tilemap courante.
     *
     * @param x, coordonnée en abssice à laquelle accéder.
     * @param y, coordonnée en ordonnée à laquelle accéder.
     *
     * @return référence vers la tuile dans la tilemap.
     *
     * @throw std::invalid_argument si x >= map_width || y >= map_height
     */
    uint64_t& operator()(size_t x, size_t y);

    /**
     * @brief Affiche la tilemap interne via le moteur de rendue du moteur.
     *
     * @param renderer, instance du moteur de rendue.
     *
     * @throw std::runtime_error si tileset vide.
     */
    void display(Renderer* renderer) const;

  private:
    std::map<uint64_t, SDL_Color> tileset;
    uint64_t *tilemap;
    size_t map_width;
    size_t map_height;
    size_t tile_width;
    size_t tile_height;
};

/**
 * @class MultilayerColoredTilemap
 * @brief Tilemap 3D vue du dessus fait de rectangle de couleur.
 */
class MultilayerColoredTilemap {
  public:
    /**
     * @brief Instancie une tilemap de la taille en paramètre avec au moins une couche.
     *
     * @param map_width, largeur de la tilemap à instancier.
     * @param map_height, hauteur de la tilemap à instancier.
     * @param nb_layer, nombre de couche du tilemap, au minimum 1.
     * @param tile_width, largeur des tuiles de la tilemap à instancier.
     * @param tile_height, hauteur des tuiles de la tilemap à instancier.
     *
     * @throw std::invalid_argument si nb_layer < 1
     */
    MultilayerColoredTilemap(size_t map_width, size_t map_height, size_t nb_layer, size_t tile_width, size_t tile_height);

    /**
     * @brief Désalloue le tilemap courante.
     */
    ~MultilayerColoredTilemap();

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
     * @param x, coordonnée en abssice à laquelle accéder.
     * @param y, coordonnée en ordonnée à laquelle accéder.
     * @param layer, couche à laquelle accéder.
     * @param tile, tuile à écrire à la position en paramètre.
     * 
     * @throw std::invalid_argument si x >= map_width || y >= map_height || layer >= nb_layer.
     * @throw std::invalid_argument tile inconnus dans le tileset.
     */
    void set(size_t x, size_t y, size_t layer, uint64_t tile);

    /**
     * @brief Accesseur de tuile à la position en paramètre.
     * 
     * @param x, coordonnée en abssice à laquelle accéder.
     * @param y, coordonnée en ordonnée à laquelle accéder.
     * @param layer, couche à laquelle accéder.
     *
     * @return valeur de la tuile dans la tilemap.
     *
     * @throw std::invalid_argument si x >= map_width || y >= map_height || layer >= nb_layer
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
     * @throw std::invalid_argument si x >= map_width || y >= map_height || layer >= nb_layer
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
     * @throw std::invalid_argument si x >= map_width || y >= map_height || layer >= nb_layer
     */
    uint64_t& operator()(size_t x, size_t y, size_t layer);

    /**
     * @brief Affiche une couche de la tilemap interne via le moteur de rendue du moteur.
     *
     * @param renderer, instance du moteur de rendue.
     * @param layer, couche à afficher.
     *
     * @throw std::runtime_error si tileset vide.
     * @throw std::invalid_argument si layer >= nb_layer.
     */
    void display(Renderer* renderer, size_t layer) const;

  private:
    std::map<uint64_t, SDL_Color> tileset;
    uint64_t *tilemap;
    size_t map_width;
    size_t map_height;
    size_t nb_layer;
    size_t tile_width;
    size_t tile_height;
};

#endif // !TILEMAP_HEADER
