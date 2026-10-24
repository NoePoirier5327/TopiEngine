#include "vector2f.hpp"
#include <iostream>

namespace topi::type::vector {
  Vector2f::Vector2f(float x, float y) {
    this->x = x;
    this->y = y;
  }

  Vector2f::Vector2f(const Vector2f &v) {
    this->x = v.x;
    this->y = v.y;
  }

  Vector2f::Vector2f(Vector2f &&v) noexcept {
    this->x = v.x;
    this->y = v.y;

    v.x = 0;
    v.y = 0;
  }

  bool Vector2f::operator==(const Vector2f &v) const {
    return this->x == v.x && this->y == v.y;
  }

  Vector2f Vector2f::operator+(const Vector2f &v) const {
    return Vector2f(this->x + v.x, this->y + v.y);
  }

  Vector2f& Vector2f::operator=(const Vector2f &v) {
    if (this == &v) {
      return *this;
    }

    this->x = v.x;
    this->y = v.y;

    return *this;
  }

  Vector2f& Vector2f::operator=(Vector2f &&v) noexcept {
    if (this == &v) {
      return *this;
    }

    this->x = v.x;
    this->y = v.y;

    v.x = 0;
    v.y = 0;

    return *this;
  }

  void Vector2f::debug_disp() const {
    std::cout << "( x: " << this->x << ", y: " << this->y << " )" << std::endl;
  }

  Vector2f operator*(Vector2f v, int a) {
    return Vector2f(v.x * static_cast<float>(a), v.y * static_cast<int>(a));
  }

  Vector2f operator*(int a, Vector2f v) {
    return v * a;
  }

  Vector2f operator*(Vector2f v, float a) {
    return Vector2f(v.x * a, v.y * a);
  }

  Vector2f operator*(float a, Vector2f v) {
    return v * a;
  }

  Vector2f operator*(Vector2f v, double a) {
    return Vector2f(static_cast<float>(static_cast<double>(v.x) * a), static_cast<float>(static_cast<double>(v.y) * a));
  }

  Vector2f operator*(double a, Vector2f v) {
    return v * a;
  }
}

