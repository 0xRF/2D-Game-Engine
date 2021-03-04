
#pragma once

#include "../components/component.hh"
#include "../system.hh"
#include <memory>

struct BoxCollider;
typedef Vector2 Position;
struct PolygonCollider;
struct RigidBody;
struct Rotatable;

namespace engine {
struct Engine;

namespace systems {

class CollisionSystem : public System {

public:
  std::unique_ptr<std::vector<Vector2>>
  Collides(Position t1, PolygonCollider p1, Rotatable rot1, Scale scale1,
           Position t2, PolygonCollider p2, Rotatable rot2, Scale scale2);

private:
  static CollisionSystem *m_instance;
  static Engine *m_engine;
  void update(float dt, const Scene &scene) override;
  void update_end(float dt, const Scene &scene) override;
  void on_render(const Scene &scene) override;
  void scene_end(const Scene &scene) override;
  void scene_load(const Scene &scene) override;
  void shutdown(const Scene &scene) override;

  CollisionSystem();
  friend Engine;
};

} // namespace systems
} // namespace engine
