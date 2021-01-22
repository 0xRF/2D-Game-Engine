#pragma once

#include <cstdint>

#include "polygon_collider.hh"

struct BoxCollider : public PolygonCollider{
    BoxCollider(int32_t w, int32_t h)
    {
        this->points = {
            {-w/2, -h/2},
            {w/2, -h/2},
            {-w/2, -h/2},
            {w/2, h/2}
        };

    }
};
