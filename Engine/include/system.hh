#pragma once

#include "common.hh"


namespace engine {
class Engine;

class System {
protected:
    virtual void update(float dt, Scene& scene) = 0;
    virtual void update_end(float dt, Scene& scene) = 0;
    virtual void on_render(Scene& scene) = 0;
    virtual void scene_end(Scene& scene) = 0;
    virtual void scene_load(Scene& scene) = 0;
    virtual void shutdown(Scene& scene) = 0;
    friend Engine;
};
} // namespace engine

