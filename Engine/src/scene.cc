#pragma once
#include <entt/entt.hpp>

namespace engine {
    class Entity;
class Scene {
public:

private:

    entt::registry m_registry;
    friend class Entity;

};

} // namespace engine
