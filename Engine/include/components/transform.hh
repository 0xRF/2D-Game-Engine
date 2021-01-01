#include "../vector.hh"

struct Transform {
    Vector2 positon;
    float rotation;
    Transform() : positon(0, 0), rotation(0.0f)
    {
    }
};
