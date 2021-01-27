#include "common.hh"
#include <math.h>

static inline Vector2 RotateVector2D(Vector2 point, float angle) {
  return {point.x * cosf(angle), point.y * sinf(angle)};
}

static inline float DotProduct(Vector2 v1, Vector2 v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

static inline Vector2 Normalize(const Vector2 &v) {
  float s = 1 / sqrt(v.x * v.x + v.y * v.y);
  return {v.x * s, v.y * s};
}
