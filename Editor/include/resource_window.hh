#pragma once

#include <system.hh>

class ResourceWindow : public engine::System {
private:
  void update(float dt, entt::registry &registry) override;
  void update_end(float dt, entt::registry &registry) override;
  void on_render(entt::registry &registry) override;
  void scene_end(entt::registry &registry) override;
  void scene_load(entt::registry &registry) override;
  void shutdown(entt::registry &registry) override;
    

};
