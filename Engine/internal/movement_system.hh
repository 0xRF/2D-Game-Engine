#pragma once

#include "../include/system.hh"


namespace engine {

namespace internal {

class MovementSystem : public System {

public:
    static MovementSystem *create(Engine *engine);


private:
    static MovementSystem *m_instance;
    static Engine* m_engine;

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
