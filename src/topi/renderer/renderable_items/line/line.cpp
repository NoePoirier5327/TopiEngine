#include "line.hpp"
#include <cmath>

namespace topi::render::items {
  Line::Line(int _x1, int _y1, int _x2, int _y2, size_t _thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->color = SDL_Color {r, g, b, a};
    this->x1 = _x1;
    this->y1 = _y1;
    this->x2 = _x2;
    this->y2 = _y2;
    this->thickness = _thickness;
  }

  void Line::display(SDL_Renderer *renderer) const {
    // On calcul le vecteur de norme thickness normal à la ligne courante.
    float dx = static_cast<float>(this->x2) - static_cast<float>(this->x1);
    float dy = static_cast<float>(this->y2) - static_cast<float>(this->y1);
    float length = sqrt(dx*dx + dy*dy);

    if (length == 0) return;

    float half_thickness = static_cast<float>(this->thickness) * 0.5f;
    float ox = -(dy / length) * half_thickness;
    float oy = (dx / length) * half_thickness;

    // On calcul les coordonnées de vertices définissant l'affichage de la ligne.
    SDL_Vertex vertices[4] = {
      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->x1) + ox, static_cast<float>(this->y1) + oy},
        this->color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->x1) - ox, static_cast<float>(this->y1) - oy},
        this->color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->x2) - ox, static_cast<float>(this->y2) - oy},
        this->color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->x2) + ox, static_cast<float>(this->y2) + oy},
        this->color,
        SDL_FPoint {0.0f, 0.0f}
      }
    };

    // On les affiches.
    const int indices[] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometry(renderer, nullptr, vertices, 4, indices, 6);
  }
}
