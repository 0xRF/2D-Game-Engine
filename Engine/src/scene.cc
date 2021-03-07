#include "../include/scene.hh"
#include "../include/entity.hh"

namespace engine {
Entity Scene::create_entity() { return std::move(Entity(this)); }
} // namespace engine
