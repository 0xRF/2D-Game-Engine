#pragma once

#include "common.hh"


namespace engine {
class Engine;

class System {
protected:
    virtual void update(float dt, const Scene& scene) = 0;
    virtual void update_end(float dt, const Scene& scene) = 0;
    virtual void on_render(const Scene& scene) = 0;
    virtual void scene_end(const Scene& scene) = 0;
    virtual void scene_load(const Scene& scene) = 0;
    virtual void shutdown(const Scene& scene) = 0;
    friend Engine;
};
} // namespace engine

