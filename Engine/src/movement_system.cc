#include "../include/systems/movement_system.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/scene.hh"
#include "../include/entity.hh"
#include <imgui.h>

namespace engine::systems {

MovementSystem *MovementSystem::m_instance = nullptr;
Engine *MovementSystem::m_engine = nullptr;

void MovementSystem::update(float dt, entt::registry &registry) {}
void MovementSystem::update_end(float dt, entt::registry &registry) {

  auto entities = registry.view<Position, RigidBody>();

  for (auto mv = entities.begin(); mv != entities.end(); mv++) {

    Vector2 &pos = registry.get<Position>(*mv);
    RigidBody &rigid = registry.get<RigidBody>(*mv);

    pos.x += rigid.velocity.x * dt;
    pos.y += rigid.velocity.y * dt;
  }
}
void MovementSystem::scene_end(const Scene& scene) {}
void MovementSystem::scene_load(const Scene& scene) {}
void MovementSystem::shutdown(const Scene& scene) {}
void MovementSystem::render_begin(const Scene& scene) {}
void MovementSystem::on_render(const Scene& scene) {

  auto entities = scene.get_entity_list().view<Position>();
     // scene view<Position>();
  int i = 0;
  for (auto mv = entities.begin(); mv != entities.end(); mv++) {
    Vector2 &pos = registry.get<Position>(*mv);
    ImGui::Begin("Pos");
    ImGui::Text("%d %f", i, pos.y);
    ImGui::End();
    i++;
  }
}
} // namespace engine::internal
