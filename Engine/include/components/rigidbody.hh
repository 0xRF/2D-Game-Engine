#pragma once

#include "../vector.hh"

struct RigidBody
{
    float mass;
    float inertia;
    Vector2 velocity;
    float friction;
    float elasticity; // Between 0 and 1
};
