#include "vector2i.hpp"
#include <iostream>

namespace topi::type::vector {
  Vector2i::Vector2i(int x, int y) {
    this->x = x;
    this->y = y;
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

  bool Vector2i::operator!=(const Vector2i &v) const {
    return !(*this == v);
  }

  Vector2i Vector2i::operator+(const Vector2i &v) const {
    return Vector2i(this->x + v.x, this->y + v.y);
  }

  Vector2i Vector2i::operator-(const Vector2i &v) const {
    return *this + (-1 * v);
  }

  void Vector2i::operator+=(const Vector2i &v) {
    this->x += v.x;
    this->y += v.y;
  }

  void Vector2i::operator-=(const Vector2i &v) {
    this->x -= v.x;
    this->y -= v.y;
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

  Vector2i operator*(Vector2i v, int a) {
    return Vector2i(v.x * a, v.y * a);
  }

  Vector2i operator*(int a, Vector2i v) {
    return v * a;
  }

  Vector2i operator*(Vector2i v, float a) {
    return Vector2i(static_cast<int>(static_cast<float>(v.x) * a), static_cast<int>(static_cast<float>(v.y) * a));
  }

  Vector2i operator*(float a, Vector2i v) {
    return v * a;
  }

  Vector2i operator*(Vector2i v, double a) {
    return Vector2i(static_cast<int>(static_cast<double>(v.x) * a), static_cast<int>(static_cast<double>(v.y) * a));
  }

  Vector2i operator*(double a, Vector2i v) {
    return v * a;
  }
}
