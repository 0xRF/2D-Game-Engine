#pragma once

#include "../include/system.hh"

struct SDL_Renderer;

namespace engine {
class Engine;
class TextureManager;
namespace internal {

class GraphicsSystem : public System {

public:
    static GraphicsSystem *create(Engine *engine);

private:
    GraphicsSystem();
    SDL_Renderer* m_renderer;
    static GraphicsSystem* m_instance;
    friend Engine;
    friend TextureManager;

    void render(entt::registry &registry);
    void update(float dt, entt::registry &registry);
    void update_end(entt::registry &registry);
    void scene_end(entt::registry &registry);
    void scene_load(entt::registry &registry);
    void shutdown(entt::registry &registry);
};

} // namespace internal
} // namespace engine
