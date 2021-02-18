
#pragma once

#include "../include/system.hh"

namespace engine {
namespace internal {

class PhysicsSystem : public System {

public:
    static PhysicsSystem *create(Engine *engine);
    float gravity = 0;//9.8f;

private:
    static PhysicsSystem *m_instance;

    void update(float dt, entt::registry &registry);
    void update_end(float dt, entt::registry &registry);
    void scene_end(entt::registry &registry);
    void scene_load(entt::registry &registry);
    void shutdown(entt::registry &registry);
    void render_begin(entt::registry &registry);
    void on_render(entt::registry &registry);
};

} // namespace internal
} // namespace engine

