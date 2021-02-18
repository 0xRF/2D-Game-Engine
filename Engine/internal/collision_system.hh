
#pragma once

#include "../include/components/component.hh"
#include "../include/system.hh"
#include <memory>

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

  static std::unique_ptr<std::vector<Vector2>>
  Collides(Position t1, PolygonCollider p1, Rotatable rot1, Scale scale1,
           Position t2, PolygonCollider p2, Rotatable rot2, Scale scale2);

private:
  static CollisionSystem *m_instance;
  static Engine *m_engine;

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
