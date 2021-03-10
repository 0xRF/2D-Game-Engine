#pragma once

#include <system.hh>

namespace engine {
class InspectorWindow : public System {
private:
  void update(float dt, Scene &scene) override;
  void update_end(float dt, Scene &scene) override;
  void on_render(Scene &scene) override;
  void scene_end(Scene &scene) override;
  void scene_load(Scene &scene) override;
  void shutdown(Scene &scene) override;
  void InspectEntity(entt::registry &registry);
};
} // namespace engine
