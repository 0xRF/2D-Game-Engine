#include "../include/scene.hh"
#include "../include/entity.hh"

namespace engine {
Entity Scene::create_entity() { return std::move(Entity(this)); }

entt::registry &Scene::get_entity_list() { return m_registry; }

} // namespace engine
