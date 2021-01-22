
#pragma once

#include "../include/system.hh"

struct BoxCollider;
struct Engine;
typedef Vector2 Position;
struct PolygonCollider;
struct RigidBody;
struct Rotatable;

namespace engine {

namespace internal {

class CollisionSystem : public System {

public:
    static CollisionSystem *create(Engine *engine);

    static bool Collides(Rect rect1, Rect rect2);
    static bool Collides(Position t1, PolygonCollider p1, Rotatable rot1,
                         Position t2, PolygonCollider p2, Rotatable rot2);

private:
    static CollisionSystem *m_instance;

    void update(float dt, entt::registry &registry);
    void update_end(entt::registry &registry);
    void scene_end(entt::registry &registry);
    void scene_load(entt::registry &registry);
    void shutdown(entt::registry &registry);
    void render_begin(entt::registry &registry);
    void on_render();
};

} // namespace internal
} // namespace engine
