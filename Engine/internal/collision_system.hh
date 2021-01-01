
#pragma once

#include "../include/system.hh"

namespace engine::internal {

class CollisionSystem : public System {

public:
    static CollisionSystem *create(Engine *engine);

private:
    CollisionSystem();
    static CollisionSystem *m_instance;

    void update(float dt, entt::registry &registry);
    void update_end(entt::registry &registry);
    void scene_end(entt::registry &registry);
    void scene_load(entt::registry &registry);
    void shutdown(entt::registry &registry);
    void render_begin(entt::registry &registry);
    void on_render();
};

} // namespace engine::internal

