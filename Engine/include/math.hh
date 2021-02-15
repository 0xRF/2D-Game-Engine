#include "common.hh"
#include "vector.hh"
#include <math.h>

// TODO FIX
static Vector2 RotateVector2D(Vector2 point, float angle) {
  return {point.x * cosf(angle * DEG2RAD), point.y * sinf(angle * DEG2RAD)};
}

static inline float DotProduct(Vector2 v1, Vector2 v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

static inline Vector2 Normalize(const Vector2 &v) {
  float s = 1 / sqrt(v.x * v.x + v.y * v.y);
  return {v.x * s, v.y * s};
}

static inline std::vector<Vector2> RebaseVectors(std::vector<Vector2> vecs,
                                                 Vector2 base) {
  std::vector<Vector2> ret(vecs.size());
  for (int i = 0; i < vecs.size(); i++)
    ret[i] = vecs[i] + base;
  return ret;
}

static inline std::vector<Vector2> ScaleVectors(std::vector<Vector2> vecs,
                                                float scale) {
  std::vector<Vector2> ret(vecs.size());
  for (int i = 0; i < vecs.size(); i++)
    ret[i] = {vecs[i].x * scale, vecs[i].y * scale};
  return ret;
}
