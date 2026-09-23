#ifndef COLORED_TILEMAP_HEADER
#define COLORED_TILEMAP_HEADER

#include <SDL2/SDL.h>
#include <cstdint>
#include <cstdlib>
#include <map>
#include "../../../renderer/renderer.hpp"

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
     * @param x_offset, position en x du tilemap à afficher, par défaut à 0.
     * @param y_offset, position en y du tilemap à afficher, par défaut à 0.
     * @param tile_width, largeur des tuiles de la tilemap à instancier, par défaut à 32.
     * @param tile_height, hauteur des tuiles de la tilemap à instancier, par défaut à 32.
     * @param is_x_flipped, détermine si on affiche la dernière tuile en x de la tilemap à gauche ou non, par défaut false donc non.
     * @param is_y_flipped, détermine si on offiche la dernière tuile en y de la tilemap en haut ou non, par défaut false donc non.
     */
    ColoredTilemap(
        size_t map_width,
        size_t map_height,
        int x_offset = 0,
        int y_offset = 0,
        size_t tile_width = 32,
        size_t tile_height = 32,
        bool is_x_flipped = false,
        bool is_y_flipped = false
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
     * @brief Inverse l'ordre d'affichage des tuiles en x.
     */
    void flip_x();

    /**
     * @brief Inverse l'ordre d'affichage des tuiles en y.
     */
    void flip_y();

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
    int x_offset;
    int y_offset;
    bool is_x_flipped;
    bool is_y_flipped;
};

#endif // !COLORED_TILEMAP_HEADER
