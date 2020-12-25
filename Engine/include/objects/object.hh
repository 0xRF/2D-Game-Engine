#pragma once

#include "../vector.hh"

class Object {
public:
    Vector2 position;
    Vector2 rotation;

private:
    void render();
};