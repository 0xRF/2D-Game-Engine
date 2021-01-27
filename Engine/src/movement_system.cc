#include "../internal/movement_system.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include <imgui.h>

namespace engine::internal {

MovementSystem *MovementSystem::m_instance = nullptr;
Engine *MovementSystem::m_engine = nullptr;

MovementSystem *MovementSystem::create(Engine *engine) {
  m_instance = new MovementSystem;
  m_instance->m_engine = engine;
  return m_instance;
}

void MovementSystem::update(float dt, entt::registry &registry) {
  auto entities = registry.view<Position, RigidBody>();

  for (auto mv = entities.begin(); mv != entities.end(); mv++) {

    Vector2 &pos = registry.get<Position>(*mv);
    RigidBody &rigid = registry.get<RigidBody>(*mv);

    pos.x += rigid.velocity.x * dt;
    pos.y += rigid.velocity.y * dt;
  }
}
void MovementSystem::update_end(entt::registry &registry) {}
void MovementSystem::scene_end(entt::registry &registry) {}
void MovementSystem::scene_load(entt::registry &registry) {}
void MovementSystem::shutdown(entt::registry &registry) {}
void MovementSystem::render_begin(entt::registry &registry) {}
void MovementSystem::on_render(entt::registry &registry) {

  auto entities = registry.view<Position>();
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
