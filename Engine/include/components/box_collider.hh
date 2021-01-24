#pragma once

#include <cstdint>

#include "../log.hh"
#include "polygon_collider.hh"
#define R(x) (float)x

struct BoxCollider : public PolygonCollider {
  BoxCollider(int32_t w, int32_t h) {
    this->points = {{-R(w) / 2, -R(h) / 2},
                    {R(w) / 2, -R(h) / 2},
                    {R(w) / 2, R(h) / 2},
                    {-R(w) / 2, R(h) / 2}};
  }
};

#undef R
