#include "../include/systems/movement_system.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/engine.hh"
#include "../include/log.hh"
#include "../include/scene.hh"
#include "../include/entity.hh"
#include <imgui.h>

namespace engine::systems {

void MovementSystem::update(float dt, Scene& scene) {}
void MovementSystem::update_end(float dt, Scene& scene) {

  auto entities = scene.get_entity_list().view<Position, RigidBody>();

  for (auto mv = entities.begin(); mv != entities.end(); mv++) {

    Vector2 &pos = scene.get_entity_list().get<Position>(*mv);
    RigidBody &rigid = scene.get_entity_list().get<RigidBody>(*mv);

    pos.x += rigid.velocity.x * dt;
    pos.y += rigid.velocity.y * dt;
  }
}
void MovementSystem::scene_end(Scene& scene) {}
void MovementSystem::scene_load(Scene& scene) {}
void MovementSystem::shutdown(Scene& scene) {}
void MovementSystem::render_begin(Scene& scene) {}
void MovementSystem::on_render(Scene& scene) {

  auto entities = scene.get_entity_list().view<Position>();
     // scene view<Position>();
  int i = 0;
  for (auto mv = entities.begin(); mv != entities.end(); mv++) {
    Vector2 &pos = scene.get_entity_list().get<Position>(*mv);
    ImGui::Begin("Pos");
    ImGui::Text("%d %f", i, pos.y);
    ImGui::End();
    i++;
  }
}
} // namespace engine::internal
