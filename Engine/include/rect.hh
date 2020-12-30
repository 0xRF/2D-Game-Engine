#pragma once

#include "vector.hh"
#include <cstdint>

struct Rect {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
    Rect(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h)
        : x(_x), y(_y), w(_w), h(_h)
    {
    }

    Rect(Vector2 pos, uint32_t _w, uint32_t _h)
        : x(pos.x), y(pos.y), w(_w), h(_h)
    {
    }
    Rect() : x(0), y(0), w(0), h(0)
    {
    }
};
