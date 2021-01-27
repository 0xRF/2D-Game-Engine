#pragma once
#include <cstdint>

struct Vector2 {

  float x;
  float y;

  Vector2() : x(0.0f), y(0.0f) {}
  Vector2(float x, float y) : x(x), y(y) {}
  Vector2(int32_t x, int32_t y) : x(x), y(y) {}

  Vector2 operator*(const float &scalar) { return {x * scalar, y * scalar}; }

  Vector2 &operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2 operator+(const Vector2 &other) { return {x + other.x, y + other.y}; }
  Vector2 operator-(const Vector2 &other) { return {x - other.x, y - other.y}; }

  Vector2 perpendicular() { return {-y, x}; }
  Vector2 twopoints(Vector2 v) { return v - *this; }
  float dot(Vector2 v) { return this->x * v.x + this->y * v.y; }

  static const Vector2 Zero;
};
