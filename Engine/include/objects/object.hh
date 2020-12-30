#pragma once

#include "../vector.hh"

class Object {
public:

    Object() : position(0,0), rotation(0,0), m_alive(false) {}
    Vector2 position;
    Vector2 rotation;
    
    const bool active();

private:
    bool m_alive;
};
