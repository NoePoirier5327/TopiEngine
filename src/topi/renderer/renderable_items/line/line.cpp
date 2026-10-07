#include "line.hpp"
#include <cmath>

namespace topi::render::items {
  Line::Line(int x1, int y1, int x2, int y2, size_t thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->_color = SDL_Color {r, g, b, a};
    this->_x1 = x1;
    this->_y1 = y1;
    this->_x2 = x2;
    this->_y2 = y2;
    this->_thickness = thickness;
  }

  void Line::display(SDL_Renderer *renderer) const {
    // On calcul le vecteur de norme thickness normal à la ligne courante.
    float dx = static_cast<float>(this->_x2) - static_cast<float>(this->_x1);
    float dy = static_cast<float>(this->_y2) - static_cast<float>(this->_y1);
    float length = sqrt(dx*dx + dy*dy);

    if (length == 0) return;

    float half_thickness = static_cast<float>(this->_thickness) * 0.5f;
    float ox = -(dy / length) * half_thickness;
    float oy = (dx / length) * half_thickness;

    // On calcul les coordonnées de vertices définissant l'affichage de la ligne.
    SDL_Vertex vertices[4] = {
      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x1) + ox, static_cast<float>(this->_y1) + oy},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x1) - ox, static_cast<float>(this->_y1) - oy},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x2) - ox, static_cast<float>(this->_y2) - oy},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      },

      SDL_Vertex {
        SDL_FPoint {static_cast<float>(this->_x2) + ox, static_cast<float>(this->_y2) + oy},
        this->_color,
        SDL_FPoint {0.0f, 0.0f}
      }
    };

    // On les affiches.
    const int indices[] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometry(renderer, nullptr, vertices, 4, indices, 6);
  }
}
