#include "../internal/physics_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/rigidbody.hh"
#include "../include/components/transform.hh"

namespace engine::internal {

PhysicsSystem *PhysicsSystem::create(Engine *engine)
{
    m_instance = new PhysicsSystem;
    return m_instance;
}

void PhysicsSystem::update(float dt, entt::registry &registry)
{
    auto view = registry.view<Transform, BoxCollider>();
    view.each([&](Transform transform, RigidBody rigid) {
            transform.positon.y += gravity*dt;
    });
}
void PhysicsSystem::update_end(entt::registry &registry)
{
}
void PhysicsSystem::scene_end(entt::registry &registry)
{
}
void PhysicsSystem::scene_load(entt::registry &registry)
{
}
void PhysicsSystem::shutdown(entt::registry &registry)
{
}
void PhysicsSystem::render_begin(entt::registry &registry)
{
}
void PhysicsSystem::on_render()
{
}

} // namespace engine::internal
