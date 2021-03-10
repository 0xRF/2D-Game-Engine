
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
  void update(float dt, Scene &scene) override;
  void update_end(float dt, Scene &scene) override;
  void on_render(Scene &scene) override;
  void scene_end(Scene &scene) override;
  void scene_load(Scene &scene) override;
  void shutdown(Scene &scene) override;

  CollisionSystem();
  friend Engine;
};

} // namespace systems
} // namespace engine
