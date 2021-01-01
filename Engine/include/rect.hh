#pragma once

#include "vector.hh"
#include <cstdint>

struct Rect {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    Rect(int32_t _x, int32_t _y, int32_t _w, int32_t _h)
        : x(_x), y(_y), w(_w), h(_h)
    {
    }

    Rect(Vector2 pos, int32_t _w, int32_t _h) : x(pos.x), y(pos.y), w(_w), h(_h)
    {
    }
    Rect() : x(0), y(0), w(0), h(0)
    {
    }
};
