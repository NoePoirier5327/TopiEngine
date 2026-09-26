#include "vector.hpp"
#include <iostream>

namespace topi::tools::vector {
  Vector2i::Vector2i(int _x, int _y) {
    this->x = _x;
    this->y = _y;
  }

  Vector2i::Vector2i(const Vector2i &v) {
    this->x = v.x;
    this->y = v.y;
  }

  Vector2i::Vector2i(Vector2i &&v) noexcept {
    this->x = v.x;
    this->y = v.y;

    v.x = 0;
    v.y = 0;
  }

  bool Vector2i::operator==(const Vector2i &v) const {
    return this->x == v.x && this->y == v.y;
  }

  Vector2i Vector2i::operator*(int a) const {
    return Vector2i(this->x * a, this->y * a);
  }

  Vector2i Vector2i::operator+(const Vector2i &v) const {
    return Vector2i(this->x + v.x, this->y + v.y);
  }

  Vector2i& Vector2i::operator=(const Vector2i &v) {
    if (this == &v) {
      return *this;
    }

    this->x = v.x;
    this->y = v.y;

    return *this;
  }

  Vector2i& Vector2i::operator=(Vector2i &&v) noexcept {
    if (this == &v) {
      return *this;
    }

    this->x = v.x;
    this->y = v.y;

    v.x = 0;
    v.y = 0;

    return *this;
  }

  void Vector2i::debug_disp() const {
    std::cout << "( x: " << this->x << ", y: " << this->y << " )" << std::endl;
  }
}
