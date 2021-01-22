#pragma once

#include "../common.hh"

struct PolygonCollider {
    std::vector<Vector2> points;
    bool convex;
    uint32_t layer;
};
