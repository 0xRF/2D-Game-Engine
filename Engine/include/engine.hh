#pragma once

#include "common.hh"

union SDL_Event;

namespace engine {

class Window;
struct Frame;
class TextureManager;
namespace internal {
class GraphicsSystem;
}
class System;

typedef std::function<void(const SDL_Event)> eventfn;
typedef std::function<void(entt::registry& registry, float dt)> updatefn;
typedef std::function<void()> renderfn;
typedef std::function<void(entt::registry&)> startfn;

class Engine {
public:
    static Engine *initialize();

    Window *get_window() const;

    void run();

    void stop();

    void register_system(System *sys);

    void subscribe_to_start(startfn func);
    void subscibe_to_event(uint32_t type, eventfn func);
    void subscribe_to_update(updatefn func);
    void subscribe_to_post_update(updatefn func);
    void subscribe_to_render(renderfn func);

private:
    Window *m_window;
    TextureManager *m_texture_manager;
    internal::GraphicsSystem *m_graphics;
    std::vector<System *> m_systems{};
    
    bool m_alive = false;
    std::vector<std::pair<uint32_t, eventfn>> m_event_queue{};
    std::vector<updatefn> m_update_queue{};
    std::vector<updatefn> m_post_update_queue{};
    std::vector<renderfn> m_render_queue{};
    std::vector<startfn> m_start_queue{};
    entt::registry registry;

    friend TextureManager;

    Engine();
    ~Engine();
};
} // namespace engine
