#pragma once
#include <cstdint>
#include <math.h>

struct Vector2 {

  float x;
  float y;

  Vector2() : x(0.0f), y(0.0f) {}
  Vector2(float x, float y) : x(x), y(y) {}
  //  Vector2(int32_t x, int32_t y) : x(x), y(y) {}

  Vector2 operator*(const float &rhs) const { return {x * rhs, y * rhs}; }
  Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

  Vector2 &operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vector2 &operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector2 &operator*=(const float &other) {
    x *= other;
    y *= other;
    return *this;
  }

  Vector2 operator+(const Vector2 &other) { return {x + other.x, y + other.y}; }
  Vector2 operator-(const Vector2 &other) { return {x - other.x, y - other.y}; }

  Vector2 perpendicular() { return {-y, x}; }
  Vector2 twopoints(Vector2 v) { return v - *this; }
  float magnitude() { return sqrtf(x * x + y * y); }
  float dot(Vector2 v) { return this->x * v.x + this->y * v.y; }

  static const Vector2 Zero;
};

#define PI 3.14159265
#define DEG2RAD PI / 180
