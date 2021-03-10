#pragma once
#include <entt/entt.hpp>

namespace engine {
class Entity;
class Scene {
public:
  Entity create_entity();
  entt::registry &get_entity_list();

private:
  entt::registry m_registry;
  friend class Entity;
};

} // namespace engine
