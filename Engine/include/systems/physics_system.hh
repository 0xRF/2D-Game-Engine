
#pragma once

#include "../system.hh"

namespace engine {
namespace systems {

class PhysicsSystem : public System {

public:
  float gravity = 0; // 9.8f;

private:
  void update(float dt, Scene &) override;
  void update_end(float dt, Scene &) override;
  void on_render(Scene &) override;
  void scene_end(Scene &) override;
  void scene_load(Scene &) override;
  void shutdown(Scene &) override;
};

} // namespace systems
} // namespace engine
