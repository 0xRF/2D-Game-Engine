#pragma once

#include "../include/system.hh"

struct SDL_Renderer;
struct SDL_Event;

namespace engine {
class Engine;
class TextureManager;
namespace internal {

class GraphicsSystem : public System {


public:
    static bool Initialize();
    static std::optional<GraphicsSystem> Create();
    GraphicsSystem(const  GraphicsSystem&) = delete;

private:
    void WindowResized(SDL_Event e);
    GraphicsSystem();

    friend Engine;
    friend TextureManager;

    void update(float dt, entt::registry &registry);
    void update_end(float dt, entt::registry &registry);
    void scene_end(entt::registry &registry);
    void scene_load(entt::registry &registry);
    void shutdown(entt::registry &registry);
    void render_begin(entt::registry &registry);
    void on_render(entt::registry &registry);
    void render_end();


    static GraphicsSystem* m_instance;
    SDL_Renderer* m_renderer;
};

} // namespace internal
} // namespace engine

