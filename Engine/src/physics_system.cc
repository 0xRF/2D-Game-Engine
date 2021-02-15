#include "../internal/physics_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"

namespace engine::internal {

PhysicsSystem *PhysicsSystem::m_instance = nullptr;

PhysicsSystem *PhysicsSystem::create(Engine *engine) {
  m_instance = new PhysicsSystem;
  return m_instance;
}

void PhysicsSystem::update(float dt, entt::registry &registry) {
  auto view = registry.view<RigidBody>();
  view.each([&](RigidBody &rigid) { rigid.velocity.y += gravity * dt; });
}
void PhysicsSystem::update_end(float dt, entt::registry &registry) {}
void PhysicsSystem::scene_end(entt::registry &registry) {}
void PhysicsSystem::scene_load(entt::registry &registry) {}
void PhysicsSystem::shutdown(entt::registry &registry) {}
void PhysicsSystem::render_begin(entt::registry &registry) {}
void PhysicsSystem::on_render(entt::registry &registry) {}
} // namespace engine::internal
