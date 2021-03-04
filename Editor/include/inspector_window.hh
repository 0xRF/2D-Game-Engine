#pragma once

#include <system.hh>

class InspectorWindow : public engine::System {
private:
    void update(float dt, const Scene& scene) override;
    void update_end(float dt, const Scene& scene) override;
    void on_render(const Scene& scene) override;
    void scene_end(const Scene& scene) override;
    void scene_load(const Scene& scene) override;
    void shutdown(const Scene& scene) override;
  void InspectEntity(entt::registry &registry);
};
