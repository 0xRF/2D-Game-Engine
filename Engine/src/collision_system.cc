#include "../internal/collision_system.hh"
#include "../include/components/box_collider.hh"
#include "../include/components/rigidbody.hh"
#include "../include/components/transform.hh"

namespace engine::internal {

CollisionSystem *CollisionSystem::create(Engine *engine)
{
    m_instance = new CollisionSystem;
    return m_instance;
}

void CollisionSystem::update(float dt, entt::registry &registry)
{
    auto view = registry.view<Transform, BoxCollider, RigidBody>();
    /*
        std::for_each(std::execution::par_unseq, view.begin(), view.end(),
                      [&view](auto entity) {
                          // ...
                      });
                      */
    view.each(
        [&](const Transform transform, BoxCollider collider, RigidBody rigid) {
            // Collision for rigid to rigid objects
            auto view2 = registry.view<Transform, BoxCollider, RigidBody>();
        });
}
void CollisionSystem::update_end(entt::registry &registry)
{
}
void CollisionSystem::scene_end(entt::registry &registry)
{
}
void CollisionSystem::scene_load(entt::registry &registry)
{
}
void CollisionSystem::shutdown(entt::registry &registry)
{
}
void CollisionSystem::render_begin(entt::registry &registry)
{
}
void CollisionSystem::on_render()
{
}
} // namespace engine::internal
