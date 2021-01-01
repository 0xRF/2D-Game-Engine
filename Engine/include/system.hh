#pragma once

#include "common.hh"


namespace engine {
class Engine;

class System {
protected:
    virtual void update(float dt, entt::registry &registry) = 0;
    virtual void update_end(entt::registry &registry) = 0;
    virtual void on_render() = 0;
    virtual void scene_end(entt::registry &registry) = 0;
    virtual void scene_load(entt::registry &registry) = 0;
    virtual void shutdown(entt::registry &registry) = 0;
    friend Engine;
};
} // namespace engine

