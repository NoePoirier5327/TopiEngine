#include "vector2d.hpp"
#include <iostream>

namespace topi::type::vector {
  Vector2d::Vector2d(double x, double y) {
    this->x = x;
    this->y = y;
  }

  Vector2d::Vector2d(const Vector2d &v) {
    this->x = v.x;
    this->y = v.y;
  }

  Vector2d::Vector2d(Vector2d &&v) noexcept {
    this->x = v.x;
    this->y = v.y;

    v.x = 0.0;
    v.y = 0.0;
  }

  bool Vector2d::operator==(const Vector2d &v) const {
    return this->x == v.x && this->y == v.y;
  }

  bool Vector2d::operator!=(const Vector2d &v) const {
    return !(*this == v);
  }

  Vector2d Vector2d::operator+(const Vector2d &v) const {
    return Vector2d(this->x + v.x, this->y + v.y);
  }

  Vector2d Vector2d::operator-(const Vector2d &v) const {
    return *this + (-1.0 * v);
  }

  void Vector2d::operator+=(const Vector2d &v) {
    this->x += v.x;
    this->y += v.y;
  }

  void Vector2d::operator-=(const Vector2d &v) {
    this->x -= v.x;
    this->y -= v.y;
  }

  void Vector2d::operator*=(int a) {
    this->x *= static_cast<double>(a);
    this->y *= static_cast<double>(a);
  }

  void Vector2d::operator*=(float a) {
    this->x *= static_cast<double>(a);
    this->y *= static_cast<double>(a);
  }

  void Vector2d::operator*=(double a) {
    this->x *= a;
    this->y *= a;
  }

  Vector2d& Vector2d::operator=(const Vector2d &v) {
    if (this == &v) {
      return *this;
    }

    this->x = v.x;
    this->y = v.y;

    return *this;
  }

  Vector2d& Vector2d::operator=(Vector2d &&v) noexcept {
    if (this == &v) {
      return *this;
    }

    this->x = v.x;
    this->y = v.y;

    v.x = 0.0;
    v.y = 0.0;

    return *this;
  }

  void Vector2d::debug_disp() const {
    std::cout << "( x: " << this->x << ", y: " << this->y << " )" << std::endl;
  }

  Vector2d operator*(Vector2d v, int a) {
    return Vector2d(v.x * static_cast<double>(a), v.y * static_cast<double>(a));
  }

  Vector2d operator*(int a, Vector2d v) {
    return v * a;
  }

  Vector2d operator*(Vector2d v, float a) {
    return Vector2d(v.x * static_cast<double>(a), v.y * static_cast<double>(a));
  }

  Vector2d operator*(float a, Vector2d v) {
    return v * a;
  }

  Vector2d operator*(Vector2d v, double a) {
    return Vector2d(v.x * a, v.y * a);
  }

  Vector2d operator*(double a, Vector2d v) {
    return v * a;
  }
}

