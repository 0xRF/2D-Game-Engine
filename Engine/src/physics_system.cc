#include "../include/systems/physics_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/position.hh"
#include "../include/components/rigidbody.hh"
#include "../include/scene.hh"

namespace engine::systems {

void PhysicsSystem::update(float dt, Scene &scene) {
  auto view = scene.get_entity_list().view<RigidBody>();
  view.each([&](RigidBody &rigid) { rigid.velocity.y += gravity * dt; });
}

void PhysicsSystem::update_end(float dt, Scene &scene) {}
void PhysicsSystem::on_render(Scene &scene) {}
void PhysicsSystem::scene_end(Scene &scene) {}
void PhysicsSystem::scene_load(Scene &scene) {}
void PhysicsSystem::shutdown(Scene &scene) {}
} // namespace engine::systems
