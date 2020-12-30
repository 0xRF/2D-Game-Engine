#include "../include/engine.hh"
#include "../include/frame.hh"
#include "../include/input.hh"
#include "../include/log.hh"
#include "../include/system.hh"
#include "../include/texture.hh"
#include "../include/texture_manager.hh"
#include "../include/window.hh"
#include "../internal/graphics_system.hh"
#include <SDL.h>

namespace engine {

Engine *Engine::initialize()
{

    Engine *instance = new Engine;

    if (SDL_Init(0) != 0) {
        log("Failed to init sdl");
        delete instance;
        return nullptr;
    }

    if (!Window::initialize()) {
        log("Failed to init Window");
        delete instance;
        return nullptr;
    }

    instance->m_window = Window::create("Test", 1280, 720);

    if (!Input::initialize(instance)) {
        log("Failed to init input");
        delete instance;
        return nullptr;
    }

    instance->m_graphics = internal::GraphicsSystem::create(instance);
    if (!instance->m_graphics) {
        logl("Failed to init texture_manager");
        delete instance;
        return nullptr;
    }

    instance->m_texture_manager = TextureManager::create(instance);
    if (!instance->m_texture_manager) {
        logl("Failed to init texture_manager");
        delete instance;
        return nullptr;
    }

    return instance;
}

Window *Engine::get_window() const
{
    return m_window;
}

void Engine::run()
{
    m_alive = true;
    Frame frame = Frame();

    for (auto sys : m_systems)
        sys->scene_load(registry);

    while (m_alive) {

        SDL_Event event;
        while (SDL_PollEvent(&event))
            for (auto fn : m_event_queue)
                if (event.type == fn.first) fn.second(event);

        Uint32 t1 = SDL_GetTicks();

        for (auto fn : m_update_queue)
            fn(frame.deltaTime);

        for (auto sys : m_systems)
            sys->update(frame.deltaTime, registry);

        for (auto fn : m_post_update_queue)
            fn(frame.deltaTime);

        for (auto sys : m_systems)
            sys->update_end(registry);

        m_graphics->render(registry);

        Uint32 t2 = SDL_GetTicks();

        frame.deltaTime = (float)(t2 - t1) / 1000;
    }
}

void Engine::stop()
{
    if (!m_alive) log("Already shutting down");
    m_alive = false;
}

void Engine::subscibe_to_event(uint32_t type, eventfn func)
{
    m_event_queue.emplace_back(type, func);
}
void Engine::subscribe_to_update(updatefn func)
{
    m_update_queue.emplace_back(func);
}

void Engine::subscribe_to_post_update(updatefn func)
{
    m_post_update_queue.emplace_back(func);
}

void Engine::register_system(System *sys)
{
    m_systems.push_back(sys);
}

Engine::Engine()
{
}
Engine::~Engine()
{
    delete m_window;
}

}; // namespace engine
