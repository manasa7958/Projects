// Copyright 2025 Manasa Praveen
#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>
#include <cmath>

namespace NB {

struct Vector2D {
  double x, y;

  Vector2D() : x(0), y(0) {}
  Vector2D(double x, double y) : x(x), y(y) {}

  Vector2D operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  Vector2D operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  Vector2D operator/(double scalar) const {
    return Vector2D(x / scalar, y / scalar);
  }

  double magnitude() const {
    return std::sqrt(x * x + y * y);
  }

  void normalize() {
    double mag = magnitude();
    if (mag > 0) {
      x /= mag;
      y /= mag;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec) {
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
  }
};

}  // namespace NB

#endif
